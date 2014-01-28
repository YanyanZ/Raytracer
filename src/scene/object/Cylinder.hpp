#ifndef CYLINDER_HPP
# define CYLINDER_HPP

# include <iostream>
# include <cmath>
# include <cfloat>
# include <vector>

# include <tools/Ray.hpp>
# include <tools/Color.hpp>
# include <tools/Transformer.hpp>

# include <scene/object/Object.hpp>

using namespace Tools;

namespace Scene
{
  class Cylinder : public Object
  {
  private:
    double radius;
    double length;

  private:
    Transformer* trans;

  public:
    Cylinder(double r, double l);
    virtual ~Cylinder(void);

  public:
    double hit(Ray* r, std::vector<double> i);
    void normal(std::vector<double> p, Ray *r,
		std::vector<double> normal);
  };
}

#endif
