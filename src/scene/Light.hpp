#ifndef LIGHT_HPP
# define LIGHT_HPP

# include <iostream>
# include <cmath>
# include <vector>

using namespace Tools;

namespace Scene
{
  class Light
  {
  protected:
    Color color;

  public:
    Light(Color c);
    virtual ~Color(void);

  public:
    void normalize(std::vector<double>& v);
    double dot(std::vector<double> v1, std::vector<double> v2);

  public:
    const Color getColor(void);
  };
}

#endif
