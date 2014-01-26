#include "Background.hpp"

Scene::Background(void) : color (Color(0, 0, 0))
{
}

Scene::Background(Color c) : color (c)
{
}

Scene::Background(Background b)
{
  color = b;
}

Scene::~Background(void)
{
}

Color& Scene::operator=(Background& b)
{
  return color;
}
