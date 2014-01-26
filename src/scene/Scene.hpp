#ifndef SCENE_HPP
# define SCENE_HPP

class Scene
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
  Camera* camera;

private:
  Color bgColor;
  int maxTraceLevel;
  int antialiasing;
  double aThreshold;
  int outputH;
  int outputW;
  double softShowdow;
  double enableSoftShadow;
  int nbShadowRay;

public:
  Scene();
  ~Scene();

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
}

#endif
