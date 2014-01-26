#ifndef CAMERA_HPP
# define CAMERA_HPP

# include <iostream>
# include <vector>
# include <cmath>

# include <tools/Ray.hpp>

using namespace Tools;

namespace Scene
{
  enum {PERSPECTIVE, ORTHOGRAPHIC};

  class Camera
  {
  protected:
    double focal;
    double fov;
    double sprojection;
    int tprojection;

  protected:
    std::vector<double> position;
    std::vector<double> lookAt;

  protected:
    Transformer* t;

  public:
    Camera(std::vector<double> p, std::vecctor<double> lkt);

  public:
    virtual ~Camera(void);

  public:
    const double getFocal(void);
    const double getFov(void);
    const double getSProjection(void);
    const int getTProjection(void);

  public:
    void setFocal(const double f);
    void setFov(const double f);
    void setSProjection(const double p);
    void setTProjection(const int p);

  public:
    void rScene(Ray* r1, Ray* r2);
    void setTransformation(void);
  };
}

#endif