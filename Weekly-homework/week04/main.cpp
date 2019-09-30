# include "std_lib_facilities.h"
# include "Interpolation.hpp"
# include <cctype>

int n;
vector < pair <double, double> > vec;

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

int main() {
  freopen("test.in","r",stdin);
  string str;
  double x;
  getline(cin, str);
  try {
    Parse :: onedouble(str, x);
  } catch(...) {
    cout << "error";
    return 0;
  }
  
  pair <double, double> p;
  
  NewtonInterpolation solver;
  
  while(getline(cin, str)) {
    try {
      Parse :: twodouble(str, p.first, p.second);
    } catch(...) {
      cout << "error";
      return 0;
    }
    vec.push_back(p);
  }
  
  sort(vec.begin(), vec.end());
  
  for (int i = 0; i < vec.size() - 1; ++ i) 
    if(Tools :: checkEq(vec[i + 1].first - vec[i].first, vec[1].first - vec[0].first, 1e-8) == false) {
      cout << "error";
      return 0;
    }
  
  solver.initialize_same(vec);
  
  double ans = solver.getfunc(x);
  if(Tools :: checkEq(ans, 0.0, 1e-5)) cout << "0.0000";
  else printf("%.4lf", ans - 0.00001);
//  if(Tools :: output(ans) == false) cout << "0.0000";
  return 0;
}
