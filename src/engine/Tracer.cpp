# include "Tracer.hpp"

Tracer::Tracer(Scene* sc)
{
  s = sc;
  nbThrowRay = 0;
}

Tracer::~Tracer(void)
{
  if (s)
    delete s;
}

void Tracer::saveScene(std::string output)
{

}

void Tracer::setPixel(int x, int y, Color c)
{
  map[x * 3 * w + y * 3] = static_cast<unsigned char>(c[0] * 255);
  map[x * 3 * w + y * 3 + 1] = static_cast<unsigned char>(c[1] * 255);
  map[x * 3 * w + y * 3 + 2] = static_cast<unsigned char>(c[2] * 255);
}

void Tracer::getPixel(int x, int y, Color& c)
{
  c[0] = map[x * 3 * w + y * 3];
  c[1] = map[x * 3 * w + y * 3 + 1];
  c[2] = map[x * 3 * w + y * 3 + 2];
}

void Tracer::enderScene(void)
{
  int i, j;
  Color c;

  s->getAmbiantLight(alight);
  bgColor = s->getBackground();

  w = s->getOutputWidth();
  h = s->getOutputHeight();

  pwidth = (s->getCamera())->getProjectionSize();
  pheight = pwidth * h / w;

  pasy = static_cast<double>(pwidth) / static_cast<double>(w);
  pasx = static_cast<double>(pheight) / static_cast<double>(h);

  map = (unsigned char *) malloc(3 * w * h * sizeof(unsigned char));
  for (i = 0; i < h; i++)
    for (j = 0; j < w; j++)
    {
      throwRays(i, j, c);
      map[i * 3 * w + j * 3] = (unsigned char) (c[0] * 255);
      map[i * 3 * w + j * 3 + 1] = (unsigned char) (c[1] * 255);
      map[i * 3 * w + j * 3 + 2] = (unsigned char) (c[2] * 255);
    }
}

void Tracer::throwRays(int i, int j, Color c)
{
  Color tmpc;
  std::vector<int> ph = {0, 0};
  std::vector<int> pg = {0, 0};
  Color ch = {0, 0, 0};
  Color cg = {0, 0, 0};

  double diff1;
  double diff2;

  Ray* r = new Ray();
  Ray* r2 = new Ray();

  double x, y, k;
  int aa = s->getAntialiasing();
  int aa2 = pow(aa, 2);
  initRayon(x, y, r);
  (s->getCamera())->repereScene(r, r2);

  c = {0, 0, 0};
  throwOneRay(r2, s->getMaxTraceLevel(), c);
  if (aa > 1)
  {
    if (i == 0 && j == 0)
    {
      ph[0] = 0;
      ph[1] = 0;
      pg[0] = 0;
      pg[1] = 0;
    }
    if (i == 0 && j > 0)
    {
      ph[0] = 0;
      ph[1] = j;
      pg[0] = 0;
      pg[1] = j - 1;
    }
    if (i > 0 && j == 0)
    {
      ph[0] = i - 1;
      ph[1] = 0;
      pg[0] = i;
      pg[1] = 0;
    }
    if (i > 0 && j > 0)
    {
      ph[0] = i - 1;
      ph[1] = j;
      pg[0] = i;
      pg[1] = j - 1;
    }

    getPixel(ph[0], ph[1], ch);
    getPixel(pg[0], pg[1], cg);

    diff1 = fabs(c[0] - ch[0]) + fabs(c[1] - ch[1]) +
      fabs(c[2] - ch[2]);
    diff2 = fabs(c[0] - cg[0]) + fabs(c[1] - cg[1]) +
      fabs(c[2] - cg[2]);

    k = 1;
    while (k <= aa && (diff1 > aathreshold || diff2 > aathreshold))
    {
      y = pasy * ((double) j - (double) random() / (double) INT_MAX)
	- pwidth / 2.0;
      x = pasx * ((double) i - (double) random() / (double) INT_MAX)
	- pheight / 2.0;

      initRay(x, y, r);
      (s->getCamera())->repereScene(r, r2);
      tmpc = {0, 0, 0};
      throwRay(r2, s->getMaxTraceLevel(), tmpc);

      for (int t = 0; t < 3; t++)
	c[t] = (((double) aa - 1) * c[t] + tmpc[t]) / (double) aa;
      diff1 = fabs(c[0] - ch[0]) + fabs(c[1] - ch[1]) +
	fabs(c[2] - ch[2]);
      diff2 = (c[0] - cg[0]) + fabs(c[1] - cg[1]) +
	fabs(c[2] - cg[2]);
      k++;
    }
  }

  for (int k = 0; k < 3; k++)
    c[k] = c[k] > 1.0 ? 1.0 : c[k];
}

void Tracer::initRay(double x, double y, Ray *r)
{
  Camera* c = s->getCamera();
  r->setIn(false);

  if (c->getTProjection() == PERSPECTIVE)
  {
    std::vector<double> dir = {x, y, c->getFocal(), 0.0};
    std::vector<double> pos = {0, 0, 0, 1};

    r->setOrigin(pos);
    r->setDirection(dir)
  }
  else
  {
    std::vector<double> dir = {0, 0, 1, 0};
    std::vector<double> pos = {0, 0, 0, 1};

    r->setOrigin(pos);
    r->setDirection(dir);
  }
}

void Traver::throwOneRay(Ray* r, int depth, Color c)
{
  double d;
  Object *o;
  std::vector<double> hit = {0, 0, 0, 0};
  std::vector<double> normal = {0, 0, 0, 0};
  Color cd, ca, cr, ct;

  if (depth > 0)
  {
    nbThrowRay++;
    d = evalHit(r, hit, &o);

    if (d != DBL_MAX)
    {
      o->normal(hit, r, normal);
      evalDirectRadiance(r, o, hit, normal, cd);
      evalAmbiantRadiance(o, hit, ca);
      evalReflectRadiance(r, o, hit, normal,
			  depth, cr);
      evalSendRadiance(r, o, hit, normal,
		       depth, ct);

      for (int i = 0; i < 3; i++)
	c[i] += cd[i] + o->getRhoA() * ca[i] +
	  o->getRhoR() * cr[i] + o->getRhoT() * ct[i];
    }
    else
    {
      c[0] += bgColor[0];
      c[1] += bgColor[1];
      c[2] += bgColor[2];
    }
  }
}

double Tracer::evalHit(Ray* r, std::vector<double> hit,
		       std::vector<Object>* o)
{
  double d1, d2;
  Object* o2;
  std::vector<double> i2 = {0, 0, 0, 0};

  o = s->getObject(0);
  d1 = (*o)->hit(r, hit);

  for (int i = 1; i < s->getNbObject(); i++)
  {
    o2 = s->getObject(i);
    d2 = o2->hit(r, i2);

    if (d2 < d1)
    {
      d1 = d2;
      *o = s->getObject(i);
      hit = i2;
    }
  }
  return d1;
}

void Tracer::evalDirectRadiance(Ray*r, Object* o,
				std::vector<double> hit,
				std::vector<double> normal,
				Color c)

{
  Color c2 = {0, 0, 0};
  c = {0, 0, 0};

  for (int i = 0; i < s->getNbPointLight(); i++)
  {
    for (int j = 0; j < s->getNbShadowRay(); j++)
    {
      if (s->isPointLight(hit, i))
      {
	(s->getPointLight(i))->getBrigthness(r, hit, normal, i, c2);
	c[0] += c2[0] / s->getNbShadowRay();
	c[1] += c2[1] / s->getNbShadowRay();
	c[2] += c2[2] / s->getNbShadowRay();
      }
    }
  }

  for (int i = 0; i < s->getNbDirectLight(); i++)
  {
    for (int j = 0; j < s->getNbShadowRay(); i++)
      if (s->isDirectionalLight(hit, i))
      {
	s->getDirectionalLight(i)->getBrigthness(r, hit, normal, o, c1);
	c[0] += c2[0] / s->getNbShadowRay();
	c[1] += c2[1] / s->getNbShadowRay();
	c[2] += c2[2] / s->getNbShadowRay();
      }
  }
}

void Tracer::evalSendRadiance(Ray* r, Object* o,
			      std::vector<double> hit,
			      std::vector<double> normal,
			      int depth,
			      Color c)
{
  Ray* rsend = new Ray();

  c = {0, 0, 0};

  if (o->getSendRay(r, hit, normal, rsend))
    throwOneRay(rsend, depth - 1, c);

  delete rsend;
}

void Traver::evalAmbiantRadiance(Object* o,
				 std::vector<double> p,
				 Color c)
{
  Color objColor;

  c = {0, 0, 0, 0};
  o->getColor(p, objColor);

  for (int i = 0; i < 3; i++)
    c[i] = objColor[i] * alight[i];
}
