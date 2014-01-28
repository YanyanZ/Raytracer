# include "Plan.hpp"

using namespace Scene;

Plan::Plan(void) : Object()
{
  trans = new Transformer();
}

Plan::~Plan(void)
{
}

double Plan::hit (Ray* r, std::vector<double> i)
{
  double d;

  std::vector<double> p = {0, 0, 0, 0};
  std::vector<double> temp = {0, 0, 0, 0};
  std::vector<double> pos = {0, 0, 0, 0};
  std::vector<double> dir = {0, 0, 0, 0};
  std::vector<double> pos2 = {0, 0, 0, 0};
  std::vector<double> dir2 = {0, 0, 0, 0};

  pos = r->getOrigin();
  dir = r->getDirection();

  trans->transformationInv(pos2, pos);
  trans->transformationInv(dir2, dir);

  double t;

  if (dir2[0] != 0)
  {
    t = -pos2[0] / dir2[0];
    if (t > epsilon)
    {
      p[0] = 0.0;
      p[1] = pos2[1] + dir2[1] * t;
      p[2] = pos2[2] + dir2[2] * t;
      p[3] = 1.0;

      d = distance (p, pos2);

      trans->transformation(i, p);

      return d;
    }
    else
      return DBL_MAX;
  }
  else
    return DBL_MAX;
}

void Plan::normal(std::vector<double> p, Ray* r,
		  std::vector<double> normal)
{
  std::vector<double> p2 = {0, 0, 0, 0};

  trans->transformationInv(p2, p);
  normal = {1, 0, 0, 0};

  correctNormal(normal, p2, r);
}
