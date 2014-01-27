# include "Camera.hpp"

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

void Camera::setFocal(const double f)
{
  focal = f;
}

void Camera::setFov(const double f)
{
  fov = f;
}

void Camera::setSProjection(const double p)
{
  sprojection = p;
}

void Camera::setTProjection(const int p)
{
  tprojection = p;
}

/******************** GETTER ********************/

const double Camera::getFocal(void)
{
  return (sprojection / (2.0 * tan(fov / 2.0 * (M_PI / 180.0))));
}

const double Camera::getFov(void)
{
  return fov;
}

const double Camera::getSProjection(void)
{
  return sprojection;
}

const int Camera::getTProjection(void)
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

  t->transformation(pos2, pos1);
  t->transformation(dir2, dir1);

  r2->setOrigin(pos2);
  r2->setDirection(dir2);
  r2->setIn(r1->isIn());
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

  d = sqrt(pow(vlookAt[1], 2) +
	   pow(vlookAt[2], 2));

  theta = vlookAt[1] < 0 ?
    -acos(vlookAt[2] / d) : acos(vlookAt[2] / d);

  rotation[0] = theta;

  d = sqrt(pow(vlookAt[0], 2) +
	   pow(vlookAt[2], 2));

  theta = vlookAt[0] < 0 ?
    -acos(vlookAt[2] / d) : acos(vlookAt[2] / d);

  rotation[1] = theta;

  t->setRotation(rotation);
}
