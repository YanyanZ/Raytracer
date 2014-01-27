set(SOURCES Checker.cpp
  ParlinNoise.cpp
  TextureMapper.cpp)

add_library(Texture STATIC ${SOURCES})

target_link_libraries(Texture Tools)