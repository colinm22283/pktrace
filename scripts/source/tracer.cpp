#include <thread>
#include <iostream>

#include <engine.h>

#include <render/render.h>

#include <misc/clamp.h>

#include <tracer.h>
#include <world.h>
#include <camera.h>

#include <post/post.h>

#include <math/trig.h>
#include <math/random.h>
#include <math/matrix.h>

#include <object/sphere.h>

#if TRACER_PTHREAD_PRIORITIZE_THREADS
    #include <pthread.h>
#endif

struct renderInstruction { int x; int y; };

bool Tracer::ready = true;
bool Tracer::indirectLighting = INDIRECT_LIGHTING;
bool Tracer::transparency = TRANSPARENCY;

unsigned int currentInstruction;
unsigned int totalInstructions;
renderInstruction* instructions;

void tracerThread();
fcolor tracerRecur(ray r, unsigned int currentIteration);
fcolor tracerRecur(ray r, unsigned int currentIteration, Object* mask);
TRACER_FLOAT lightMult(TRACER_FLOAT distance);

unsigned int Tracer::width = TRACER_BUFFER_WIDTH;
unsigned int Tracer::height = TRACER_BUFFER_HEIGHT;

TRACER_FLOAT Tracer::aspectRatio = (TRACER_FLOAT)TRACER_BUFFER_WIDTH / (TRACER_FLOAT)TRACER_BUFFER_HEIGHT;
TRACER_FLOAT Tracer::exposure = TRACER_EXPOSURE;
TRACER_FLOAT Tracer::dynamicRange = DYNAMIC_RANGE;

fcolor** Tracer::pixelBuf;

double startTime = 0.0;

void Tracer::init()
{
#if TRACER_THREADS
    std::cout << "Running with " << TRACER_THREADS << " concurrent threads.\n";
#else
    std::cout << "Running with " << std::thread::hardware_concurrency() << " concurrent threads.\n";
#endif

    // init the pixel buffer
    instructions = new renderInstruction[Tracer::width * Tracer::height];
    Tracer::pixelBuf = new fcolor*[Tracer::width];
    for (unsigned int x = 0; x < Tracer::width; x++)
    {
        Tracer::pixelBuf[x] = new fcolor[Tracer::height];

        for (unsigned int y = 0; y < Tracer::height; y++)
        {
            uint8_t r = (TRACER_FLOAT)rand() / RAND_MAX * COLOR_RANDOMIZATION - (COLOR_RANDOMIZATION / 2);
            Tracer::pixelBuf[x][y] = FRGB255(
                (uint8_t)(DEFAULT_COLOR.r + r),
                (uint8_t)(DEFAULT_COLOR.g + r),
                (uint8_t)(DEFAULT_COLOR.b + r)
            );
        }
    }

    // prepare instructions
    for (int i = 0, x = 0; x < Tracer::width; x++)
    {
        for (int y = 0; y < Tracer::height; y++)
        {
            instructions[i] = { x, y };
            i++;
        }
    }

    totalInstructions = Tracer::width * Tracer::height;

    // shuffle render positions
    for (int current, top = totalInstructions; top > 0; top--)
    {
        current = (int)((TRACER_FLOAT)rand() / RAND_MAX * top + 1);
        renderInstruction temp = instructions[current];
        instructions[current] = instructions[top];
        instructions[top] = temp;
    }
}

void Tracer::draw()
{
    for (unsigned int x = 0; x < Tracer::width; x++)
    {
        for (unsigned int y = 0; y < Tracer::height; y++)
        {
            Render::drawPixel(x, Tracer::height - y - 1, fcolorToColor(Tracer::pixelBuf[x][y]));
        }
    }
}

void Tracer::update()
{
    startTime = Engine::currentTime;

    for (unsigned int x = 0; x < Tracer::width; x++)
    {
        for (unsigned int y = 0; y < Tracer::height; y++)
        {
            uint8_t r = (TRACER_FLOAT)rand() / RAND_MAX * COLOR_RANDOMIZATION - (COLOR_RANDOMIZATION / 2);
            Tracer::pixelBuf[x][y] = FRGB255(
                (uint8_t)(DEFAULT_COLOR.r + r),
                (uint8_t)(DEFAULT_COLOR.g + r),
                (uint8_t)(DEFAULT_COLOR.b + r)
            );
        }
    }

    ready = false;
    currentInstruction = 0;

#if not TRACER_THREADS
    unsigned int tracerThreads = std::thread::hardware_concurrency();
#endif

#if TRACER_THREADS
    std::thread* threads[TRACER_THREADS];
    for (unsigned int i = 0; i < TRACER_THREADS; i++)
    {
        threads[i] = new std::thread(tracerThread);

#if TRACER_PTHREAD_PRIORITIZE_THREADS

        sched_param* params = new sched_param { .sched_priority = 100 };

        pthread_setschedparam(threads[i]->native_handle(), SCHED_FIFO, params);

#endif
    }
#else
    std::thread* threads[tracerThreads];
    for (unsigned int i = 0; i < tracerThreads; i++)
    {
        threads[i] = new std::thread(tracerThread);

#if TRACER_PTHREAD_PRIORITIZE_THREADS

        sched_param* params = new sched_param { .sched_priority = 100 };

        pthread_setschedparam(threads[i]->native_handle(), SCHED_FIFO, params);

#endif
    }
#endif

    while (currentInstruction < totalInstructions) std::this_thread::sleep_for(std::chrono::milliseconds(100));

#if TRACER_THREADS
    for (unsigned int i = 0; i < TRACER_THREADS; i++) threads[i]->join();
#else
    for (unsigned int i = 0; i < tracerThreads; i++) threads[i]->join();
#endif

    float timeTaken = (Engine::currentTime - startTime) / 1000.0;
    std::cout << "Tracer time elapsed: " << std::to_string(timeTaken) << " seconds\n";

    for (unsigned int i = 0; i < Post::effectCount; i++) Post::effects[i]->activate(Tracer::pixelBuf, Tracer::width, Tracer::height);

    ready = true;

    timeTaken = (Engine::currentTime - startTime) / 1000.0;
    std::cout << "Total time elapsed: " << std::to_string(timeTaken) << " seconds\n";
}

void Tracer::drawProgress()
{
    Render::fillRect(0, Global::windowHeight - 10, (TRACER_FLOAT)currentInstruction / totalInstructions * Global::windowWidth, 10, RGB(0, 255, 0));
}

void tracerThread()
{
    while (currentInstruction < totalInstructions)
    {
        unsigned int temp = currentInstruction++;
        renderInstruction inst = instructions[temp];

        TRACER_FLOAT pitch = Camera::rotation.x + (((TRACER_FLOAT)inst.y / Tracer::height - 0.5f) * FOV);
        TRACER_FLOAT yaw = Camera::rotation.y + (((TRACER_FLOAT)inst.x / Tracer::width - 0.5f) * FOV * Tracer::aspectRatio);

        ray r = { Camera::position, VECTOR3(
            SIN(yaw) * COS(pitch),
            SIN(pitch),
            COS(yaw) * COS(pitch)
        ) };

        Tracer::pixelBuf[inst.x][inst.y] = tracerRecur(r, 1) * FGS(Tracer::exposure) - FGS(Tracer::dynamicRange);
    }
}

#define USING_NEW_TRACER_FUNCTION 1
#if USING_NEW_TRACER_FUNCTION

fcolor tracerRecur(ray r, unsigned int currentIteration)
{
    if (currentIteration > REFLECTION_RECURSION_LIMIT) return FGS(0);

    collisionResult res = World::raycast(r);

    if (!res.hit) return SKYBOX_COLOR;

    // CALCULATE DIRECT LIGHTING
    fcolor directLighting = FGS(0.0);

#if DIRECT_LIGHTING
    for (int i = 0; i < World::lightCount; i++)
    {
        // calc light vectors
        vector3 lightDisplacement = World::lights[i].position - res.position;
        TRACER_FLOAT lightMagnitude = magnitude(lightDisplacement);
        vector3 lightNormalized = lightDisplacement / lightMagnitude;

        // cast a ray towards the light
        collisionResult lightRes = World::raycast((ray){
                res.position + (lightNormalized * NEAR_CLIPPING_DISTANCE),
                lightNormalized
        });

        // check if ray reached the light
        if (!lightRes.hit || lightRes.distance > lightMagnitude)
        {
            directLighting +=
                    World::lights[i].col * //                  light color
                    World::lights[i].intensity * //            light intensity
                    lightMult(lightMagnitude); //      light distance
        }
    }
#endif

    fcolor indirectLighting = FGS(0.0);
    if (Tracer::indirectLighting)
    {
        for (unsigned int i = 0; i < INDIRECT_LIGHTING_RECURSIONS; i++) // TODO: reduce INDIRECT_LIGHTING_RECURSIONS based on roughness
        {
            // generate random angles
            TRACER_FLOAT range = (1.0 - res.reflectivity);
//            TRACER_FLOAT range = M_PIf64 / 2;
            TRACER_FLOAT theta0 = range * ASIN(randomRange(-1, 1));
            TRACER_FLOAT theta1 = range * ASIN(randomRange(-1, 1));

            vector3 normalNormalized = normalize(res.result);

            vector2 angles = VECTOR2(
                    ATAN2(sqrtf64(powf64(normalNormalized.x, 2.0) + powf64(normalNormalized.z, 2.0)), normalNormalized.y) + theta0,
                    ATAN2(normalNormalized.z, normalNormalized.x) + theta1
            );

            vector3 rayDir = VECTOR3(
                    SIN(angles.x) * COS(angles.y),
                    COS(angles.x),
                    SIN(angles.x) * SIN(angles.y)
            );

            // TODO: finish this

            indirectLighting +=
                    tracerRecur(
                            (ray){
                                    res.position + (normalNormalized * NEAR_CLIPPING_DISTANCE),
                                    rayDir
                            },
                            currentIteration + 1
                    ); //              raycast value
        }

        indirectLighting = indirectLighting / INDIRECT_LIGHTING_RECURSIONS; // TODO: implement /=
    }

    fcolor transparencyLighting = FGS(0.0);
    if (Tracer::transparency)
    {
        if (res.transparency > 0)
        {
            transparencyLighting += tracerRecur(
                (ray){
                        res.position + (res.result * -NEAR_CLIPPING_DISTANCE),
                        res.result * -1
                },
                currentIteration + 1
            );
        }
    }

    directLighting *= (1.0 - res.transparency);
    indirectLighting *= (1.0 - res.transparency);

    fcolor sum = directLighting;
    if (Tracer::indirectLighting) sum += indirectLighting;
    if (Tracer::transparency) sum += transparencyLighting;
    return sum / (
#if DIRECT_LIGHTING
            (1.0 - res.transparency) +
#endif
            (Tracer::indirectLighting ? (1.0 - res.transparency) : 0.0) +
            (Tracer::transparency ? 1 : 0.0)
    ) * res.col;
}
fcolor tracerRecur(ray r, unsigned int currentIteration, Object* mask)
{
    if (currentIteration > REFLECTION_RECURSION_LIMIT) return FGS(0);

    collisionResult res = World::raycast(r, mask);

    if (!res.hit) return SKYBOX_COLOR;

    // CALCULATE DIRECT LIGHTING
    fcolor directLighting = FGS(0.0);
    for (int i = 0; i < World::lightCount; i++)
    {
        // calc light vectors
        vector3 lightDisplacement = World::lights[i].position - res.position;
        TRACER_FLOAT lightMagnitude = magnitude(lightDisplacement);
        vector3 lightNormalized = lightDisplacement / lightMagnitude;

        // cast a ray towards the light
        collisionResult lightRes = World::raycast((ray){
            res.position + (lightNormalized * NEAR_CLIPPING_DISTANCE),
            lightNormalized
        });

        // check if ray reached the light
        if (!lightRes.hit || lightRes.distance > lightMagnitude)
        {
            directLighting +=
                World::lights[i].col * //                  light color
                World::lights[i].intensity * //            light intensity
                lightMult(lightMagnitude); //      light distance
        }
    }

    fcolor indirectLighting = FGS(0.0);
    if (Tracer::indirectLighting)
    {
        for (unsigned int i = 0; i < INDIRECT_LIGHTING_RECURSIONS; i++) // TODO: reduce INDIRECT_LIGHTING_RECURSIONS based on roughness
        {
            // generate random angles
            TRACER_FLOAT range = (1.0 - res.reflectivity);
//            TRACER_FLOAT range = M_PIf64 / 2;
            TRACER_FLOAT theta0 = range * ASIN(randomRange(-1, 1));
            TRACER_FLOAT theta1 = range * ASIN(randomRange(-1, 1));

            vector3 normalNormalized = normalize(res.result);

            vector2 angles = VECTOR2(
                    ATAN2(sqrtf64(powf64(normalNormalized.x, 2.0) + powf64(normalNormalized.z, 2.0)), normalNormalized.y) + theta0,
                    ATAN2(normalNormalized.z, normalNormalized.x) + theta1
            );

            vector3 rayDir = VECTOR3(
                SIN(angles.x) * COS(angles.y),
                COS(angles.x),
                SIN(angles.x) * SIN(angles.y)
            );

            // TODO: finish this

            indirectLighting +=
                tracerRecur(
                    (ray){
                        res.position + (normalNormalized * NEAR_CLIPPING_DISTANCE),
                        rayDir
                    },
                    currentIteration + 1
                ); //              raycast value
        }

        indirectLighting = indirectLighting / INDIRECT_LIGHTING_RECURSIONS; // TODO: implement /=
    }

    fcolor transparencyLighting = FGS(0.0);
    if (Tracer::transparency)
    {
        if (res.transparency > 0)
        {
            transparencyLighting += tracerRecur(
                (ray){
                    res.position + (res.transparencyResult * NEAR_CLIPPING_DISTANCE),
                    res.transparencyResult
                },
                currentIteration + 1
            );
        }
    }

    directLighting *= (1.0 - res.transparency);
    indirectLighting *= (1.0 - res.transparency);
    transparencyLighting *= res.transparency;

#if DIRECT_LIGHTING
    fcolor sum = directLighting;
#else
    fcolor sum = FGS(0.0);
#endif
    if (Tracer::indirectLighting) sum += indirectLighting;
    if (Tracer::transparency) sum += transparencyLighting;
    return sum / (
#if DIRECT_LIGHTING
        1 +
#endif
        (Tracer::indirectLighting ? 1 : 0) +
        (Tracer::transparency ? 1 : 0)
    ) * res.col;
}

#else

fcolor tracerRecur(ray r, unsigned int currentIteration, TRACER_FLOAT currentDistance)
{
    if (currentIteration > REFLECTION_RECURSION_LIMIT) return FGS(0);

    collisionResult res = World::raycast(r);

    if (res.hit)
    {
        fcolor c = FGS(0);

        // DIRECT LIGHTING
        for (unsigned int i = 0; i < World::lightCount; i++)
        {
            vector3 lightVec = World::lights[i].position - res.position;
            TRACER_FLOAT lightVecMagnitude = magnitude(lightVec);
            vector3 lightVecNormalized = lightVec / lightVecMagnitude;

            collisionResult lightRes = World::raycast((ray) {
                res.position + (lightVecNormalized * NEAR_CLIPPING_DISTANCE),
                lightVecNormalized
            });
            if (!lightRes.hit || lightRes.distance > lightVecMagnitude) c +=
                res.col *
                World::lights[i].col *
                World::lights[i].intensityAt(currentDistance + res.distance + lightVecMagnitude) *
                res.diffuse;
        }

        // INDIRECT LIGHTING
        if (Tracer::indirectLighting)
        {
            fcolor indirectColoring = FGS(0.0);

            for (unsigned int j = 0; j < INDIRECT_LIGHTING_RECURSIONS; j++)
            {
                TRACER_FLOAT theta0 = randomRange(-0.4 * M_PIf64, 0.4 * M_PIf64);
                TRACER_FLOAT theta1 = randomRange(-0.4 * M_PIf64, 0.4 * M_PIf64);

                matrix3 mat = matrix3::rotMat(theta0, theta1, 0.0);

                vector3 rayDir = normalize(mat * res.normal);

                indirectColoring += tracerRecur(
                    (ray){
                        res.position + (rayDir * NEAR_CLIPPING_DISTANCE),
                        rayDir
                    },
                    currentIteration + 1,
                    currentDistance
                );
            }

            indirectColoring = indirectColoring / INDIRECT_LIGHTING_RECURSIONS;

            c += res.col * indirectColoring * ((res.diffuse / (INDIRECT_LIGHTING_RECURSIONS + 1) * INDIRECT_LIGHTING_RECURSIONS));
        }

        if (res.transparency == 0) return c + (tracerRecur(
            (ray) {
                res.position + (normalize(res.result) * NEAR_CLIPPING_DISTANCE),
                res.result
            },
            currentIteration + 1, currentDistance + res.distance
        ) * res.reflectivity * res.col);
        else return c + (tracerRecur(
            (ray){
                res.position + (normalize(res.result) * NEAR_CLIPPING_DISTANCE),
                res.result
            },
            currentIteration + 1, currentDistance + res.distance
        ) * res.reflectivity * res.col) + (tracerRecur(
            (ray){
                res.transparencyPos + (normalize(res.transparencyDir) * NEAR_CLIPPING_DISTANCE),
                res.transparencyDir
            },
            currentIteration + 1, currentDistance + res.distance
        ) * res.transparency * res.col);
    }
    else return SKYBOX_COLOR;
}

#endif

TRACER_FLOAT lightMult(TRACER_FLOAT distance)
{
    return 1.0 / (4.0 * M_PIf64 * powf64(distance, 1.0));
}