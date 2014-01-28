#ifndef CUBE_HPP
# define CUBE_HPP

# include <vector>
# include <cmath>
# include <iostream>
# include <cfloat>

# include <tools/Color.hpp>
# include <tools/Ray.hpp>
# include <tools/Transformer.hpp>

# include <scene/object/Object.hpp>

namespace Scene
{
  class Cube : public Object
  {
  private:
    Transformer* trans;

  public:
    Cube(void);
    virtual ~Cube(void);

  public:
    double hit(Ray* r, std::vector<double> i);
    void normal(std::vector<double> p, Ray* r,
		std::vector<double> normal);
  };
}

#endif
