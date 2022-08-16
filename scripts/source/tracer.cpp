#include <thread>

#include <render/render.h>

#include <misc/clamp.h>

#include <tracer.h>
#include <world.h>
#include <camera.h>
#include <math/trig.h>

#include <object/sphere.h>

#define PIXEL_INSTRUCTION_SPACING 5

struct renderInstruction
{
    int x;
    int y;
};

bool Tracer::ready = true;
unsigned int currentInstruction;
unsigned int totalInstructions;
renderInstruction* instructions;

void tracerThread();

unsigned int Tracer::width = TRACER_BUFFER_WIDTH;
unsigned int Tracer::height = TRACER_BUFFER_HEIGHT;

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
            uint8_t r = (float)rand() / RAND_MAX * COLOR_RANDOMIZATION - (COLOR_RANDOMIZATION / 2);
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
            instructions[i] = {
                x,
                y
            };
            i++;
        }
    }

    totalInstructions = Tracer::width * Tracer::height;

    // shuffle render positions
    for (int current, top = totalInstructions; top > 0; top--)
    {
        current = (int)((float)rand() / RAND_MAX * top + 1);
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
            uint8_t r = (float)rand() / RAND_MAX * COLOR_RANDOMIZATION - (COLOR_RANDOMIZATION / 2);
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
    Render::fillRect(0, Global::windowHeight - 10, (float)currentInstruction / totalInstructions * Global::windowWidth, 10, RGB(0, 255, 0));
}

void tracerThread()
{
    while (currentInstruction < totalInstructions)
    {
        unsigned int temp = currentInstruction++;
        renderInstruction inst = instructions[temp];

        float pitch = Camera::rotation.x + (((float)inst.y / Tracer::height - 0.5f) * FOV);
        float yaw = Camera::rotation.y + (((float)inst.x / Tracer::width - 0.5f) * FOV);

        ray r = { Camera::position, VECTOR3(
            SIN(yaw) * COS(pitch),
            SIN(pitch),
            COS(yaw) * COS(pitch)
        ) };

        collisionResult res = World::raycast(r);

        if (res.hit)
        {
            float c = 0;

            for (unsigned int i = 0; i < World::lightCount; i++)
            {
                vector3 lightDir = World::lights[i].position - res.position;
                collisionResult lightRes = World::raycast({ res.position + (lightDir * 0.001f), lightDir });

                if (!lightRes.hit) c += 150 * World::lights[0].intensityAt(res.position);
            }

            Tracer::pixelBuf[inst.x][inst.y] = GS((uint8_t) CLAMP(
                    AMBIENT_LIGHT + c,
                    0, 255
            ));
        }
        else Tracer::pixelBuf[inst.x][inst.y] = SKYBOX_COLOR;

//        for (unsigned int i = 0; i < 100000; i++);
    }
}