# include <bits/stdc++.h>
# include "number.hpp"
# include "expression.hpp"
 
using namespace std;

int main() {
  string str;
  cin >> str;
  try {
    Expression expr(str);
    expr.output(cout);
  } catch(...) {
    cerr << "Expression Error!\n";
  }
  return 0;
}



