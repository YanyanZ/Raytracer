#ifndef DIRECTIONALLIGHT_HPP
# define DIRECTIONALLIGHT_HPP

# include <vector>

# include <tools/Ray.hpp>
# include <tools/Color.hpp>

# include <scene/object/Object.hpp>
# include <scene/light/Light.hpp>

using namespace Tools;

namespace Scene
{
  class Directional : public Light
  {
  protected:
    std::vector<double> direction;

  public:
    Directional(std::vector<double> d, Color c);
    virtual ~Directional(void);

  public:
    const std::vector<double> getDirection(void);

  public:
    void getBrightness(Ray* r, std::vector<double> p,
		       std::vector<double> n, Object* o,
		       std::vector<double> l);
  };
}

#endif
