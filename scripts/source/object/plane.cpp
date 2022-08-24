#include <math/trig.h>

#include <object/plane.h>

Plane::Plane() : position(VECTOR3(0.0, 0.0, 0.0)), normal(VECTOR3(0.0, 0.0, 0.0))
{ }

Plane::Plane(vector3 _position, vector3 _normal, Material* _mat) : position(_position), normal(_normal), mat(_mat)
{ }

collisionResult Plane::checkCollision(ray r)
{
    double denominator = dotProd(r.direction, normal);

    if (denominator < 0.001) return { false };

    double t = dotProd((position - r.direction), normal) / denominator;

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