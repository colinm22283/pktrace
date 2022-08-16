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

    World::objectCount = 3;
    World::objects = new Object*[]
    {
            (Object*)new Sphere(3, VECTOR3(0, 0, 0)),
            (Object*)new Sphere(2, VECTOR3(1, 6, 0)),
            (Object*)new Sphere(1, VECTOR3(3, 10, 0))
    };
    World::lightCount = 1;
    World::lights = new Light[]
    {
        Light(200, VECTOR3(5, 20, 5)),
        Light(200, VECTOR3(-5, -10, -5))
    };

    Camera::position = VECTOR3(0, 11, -10);
    Camera::rotation = VECTOR3(RADIANS(-70), 0, 0);

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
        Camera::rotation.y += 0.5f;

        Camera::position.x = sin(-Camera::rotation.y) * 10;
        Camera::position.z = -cos(-Camera::rotation.y) * 10;

        new std::thread(Tracer::update);
    }
}