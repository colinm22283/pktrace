#include <thread>
#include <iostream>

#include <script.h>
#include <global.h>
#include <engine.h>
#include <input.h>

#include <render/render.h>
#include <render/font.h>

#include <tracer.h>
#include <world.h>
#include <camera.h>

#include <object/sphere.h>

#define PREVIEW_INTERVAL 100

void Script::start()
{
    Global::fpsLimit = 100000;
//    Global::fpsOutput = true;

    Engine::resizeWindow(800, 800);

    World::objectCount = 3;
    World::objects = new Object*[]
    {
            (Object*)new Sphere(3, VECTOR3(0, 0, 0)),
            (Object*)new Sphere(2, VECTOR3(0, 5, 0)),
            (Object*)new Sphere(2, VECTOR3(0, 5, 0))
    };
    World::lightCount = 1;
    World::lights = new Light[]
    {
        Light(400, VECTOR3(5, 20, 5))
    };

    Camera::position = VECTOR3(0, 0, -10);
    Camera::rotation = VECTOR3(0, 0, 0);

    Tracer::init();
}

void Script::update()
{
    Tracer::draw();

    if (!Tracer::ready) Tracer::drawProgress();
    else
    {
        Tracer::draw();

        Camera::rotation.y += 0.5f;

        Camera::position.x = sin(-Camera::rotation.y) * 10;
        Camera::position.z = -cos(-Camera::rotation.y) * 10;

        new std::thread(Tracer::update);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(PREVIEW_INTERVAL));
}

void Script::exit()
{

}