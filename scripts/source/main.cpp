#include <thread>
#include <iostream>

#include <script.h>
#include <global.h>
#include <engine.h>
#include <debug.h>

#include <tracer.h>
#include <world.h>
#include <camera.h>

#include <object/sphere.h>

bool keyDown = false;

void Script::start()
{
    Global::fpsLimit = 10000000;
    Global::fpsOutput = false;

    Engine::resizeWindow(1600, 900);

    debugPrint("Generating object");
    World::objectCount = 9;
    World::objects = new Object*[]
    {
        (Object*)new Sphere( // floor
            1000000,
            VECTOR3(0, -1000020, 0),
            FGS(1.0),
            0.02, 0.8
        ),
        (Object*)new Sphere( // ceiling
            1000000,
            VECTOR3(0, 1000020, 0),
            FGS(1.0),
            0.02, 0.8
        ),
        (Object*)new Sphere( // back wall
            1000000,
            VECTOR3(0, 0, 1000020),
            FGS(1.0),
            1.0, 0.1
        ),
        (Object*)new Sphere( // front wall
            1000000,
            VECTOR3(0, 0, -1000020),
            FGS(1.0),
            1.0, 0.1
        ),
        (Object*)new Sphere( // left wall
            1000000,
            VECTOR3(-1000020, 0, 0),
            FGS(1.0),
            0.02, 0.8
        ),
        (Object*)new Sphere( // right wall
            1000000,
            VECTOR3(1000020, 0, 0),
            FGS(1.0),
            0.02f,
            0.8
        ),
        (Object*)new Sphere(2, VECTOR3(0, 0, 0), FGS(1.0f), 0.7, 0.5), // center sphere
        (Object*)new Sphere(1, VECTOR3(0, 6, 3), FRGB255(0, 255, 0), 0.2f, 0.7),
        (Object*)new Sphere(7, VECTOR3(0, 20, 0), FGS(1.0f), 1.0f, 0.1)
    };
    debugPrint("Generating lights");
    World::lightCount = 4;
    World::lights = new Light[]
    {
        Light(50.0, VECTOR3(-19, 19, -19), FGS(1.0f)),
        Light(50.0, VECTOR3(-19, 19,  19), FGS(1.0f)),
        Light(50.0, VECTOR3(19,  19, -19), FGS(1.0f)),
        Light(50.0, VECTOR3(19,  19,  19), FGS(1.0f))
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
}

void Script::keyUp(SDL_Keysym keysym)
{
    if (Tracer::ready)
    {
        debugPrint("Reloading render");

        Camera::rotation.y += RADIANS(30.0f);

        Camera::position.x = sin(-Camera::rotation.y) * 10;
        Camera::position.z = -cos(-Camera::rotation.y) * 10;

//        new std::thread(Tracer::update);
        Tracer::update();
    }
}