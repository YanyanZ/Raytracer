#ifndef PLAN_HPP
# define PLAN_HPP

# include <vector>
# include <iostream>
# include <cmath>
# include <cfloat>

# include <scene/object/Object.hpp>

# include <tools/Ray.cpp>

using namespace Tools;

namespace Scene
{
  class Plan : public object
  {
  public:
    Plan(void);
    virtual ~Plan(void);

  public:
    double hit(Ray* r, std::vector<double> i);
    void normal(std::vector<double> p, Ray* r,
		std::vector<double> i);
  };
}

#endif
