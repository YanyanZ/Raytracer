#ifndef SCENE_HPP
# define SCENE_HPP

# include <vector>
# include <iostream>
# include <climits>
# include <cmath>
# include <cfloat>

# include <tools/Color.hpp>
# include <tools/Ray.hpp>

# include <scene/object/Object.hpp>
# include <scene/camera/Camera.hpp>
# include <scene/light/AmbiantLight.hpp>
# include <scene/light/DirectionalLight.hpp>
# include <scene/light/PointLight.hpp>

using namespace Tools;

namespace Scene
{
  class Descriptor
  {
  private:
    std::vector<Object>* objects;
    std::vector<Directional>* dlights;
    std::vector<Point>* plights;
    Ambiant alights;

  private:
    int nbObjects;
    int nbDlights;
    int nbPlights;

  private:
    Camera camera;

  private:
    Color bgColor;
    int maxTraceLevel;
    int antialiasing;
    double aThreshold;
    int outputH;
    int outputW;
    double softShadow;
    double enableSoftShadow;
    int nbShadowRay;

  public:
    Descriptor();
    ~Descriptor();

  public:
    void addObject(Object o);
    void addAmbiantLight(Ambiant l);
    void addDirectionalLight(Directional l);
    void addPointLight(Point l);
    void changeCamera(Camera c);

  public:
    bool pointIllumination(std::vector<double> p, int nlum);
    bool directionalIllumination(std::vector<double> p, int nlum);

  public:
    Camera getCamera(void);
    Object getObject(int i);
    Point getPointLight(int i);
    Directional getDirectionalLight(int i);
    int getNbObject(void);
    int getNbPointLight(void);
    int getNbDirectional(void);
    int getNbShadowRay(void);
    int getMaxTraceLevel(void);
    int getAntialiasing(void);
    double getAAThreshold(void);
    int getOutputHeight(void);
    int getOutputWidth(void);
    Color getBackground(void);

  public:
    void setGlobalSetting(int mtl, int anti, double aath, double ss,
			  int nbrs, int oph, int opw);
    void setBackground(Color c);
  };
}

#endif
