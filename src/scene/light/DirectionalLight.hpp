#ifndef DIRECTIONALLIGHT_HPP
# define DIRECTIONALLIGHT_HPP

# include <vector>

namespace Scene
{
  namespace Light
  {
    class Directional
    {
    protected:
      std::vector<double> direction;

    public:
      Directional(std::vector<double> d, Color c);
      ~Directional(void);

    public:
      const std::vector<double> getDirection(void);

    public:
      void getBrightness(Ray* r, std::vector<double> p,
			 std::vector<double> n, Object* o,
			 std::vector<double> l);
    };
  }
}

#endif
