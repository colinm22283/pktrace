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

    Engine::resizeWindow(800, 800);

    World::objectCount = 7;
    World::objects = new Object*[]
    {
            (Object*)new Sphere(2, VECTOR3(0, 0, 0)),        // center sphere
            (Object*)new Sphere(10000, VECTOR3(0, -10020, 0)), // floor
            (Object*)new Sphere(10000, VECTOR3(0, 10020, 0)),   // ceiling
            (Object*)new Sphere(10000, VECTOR3(0, 0, 10020)),   // back wall
            (Object*)new Sphere(10000, VECTOR3(0, 0, -10020)),  // front wall
            (Object*)new Sphere(10000, VECTOR3(-10020, 0, 0)),  // left wall
            (Object*)new Sphere(10000, VECTOR3(10020, 0, 0))    // right wall
    };
    World::lightCount = 2;
    World::lights = new Light[]
    {
        Light(1000, VECTOR3(18, 18, 18)),
        Light(1000, VECTOR3(-18, 18, -18))
    };

    Camera::position = VECTOR3(0, 0, -6);
    Camera::rotation = VECTOR3(RADIANS(0.0f), 0, 0);

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

        Camera::position.x = sin(-Camera::rotation.y) * 6;
        Camera::position.z = -cos(-Camera::rotation.y) * 6;

        new std::thread(Tracer::update);
    }
}