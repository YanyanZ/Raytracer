#ifndef SPHERE_HPP
# define SPHERE_HPP

# include <vector>
# include <iostream>
# include <cfloat>

# include <tools/Transformer.hpp>
# include <tools/Ray.hpp>

# include <scene/object/Object.hpp>

namespace Scene
{
  class Sphere : public Object
  {
  private:
    double radius;
    Transformer* trans;

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
