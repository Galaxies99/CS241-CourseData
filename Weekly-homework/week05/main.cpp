# include "std_lib_facilities.h"
# include <cctype>
# include <cmath>

int n;
vector < pair <double, double> > vec;

namespace Tools {
  inline double Abs(double x) {
    return x >= 0 ? x : -x;
  } 
  inline bool checkEq(double x, double y, double eps) {
    return Abs(x - y) < eps;
  }
  inline bool output(double p) {
	if(p > 0) p += 0.000001;
	else p -= 0.000001;
    std :: string out = ""; 
    int pc = p * 10000, z = p;
    if(pc == 0) return false;
    if(p < 0) {
      z = -z; pc = -pc;
      out = out + "-";
    }
    out = out + std :: to_string(z) + ".";
    pc -= z * 10000;
    if(pc < 10) out = out + "000";
    else if(pc < 100) out = out + "00";
    else if(pc < 1000) out = out + "0";
    out = out + std :: to_string(pc);
    std :: cout << out;
    return true;
  }
}

namespace Parse {
  void onedouble(const string &str, double &x) {
    bool f = 0; x = 0;
    int beg;
    if(str[0] == '-') f = 1;
    beg = f;
    double bse = 1.0;
    while(beg < str.size() && isdigit(str[beg]) || str[beg] == '.') {
      if(str[beg] == '.') {
        if(bse != 1.0) throw 233;
        else bse = 0.1;
      } else {
        if(bse != 1.0) {
          x = x + bse * (str[beg] - '0');
          bse *= 0.1;
        } else x = x * 10 + (str[beg] - '0');
      }
      ++ beg;
    }
    if(beg == f) throw 233;
    if(beg != str.size()) throw 233;
    if(f) x = -x;
  }
  void twodouble(const string &str, double &x, double &y) {
    bool f = 0; x = 0; y = 0;
    int beg;
    if(str[0] == '-') f = 1;
    beg = f;
    double bse = 1.0;
    while(beg < str.size() && isdigit(str[beg]) || str[beg] == '.') {
      if(str[beg] == '.') {
        if(bse != 1.0) throw 233;
        else bse = 0.1;
      } else {
        if(bse != 1.0) {
          x = x + bse * (str[beg] - '0');
          bse *= 0.1;
        } else x = x * 10 + (str[beg] - '0');
      }
      ++ beg;
    }
    if(beg == f) throw 233;
    if(f) x = -x;
    
    if(str[beg] != ' ') throw 233;
    ++ beg; f = 0; bse = 1.0;
    if(str[beg] == '-') f = 1, ++ beg;
    int lst = beg;
    
    while(beg < str.size() && isdigit(str[beg]) || str[beg] == '.') {
      if(str[beg] == '.') {
        if(bse != 1.0) throw 233;
        else bse = 0.1;
      } else {
        if(bse != 1.0) {
          y = y + bse * (str[beg] - '0');
          bse *= 0.1;
        } else y = y * 10 + (str[beg] - '0');
      }
      ++ beg;
    }
    if(beg == lst) throw 233;
    if(beg != str.size()) throw 233;
    if(f) y = -y;
  }
} 

class LeastSquare {
  private:
    int n;
    double A, B;
    double r;
    std :: vector < std :: pair <double, double> > p;
    
  public:
    LeastSquare() = default;
    
    LeastSquare(const std :: vector < std :: pair <double, double> > &_p) {
      initialize(_p);
    }
    
    void initialize(const std :: vector < std :: pair <double, double> > &_p) {
      p = _p; n = p.size();
      double xx = 0, x = 0, xy = 0, y = 0, ru = 0, rd1 = 0, rd2 = 0, rd;
      for (int i = 0; i < n; ++ i) {
        xx += p[i].first * p[i].first;
        x += p[i].first;
        xy += p[i].first * p[i].second;
        y += p[i].second;
      }
      double xbar = x / n, ybar = y / n;
      for (int i = 0; i < n; ++ i) {
        ru += (p[i].first - xbar) * (p[i].second - ybar);
        rd1 += (p[i].first - xbar) * (p[i].first - xbar);
        rd2 += (p[i].second - ybar) * (p[i].second - ybar);
      }
      rd = sqrt(rd1 * rd2);
      r = ru / rd;
      if(Tools :: Abs(r) < 0.75) throw "error";
      if(Tools :: checkEq(xx * n - x * x, 0.0, 1e-8)) throw "error";
      A = (xy * n - x * y) / (xx * n - x * x);
      B = (xx * y - x * xy) / (xx * n - x * x);
    }
    
    void output_r() {
      if(Tools :: output(r) == false) cout << "0.0000";
    }
    
    void output_poly() {
      if(Tools :: checkEq(A, 0.0, 1e-8) == false) {
        Tools :: output(A);
        std :: cout << "*x";
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

int main() {
  string str;
  double x;
  getline(cin, str);
  try {
    Parse :: onedouble(str, x);
  } catch(...) {
    cout << "error\nerror\nerror";
    return 0;
  }
  
  pair <double, double> p;
  
  LeastSquare solver;
  
  while(getline(cin, str)) {
    try {
      Parse :: twodouble(str, p.first, p.second);
    } catch(...) {
      cout << "error\nerror\nerror";
      return 0;
    }
    vec.push_back(p);
  }

  if(vec.size() < 2) { 
    cout << "error\nerror\nerror";
    return 0;
  }
  
  try {
    solver.initialize(vec);
  } catch(...) {
	  solver.output_r();
    cout << "\nerror\nerror";
    return 0;
  }
  
  double ans = solver.getfunc(x);
  solver.output_r(); cout << endl;
  cout << "y=";
  solver.output_poly(); cout << endl;
  if(Tools :: output(ans) == false) cout << "0.0000";
  return 0;
}
