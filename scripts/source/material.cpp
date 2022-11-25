#include <material.h>

Material::Material() : Material(0.0, 0.0, 0.0, 0.0, FGS(0))
{ }
Material::Material(TRACER_FLOAT _reflectivity, TRACER_FLOAT _refractionIndex, TRACER_FLOAT _diffuse) : Material(_reflectivity, _refractionIndex, _diffuse, 1.0, FGS(1.0))
{ }
Material::Material(TRACER_FLOAT _reflectivity, TRACER_FLOAT _refractionIndex, TRACER_FLOAT _diffuse, TRACER_FLOAT _opacity) : Material(_reflectivity, _refractionIndex, _diffuse, _opacity, FGS(1.0))
{ }
Material::Material(TRACER_FLOAT _reflectivity, TRACER_FLOAT _refractionIndex, TRACER_FLOAT _diffuse, TRACER_FLOAT _opacity, fcolor _col) : reflectivity(_reflectivity), refractionIndex(_refractionIndex), diffuse(_diffuse), opacity(_opacity), col(_col)
{ }