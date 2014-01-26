#ifndef TEXTUREMAPPER_HPP
# define TEXTUREMAPPER_HPP

# include <iostream>
# include <fstream>
# include <cmath>

# include <tools/Transformer.hpp>

namespace Texture
{
  enum {PLAN, SPHERE, UNKNOW};
  class TextureMapper
  {
  private:
    std::ifstream* file;
    std::string filename;
    unsigned char *map;
    int w, int h, int intensity;
    int freq;
    int tObject;
    double rSphere;

  private:
    Transformer* t;

  public:
    TextureMapper(std::string fn);
    TextureMapper(void);
    ~TextureMapper(void);

  public:
    void fillMap(void);
    void err(std::string msg);

  public:
    char getChar(void);
    unsigned char getByte(void);
    int getInt(void);
    void getMappingPlan(std::vector<double> p, Color c);
    void getMappingSphere(std::vector<double> p, Color c);
    void getColorTexture(int i, int j, Color c);
    void getMapping(std::vector<double> p, Color c);

  public:
    void setTextureSphere(double r);
    void setTexturePlan(void);
    void setFrequency(int f);
    void setTransformer(Transformer* tr);
  };
}

#endif
