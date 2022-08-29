#include <thread>
#include <iostream>

#include <render/render.h>

#include <misc/clamp.h>

#include <tracer.h>
#include <world.h>
#include <camera.h>
#include <math/trig.h>

#include <object/sphere.h>

struct renderInstruction { int x; int y; };

bool Tracer::ready = true;
unsigned int currentInstruction;
unsigned int totalInstructions;
renderInstruction* instructions;

void tracerThread();
fcolor tracerRecur(ray r, unsigned int currentIteration, TRACER_FLOAT currentDistance);

unsigned int Tracer::width = TRACER_BUFFER_WIDTH;
unsigned int Tracer::height = TRACER_BUFFER_HEIGHT;

TRACER_FLOAT Tracer::aspectRatio = (TRACER_FLOAT)TRACER_BUFFER_WIDTH / (TRACER_FLOAT)TRACER_BUFFER_HEIGHT;
TRACER_FLOAT Tracer::exposure = TRACER_EXPOSURE;

color** Tracer::pixelBuf;

void Tracer::init()
{
    // init the pixel buffer
    instructions = new renderInstruction[Tracer::width * Tracer::height];
    Tracer::pixelBuf = new color*[Tracer::width];
    for (unsigned int x = 0; x < Tracer::width; x++)
    {
        Tracer::pixelBuf[x] = new color[Tracer::height];

        for (unsigned int y = 0; y < Tracer::height; y++)
        {
            uint8_t r = (TRACER_FLOAT)rand() / RAND_MAX * COLOR_RANDOMIZATION - (COLOR_RANDOMIZATION / 2);
            Tracer::pixelBuf[x][y] = RGB(
                (uint8_t)(DEFAULT_COLOR.r + r),
                (uint8_t) (DEFAULT_COLOR.g + r),
                (uint8_t) (DEFAULT_COLOR.b + r)
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

    new std::thread(Tracer::update);
}

void Tracer::draw()
{
    for (unsigned int x = 0; x < Tracer::width; x++)
    {
        for (unsigned int y = 0; y < Tracer::height; y++)
        {
            Render::drawPixel(x, Tracer::height - y - 1, Tracer::pixelBuf[x][y]);
        }
    }
}

void Tracer::update()
{
    for (unsigned int x = 0; x < Tracer::width; x++)
    {
        Tracer::pixelBuf[x] = new color[Tracer::height];

        for (unsigned int y = 0; y < Tracer::height; y++)
        {
            uint8_t r = (TRACER_FLOAT)rand() / RAND_MAX * COLOR_RANDOMIZATION - (COLOR_RANDOMIZATION / 2);
            Tracer::pixelBuf[x][y] = RGB(
                (uint8_t)(DEFAULT_COLOR.r + r),
                (uint8_t)(DEFAULT_COLOR.g + r),
                (uint8_t)(DEFAULT_COLOR.b + r)
            );
        }
    }

    ready = false;
    currentInstruction = 0;

    std::thread* threads[TRACER_THREADS];
    for (unsigned int i = 0; i < TRACER_THREADS; i++) threads[i] = new std::thread(tracerThread);

    while (currentInstruction < totalInstructions);

    for (unsigned int i = 0; i < TRACER_THREADS; i++) threads[i]->join();

    ready = true;
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

        Tracer::pixelBuf[inst.x][inst.y] = fcolorToColor(tracerRecur(r, 1, 0) * FGS(TRACER_EXPOSURE));

//        for (unsigned int i = 0; i < 100000; i++);
    }
}

fcolor tracerRecur(ray r, unsigned int currentIteration, TRACER_FLOAT currentDistance)
{
    if (currentIteration > REFLECTION_RECURSION_LIMIT) return FGS(0);

    collisionResult res = World::raycast(r);

    if (res.hit)
    {
        fcolor c = FGS(0);

        for (unsigned int i = 0; i < World::lightCount; i++)
        {
            vector3 lightVec = World::lights[i].position - res.position;
            TRACER_FLOAT lightVecMagnitude = magnitude(lightVec);
            vector3 lightVecNormalized = lightVec / lightVecMagnitude;

            collisionResult lightRes = World::raycast({ res.position + (lightVecNormalized * NEAR_CLIPPING_DISTANCE), lightVecNormalized });

            if (!lightRes.hit || lightRes.distance > lightVecMagnitude) c += res.col * (World::lights[i].col * World::lights[i].intensityAt(currentDistance + res.distance + lightVecMagnitude)) * res.diffuse;
        }

        fcolor atmoEffect = FGS(0.0);
        for (TRACER_FLOAT i = 0.0; i < res.distance; i += ATMO_PROBE_SPACING)
        {
            vector3 pos = r.direction * i + r.origin;

            for (unsigned int j = 0; j < World::atmoCount; j++)
            {
                atmoResult aRes = World::atmos[j]->checkPos(pos);

                if (aRes.hit) atmoEffect += aRes.col * ATMO_PROBE_SPACING;
            }
        }

        c += atmoEffect;

        return c + (tracerRecur(
            (ray) {
                res.position + (normalize(res.result) * NEAR_CLIPPING_DISTANCE),
                res.result
            },
            currentIteration + 1, currentDistance + res.distance
        ) * res.reflectivity * res.col);
    }
    else return SKYBOX_COLOR;
}