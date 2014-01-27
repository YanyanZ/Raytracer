# include "Scene.hpp"

using namespace Scene;

Descriptor::Descriptor()
{
}

Descriptor::~Descriptor()
{
  if (objects)
    delete objects;

  if (dlights)
    delete dlights;

  if (plights)
    delete plights;
}

void Descriptor::addObject(Object o)
{
  objects->push_back(o);
  nbObjects = objects->size();
}

void Descriptor::addDirectionalLight(Directional l)
{
  dlights->push_back(l);
  nbDlights = dlights->size();
}

void Descriptor::addAmbiantLight(Ambiant l)
{
  alights = l;
}

void Descriptor::addPointLight(Point l)
{
  plights->push_back(l);
  nbPlights = plights->size();
}

void Descriptor::changeCamera(Camera c)
{
  //camera = Camera(c);
}

bool Descriptor::pointIllumination(std::vector<double> p, int nlum)
{
  int i;
  bool illumination = true;
  double d;
  double dLum = 0;

  std::vector<double> pos;
  std::vector<double> dir;
  std::vector<double> p2;

  pos.resize(4);
  dir.resize(4);
  p2.resize(4);

  Ray* r = new Ray();
  for (int j = 0; j < 4; j++)
    p[j] /= p[3];

  r->setOrigin(p);
  pos = (*plights)[nlum].getPosition();

  if (enableSoftShadow)
    for (int j = 0; j < 3; j++)
      pos[j] += static_cast<double>(random()) / (static_cast<double>(INT_MAX) / softShadow) - softShadow / 2.0;

  for (int j = 0; j < 3; j++)
    dir[j] = pos[j] - p[j];
  dir[3] = 0;

  r->setDirection(dir);

  for (int i = 0; i < 3; i++)
    dLum += (p[i] - pos[i]) * (p[i] - pos[i]);
  dLum = sqrt(dLum);

  i = 0;
  while (illumination && i < nbObjects)
  {
    d = (*objects)[i].hit(r, p2);

    if (d < dLum && d > 0.001)
      illumination = false;
    i++;
  }

  return illumination;
}

bool Descriptor::directionalIllumination(std::vector<double> p, int nlum)
{
  double i;
  bool illumination = true;
  double d;
  std::vector<double> p2;
  std::vector<double> dir;
  Ray* r = new Ray();

  for (int j = 0; j < 4; j++)
    p[j] /= p[3];
  r->setOrigin(p);

  dir = (*dlights)[nlum].getDirection();
  for (int i = 0; i < 3; i++)
    dir[i] = - dir[i];

  if (enableSoftShadow)
  {
    for (int j = 0; j < 3; j++)
      dir[j] += static_cast<double>(random()) / (static_cast<double>(INT_MAX) / softShadow) - softShadow / 2.0;
    r->setDirection(dir);
  }
  else
    r->setDirection(dir);

  i = 0;
  while (illumination && i < nbObjects)
  {
    d = (*objects)[i].hit(r, p2);
    if (d < DBL_MAX && d > 0.001)
      illumination = false;
    i++;
  }

  return illumination;
}

Camera Descriptor::getCamera(void)
{
  return camera;
}

Object Descriptor::getObject(int i)
{
  return (*objects)[i];
}

Point Descriptor::getPointLight(int i)
{
  return (*plights)[i];
}

Directional Descriptor::getDirectionalLight(int i)
{
  return (*dlights)[i];
}

int Descriptor::getNbObject(void)
{
  return nbObjects;
}

int Descriptor::getNbPointLight(void)
{
  return nbPlights;
}

int Descriptor::getNbDirectional(void)
{
  return nbDlights;
}

int Descriptor::getNbShadowRay(void)
{
  return nbShadowRay;
}

int Descriptor::getMaxTraceLevel(void)
{
  return maxTraceLevel;
}

int Descriptor::getAntialiasing(void)
{
  return antialiasing;
}

double Descriptor::getAAThreshold(void)
{
  return aThreshold;
}

int Descriptor::getOutputHeight(void)
{
  return outputH;
}

int Descriptor::getOutputWidth(void)
{
  return outputW;
}

Color Descriptor::getBackground(void)
{
  return bgColor;
}

void Descriptor::setGlobalSetting(int mtl, int anti, double aath, double ss,
				  int nbrs, int oph, int opw)
{
  maxTraceLevel = mtl;
  antialiasing = anti;
  aThreshold = aath;
  softShadow = ss;
  nbShadowRay = nbrs;
  outputH = oph;
  outputW = opw;

  if (softShadow == -1)
    enableSoftShadow = false;
  else
    enableSoftShadow = true;
}

void Descriptor::setBackground(Color c)
{
  bgColor = c;
}
