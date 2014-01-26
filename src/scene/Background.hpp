#ifndef BACKGROUND_HPP
# define BACKGROUND_HPP

# include <iostream>

# include <tools/Color.hpp>

# using namespace Tools;

namespace Scene
{
  class Background
  {
  private:
    Color color;

  public:
    Background(void);
    Background(Color c);
    Background(Background b);

  public:
    ~Background(void);

  public:
    Color& operator=(Background& b);
  };
}

#endif
