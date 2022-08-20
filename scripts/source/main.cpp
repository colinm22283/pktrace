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
        (Object*)new Sphere(10000, VECTOR3(0, -10020, 0), FGS(1.0f), 0.02f, 0.8), // floor
        (Object*)new Sphere(10000, VECTOR3(0, 10020, 0), FGS(1.0f), 0.02f, 0.8),   // ceiling
        (Object*)new Sphere(10000, VECTOR3(0, 0, 10020), FGS(1.0f), 1.0f, 0.0),   // back wall
        (Object*)new Sphere(10000, VECTOR3(0, 0, -10020), FGS(1.0f), 1.0f, 0.0),  // front wall
        (Object*)new Sphere(10000, VECTOR3(-10020, 0, 0), FGS(1.0f), 0.02f, 0.8),  // left wall
        (Object*)new Sphere(10000, VECTOR3(10020, 0, 0), FGS(1.0f), 0.02f, 0.8),    // right wall
        (Object*)new Sphere(2, VECTOR3(0, 0, 0), FGS(1.0f), 0.7f, 0.5),        // center sphere
        (Object*)new Sphere(1, VECTOR3(0, 6, 3), FRGB255(0, 255, 0), 0.2f, 0.7)
    };
    World::lightCount = 4;
    World::lights = new Light[]
    {
        Light(5.0f, VECTOR3(-19, 19, -19), FGS(1.0f)),
        Light(5.0f, VECTOR3(-19, 19,  19), FGS(1.0f)),
        Light(5.0f, VECTOR3(19,  19, -19), FGS(1.0f)),
        Light(5.0f, VECTOR3(19,  19,  19), FGS(1.0f)),

        Light(1000, VECTOR3(18, 18, -18), FRGB(1.0f, 0.0f, 0.0f)),
        Light(1000, VECTOR3(-18, 18, -18), FRGB(0.0f, 1.0f, 0.0f)),
        Light(1000, VECTOR3(18, 18, 18), FRGB(0.0f, 0.0f, 1.0f)),
        Light(1000, VECTOR3(-18, 18, 18), FRGB(1.0f, 1.0f, 1.0f))
    };

    Camera::position = VECTOR3(0, 3, -10);
    Camera::rotation = VECTOR3(RADIANS(-20.0f), RADIANS(40.0f), 0);

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
        Camera::rotation.y += RADIANS(30.0f);

        Camera::position.x = sin(-Camera::rotation.y) * 10;
        Camera::position.z = -cos(-Camera::rotation.y) * 10;

//        new std::thread(Tracer::update);
        Tracer::update();
    }
}