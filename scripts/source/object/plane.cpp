#include <math/trig.h>

#include <object/plane.h>

#define PLANE_MIN_ANGLE 0.000001

Plane::Plane() : position(VECTOR3(0.0, 0.0, 0.0)), normal(VECTOR3(0.0, 0.0, 0.0))
{ }

Plane::Plane(vector3 _position, vector3 _normal, Material* _mat) : position(_position), normal(_normal), mat(_mat)
{ }

collisionResult Plane::checkCollision(ray r)
{
    double denominator = dotProd(normal, r.direction);

    if (denominator < PLANE_MIN_ANGLE) return { false };

    double t = dotProd((position - r.origin), normal) / denominator;

    if (t >= 0) return {
        true,
        r.origin + (r.direction * t),
        t,
        normalize(r.direction - (normal * (2 * dotProd(r.direction, normal)))),
        mat->reflectivity,
        mat->diffuse,
        FRGB255(255, 50, 50)
    };
    else return { false };
}