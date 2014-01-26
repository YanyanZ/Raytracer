#include "Scene.hpp"

Scene::Scene()
{
}

Scene::~Scene()
{
  if (camera)
    delete camera;

  if (objects)
    delete objects;

  if (dlights)
    delete dlights;

  if (plights)
    delete plights;
}

void Scene::addObject(Object o)
{
  objects->push_back(o);
  nbObjects = objects->size();
}

void Scene::addDirectionalLight(Directional l)
{
  dlights->push_back(l);
  nbDlights = dlights->size();
}

void Scene::addAmbiantLight(Ambiant l)
{
  alights = l;
}

void Scene::addPointLight(Point l)
{
  plights->push_back(l);
  nbPlights = plights->size();
}

void Scene::changeCamera(Camera c)
{
  camera = c;
}

Camera Scene::getCamera(void)
{
  return camera;
}

Object Scene::getObject(int i)
{
  return objects[i];
}

Point Scene::getPointLight(int i)
{
  return plights[i];
}

Directional Scene::getDirectionalLight(int i)
{
  return dlights[i];
}

bool Scene::pointIllumination(std::vector<double> p, int nlum)
{
  int i;
  bool illumination = true;
  double d;
  double dLum;

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
  (*plights)[nlum]->getPosition(pos);

  if (enableSoftShadow)
    for (int j = 0; j < 3; j++)
      pos[j] += static_cast<double> random() / (static_cast<double> MAXINT / softShadow) - softShadow / 2.0;

  for (int j = 0; j < 3; j++)
    dir[j] = pos[j] - p[j];
  dir[3] = 0;

  r->setDirection(dir);

  for (int i = 0; i < 3; i++)
    dLum += (p[i] - pos[i]) * (p[i] - pos[i]);
  dLum = sqrt(dLum);

  i = 0;
  while (illumination && i < nbObjets)
  {
    d = (*objects)[i]->hit(r, p2);

    if (d < dLum && d > 0.001)
      illumination = false;
    i++;
  }

  return illumination;
}

bool Scene::directionalIllumination(std::vector<double> p, int nlum)
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

  (*dlights)[nlum]->getDirection (dir);
  for (int i = 0; i < 3; i++)
    dir[i] = - dir[i];

  if (enableShadow)
  {
    for (int j = 0; j < 3; j++)
      dir[j] += static_cast<double> random() / (static_cast<double>(MAXINT) / softShadow) - softShadow / 2.0;
    r->setDirection(dir);
  }
  else
    r->setDirection(dir);

  i = 0;
  while (illumination && i < nbObjects)
  {
    d = (*objects)[i]->hit(r, p2);
    if (d < MAXDOUBLE && d > 0.001)
      illumination = false;
    i++;
  }

  return illumination;
}

Camera Scene::getCamera(void)
{
  return camera;
}

Object Scene::getObject(int i)
{
  return (*objects)[i];
}

Point Scene::getPointLight(int i)
{
  return (*plights)[i]
}

Directional Scene::getDirectionalLight(int i)
{
  return (*dlights)[i];
}

int Scene::getNbObject(void)
{
  return nbObject;
}

int Scene::getNbPointLight(void)
{
  return nbPlights;
}

int Scene::getDirectional(void)
{
  return nbDlights;
}

int Scene::getNbShadowRay(void)
{
  return nbShadowRay;
}

int Scene::getMaxTraceLevel(void)
{
  return maxTraceLevel;
}

int Scene::getAntialiasing(void)
{
  return antialisaing;
}

int Scene::getAAThreshold(void)
{
  return aThreshold;
}

int Scene::getOutputHeight(void)
{
  return outputH;
}

int Scene::getOutputW(void)
{
  return outputW;
}

Color Scene::getBackground(void)
{
  return bgColor;
}

void Scene::setGlobalSetting(int mtl, int anti, double aath, double ss,
		      int nbrs, int oph, int opw)
{
  maxTraceLevel = mtl;
  antialisaing = anti;
  aThreshold = aath;
  softShadow = ss;
  nbShadowRay = nbrs;
  outputH = oph;
  outputW = opw;

  if (softShadow == -1)
    enableShadow = false;
  else
    enableShadow = true;
}

void Scene::setBackground(Color c);
