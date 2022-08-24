#include <material.h>

Material::Material() : reflectivity(0.0), diffuse(0.0), opacity(0.0)
{ }
Material::Material(double _reflectivity, double _diffuse, double _opacity) : reflectivity(_reflectivity), diffuse(_diffuse), opacity(_opacity)
{ }