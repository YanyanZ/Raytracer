#ifndef RAY_HPP
# define RAY_HPP

# include <iostream>
# include <cmath>
# include <vector>

namespace Tools
{
  class Ray
  {
  private:
    std::vector<double> origin;
    std::vector<double> direction;
    bool in;

  public:
    Ray();
    Ray(std::vector<double> o, std::vector<double> d);
    ~Ray();

  public:
    void normalize(std::vector<double>& v);

  public:
    void setDirection(std::vector<double> d);
    void setOrigin(std::vector<double> o);
    void setIn(bool i);

  public:
    std::vector<double> getDirection(void);
    std::vector<double> getOrigin(void);

  public:
    void swapInOut(void);
    bool isIn(void);
    double dot(std::vector<double> v);
  };
}

#endif
