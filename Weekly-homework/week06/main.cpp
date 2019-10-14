# include <vector>
# include <iostream>
# include "std_lib_facilities.h"
# include "NodeRecognition.hpp"

using namespace std;

LineParsor lp;

string str;
vector < pair <int, int> > v;

int main() {
  getline(cin, str);
  v = lp.parse(str);
  GraphParsor g(v);
  g.output(cout);
  return 0;
}
