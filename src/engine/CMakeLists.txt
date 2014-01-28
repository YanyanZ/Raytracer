SET(SOURCES Engine.cpp)

add_library(Engine STATIC ${SOURCES})

target_link_libraries(Engine Tools)
target_link_libraries(Scene Tools)
