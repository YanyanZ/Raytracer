#ifndef BACKGROUND_HPP
# define BACKGROUND_HPP

# include <iostream>

# include <tools/Color.hpp>

namespace Scene
{
  class Background
  {
  public:
    Color color;

  public:
    Background(void);
    Background(Color c);

  public:
    ~Background(void);
  };
}

#endif
