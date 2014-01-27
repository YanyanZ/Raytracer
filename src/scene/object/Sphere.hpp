#ifndef SPHERE_HPP
# define SPHERE_HPP

namespace Scene
{
  class Sphere : public Object
  {
  private:
    double radius;

  public:
    Sphere(double r);
    virtual ~Sphere(void);

  public:
    double hit(Ray* r, std::vector<double> i);
    void normal(std::vector<double> p, Ray* r,
		std::vector<double> normal);
  };
}

#endif
