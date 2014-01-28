#ifndef PLAN_HPP
# define PLAN_HPP

# include <vector>
# include <iostream>
# include <cmath>
# include <cfloat>

# include <scene/object/Object.hpp>

# include <tools/Ray.hpp>
# include <tools/Transformer.hpp>

using namespace Tools;

namespace Scene
{
  class Plan : public Object
  {
  private:
    Transformer* trans;

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
