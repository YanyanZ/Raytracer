# include "Object.hpp"

using namespace Scene;

Object::Object()
  : epsilon (0.001),
    rhoA (0.5),
    rhoD (0.5),
    rhoS (0.5),
    rhoR (0.5),
    rhoT (0.0),
    n (1.0),
    shiness (1.0),
    color ({1.0, 1.0, 1.0}),
    tPigment (COLOR),
    tNormal (NO),
    m (NULL)
{
}

Object::~Object(void)
{
}

const double Object::getEpsilon(void)
{
  return epsilon;
}

const double Object::getRhoA(void)
{
  return rhoA;
}

const double Object::getRhoD(void)
{
  return rhoD;
}

const double Object::getRhoR(void)
{
  return rhoR;
}

const double Object::getRhoS(void)
{
  return rhoS;
}

const double Object::getRhoT(void)
{
  return rhoT;
}

const double Object::getRefractionIndex(void)
{
  return n;
}

void Object::getColor(std::vector<double> p, std::vector<double> cObj)
{
  std::vector<double> p2;
  p2.resize(4);

  switch(tPigment)
  {
    case COLOR:
      for (int i = 0; i < 3; i++)
	cObj[i] = (1 - rhoT) * color[i];
      break;
    case CHECKER:
      check->getChecker(p, cObj);
      break;
    case PERLIN:
      pColor->PerlinColor(p, cObj);
      break;
    case TEXTURE_MAPPING:
      t->transformationInv(p2, p);
      m->getMapping(p2, cObj);
      break;
    default:
      break;
  }
}

Checker* Object::getChecker(void)
{
  return check;
}

void Object::setTransformer(Transformer* trans)
{
  t = trans;
}
void Object::setEpsilon(double e)
{
  epsilon = e;
}

void Object::setRhoA(double a)
{
  rhoA = a;
}

void Object::setRhoD(double d)
{
  rhoD = d;
}

void Object::setRhoR(double r)
{
  rhoR = r;
}
void Object::setRhoS(double s)
{
  rhoS = s;
}

void Object::setRhoT(double t)
{
  rhoT = t;
}

void Object::setRefractionIndex(double n)
{
  this->n = n;
}

void Object::setShiness(double s)
{
  shiness = s;
}

void Object::setTPigment(int t)
{
  tPigment = t;
}

void Object::setColor(Color c)
{
  color = c;
}

void Object::setChecker(Checker* c)
{
  check = c;
}

void Object::setPerlin(PerlinNoise* pNoise)
{
  pColor = pNoise;
}

void Object::setPerlinNormal(PerlinNoise* pNoise)
{
  pNormal = pNoise;
}

void Object::setTypeNormal(int t)
{
  tNormal = t;
}

void Object::setMapper(Mapper* mp)
{
  m = mp;
}

bool Object::sendRay(Ray* r, std::vector<double> i,
		     std::vector<double> normal, Ray* rSend)
{
  double deviation;
  double thetat, thetai;
  double coef;
  double ps;
  std::vector<double> dir;

  dir.resize(4);

  if (rhoT == 0)
    return false;
  else
  {
    rSend->setOrigin(i);

    if (n == 1.0)
      rSend->setIn(false);
    else
      rSend->swapInOut();

    if (r->isIn())
      deviation = n;
    else
      deviation = 1.0 / n;

    t->normalize(normal);
    ps = r->dot(normal);
    thetai = acos(ps);
    thetat = asin(deviation * sin(thetai));
    coef = cos(thetat) + deviation * ps;

    dir = r->getDirection();
    for (int ii = 0; ii < 3; ii++)
      dir[ii] = deviation * dir[ii] - coef * normal[ii];
    dir[3] = 0;
    rSend->setDirection(dir);

    return true;
  }
}

bool Object::reflectRay(Ray *r, std::vector<double> i,
			std::vector<double> normal, Ray* rReflect)
{
  std::vector<double> dir;
  dir.resize(4);

  if (rhoR == 0)
    return false;
  else
  {
    rReflect->setOrigin(i);
    rReflect->setIn(r->isIn());
    dir = r->getDirection();

    for (int j = 0; j < 3; j++)
      dir[j] = dir[j] - 2 * r->dot(normal) * normal[j];
    dir[3] = 0;

    rReflect->setDirection(dir);

    return true;
  }
}

double Object::hit(Ray* r, std::vector<double> i)
{
  return DBL_MAX;
}

void Object::correctNormal(std::vector<double> normal, std::vector<double> p,
			   Ray* r)
{
  std::vector<double> temp;
  std::vector<double> rd;
  std::vector<double> tmp;
  double ps;

  temp.resize(4);
  rd.resize(4);
  tmp.resize(4);

  if (tNormal == PERLIN)
    pNormal->PerlinNormal(p, normal);

  tmp = r->getDirection();
  t->transformationInv(rd, tmp);

  ps = 0;
  for (int i = 0; i < 3; i++)
    ps += normal[i] * rd[i];

  if (ps > 0.0)
  {
    temp[0] = -normal[0];
    temp[1] = -normal[1];
    temp[2] = -normal[2];
    temp[3] = 0;
  }
  else
  {
    temp[0] = normal[0];
    temp[1] = normal[1];
    temp[2] = normal[2];
    temp[3] = 0;
  }

  t->transformation(normal, temp);
  t->normalize(normal);
}
