#ifndef TRACER_HPP
# define TRACER_HPP

# include <cmath>
# include <cvalues>
# include <cstdlib>
# include <fstream>

# include <scene/object/Object.hpp>
# include <scene/camera/Camera.hpp>
# include <scene/light/Light.hpp>
# include <scene/Background.hpp>
# include <scene/Scene.hpp>

# include <tools/Ray.hpp>
# include <tools/Color.hpp>

using namespace Tools;
using namespace Scene;

namespace Engine
{
  class Tracer
  {
  private:
    Scene* s;

  private:
    double pheight;
    double pwidth;
    double pasx;
    double pasy;
    Color alight;
    double bgColor;
    double aathreshold;
    double aadepth;
    double nbThrowRay;

  private:
    int w;
    int h;

  private:
    unsigned char *map;

  public:
    Tracer(Scene* sc);
    ~Tracer(void);

  public:
    void initRay(double x, double y, Ray* r);
    void throwOneRay(Ray* r, int depth, Color c);
    void trhowRays(int i, int j, Color c);

  public:
    double evalHit(Ray* r, std::vector<double> phit,
		   std::vector<Object>* o);

  public:
    void evalDirectRadiance(Ray* r, Object* o,
			    std::vector<double> phit,
			    std::vector<double> normal,
			    Color c);
    void evalReflectRadiance(Ray* r, Object* o,
			     std::vector<double> phit,
			     std::vector<double> normal,
			     int depth, Color c);
    void evalAmbiantRadiance(Object* o,
			     std::vector<double> p,
			     Color c);

  public:
    void setPixel(int x, int y, Color c);
    void getPixel(int x, int y, Color& c);

  public:
    void renderScene(void);
    void saveScene(std::string output);
  };
}

#endif
