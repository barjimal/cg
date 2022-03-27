#include <iostream>

#include "scene.hpp"

int main ()
{
  using namespace cg;

  Sphere * sphere1 = new Sphere(
    1,
    point3_t(0.0, -1.0, 3.0),
    Color(255, 0, 0),
    500,
    0.2
  );
  Sphere * sphere2 = new Sphere(
    1,
    point3_t(2.0, 0.0, 4.0),
    Color(0, 0, 255),
    500,
    0.3
  );
  Sphere * sphere3 = new Sphere(
    1,
    point3_t(-2.0, 0.0, 4.0),
    Color(0, 255, 0),
    100,
    0.4
  );
  Sphere * sphere4 = new Sphere(
    5000,
    point3_t(0.0, -5001.0, 0.0),
    Color(255, 255, 0),
    1000,
    0.5
  );

  AmbientLight * ambientLight = new AmbientLight(
    0.2
  );
  PointLight * pointLight = new PointLight(
    0.6,
    point3_t(2, 1, 0)
  );
  DirectionalLight * directionalLight = new DirectionalLight(
    0.2,
    point3_t(1, 4, 4)
  );

  Scene scene;
  scene.sceneObjects = {sphere1, sphere2, sphere3, sphere4};
  scene.sceneLights = {ambientLight, pointLight, directionalLight};
  scene.RenderScene();

  return 0;
}
