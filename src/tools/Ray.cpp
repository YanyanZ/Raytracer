# include "Ray.hpp"

using namespace Tools;

Ray::Ray(std::vector<double> o, std::vector<double> d)
  : origin (o), direction (d)
{
}

Ray::Ray()
  : in (false)
{
}

Ray::~Ray()
{
}

void Ray::normalize(std::vector<double>& v)
{
  double d = 0;

  for (int i = 0; i < 3; i++)
    d += v[i] * v[i];

  d = sqrt(d);
  for (int i = 0; i < 3; i++)
    v[i] /= d;
}

void Ray::setDirection(std::vector<double> d)
{
  direction = d;
  normalize(direction);
}

void Ray::setOrigin(std::vector<double> o)
{
  origin = o;
}

void Ray::setIn(bool i)
{
  in = i;
}

std::vector<double> Ray::getDirection(void)
{
  return direction;
}

std::vector<double> Ray::getOrigin(void)
{
  return origin;
}

bool Ray::isIn(void)
{
  return in;
}

void Ray::swapInOut(void)
{
  in = !in;
}

double Ray::dot(std::vector<double> v)
{
  double ps = 0;

  for (int i = 0; i < 3; i++)
    ps += direction[i] * v[i];

  return ps;
}
