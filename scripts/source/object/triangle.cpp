#include <object/triangle.h>

Triangle::Triangle() : p1(VECTOR3(0.0, 0.0, 0.0)), p2(VECTOR3(0.0, 0.0, 0.0)), p3(VECTOR3(0.0, 0.0, 0.0))
{ }

Triangle::Triangle(vector3 _p1, vector3 _p2, vector3 _p3) : p1(_p1), p2(_p2), p3(_p3)
{ }

collisionResult Triangle::checkCollision(ray r)
{


    return {false };
}