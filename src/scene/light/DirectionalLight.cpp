# include "DirectionalLight.hpp"

using namespace Scene;

Directional::Directional(std::vector<double> d, Color c)
  : Light(c)
{
  direction = d;
}

Directional::~Directional(void)
{
}

const std::vector<double> Directional::getDirection(void)
{
  return direction;
}

void Directional::getBrightness(Ray* r, std::vector<double> p,
				std::vector<double> n, Object* o,
				std::vector<double> l)
{
  std::vector<double> reflexion;
  std::vector<double> dir;
  Color cObj;
  double ps1;
  double ps2;
  //double dist;

  reflexion.resize(4);

  o->getColor(p, cObj);
  for (int i = 0; i < 3; i++)
    dir[i] = - direction[i];

  normalize(dir);
  ps1 = dot(n, dir);

  for (int i = 0; i < 3; i++)
    reflexion[i] = 2 * ps1 * n[i] - dir[i];
  reflexion[3] = 0;

  normalize(reflexion);
  ps2 = - r->dot(reflexion);

  if (ps1 > 0.0)
  {
    if (ps2 > 0.0)
    {
      for (int i = 0; i < 3; i++)
	l[i] = color[i] * (o->getRhoD() * cObj[i] * ps1 +
			   o->getRhoS() * pow(ps2, o->getShiness()));
    }
    else
    {
      for (int i = 0; i < 3; i++)
	l[i] = color[i] * (o->getRhoD() * cObj[i] * ps1);
    }
  }
  else
  {
    l[0] = 0.0;
    l[1] = 0.0;
    l[2] = 0.0;
  }
}
