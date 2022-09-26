#include <thread>
#include <iostream>

#include <script.h>
#include <global.h>
#include <engine.h>
#include <debug.h>

#include <tracer.h>
#include <world.h>
#include <camera.h>

#include <math/random.h>

#include <object/sphere.h>
#include <object/plane.h>
#include <object/triangle.h>
#include <object/cube.h>

#include <math/noise.h>

#include <post/post.h>
#include <post/bloomEffect.h>
#include <post/pixelLerp.h>
#include <post/adjacentAverage.h>

bool keyDown = false;

std::thread* updateThread;

Texture* blankTexture;
Texture* redTexture;
Texture* greenTexture;
Texture* blueTexture;
Texture* steelTexture;
Texture* woodHorizontalTexture;
Texture* floorTexture;

void Script::start()
{
    Global::fpsLimit = 100000;
    Global::fpsOutput = false;

    Engine::resizeWindow(800, 600);

    debugPrint("Loading random values");
    randomInit();

    debugPrint("Loading textures");
    blankTexture = new Texture("textures/blank.bmp");
    redTexture = new Texture("textures/red.bmp");
    greenTexture = new Texture("textures/green.bmp");
    blueTexture = new Texture("textures/blue.bmp");
    steelTexture = new Texture("textures/steel2.bmp", 0.9);
    woodHorizontalTexture = new Texture("textures/woodHorizontal.bmp", 400000.0);
    floorTexture = new Texture("textures/tile.bmp", 3.0);

    debugPrint("Generating materials");
    Material* steelMat = new Material(0.5, 0.0, 0.5, 1.0);
    Material* mirrorMat = new Material(1.0, 0.0, 0.0, 1.0);
    Material* woodMat = new Material(0.05, 0.0, 0.95, 1.0);
    Material* tileMat = new Material(0.0, 0.0, 0.9, 1.0);
    Material* glassMat = new Material(0.9, 0.0, 0.2, 0.2);
    Material* matteMat = new Material(0.0, 0.0, 1.0, 1.0);

    debugPrint("Generating object");
    World::objectCount = 9;
    World::objects = new Object*[]
    {
        (Object*)new Sphere( // floor
            1000000,
            VECTOR3(0, -1000020, 0),
            blankTexture,
            tileMat
        ),
        (Object*)new Sphere( // ceiling
            1000000,
            VECTOR3(0, 1000020, 0),
            blankTexture,
            tileMat
        ),
        (Object*)new Sphere( // back wall mirror
            1000000,
            VECTOR3(0, 0, 1000020),
            woodHorizontalTexture,
            tileMat
        ),
        (Object*)new Sphere( // front wall mirror
            1000000,
            VECTOR3(0, 0, -1000020),
            woodHorizontalTexture,
            tileMat
        ),
        (Object*)new Sphere( // left wall
            1000000,
            VECTOR3(-1000020, 0, 0),
            woodHorizontalTexture,
            tileMat
        ),
        (Object*)new Sphere( // right wall
            1000000,
            VECTOR3(1000020, 0, 0),
            woodHorizontalTexture,
            tileMat
        ),
        (Object*)new Sphere(2, VECTOR3(0, 0, 0), blankTexture, steelMat), // center sphere
        (Object*)new Plane(VECTOR3(10, 0, 0), VECTOR3(1, 0, 0), blankTexture, mirrorMat)
//        (Object*)new Plane(VECTOR3(10, 0, 0), VECTOR3(1, 0, 0), blankTexture, mirrorMat)
    };
    debugPrint("Generating lights");
    World::lightCount = 40;
//    World::lights = new Light[]
//    {
//        Light(4.0, VECTOR3(-10, 19, -10), FGS(1.0)),
//        Light(2.0, VECTOR3(-19, 19, -19), FGS(1.0)),
//        Light(2.0, VECTOR3(-19, 0,  0), FGS(1.0)),
//        Light(200.0, VECTOR3(19,  19, -19), FGS(1.0)),
//        Light(200.0, VECTOR3(19,  19,  19), FGS(1.0))
//    };
    World::lights = new Light[World::lightCount];
    for (int i = 0; i < World::lightCount; i++)
    {
        TRACER_FLOAT angle = (TRACER_FLOAT)i / World::lightCount * 2 * M_PIf64;

        World::lights[i] = Light(0.075, VECTOR3(cosf64(angle) * 19.0, 19.0, sinf64(angle) * 19.0), FGS(1.0));
    }

    debugPrint("Generating post effects");
    Post::effectCount = 0;
    Post::effects = new PostEffect*[]
    {
        (PostEffect*)new AdjacentAverage(1),
//        (PostEffect*)new AdjacentAverage(),
//        (PostEffect*)new AdjacentAverage(),
//        (PostEffect*)new AdjacentAverage(),
//        (PostEffect*)new AdjacentAverage(),
//        (PostEffect*)new AdjacentAverage(),
//        (PostEffect*)new AdjacentAverage(),
//        (PostEffect*)new AdjacentAverage(),
//        (PostEffect*)new AdjacentAverage(),
//        (PostEffect*)new AdjacentAverage(),

        (PostEffect*)new PixelLerp(10),
        (PostEffect*)new BloomEffect(10.0)
    };

    debugPrint("Translating camera");
    Camera::position = VECTOR3(0, 7, -10);
    Camera::rotation = VECTOR3(RADIANS(-40.0f), RADIANS(70.0f), 0);

    Camera::position.x = sin(-Camera::rotation.y) * 10;
    Camera::position.z = -cos(-Camera::rotation.y) * 10;

    debugPrint("Initializing tracer");
    Tracer::init();
    updateThread = new std::thread(Tracer::update);
}

void Script::update()
{
    Tracer::draw();

    if (!Tracer::ready) Tracer::drawProgress();
}

void Script::exit()
{
    World::cleanup();

    delete blankTexture;
    delete steelTexture;
    delete woodHorizontalTexture;
    delete floorTexture;
}

void Script::keyUp(SDL_Keysym keysym)
{
    if (Tracer::ready)
    {
        debugPrint("Reloading render");

        Camera::rotation.y += RADIANS(30.0f);

        Camera::position.x = sin(-Camera::rotation.y) * 10;
        Camera::position.z = -cos(-Camera::rotation.y) * 10;

        updateThread->join();
        updateThread = new std::thread(Tracer::update);
//        Tracer::update();
    }
}