#ifndef CONE_HPP
# define CONE_HPP

# include <vector>
# include <iostream>
# include <cfloat>
# include <cmath>

# include <tools/Ray.hpp>
# include <tools/Color.hpp>
# include <tools/Transformer.hpp>

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
    Transformer* trans;

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
