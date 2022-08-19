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
    Global::fpsLimit = 100;

    Engine::resizeWindow(1400, 800);

    World::objectCount = 7;
    World::objects = new Object*[]
    {
        (Object*)new Sphere(2, VECTOR3(0, 0, 0), 0.9f),        // center sphere
        (Object*)new Sphere(10000, VECTOR3(0, -10020, 0), 0.01f), // floor
        (Object*)new Sphere(10000, VECTOR3(0, 10020, 0), 0.01f),   // ceiling
        (Object*)new Sphere(10000, VECTOR3(0, 0, 10020), 1.0f),   // back wall
        (Object*)new Sphere(10000, VECTOR3(0, 0, -10020), 1.0f),  // front wall
        (Object*)new Sphere(10000, VECTOR3(-10020, 0, 0), 0.01f),  // left wall
        (Object*)new Sphere(10000, VECTOR3(10020, 0, 0), 0.01f),    // right wall
        (Object*)new Sphere(6, VECTOR3(7, 4, 0), 0.5f)
    };
    World::lightCount = 1;
    World::lights = new Light[]
    {
        Light(3000, VECTOR3(0, 18, 0), RGB(255, 255, 255)),
        Light(1000, VECTOR3(0, -4, 0), RGB(255, 0, 0)),
        Light(1000, VECTOR3(18, 18, -18), RGB(255, 0, 0)),
        Light(1000, VECTOR3(-18, 18, -18), RGB(0, 255, 0)),
        Light(1000, VECTOR3(18, 18, 18), RGB(0, 0, 255)),
        Light(1000, VECTOR3(-18, 18, 18), RGB(255, 255, 255))
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

    Camera::position = VECTOR3(0, 3, -6);
    Camera::rotation = VECTOR3(RADIANS(-20.0f), RADIANS(20.0f), 0);

    Camera::position.x = sin(-Camera::rotation.y) * 19;
    Camera::position.z = -cos(-Camera::rotation.y) * 6;

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
        Camera::rotation.y += 0.1f;

        Camera::position.x = sin(-Camera::rotation.y) * 19;
        Camera::position.z = -cos(-Camera::rotation.y) * 6;

        new std::thread(Tracer::update);
//        Tracer::update();
    }
}