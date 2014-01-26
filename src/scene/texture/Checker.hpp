#ifndef CHECKER_HPP
# define CHECKER_HPP

# include <vector>

# include <tools/Color.hpp>

namespace Texture
{
  class Checker
  {
  private:
    double size;
    Color c1;
    Color c2;

  private:
    Transformer* t;

  public:
    Checker(void);
    ~Checker(void);

  public:
    void setSize(double s);
    void setColor1(Color c);
    void setColor2(Color c);
    void setTransformer(Transformer* t);

  public:
    void getChecker(std::vector<double> pt, Color c);
  };
}

#endif
