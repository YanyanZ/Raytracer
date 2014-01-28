#ifndef BOX_HPP
# define BOX_HPP

# include <vector>
# include <iostream>
# include <cmath>
# include <cfloat>

# include <tools/Ray.hpp>
# include <tools/Color.hpp>
# include <tools/Transformer.hpp>

# include <scene/object/Object.hpp>
# include <scene/object/Parallelogram.hpp>

namespace Scene
{
  class Box : public Object
  {
  private:
    double side;
    std::vector<Parallelogram*> sides;
    int hitSide;
    Transformer *trans;

  public:
    Box(double s);
    virtual ~Box(void);

  public:
    double hit(Ray* r, std::vector<double> i);
    void normal(std::vector<double> p, Ray* r,
		std::vector<double> normal);
  };
}

#endif
