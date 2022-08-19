#include <thread>
#include <iostream>

#include <script.h>
#include <global.h>
#include <engine.h>

#include <tracer.h>
#include <world.h>
#include <camera.h>

#include <object/sphere.h>

bool keyDown = false;

void Script::start()
{
    Global::fpsLimit = 10000000;
    Global::fpsOutput = true;

    Engine::resizeWindow(800, 800);

    World::objectCount = 8;
    World::objects = new Object*[]
    {
        (Object*)new Sphere(10000, VECTOR3(0, -10020, 0), FGS(1.0f), 0.01f), // floor
        (Object*)new Sphere(10000, VECTOR3(0, 10020, 0), FGS(1.0f), 0.01f),   // ceiling
        (Object*)new Sphere(10000, VECTOR3(0, 0, 10020), FGS(1.0f), 0.01f),   // back wall
        (Object*)new Sphere(10000, VECTOR3(0, 0, -10020), FGS(1.0f), 0.01f),  // front wall
        (Object*)new Sphere(10000, VECTOR3(-10020, 0, 0), FGS(1.0f), 0.01f),  // left wall
        (Object*)new Sphere(10000, VECTOR3(10020, 0, 0), FGS(1.0f), 0.01f),    // right wall
        (Object*)new Sphere(2, VECTOR3(0, 0, 0), FGS(1.0f), 0.7f),        // center sphere
        (Object*)new Sphere(1, VECTOR3(0, 6, 3), FRGB255(0, 255, 0), 0.2f)
    };
    World::lightCount = 1;
    World::lights = new Light[]
    {
        Light(50.0f, VECTOR3(0, 19, 0), FGS(1.0f)),

        Light(1000, VECTOR3(18, 18, -18), FRGB(1.0f, 0.0f, 0.0f)),
        Light(1000, VECTOR3(-18, 18, -18), FRGB(0.0f, 1.0f, 0.0f)),
        Light(1000, VECTOR3(18, 18, 18), FRGB(0.0f, 0.0f, 1.0f)),
        Light(1000, VECTOR3(-18, 18, 18), FRGB(1.0f, 1.0f, 1.0f))
//        Light(1000, VECTOR3(16, 18, -18)),
//        Light(1000, VECTOR3(15, 18, -18)),
//        Light(1000, VECTOR3(14, 18, -18)),
//        Light(1000, VECTOR3(13, 18, -18)),
//        Light(1000, VECTOR3(12, 18, -18)),
//        Light(1000, VECTOR3(11, 18, -18)),
//        Light(1000, VECTOR3(10, 18, -18)),
//        Light(1000, VECTOR3(9, 18, -18)),
//        Light(1000, VECTOR3(18, 17, -18)),
//        Light(1000, VECTOR3(17, 17, -18)),
//        Light(1000, VECTOR3(16, 17, -18)),
//        Light(1000, VECTOR3(15, 17, -18)),
//        Light(1000, VECTOR3(14, 17, -18)),
//        Light(1000, VECTOR3(13, 17, -18)),
//        Light(1000, VECTOR3(12, 17, -18)),
//        Light(1000, VECTOR3(11, 17, -18)),
//        Light(1000, VECTOR3(10, 17, -18)),
//        Light(1000, VECTOR3(9, 17, -18)),
//        Light(1000, VECTOR3(18, 16, -18)),
//        Light(1000, VECTOR3(17, 16, -18)),
//        Light(1000, VECTOR3(16, 16, -18)),
//        Light(1000, VECTOR3(15, 16, -18)),
//        Light(1000, VECTOR3(14, 16, -18)),
//        Light(1000, VECTOR3(13, 16, -18)),
//        Light(1000, VECTOR3(12, 16, -18)),
//        Light(1000, VECTOR3(11, 16, -18)),
//        Light(1000, VECTOR3(10, 16, -18)),
//        Light(1000, VECTOR3(9, 16, -18))
    };

    Camera::position = VECTOR3(0, 3, -10);
//    Camera::rotation = VECTOR3(RADIANS(-20.0f), 0, 0);
    Camera::rotation = VECTOR3(RADIANS(-20.0f), 0, 0);

    Camera::position.x = sin(-Camera::rotation.y) * 10;
    Camera::position.z = -cos(-Camera::rotation.y) * 10;

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
        Camera::rotation.y += RADIANS(45.0f);

        Camera::position.x = sin(-Camera::rotation.y) * 10;
        Camera::position.z = -cos(-Camera::rotation.y) * 10;

        new std::thread(Tracer::update);
//        Tracer::update();
    }
}