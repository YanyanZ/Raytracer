# include "Box.hpp"

using namespace Scene;

Box::Box(double s)
  : side (s)
{
  double l = side / 2.0;
  std::vector<double> p1 = {l, l, -l, 1};
  std::vector<double> p2 = {l, l, l, 1};
  std::vector<double> p3 = {l, -l, l, 1};
  std::vector<double> p4 = {l, -l, -l, 1};
  std::vector<double> p5 = {-l, -l, -l, 1};
  std::vector<double> p6 = {-l, l, -l, 1};
  std::vector<double> p7 = {-l, l, l, 1};
  std::vector<double> p8 = {-l, -l, l, 1};

  Transformer *trans = new Transformer();

  sides.resize(6);
  sides[0] = new Parallelogram(p1, p2, p4);
  sides[1] = new Parallelogram(p6, p7, p5);
  sides[2] = new Parallelogram(p1, p2, p6);
  sides[3] = new Parallelogram(p2, p7, p3);
  sides[4] = new Parallelogram(p3, p8, p4);
  sides[5] = new Parallelogram(p4, p5, p1);

  for (int i = 0; i < 6; i++)
    sides[i]->setTransformer(trans);
}

Box::~Box(void)
{
}

double Box::hit(Ray* r, std::vector<double> i)
{
  double d, d2;

  std::vector<double> i2 = {0, 0, 0, 0};
  std::vector<double> temp = {0, 0, 0, 0};
  std::vector<double> pos = {0, 0, 0, 0};
  std::vector<double> dir = {0, 0, 0, 0};
  std::vector<double> pos2 = {0, 0, 0, 0};
  std::vector<double> dir2 = {0, 0, 0, 0};

  pos = r->getOrigin();
  dir = r->getDirection();

  trans->transformationInv(pos2, pos);
  trans->transformationInv(dir2, dir);

  Ray* r2 = new Ray(pos2, dir2);
  d = sides[0]->hit(r2, temp);
  if (d < DBL_MAX)
    hitSide = 0;
  else
    hitSide = -1;

  for (int j = 1; j < 6; j++)
  {
    d2 = sides[j]->hit(r2, i2);
    if (d2 < d)
    {
      d = d2;
      temp = i2;
      hitSides = j;
    }
  }

  trans->transformation(i, temps);

  return d;

}

void Box::normal(std::vector<double> p, Ray* r,
		 std::vector<double> normal)
{
  std::vector<double> pt = {0, 0, 0, 0};

  trans->transformation(pt, p);
  for (int j = 0; j < 4; j++)
    normal[j] = 0.0;

  switch (hitSide)
  {
    case 0:
      normal[0] = 1;
      break;
    case 1:
      normal[0] = -1;
      break;
    case 2:
      normal[1] = 1;
      break;
    case 3:
      normal[2] = 1;
      break;
    case 4:
      normal[1] = -1;
      break;
    case 5:
      normal[2] = -1;
      break;
    default:
      break;
  }

  correctNormal(normal, pt, r);
}
