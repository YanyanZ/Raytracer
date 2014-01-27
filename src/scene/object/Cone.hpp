#ifndef CONE_HPP
# define CONE_HPP

# include <vector>
# include <iostream>

# include <tools/Ray.hpp>
# include <tools/Color.hpp>

# include <scene/object/Object.hpp>

using namespace Tools;

namespace Scene
{
  class Cone : public Object
  {
  private:
    double sRadius;
    double lRadius;
    double h;

  public:
    Cone(double sr, double lr, double hg);
    virtual ~Cone(void);

  public:
    double hit(Ray* r, std::vector<double> i);
    void normal(std::vector<double> p, Ray* r,
		std::vector<double> i);
  };
}

#endif
