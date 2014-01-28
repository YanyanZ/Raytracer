# include "Cone.hpp"

using namespace Scene;

Cone::Cone(double sr, double lr, double hg)
{
  sRadius = sr;
  lRadius = lr;
  h = hg;
  trans = new Transformer();
}

Cone::~Cone(void)
{
}

double Cone::hit(Ray* r, std::vector<double> i)
{
  double a, b, c, k, l, alpha, hh;
  double delta;
  double t1, t2, t = 0;
  double d = 0;

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

  alpha = atan(h / (lRadius - sRadius));
  hh = h + sRadius * tan(alpha);
  k = (lRadius * lRadius) / (h * h);
  l = pos2[0] - hh;

  a = pow(dir2[1], 2) + pow(dir2[2], 2) - k * pow(dir2[0], 2);
  b = dir2[1] * pos2[1] + dir2[2] * pos2[2] - k * l * dir2[0];
  c = pow(pos2[2], 2) + pow(pos2[1], 2) - k * l * l;

  delta = b * b - a * c;
  if (delta < 0.0)
    d = DBL_MAX;
  else
  {
    t1 = (-b + sqrt(delta)) / a;
    t2 = (-b - sqrt(delta)) / a;

    if ((pow(pos2[1], 2) + pow(pos2[2], 2)) > (k * l * l))
    {
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

	d = distance(p, pos2);
	if (p[0] > h)
	{
	  t = (h - pos2[0]) / dir2[0];
	  p[0] = h;
	  p[1] = t * dir2[1] + pos2[1];
	  p[2] = t * dir2[2] + pos2[2];
	  p[3] = 1.0;

	  if ((t > epsilon) &&
	      ((pow(p[1], 2) + pow(p[2], 2)) <= sRadius * lRadius))
	    d = distance(p, pos2);
	  else
	    d = DBL_MAX;
	}

	if (p[0] < 0.0)
	{
	  t = -pos2[0] / dir2[0];
	  p[0] = 0.0;
	  p[1] = t * dir2[1] + pos2[1];
	  p[2] = t * dir2[2] + pos2[2];
	  p[3] = 1.0;

	  if ((t > epsilon) &&
	      ((pow(p[1], 2) + pow(p[2], 2)) <= pow(lRadius, 2)))
	    d = distance (p, pos2);
	  else
	    d = DBL_MAX;
	}
      }
    }
    else if ((pow(pos2[1], 2) + pow(pos2[2], 2)) <= (k * l * l) &&
	     (pos2[0] <= h))
    {
      if (pos2[0] > h)
      {
	t = (h - pos2[0]) / dir2[0];
	p[0] = h;
	p[1] = t * dir2[1] + pos2[1];
	p[2] = t * dir2[2] + pos2[2];
	p[3] = 1.0;

	if ((t > epsilon) &&
	    ((pow(p[1], 2) + pow(p[2], 2)) <= pow(sRadius, 2)))
	  d = distance (p, pos2);
	else
	  d = DBL_MAX;
      }
      else if (pos2[0] < 0.0)
      {
	t = -pos2[0] / dir2[0];
	p[0] = 0.0;
	p[1] = t * dir2[1] + pos2[1];
	p[2] = t * dir2[2] + pos2[2];
	p[3] = 1.0;

	if ((t > epsilon) &&
	    ((pow(p[1], 2) + pow(p[2], 2)) <= pow(lRadius, 2)))
	  d = distance (p, pos2);
	else
	  d = DBL_MAX;
      }
      else if (t1 <= epsilon && t2 <= epsilon)
      {
	d = DBL_MAX;
	if (pos2[0] > h)
	{
	  t = (h - pos2[0]) / dir2[0];
	  p[0] = h;
	  p[1] = t * dir2[1] + pos[1];
	  p[2] = t * dir2[2] + pos2[2];
	  p[3] = 1.0;

	  if ((t > epsilon) &&
	      ((pow(p[1], 2) + pow(p[2], 2)) <= pow(sRadius, 2)))
	    d = distance(p, pos2);
	  else
	    d = DBL_MAX;
	}
	else
	{
	  t = -pos2[0] / dir2[0];
	  p[0] = 0.0;
	  p[1] = t * dir2[1] + pos2[1];
	  p[2] = t * dir2[2] + pos2[2];
	  p[3] = 1.0;

	  if ((t > epsilon) &&
	      ((pow(p[1], 2) + pow(p[2], 2)) <= pow(lRadius, 2)))
	    d = distance(p, pos2);
	  else
	    d = DBL_MAX;
	}

	if ((t1 <= t2 && t1 > epsilon) || (t2 < t1 && t2 < epsilon))
	  t = t1;
	else if ((t2 < t1 && t2 > epsilon)
		 || (t1 < t2 && t1 < epsilon))
	    t = t2;

	  p[0] = t * dir2[0] + pos2[0];
	  p[1] = t * dir2[1] + pos2[1];
	  p[2] = t * dir2[2] + pos2[2];
	  p[3] = 1.0;
	  d = distance (p, pos2);
	  if (p[0] > h)
	  {
	    t = (h - pos2[0]) / dir2[0];
	    p[0] = h;
	    p[1] = t * dir2[1] + pos2[1];
	    p[2] = t * dir2[2] + pos2[2];
	    p[3] = 1.0;
	    if ((t > epsilon)
		&& ((p[1] * p[1] + p[2] * p[2]) <=
		    sRadius * sRadius))
	    {
	      d = distance (p, pos2);
	    }
	    else
	      d = DBL_MAX;
	  }
	  if (p[0] < 0.0)
	  {
	    t = -pos2[0] / dir2[0];
	    p[0] = 0.0;
	    p[1] = t * dir2[1] + pos2[1];
	    p[2] = t * dir2[2] + pos2[2];
	    p[3] = 1.0;
	    if ((t > epsilon)
		&& ((p[1] * p[1] + p[2] * p[2]) <=
		    lRadius * lRadius))
	    {
	      d = distance (p, pos2);
	    }
	    else
	      d = DBL_MAX;
	  }
	}
      }
    }
  trans->transformation(i,p);

  return d;
}
