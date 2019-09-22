# include <stdio.h>
# include <string.h>
# include "Polynomial.hpp"

using namespace std;

Polynomial p;

vector <double> ans;

inline pair <double, bool> Newton_Algorithm(const Polynomial &p, double x) {
  Polynomial q(p);
  q.diff();
  int times = 0;
  double y = -1e18;
  bool flag = 0;
  while(1) {
    ++ times;
    double qx = q.getfunc(x);
    if(Tools :: checkEq(qx, 0.0, 1e-7)) break;
    y = x - p.getfunc(x) / qx;
    if(Tools :: checkEq(x, y, 1e-7)) {
      flag = 1;
      break;
    }
    x = y;
    if(times > 1000) break;
  }
  if(Tools :: checkEq(p.getfunc(x), 0.0, 1e-7) == false) flag = 0;
  return make_pair(x, flag);
}

int main() {
  string str;
  cin >> str;
  p.set(str);
  for (int i = -1000; i <= 1000; ++ i) {
    pair <double, bool> c = Newton_Algorithm(p, i);
    if(c.second == 0) continue;
    bool flag = 0;
    for (int j = 0; j < ans.size(); ++ j)
      if(Tools :: checkEq(c.first, ans[j], 1e-7)) {
        flag = 1;
        break;
      }
    if(!flag) ans.push_back(c.first);
  }
  
  for (int i = 0; i < ans.size(); ++ i) {
    cout << ans[i];
    if(i != ans.size() - 1) cout << ' ';
  }
  
  return 0;
}
