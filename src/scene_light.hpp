#ifndef SCENE_LIGTH_HPP
#define SCENE_LIGTH_HPP

#include "common.hpp"

namespace cg
{

struct SceneLight
{
double intensity;
virtual ~SceneLight() {};
};

struct AmbientLight : public SceneLight // ambient light reflection
{
    AmbientLight(double _intensity) {
        intensity = _intensity;
    };
    
    ~AmbientLight() {}
};

struct PointLight : public SceneLight  // light from a source like a bulb
{
    point3_t position;
    PointLight(double _intensity, point3_t _position): position(_position) {
        intensity = _intensity;
    };
    ~PointLight() {}
};

struct DirectionalLight : public SceneLight  // light from the sun
{
    point3_t direction;
    DirectionalLight(double _intensity, point3_t _direction): direction(_direction) {
        intensity = _intensity;
    };
    ~DirectionalLight() {}
};

} // namespace cg

#endif // #ifndef SCENE_LIGTH_HPP