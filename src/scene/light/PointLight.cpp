# include "PointLight.hpp"

using namespace Scene;

Light::Point::Point(std::vector<double> p, Color c)
  : Light(c), position (p), c1 (0.0), c2 (0.0), c3 (0.0)
{
  for (int i = 0; i < 4; i++)
    position /= position[3];
}

Light::Point::~Point(void)
{
}

const std::vector<const double> Light::Point::getDimmer(void)
{
  return ({c1, c2, c3});
}

const std::vector<double> Light::Point::getPosition(void)
{
  return position;
}

void Light::Point::setDimmer(double c1, double c2, double c3)
{
  this.c1 = c1;
  this.c2 = c2;
  this.c3 = c3;
}

void Light::Point::getBrightness(Ray *r, std::vector<double> p,
				 std::vector<double> n, Objet* o,
				 std::vector<double> l)
{
  std::vector<double> lp;
  std::vector<double> reflexion;
  Color cObj;

  lp.resize(4);
  reflexion.resize(4);

  double dist;
  double ps1, ps2;
  float fd;

  cObj = o->getColor(p);
  for (int i = 0; i < 3; i++)
    lp[i] = position[i] / position[3] - p[i] / p[3];

  normalize(lp);
  ps1 = dot(n, lp);
  for (int i = 0; i < 3; i++)
    reflexion[i] = 2 * ps1 * n[i] - lp[i];
  reflexion[3] = 0;

  normalize(reflexion);
  ps2 = -r->dot(reflexion);
  for (int i = 0; i < 4; i++)
  {
    p[i] = p[i] / p[3];
    position[i] = position[i] / position[3];
  }

  // A verifier
  dist = 0;
  for (int i = 0; i < 3; i++)
    dist += (p[i] - position[i]) * (position[i] - position[i]);

  if ((c1 + c2 * dist + c3 * dist * dist == 0) ||
      (1.0 / (c1 + c2 * dist + c3 * dist * dist) > 1))
    fd = 1;
  else
    fd = 1.0 / (c1 + c2 * dist + c3 * dist * dist);

  if (ps1 > 0.0)
  {
    if (ps2 > 0.0)
    {
      for (int i = 0; i < 3; i++)
	l[i] = fd * color[i] * (o->getRhoD() * cObj[i] * ps1 +
				o->getRhoS() * pow(ps2, o->getShiness()));
    }
    else
    {
      for (int i = 0; i < 3; i++)
	l[i] = fd * color[i] * (o->getRhoD() * cObj[i] * ps1);
    }
  }
  else
  {
    l[0] = 0.0;
    l[1] = 0.0;
    l[2] = 0.0;
  }
}
