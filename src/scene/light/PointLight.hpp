#ifndef POINTLIGHT_HPP
# define POINTLIGHT_HPP

# include <vector>
# include <cmath>

namespace Scene
{
  class Point : public Light
  {
  private:
    std::vector<double> postion;
    double c1, c2, c3;

  public:
    Point(std::vector<double> p, Color c);
    virtual ~Point(void);

  public:
    void setDimmer(double c1, double c2, double c3);

  public:
    const std::vector<const double> getDimmer(void);
    const std::vector<double> getPosition(void);

  public:
    void getBrightness(Ray *r, std::vector<double> p,
		       std::vector<double> n, Object* o,
		       std::vector<double> l);
  };
}

#endif
