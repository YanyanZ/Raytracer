# include "Cube.hpp"

using namespace Scene;

Cube::Cube(void) : Object()
{
}

Cube::~Cube(void)
{
}

double Cube::hit(Ray* r, std::vector<double> i)
{
  double t;
  double dist;

  std::vector<double> p = {0, 0, 0, 0};
  std::vector<double> temp = {0, 0, 0, 0};
  std::vector<double> pos = {0, 0, 0, 0};
  std::vector<double> dir = {0, 0, 0, 0};
  std::vector<double> pos2 = {0, 0, 0, 0};
  std::vector<double> dir2 = {0, 0, 0, 0};
  std::vector<double> roots = {0, 0, 0, 0};

  pos = r->getOrigin();
  dir = r->getDirection();
  trans->transformationInv(pos2 , pos);
  trans->transformationInv(dir2, dir);

  double a = 0;
  double b = 0;
  double c = 0;
  double d = 0;
  double e = 0;
  int nbRoots = 0;

  for (int j = 0; j < 4; j++)
    pos2[j] /= pos2[3];

  e = 11.8;
  for (int ii = 0; ii < 3; ii++)
  {
    a += pow(dir2[ii], 4);
    b += 4 * pow(dir2[ii], 3) * pos2[ii];
    c += 6 * pow(dir2[ii], 2) * pow(pos2[ii], 2) -
      5 * pow(dir2[ii], 2);
    e += pow(pos2[ii], 4) - 5 * pow(pos2[ii], 2);
  }

  PolynomialSolver spoly(a, b, c, d, e);
  nbRoots = spoly.solveQuartic(roots);

  if (!nbRoots)
    return DBL_MAX;
  else
  {
    t = DBL_MAX;
    for (int ii = 0; ii < nbRoots; ii++)
      if (roots[ii] > epsilon && roots[ii] < t)
	t = roots[ii];

    p[0] = t * dir[0] + pos2[0] / pos2[3];
    p[1] = t * dir[1] + pos2[1] / pos2[3];
    p[2] = t * dir[2] + pos2[2] / pos2[3];
    p[3] = 1.0;

    if (t == DBL_MAX)
      dist = DBL_MAX;
    else
      dist = distance (p, pos);

    trans->transformation(i, p);
  }

  return dist;
}

void Cube::normal(std::vector<double> p, Ray* r, std::vector<double> normal)
{
  std::vector<double> p2;

  trans->transformation (p2, p);

  normal[0] = 4 * pow(p2[0], 3) - 10 * p2[0];
  normal[1] = 4 * pow(p2[1], 3) - 10 * p2[1];
  normal[2] = 4 * pow(p2[2], 3) - 10 * p2[2];

  correctNormal(normal, p2, r);
}
