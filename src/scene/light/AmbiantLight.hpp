#ifndef AMBIANTLIGHT_HPP
# define AMBIANTLIGHT_HPP

# include <scene/light/Light.hpp>

# include <tools/Color.hpp>

using namespace Tools;

namespace Scene
{
  class Ambiant : public Light
  {
  public:
    Ambiant() : Light({0, 0, 0}) {};
    Ambiant(Color c);
    ~Ambiant(void);
  };
}

#endif
