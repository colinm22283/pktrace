#include <cmath>

#include <misc/minMax.h>

#include <camera.h>

#include <object/sphere.h>

Sphere::Sphere() : radius(0), position(VECTOR3(0, 0, 0))
{ }
Sphere::Sphere(float _radius, vector3 _position, float _reflectivity) : radius(_radius), position(_position), reflectivity(_reflectivity)
{ }

collisionResult Sphere::checkCollision(ray r)
{
    vector3 disp = r.origin - position;

    float a = dotProd(r.direction, r.direction);
    float b = dotProd(r.direction, disp) * 2;
    float c = dotProd(disp, disp) - powf32(radius, 2);

    float disc = powf32(b, 2) - (4 * a * c);

    float t0, t1;

    if (disc < 0.0f) return (collisionResult){ false };
    else if (disc == 0.0f) t0 = t1 = -0.5f * b / a;
    else
    {
        float q = (b > 0) ?
              -0.5 * (b + sqrt(disc)) :
              -0.5 * (b - sqrt(disc));
        t0 = q / a;
        t1 = c / q;
    }

    float t = MIN(t0, t1);

    if (t < 0)
    {
        t = MAX(t0, t1);
        if (t < 0) return (collisionResult){ false };
    }

    vector3 collisionPoint = r.origin + (r.direction * t);

    vector3 normal = normalize(collisionPoint - position);

    return (collisionResult){
        true,
        collisionPoint,
        t,
        normalize(r.direction - (normal * (2 * dotProd(r.direction, normal)))),
        reflectivity
    };
}