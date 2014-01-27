#ifndef OBJECT_HPP
# define OBJECT_HPP

# include <vector>
# include <iostream>
# include <cfloat>

# include <tools/Color.hpp>
# include <tools/Ray.hpp>

# include <texture/TextureMapper.hpp>
# include <texture/PerlinNoise.hpp>
# include <texture/Checker.hpp>

using namespace Tools;
using namespace Texture;

namespace Scene
{
  enum {COLOR, TEXTURE_MAPPING, PERLIN, CHECKER, NO};

  class Object
  {
  protected:
    double epsilon;
    double rhoA;
    double rhoD;
    double rhoS;
    double rhoR;
    double rhoT;
    double n;
    double shiness;
    Color color;
    int tPigment;
    int tNormal;

  protected:
    Mapper* m;
    Checker* check;
    PerlinNoise* pColor;
    PerlinNoise* pNormal;
    Transformer* t;

  public:
    Object();
    virtual ~Object();

  public:
    double distance(std::vector<double> p1, std::vector<double> p2);

  public:
    void setTransformer(Transformer* trans);
    void setEpsilon(double e);
    void setRhoA(double a);
    void setRhoD(double d);
    void setRhoR(double r);
    void setRhoS(double s);
    void setRhoT(double t);
    void setRefractionIndex(double n);
    void setShiness(double s);
    void setTPigment(int t);
    void setColor(Color c);
    void setChecker(Checker* c);
    void setPerlin(PerlinNoise* pNoise);
    void setPerlinNormal(PerlinNoise* pNoise);
    void setTypeNormal(int t);
    void setMapper(Mapper* mp);

  public:
    const double getEpsilon(void);
    const double getRhoA(void);
    const double getRhoD(void);
    const double getRhoR(void);
    const double getRhoS(void);
    const double getRhoT(void);
    const double getRefractionIndex(void);
    const double getShiness(void);
    void getColor(std::vector<double> p, std::vector<double> cObj);
    Checker* getChecker(void);

  public:
    bool sendRay(Ray* r, std::vector<double> i,
		 std::vector<double> normal, Ray* rSend);
    bool reflectRay(Ray *r, std::vector<double> i,
		    std::vector<double> normal, Ray* rReflect);
    void correctNormal(std::vector<double> normal, std::vector<double> p,
		       Ray* r);

  public:
    virtual double hit(Ray *r, std::vector<double> i);
    virtual void normal(std::vector<double> p,
			Ray *r, std::vector<double> vN);
  };
}

#endif
