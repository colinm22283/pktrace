#include <world.h>

unsigned int World::objectCount;
Object** World::objects;
unsigned int World::lightCount;
Light* World::lights;

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