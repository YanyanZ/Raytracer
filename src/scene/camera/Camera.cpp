#include "Camera.cpp"

using namespace Scene;

Camera::Camera(std::vector<double> p, std::vector<double> lkt)
  : fov (60.0), sprojection (10.0), position (p), lookAt (lkt)
{
  setTransformation();
}

Camera::~Camera()
{
}

/******************** SETER ********************/

void Camera::setFocale(const double f)
{
  focale = f;
}

void Camera::setFov(const double f)
{
  fov = f;
}

void Camera::setSProjection(const double p)
{
  sprojection = p;
}

void Camera::TProjection(const int p)
{
  tprojection = p;
}

/******************** GETTER ********************/

const double getFocal(void)
{
  return (sprojection / (2.0 * tan(fov / 2.0 * (M_PI / 180.0))));
}

const double getFov(void)
{
  return fov;
}

const double getSProjection(void)
{
  return sprojection;
}

const int getTProjection(void)
{
  return tprojection;
}

/******************** OTHER ********************/

void Camera::rScene(Ray *r1, Ray *r2)
{
  std::vector<double> dir1;
  std::vector<double> pos1;
  std::vector<double> dir2;
  std::vector<double> pos2;

  pos1 = r1->getOrigin();
  dir1 = r1->getDirection();

  t->transform(pos2, pos1);
  t->transform(dir2, dir);

  r2->setOrigin(pos2);
  r2->setDirection(dir2);
  r2->setIn(r->isIn());
}

void Camera::setTransformation(void)
{
  std::vector<double> rotation =
    {position[0], position[1], position[2]};
  std::vector<double> translation;
  std::vector<double> vlookAt;
  double theta;
  double d;

  t = new Transformer();
  translation.resize(3);
  vlookAt.resize(4);
  rotation[2] = 0;

  t->setTranslation(translation);

  for (int i = 0; i < vlookAt.size(); i++)
    vlookAt[i] = lookAt[i] - position[i];

  d = sqrt(sqrt(vlookAt[1], 2) +
	   sqrt(vlookAt[2], 2));

  theta = vlookAt[1] < 0 ?
    -acos(vlookAt[2] / d) : acos(vlookAt[2] / d);

  rotation[0] = theta;

  d = sqrt(sqrt(vlookAt[0], 2) +
	   sqrt(vlookAt[2], 2));

  theta = vlookAt[0] < 0 ?
    -acos(vlookAt[2] / d) : acos(vlookAt[2] / d);

  rotation[1] = theta;

  t->setRotation(rotation);
}
