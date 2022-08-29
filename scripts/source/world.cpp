#include <world.h>

unsigned int World::objectCount = 0;
Object** World::objects = nullptr;
unsigned int World::lightCount = 0;
Light* World::lights = nullptr;
unsigned int World::atmoCount = 0;
Atmo** World::atmos = nullptr;

void World::cleanup()
{
    for (unsigned int i = 0; i < World::objectCount; i++) delete World::objects[i];
    delete[] World::objects;

    delete[] World::lights;
}

collisionResult World::raycast(ray r)
{
    collisionResult res = World::objects[0]->checkCollision(r);

    for (unsigned int i = 1; i < World::objectCount; i++)
    {
        collisionResult tempRes = World::objects[i]->checkCollision(r);
        if (tempRes.hit)
        {
            if (!res.hit || tempRes.distance < res.distance) res = tempRes;
        }
    }

    return res;
}