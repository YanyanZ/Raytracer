#ifndef SOLVER_HPP
# define SOLVER_HPP

# define EPSILON 1.0e-10
# define COEFF_LIMIT 1.0e-16

# define FUDGE_FACTOR1 1.0e12
# define FUDGE_FACTOR2 -1.0e-5
# define FUDGE_FACTOR3 1.0e-7

# define TWO_PI 6.283185207179586476925286766560
# define TWO_PI_3 2.0943951023931954923084
# define TWO_PI_43 4.1887902047863909846168
# define MAX_ITERATIONS 50
# define MAXPOW 32

namespace Tools
{
  class PolynomialSolver
  {
  private:
    int n;
    std::vector<double> coef;

  public:
    PolynomialSolver(void);
    PolynomialSolver(const double& a6,
		     const double& a5,
		     const double& a4,
		     const double& a3,
		     const double& a2,
		     const double& a1,
		     const double& a0);
    PolynomialSolver(const double& a,
		     const double& b,
		     const double& c,
		     const double& d,
		     const double& e);
    PolynomialSolver(const double& a,
		     const double& b,
		     const double& c,
		     const double& d);
    PolynomialSolver(const double& a,
		     const double& b,
		     const double& c);
    PolynomialSolver(const double& a,
		     const double& b);
    PolynomialSolver(const double& a);

  public:
    ~PolynomialSolver(void);

  public:
    double& operator[] (int i);
    PolynomialSolver operator+() const;
    PolynomialSolver operator-() const;
    PolynomialSolver& operator+=(const PolynomialSolver& p);
    PolynomialSolver& operator-=(const PolynomialSolver& p);
    PolynomialSolver& operator*=(const PolynomialSolver& p);
    PolynomialSolver& operator*=(const double& c);
    PolynomialSolver& operator/=(const double& c);

  public:
    friend PolynomialSolver operator+(const PolynomialSolver& p1,
				      const PolynomialSolver& p2);
    friend PolynomialSolver operator-(const PolynomialSolver& p1,
				      const PolynomialSolver& p2);
    friend PolynomialSolver operator*(const PolynomialSolver& p1,
				      const PolynomialSolver& p2);
    friend PolynomialSolver operator*(const PolynomialSolver& p,
				      const double& c);
    friend PolynomialSolver operator*(const double& c,
				      const PolynomialSolver& p);
    friend PolynomialSolver operator/(const PolynomialSolver& p,
				      const double& c);

  public:
    double eval(const double& c);
    int solveQuadratic(double& c1, double& c2);
    int solveQuadratic(std::vector<double>& c);
    int solveCubic(std::vector<double>& c);
    int solveQuartic(std::vector<double>& c);
    int solve(std::vector<double>& c);

  public:
    int degree(void);
    void check(void);
  };
}

#endif
