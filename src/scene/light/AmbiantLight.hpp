#ifndef AMBIANTLIGHT_HPP
# define AMBIANTLIGHT_HPP

using namesapce Tools;

namespace Scene
{
  namespace Light
  {
    class Ambiant : public Light
    {
    public:
      Ambiant(Color c);
      ~Ambiant(void);
    };
  }
}

#endif
