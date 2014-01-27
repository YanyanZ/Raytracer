#include "Checker.cpp"

using namespace Texture;

Checker::Checker(void)
  : c1 ({1.0, 1.0, 1.0}), c2 ({0.0, 0.0, 0.0})
{
}

Checker::~Checker(void)
{
}

void Checker::setSize(double s)
{
  size = s;
}

void Checker::setColor1(Color c)
{
  c1 = c;
}

void Checker::setColor2(Color c)
{
  c2 = c;
}

void Checker::setTransformer(Transformer* tr)
{
  t = tr;
}

void Checker::getChecker(std::vector<double> pt, Color c)
{
  std::vector<double> p2;
  p2.resize(4);

  t->transformation(p2, pt);

  int xx = static_cast<int>(p2[0] / size);
  int yy = static_cast<int>(p2[1] / size);
  int zz = static_cast<int>(p2[2] / size);

  bool xpair, ypair, zpair;

  xpair = ((abs(xx) % 2) == 0);
  ypair = ((abs(yy) % 2) == 0);
  zpair = ((abs(zz) % 2) == 0);

  if (p2[0] < 0)
    xpair = !xpair;
  if (p2[1] < 0)
    ypair = !ypair;
  if (p2[2] < 0)
    zpair = !zpair;

  if (zpair)
    if ((xpair && ypair) ||
	(!xpair && !ypair))
      c1 = c;
    else
      c2 = c;
  else if ((xpair && ypair) ||
	   (!xpair && !ypair))
    c2 = c;
  else
    c1 = c;
}
