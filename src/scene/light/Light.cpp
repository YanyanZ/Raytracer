# include "Light.hpp"

using namespace Scene;

Light::Light(Color c) : color (c)
{
}

Light::~Light(void)
{
}

void Light::normalize(std::vector<double>& v)
{
  double d = 0;

  for (int i = 0; i < 3; i++)
    d += v[i] * v[i];

  d = sqrt(d);
  for (int i = 0; i < 3; i++)
    v[i] /= d;
}

double Light::dot(std::vector<double> v1, std::vector<double> v2)
{
  double ps = 0;

  for (int i = 0; i < 3; i++)
    ps += v1[i] * v2[i];

  return ps;
}
