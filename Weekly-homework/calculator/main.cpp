# include <bits/stdc++.h>
# include "number.hpp"
# include "expression.hpp"
 
using namespace std;

int main() {
  string str;
  cin >> str;
  Expression expr(str);
  expr.output(cout);
  return 0;
}



