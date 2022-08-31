#include <cmath>
#include <iostream>

#include <misc/minMax.h>

#include <math/trig.h>
#include <math/random.h>

#include <camera.h>

#include <object/sphere.h>

Sphere::Sphere() : radius(0), position(VECTOR3(0, 0, 0)), tex(nullptr), material(nullptr), ng(nullptr)
{ }
Sphere::Sphere(TRACER_FLOAT _radius, vector3 _position, Texture* _tex, Material* mat) :
    radius(_radius),
    position(_position),
    tex(_tex),
    material(mat),
    ng(createNoiseGenerator(100000))
{ }

collisionResult Sphere::checkCollision(ray r)
{
    vector3 disp = r.origin - position;

    TRACER_FLOAT a = dotProd(r.direction, r.direction);
    TRACER_FLOAT b = dotProd(r.direction, disp) * 2;
    TRACER_FLOAT c = dotProd(disp, disp) - powf32(radius, 2);

    TRACER_FLOAT disc = powf32(b, 2) - (4 * a * c);

    TRACER_FLOAT t0, t1;

    if (disc < 0.0f) return (collisionResult){ false };
    else if (disc == 0.0f) t0 = t1 = -0.5f * b / a;
    else
    {
        TRACER_FLOAT q = (b > 0) ?
              -0.5 * (b + sqrt(disc)) :
              -0.5 * (b - sqrt(disc));
        t0 = q / a;
        t1 = c / q;
    }

    TRACER_FLOAT t = MIN(t0, t1);
    TRACER_FLOAT t2 = MAX(t0, t1);

    if (t < 0)
    {
        t = MAX(t0, t1);
        if (t < 0) return (collisionResult){ false };
    }

    vector3 collisionPoint = r.origin + (r.direction * t);

    vector3 normal = normalize(collisionPoint - position);

    TRACER_FLOAT pitch = ASIN(-normal.y);
    TRACER_FLOAT yaw = ATAN2(normal.z, normal.x);

    return (collisionResult){
        true,
        collisionPoint,
        t,
        normalize(r.direction - (normal * (2 * dotProd(r.direction, normal)))) + VECTOR3(
            nextNoiseValue(ng),
            nextNoiseValue(ng),
            nextNoiseValue(ng)
        ),
        material->reflectivity * material->opacity,//magnitude(normalize(position - collisionPoint) - r.direction),
        material->diffuse * material->opacity,
        colorToFColor(tex->getPixel((int)(yaw * tex->scale * 100.0), (int)(pitch * tex->scale * 100.0))),
        1.0 - material->opacity,
        r.origin + (r.direction * t2),
        r.direction
    };
}