# include "std_lib_facilities.h"
# include "Polynomial.hpp"
# include "LinearEquations.hpp"

using namespace std;

double Newton_Algorithm(const Polynomial &p, double x) {
  Polynomial q(p);
  q.diff();
  int times = 0;
  double y;
  while(1) {
    ++ times;
	  if(Tools :: checkEq(q.getfunc(x), 0.0, 1e-9)) break;
    y = x - p.getfunc(x) / q.getfunc(x);
    if(Tools :: checkEq(x, y, 1e-5)) break;
    x = y;
  }
  return y;
}

int main() {
  bool exercise1 = false;
  if(exercise1)    {
    string str;    
    Polynomial p, q;
    double a, b;
    bool error = 0;
           
    getline(cin, str);    
    p.set(str); q.set(str); 
	
    if(p.errorflag == 1) {
      cout << "error";
      return 0;
    }
    q.diff();
    
    Polynomial r(q); r.diff();
    cin >> a >> b; 
    double fa = p.getfunc(a), fb = p.getfunc(b);
    if(fa * fb >= 0) error = 1;
    if(a > b) error = 1;
    for (double i = a; i <= b; i += 0.1) {
      double c = q.getfunc(i);
      if(Tools :: checkEq(c, 0.0, 1e-9)) error = 1;
    }
    double tem = r.getfunc((a + b) / 2);
    for (double i = a + 0.1; i <= b - 0.1; i += 0.1) 
      if(r.getfunc(i) * tem < 0) error = 1;
    if(error) cout << "error";
    else {
      double ans = Newton_Algorithm(p, b);
      cout<< setiosflags(ios :: fixed) << setprecision(4) << ans;
    } 
  } else {
    LinearEquation solver;
    solver.start(); 
  }
  return 0;
}


