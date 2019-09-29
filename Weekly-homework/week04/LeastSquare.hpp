# ifndef _LEAST_SQUARE_HPP_
# define _LEAST_SQUARE_HPP_

# include <vector>
# include "Polynomial.hpp"

class LeastSquare {
  private:
    int n;
    double A, B;
    std :: vector < std :: pair <double, double> > p;
    
  public:
    LeastSquare() = default;
    
    LeastSquare(const std :: vector < std :: pair <double, double> > &_p) {
      initialize(_p);
    }
    
    void initialize(const std :: vector < std :: pair <double, double> > &_p) {
      p = _p; n = p.size();
      double xx = 0, x = 0, xy = 0, y = 0;
      for (int i = 0; i < n; ++ i) {
        xx += p[i].first * p[i].first;
        x += p[i].first;
        xy += p[i].first * p[i].second;
        y += p[i].second;
      }
      if(Tools :: checkEq(xx * n - x * x, 0.0, 1e-8)) throw "error";
      A = (xy * n - x * y) / (xx * n - x * x);
      B = (xx * y - x * xy) / (xx * n - x * x);
    }
    
    void output_poly() {
      if(Tools :: checkEq(A, 0.0, 1e-8) == false) {
        Tools :: output(A);
        std :: cout << 'x';
        if(Tools :: checkEq(B, 0.0, 1e-8) == false) {
          if(B > 0) std :: cout << '+';
          Tools :: output(B);
        }
      } else {
        if(Tools :: checkEq(B, 0.0, 1e-8) == false) Tools :: output(B);
        else std :: cout << "0.0000";
      }
    }
    
    double getfunc(double x) {
      return A * x + B;
    }
    
    ~ LeastSquare() = default;
};

# endif 
