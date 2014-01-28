set (SOURCES
  Background.cpp
  Scene.cpp
  object/Object.cpp
  object/Box.cpp
  object/Cone.cpp
  object/Cube.cpp
  object/Cylinder.cpp
  object/Parallelogram.cpp
  object/Plan.cpp
  object/Sphere.cpp
  camera/Camera.cpp
  light/Light.cpp
  light/AmbiantLight.cpp
  light/DirectionalLight.cpp
  light/PointLight.cpp
)

add_library(Engine STATIC ${SOURCES})

target_link_libraries(Engine Tools)