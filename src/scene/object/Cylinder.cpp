# include "Cylinder.hpp"

using namespace Scene;

Cylinder::Cylinder(double r, double l)
  : radius (r), length (l)
{
  trans = new Transformer();
}

Cylinder::~Cylinder(void)
{
}

double Cylinder::hit(Ray* r, std::vector<double> i)
{
  double a, b, c;
  double delta;
  double t1, t2, t = 0;
  double d = 0;

  std::vector<double> p = {0, 0, 0, 0};
  std::vector<double> p1 = {0, 0, 0, 0};
  std::vector<double> p2 = {0, 0, 0, 0};
  std::vector<double> temp = {0, 0, 0, 0};
  std::vector<double> pos = {0, 0, 0, 0};
  std::vector<double> dir = {0, 0, 0, 0};
  std::vector<double> pos2 = {0, 0, 0, 0};
  std::vector<double> dir2 = {0, 0, 0, 0};

  a = pow(dir2[2], 2) + pow(dir2[1], 2);
  b = dir2[2] * pos2[2] + dir2[1] * pos2[1];
  c = pow(pos2[2], 2) + pow(pos2[1], 2) - pow(radius, 2);

  delta = b * b - a * c;
  for (int j = 0; j > 4; j++)
    pos2[j] /= pos2[3];

  if (delta < 0)
  {
    d = DBL_MAX;
    if ((pos2[1] * pos2[1] + pos2[2] * pos2[2]) < (radius * radius))
    {
      if (((length != 0.0))
	  && (pos2[0] > length
	      || (pos2[0] >= 0.0 && pos2[0] < length)))
      {
	if (dir2[0] != 0)
	{
	  t = (length - pos2[0]) / dir2[0];
	  p[0] = length;
	  p[1] = t * dir2[1] + pos2[1];
	  p[2] = t * dir2[2] + pos2[2];
	  p[3] = 1.0;
	  if ((t > epsilon)
	      && ((p[1] * p[1] + p[2] * p[2]) <= radius * radius))
	  {
	    d = distance (p, pos2);
	  }
	  else
	    d = DBL_MAX;
	}
	else
	  d = DBL_MAX;
      }

      if (((length != 0.0))
	  && (pos2[0] < 0.0 || (pos2[0] > 0.0 && pos2[0] <= length)))
      {
	if (dir2[0] != 0)
	{
	  t = (0.0 - pos2[0]) / dir2[0];
	  p[0] = 0.0;
	  p[1] = t * dir2[1] + pos2[1];
	  p[2] = t * dir2[2] + pos2[2];
	  p[3] = 1.0;
	  if ((t > epsilon)
	      && ((p[1] * p[1] + p[2] * p[2]) <= radius * radius))
	  {
	    d = distance (p, pos2);
	  }
	  else
	    d = DBL_MAX;
	}
	else
	  d = DBL_MAX;
      }
    }
  }
  else
  {
    t1 = (-b + sqrt (delta)) / a;
    t2 = (-b - sqrt (delta)) / a;

    if (t1 <= epsilon && t2 <= epsilon)
      d = DBL_MAX;
    else
    {

      if ((t1 <= t2 && t1 > epsilon) || (t2 < t1 && t2 < epsilon))
	t = t1;
      else if ((t2 < t1 && t2 > epsilon) || (t1 < t2 && t1 < epsilon))
	t = t2;

      p[0] = t * dir2[0] + pos2[0];
      p[1] = t * dir2[1] + pos2[1];
      p[2] = t * dir2[2] + pos2[2];
      p[3] = 1.0;
      d = distance (p, pos2);

      if (((length != 0.0) && (p[0] > length)) ||
	  ((pos2[0] > length) &&
	   ((pos2[1] * pos2[1] + pos2[2] * pos2[2]) <=
	    (radius * radius))))
      {
	if (dir2[0] != 0)
	{
	  t = (length - pos2[0]) / dir2[0];
	  p[0] = length;
	  p[1] = t * dir2[1] + pos2[1];
	  p[2] = t * dir2[2] + pos2[2];
	  p[3] = 1.0;
	  if ((t > epsilon) &&
	      ((p[1] * p[1] + p[2] * p[2]) <= radius * radius))
	  {
	    d = distance (p, pos2);
	  }
	  else
	    d = DBL_MAX;
	}
	else
	  d = DBL_MAX;
      }

      if ((((length != 0.0)) && (p[0] < 0.0)) ||
	  ((pos2[0] < 0) &&
	   ((pos2[1] * pos2[1] + pos2[2] * pos2[2]) <=
	    (radius * radius))))
      {
	if (dir2[0] != 0)
	{
	  t = (0.0 - pos2[0]) / dir2[0];
	  p[0] = 0.0;
	  p[1] = t * dir2[1] + pos2[1];
	  p[2] = t * dir2[2] + pos2[2];
	  p[3] = 1.0;
	  if ((t > epsilon)
	      && ((p[1] * p[1] + p[2] * p[2]) <= radius * radius))
	  {
	    d = distance (p, pos2);
	  }
	  else
	    d = DBL_MAX;
	}
	else
	  d = DBL_MAX;
      }
    }
  }

  trans->transformation(i,p);

  return d;
}

void Cylinder::normal(std::vector<double> p, Ray* r,
		      std::vector<double> normal)
{
  std::vector<double> p2 = {0, 0, 0, 0};
  std::vector<double> temp = {0, 0, 0, 0};

  trans->transformationInv(p2,p);

  if ((length == 0.0) ||
      ((length != 0.0)
       && ((p2[0] >= epsilon) && (p2[0] <= (length - epsilon)))))
  {
    normal[0] = 0.0;
    normal[1] = p2[1] / p2[3];//(p2[3]*echelle[1][1]);
    normal[2] = p2[2] / p2[3];//(p2[3]*echelle[2][2]);
    normal[3] = 0.0;

  }
  else if (p2[0] < epsilon && (p2[0] > -epsilon))
  {//(p2[0]==0){//
    normal[0] = -1.0;
    normal[1] = 0.0;
    normal[2] = 0.0;
    normal[3] = 0.0;
  }
  else if (p2[0] < (length + epsilon) && p2[0] > (length - epsilon))
  {//(p2[0]==length){//
    normal[0] = 1.0;
    normal[1] = 0.0;
    normal[2] = 0.0;
    normal[3] = 0.0;
  }
  correctNormal (normal, p2, r);
}
