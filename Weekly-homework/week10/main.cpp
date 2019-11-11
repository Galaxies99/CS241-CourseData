# include "std_lib_facilities.h"
# include "HuffmanCode.hpp"
# include "HuffmanWordCode.hpp" 

using namespace std;

int main() {
  bool exercise1 = false;
  if(exercise1) {
    string str = "", strr;
    while(getline(cin, strr)) {
      if(str != "") str += '\n';
      str = str + strr;
    }
    HuffmanCode solver(str);
    cout << solver.HuffmanLength();
  } else {
    string str = "", strr;
    while(getline(cin, strr)) {
      if(str != "") str += '\n';
      str = str + strr;
    }
    HuffmanWordCode solver(str);
    cout << solver.HuffmanLength();
  }
  return 0;  
}
