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

bool keyDown = false;

Texture* blankTexture;
Texture* steelTexture;
Texture* woodHorizontalTexture;
Texture* floorTexture;

void Script::start()
{
//    Noise1D noise(1000);
//    for (unsigned int i = 0; i < 1000; i++) std::cout << "Noise: " << noise.getValue((double)i) << "\n";

    Global::fpsLimit = 10000000;
    Global::fpsOutput = false;

    Engine::resizeWindow(1200, 900);

    debugPrint("Loading random values");
    randomInit();

    debugPrint("Loading textures");
    blankTexture = new Texture("textures/blank.bmp");
    steelTexture = new Texture("textures/steel2.bmp", 0.9);
    woodHorizontalTexture = new Texture("textures/woodHorizontal.bmp", 400000.0);
    floorTexture = new Texture("textures/tile.bmp", 3.0);

    debugPrint("Generating materials");
    Material* steelMat = new Material(0.9, 0.0, 0.1, 1.0);
    Material* mirrorMat = new Material(0.95, 0.0, 0.05, 1.0);
    Material* woodMat = new Material(0.2, 0.0, 0.7, 1.0);
    Material* tileMat = new Material(0.1, 0.0, 0.9, 1.0);
    Material* glassMat = new Material(0.9, 0.0, 0.2, 0.2);

    debugPrint("Generating object");
    World::objectCount = 7;
    World::objects = new Object*[]
    {
        (Object*)new Sphere( // floor
            1000000,
            VECTOR3(0, -1000020, 0),
            floorTexture,
            tileMat
        ),
        (Object*)new Sphere( // ceiling
            1000000,
            VECTOR3(0, 1000020, 0),
            blankTexture,
            steelMat
        ),
        (Object*)new Sphere( // back wall mirror
            1000000,
            VECTOR3(0, 0, 1000020),
            blankTexture,
            mirrorMat
        ),
        (Object*)new Sphere( // front wall mirror
            1000000,
            VECTOR3(0, 0, -1000020),
            woodHorizontalTexture,
            woodMat
        ),
        (Object*)new Sphere( // left wall
            1000000,
            VECTOR3(-1000020, 0, 0),
            woodHorizontalTexture,
            woodMat
        ),
        (Object*)new Sphere( // right wall
            1000000,
            VECTOR3(1000020, 0, 0),
            woodHorizontalTexture,
            woodMat
        ),
        (Object*)new Sphere(2, VECTOR3(0, 0, 0), steelTexture, steelMat), // center sphere
        (Object*)new Cube(VECTOR3(-5, -5, -5), VECTOR3(-2, -2, -2)), // center cube
//        (Object*)new Sphere(1, VECTOR3(0, 3, 3), steelTexture, steelMat),
        (Object*)new Plane(VECTOR3(0, 0, 20), VECTOR3(0, 0, 1), woodHorizontalTexture, woodMat),
        (Object*)new Sphere(7, VECTOR3(0, 0, 20), blankTexture, mirrorMat)
    };
    debugPrint("Generating lights");
    World::lightCount = 1;
    World::lights = new Light[]
    {
        Light(300.0, VECTOR3(0, 19, 0), FGS(1.0f)),
        Light(200.0, VECTOR3(-19, 19, -19), FGS(1.0f)),
        Light(200.0, VECTOR3(-19, 19,  19), FGS(1.0f)),
        Light(200.0, VECTOR3(19,  19, -19), FGS(1.0f)),
        Light(200.0, VECTOR3(19,  19,  19), FGS(1.0f))
    };

    debugPrint("Translating camera");
    Camera::position = VECTOR3(0, 3, -10);
    Camera::rotation = VECTOR3(RADIANS(-20.0f), RADIANS(40.0f), 0);

    Camera::position.x = sin(-Camera::rotation.y) * 10;
    Camera::position.z = -cos(-Camera::rotation.y) * 10;

    debugPrint("Initializing tracer");
    Tracer::init();
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

        new std::thread(Tracer::update);
//        Tracer::update();
    }
}