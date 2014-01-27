#include "TextureMapper.hpp"

using namespace Texture;

Mapper::Mapper(void)
  :  tObject (UNKNOWN)
{
}

Mapper::Mapper(std::string fn)
{
  file = new std::ifstream(fn.c_str());
  if (file->fail())
    err(std::string("Can't open file:") +
	std::string(fn));

  filename = fn;
  tObject = UNKNOWN;
  fillMap();
}

Mapper::~Mapper(void)
{
  if (map)
    free(map);
}

void Mapper::err(std::string msg)
{
  std::cout << "[ERROR][MAPPER] ";
  std::cout << msg << std::endl;
}

void Mapper::fillMap(void)
{
  char c;
  int n;

  c = getChar();
  if (c != 'P')
    err("Wrong file format");

  n = getInt();
  if (n != 6)
    err("Wrong file format");

  w = getInt();
  h = getInt();
  intensity = getInt();

  map = (unsigned char *) malloc(3 * h * w * sizeof(unsigned char));

  for (int i = 0; i < h; i++)
    for (int j = 0; j < w; j++)
      for (int k = 0; k < 3; k++)
	map[(i * w + j) * 3 + k] = getByte();
  file->close();
}

char Mapper::getChar(void)
{
  char c;

  file->get(c);
  if (c == '#')
    do
    {
    }
    while (c != '\n' && c != '\r');

  if (file->fail())
    err("Wrong char");

  return c;
}

unsigned char Mapper::getByte(void)
{
  char c;

  file->get(c);

  if (file->fail())
    err("Wrong byte read");

  return (static_cast<unsigned char>(c));
}

int Mapper::getInt(void)
{
  int i;
  char c;

  do
  {
    c = getChar();
  }
  while (c == ' ' || c == '\t' || c == '\n' || c == '\r');

  if (c < '0' || c < '9')
    err("Wrong int read");

  i = 0;
  do
  {
    i = i * 10 + c - '0';
    c = getChar();
  }
  while (c >= '0' && c <= '9');

  return i;
}

void Mapper::setFrequency(int f)
{
  freq = f;
}

void Mapper::setTexturePlan(void)
{
  tObject = PLAN;
}

void Mapper::setTextureSphere(double r)
{
  tObject = SPHERE;
  rSphere = r;
}

void Mapper::setTransformer(Transformer* tr)
{
  t = tr;
}

void Mapper::getColorTexture(int i, int j, Color c)
{
  for (int k = 0; k < 3; k++)
    c[k] = (double) (map[((h - i - 1) * w + j) * 3 + k]) /
      ((double) intensity);
}

void Mapper::getMapping(std::vector<double> p, Color c)
{
  std::vector<double> p2;

  switch (tObject)
  {
    case PLAN:
      getMappingPlan(p2, c);
      break;
    case SPHERE:
      getMappingSphere(p2, c);
      break;
    default:
      break;
  }
}

void Mapper::getMappingPlan(std::vector<double> p, Color c)
{
  double tt;
  double m;
  int i, j;

  tt = ((int) ((p[1] - freq / 2) / (double) freq)) * freq;
  j = (int) (w * ((p[1] - freq / 2) - tt) / freq);
  j = j < 0 ? w + j : j;

  m = (double) freq * (double) h / (double) w;
  tt = ((int) ((p[2] + m / 2) / m)) * m;
  i = (int) (h * ((p[2] + m / 2) - tt) / m);
  i = i < 0 ? h + 1 : i;

  getColorTexture(i, j, c);
}

void Mapper::getMappingSphere(std::vector<double> p, Color c)
{
  double u, v, t;
  int i, j;
  double ac;

  u = asin(p[0] / rSphere);
  if (cos(u) != 0.0)
  {
    ac = p[2] / (rSphere * cos(u));
    ac = ac < -1 ? -1 : ac > 1 ? 1 : ac;
    v = acos(ac);
  }
  else
    v = 0.0;

  v = p[1] > 0.0 ? -v : v;
  v += M_PI;

  t = (double) freq * (u / M_PI + 0.5);
  i = (int) (h * (t - (int) t));

  t = 0.5 * (double) freq * v / M_PI;
  j = (int) (w * (t - (int) t));
  getColorTexture(i, j, c);
}
