#ifndef TRANSFORMER_HPP
# define TRANSFORMER_HPP

# include <vector>
# include <iostream>
# include <cmath>

namespace Tools
{
  class Transformer
  {
  private:
    std::vector<std::vector<double> > translation;    // [4][4]
    std::vector<std::vector<double> > rotation;       // [4][4]
    std::vector<std::vector<double> > scale;          // [4][4]
    std::vector<std::vector<double> > trans;          // [4][4]
    std::vector<std::vector<double> > tPigment;       // [4][4]

    std::vector<std::vector<double> > invTranslation;    // [4][4]
    std::vector<std::vector<double> > invRotation;       // [4][4]
    std::vector<std::vector<double> > invScale;          // [4][4]
    std::vector<std::vector<double> > invTransformation; // [4][4]

  public:
    Transformer(void);
    ~Transformer(void);

  public:
    void loadNullMatrix(std::vector<std::vector<double> >& m);
    void loadIdentity(std::vector<std::vector<double> >& m);
    void matmult(std::vector<std::vector<double> >& res,
		 std::vector<std::vector<double> > mat1,
		 std::vector<std::vector<double> > mat2);
    void pointmult(std::vector<double>& res,
		   std::vector<double> point,
		   std::vector<std::vector<double> > mat);

  public:
    void setScale(std::vector<double>& s);
    void setRotation(std::vector<double>& r);
    void setTranslation(std::vector<double>& tr);

  public:
    void transformation(std::vector<double>& res,
			std::vector<double> vec);
    void transformationInv(std::vector<double>& res,
			   std::vector<double> vec);
    void normalize(std::vector<double>& v);
  };
}

#endif
