#include "Transformer.hpp"

using namespace Tools;

Transformer::Transformer()
{
  translation = {{0, 0, 0, 0}, {0, 0, 0, 0}};
  rotation = {{0, 0, 0, 0}, {0, 0, 0, 0}};
  scale = {{0, 0, 0, 0}, {0, 0, 0, 0}};
  trans = {{0, 0, 0, 0}, {0, 0, 0, 0}};
  tPigment = {{0, 0, 0, 0}, {0, 0, 0, 0}};

  invTranslation = {{0, 0, 0, 0}, {0, 0, 0, 0}};
  invRotation = {{0, 0, 0, 0}, {0, 0, 0, 0}};
  invScale = {{0, 0, 0, 0}, {0, 0, 0, 0}};
  invTransformation = {{0, 0, 0, 0}, {0, 0, 0, 0}};

  loadIdentity(translation);
  loadIdentity(rotation);
  loadIdentity(scale);
  loadIdentity(invTranslation);
  loadIdentity(invRotation);
  loadIdentity(invScale);
  loadIdentity(trans);
  loadIdentity(invTransformation);
}

Transformer::~Transformer(void)
{
}

void Transformer::pointmult(std::vector<double>& res,
			    std::vector<double> point,
			    std::vector<std::vector<double> > mat)
{
  int i, j;
  double val;

  for (i = 0; i < 4; i++)
  {
    val = 0;
    for (j = 0; j < 4; j++)
      val += mat[i][j] * point[j];
    res[i] = val;
  }

  if (res[3] != 0)
    for (i = 0; i < 4; i++)
      res[i] = res[i] / res[3];
}

void Transformer::matmult(std::vector<std::vector<double> >& res,
			  std::vector<std::vector<double> > mat1,
			  std::vector<std::vector<double> > mat2)
{
  int i, j, k;
 double val;
  std::vector<std::vector<double> > r = {{0, 0, 0, 0}, {0, 0, 0, 0}};

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
    {
      val = 0;
      for (k = 0; k < 4; k++)
	val += mat1[i][k] * mat2[k][j];
      r[i][j] = val;
    }

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      res[i][j] = r[i][j];
}

void Transformer::loadNullMatrix(std::vector<std::vector<double> >& m)
{
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      m[i][j] = 0;
}

void Transformer::loadIdentity(std::vector<std::vector<double> >& m)
{
  loadNullMatrix(m);
  for (int i = 0; i < 4; i++)
    m[i][i] = 1;
}

void Transformer::setTranslation(std::vector<double>& tr)
{
  std::vector<std::vector<double> > temp =  {{0, 0, 0, 0}, {0, 0, 0, 0}};
  loadIdentity(translation);

  for (int i = 0; i < 3; i++)
    translation[i][3] = tr[i];

  temp = trans;
  // memcpy(temp, trans, 4 * 4 * sizeof(double));
  matmult(trans, temp, translation);

  loadIdentity(invTranslation);
  for (int i = 0; i < 3; i++)
    invTranslation[i][3] = - tr[i];

  temp = invTransformation;
  // memcpy(temp, invTransformation, 4 * 4 * sizeof(double));
  matmult(invTransformation, invTranslation, temp);
}

void Transformer::setRotation(std::vector<double>& r)
{
  std::vector<std::vector<double> > rx = {{0, 0, 0, 0}, {0, 0, 0, 0}};   // 4*4
  std::vector<std::vector<double> > ry = {{0, 0, 0, 0}, {0, 0, 0, 0}};   // 4*4
  std::vector<std::vector<double> > rz = {{0, 0, 0, 0}, {0, 0, 0, 0}};   // 4*4
  std::vector<std::vector<double> > temp = {{0, 0, 0, 0}, {0, 0, 0, 0}}; // 4*4
  std::vector<std::vector<double> > temp2 = {{0, 0, 0, 0}, {0, 0, 0, 0}};

  loadIdentity(rx);
  loadIdentity(ry);
  loadIdentity(rz);

  rx[1][1] = cos (r[0]);
  rx[2][1] = sin (r[0]);
  rx[1][2] = -sin (r[0]);
  rx[2][2] = cos (r[0]);

  ry[0][0] = cos (r[1]);
  ry[2][0] = -sin (r[1]);
  ry[0][2] = sin (r[1]);
  ry[2][2] = cos (r[1]);

  rz[0][0] = cos (r[2]);
  rz[1][0] = sin (r[2]);
  rz[0][1] = -sin (r[2]);
  rz[1][1] = cos (r[2]);

  loadIdentity(rotation);

  matmult(temp, rotation, rz);
  matmult(temp2, temp, ry);
  matmult(rotation, temp2, rx);

  temp = trans;
  // memcpy(temp, trans, 4 * 4 * sizeof (double));
  matmult(trans, temp, rotation);

  rx[1][1] = cos (-r[0]);
  rx[2][1] = sin (-r[0]);
  rx[1][2] = -sin (-r[0]);
  rx[2][2] = cos (-r[0]);

  ry[0][0] = cos (-r[1]);
  ry[2][0] = -sin (-r[1]);
  ry[0][2] = sin (-r[1]);
  ry[2][2] = cos (-r[1]);

  rz[0][0] = cos (-r[2]);
  rz[1][0] = sin (-r[2]);
  rz[0][1] = -sin (-r[2]);
  rz[1][1] = cos (-r[2]);

  loadIdentity(invRotation);

  matmult(temp, invRotation, rx);
  matmult(temp2, temp, ry);
  matmult(invRotation, temp2, rz);

  temp = invTransformation;
  //memcpy(temp, invTransformation, 4 * 4 * sizeof (double));
  matmult(invTransformation, invRotation, temp);
}

void Transformer::setScale(std::vector<double>& s)
{
  std::vector<std::vector<double> > temp = {{0, 0, 0, 0}, {0, 0, 0, 0}};
  loadIdentity(scale);

  for (int i = 0; i < 3; i++)
    scale[i][i] = s[i];

  temp = trans;
  // memcpy(temp, trans, 4 * 4 * sizeof(double));
  matmult(trans, temp, scale);

  loadIdentity(invScale);

  for (int i = 0; i < 3; i++)
    invScale[i][i] = 1.0 / s[i];

  temp = invTransformation;
  // memcpy(temp, invTransformation, 4 * 4 * sizeof(double));
  matmult(invTransformation, invScale, temp);
}

void Transformer::transformation(std::vector<double>& res,
				 std::vector<double> vec)
{
  pointmult(res, vec, trans);

  if (res[3] != 0)
    for (int i = 0; i < 4; i++)
      res[i] /= res[3];
}

void Transformer::transformationInv(std::vector<double>& res,
				    std::vector<double> vec)
{
  pointmult(res, vec, invTransformation);

  if (res[3] != 0)
    for (int i = 0; i < 4; i++)
      res[i] /= res[3];
}

void Transformer::normalize(std::vector<double>& p)
{
  double d = 0;

  for (int i = 0; i < 3; i++)
    d += p[i] * p[i];

  d = sqrt(d);
  for (int i = 0; i < 3; i++)
    p[i] /= d;
}
