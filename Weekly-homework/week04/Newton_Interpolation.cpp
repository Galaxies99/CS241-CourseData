# include "std_lib_facilities.h"
# include "Polynomial.hpp"
# include "NewtonInterpolation.hpp"

int n;
vector < pair <double, double> > vec;

int main() {
  cin >> n;
  vec.resize(n);
  NewtonInterpolation solver;
  
  for (int i = 0; i < n; ++ i) {
    cin >> vec[i].first >> vec[i].second;
    solver.insert(vec[i]);
  }
  
  // or
  // solver.initialize(vec);
  
  double x; 
  int times;
  cin >> x >> times;
  cout << solver.getfunc(x, times) << endl;
  return 0;
}
/*
6
0.40 0.41075
0.55 0.57815
0.65 0.69675
0.80 0.88811
0.90 1.02652
1.05 1.25382
*/
