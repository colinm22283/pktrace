#include <material.h>

Material::Material() : Material(0.0, 0.0, 0.0, 0.0, FGS(0))
{ }
Material::Material(TRACER_FLOAT _reflectivity, TRACER_FLOAT _roughness, TRACER_FLOAT _diffuse) : Material(_reflectivity, _roughness, _diffuse, 1.0, FGS(1.0))
{ }
Material::Material(TRACER_FLOAT _reflectivity, TRACER_FLOAT _roughness, TRACER_FLOAT _diffuse, TRACER_FLOAT _opacity) : Material(_reflectivity, _roughness, _diffuse, _opacity, FGS(1.0))
{ }
Material::Material(TRACER_FLOAT _reflectivity, TRACER_FLOAT _roughness, TRACER_FLOAT _diffuse, TRACER_FLOAT _opacity, fcolor _col) : reflectivity(_reflectivity), roughness(_roughness), diffuse(_diffuse), opacity(_opacity), col(_col)
{ }