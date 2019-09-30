# include "std_lib_facilities.h"
# include "LeastSquare.hpp"

int n;
vector < pair <double, double> > vec; 

int main() {
  cin >> n; vec.resize(n);
  for (int i = 0; i < n; ++ i) cin >> vec[i].first >> vec[i].second;
  
  LeastSquare solver(vec);
  solver.output_poly(); cout << endl;
  
  double x;
  cin >> x; 
  cout << solver.getfunc(x) << endl;
  return 0;  
} 
