set (SOURCES
  Background.cpp
  Scene.cpp
  object/Object.cpp
  camera/Camera.cpp
  light/Light.cpp
  light/AmbiantLight.cpp
  light/DirectionalLight.cpp
  light/PointLight.cpp
)

add_library(Engine STATIC ${SOURCES})

target_link_libraries(Engine Tools)