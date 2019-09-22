# include "std_lib_facilities.h"
# include "Polynomial.hpp"

using namespace std;

std :: string str, str1, str2;
Polynomial poly1, poly2;
std :: pair < std :: pair <Polynomial, Polynomial>, bool>  ans;

int main() {
  bool exercise1 = true;
  if(exercise1) {
    getline(cin, str);
    poly1.set(str);
    if(poly1.errorflag == 1) {
      cout << "error\nerror\nerror";
      return 0;
    }
    double x;
    cin >> x;
    double res = poly1.getfunc(x);
    poly1.prt();
    poly1.diff();
    cout << endl; 
    poly1.prt();
    cout << endl;
    if(Tools :: checkEq(res, 0.0, 1e-7)) cout << "0.0000";
    else Tools :: output(res);
  } else {
    getline(cin, str1);
    getline(cin, str2);
    poly1.set(str1);
    poly2.set(str2);
    ans = poly1 / poly2; 
    if(ans.second == false) {
      cout << "error\nerror";
      return 0;
    }
    ans.first.first.prt();
    cout << endl;
    ans.first.second.prt();
  }
  return 0;
}
