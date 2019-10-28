# include "std_lib_facilities.h"
# include "Token_Exercise_1.hpp"
# include "Code_Exercise_2.hpp"

using namespace std;

int main() {
  freopen("test.in", "r", stdin);
  bool exercise_1 = false;
  if(exercise_1) {
    string str;
    getline(cin, str);
    TokenParsor parsor;
    parsor.parse(str);
    cout << parsor.getwords() << endl;
    vector < pair <string, int> > freq (parsor.getfreq());
    for (int i = 0; i < 5 && i < freq.size(); ++ i) {
      if(i) cout << " ";
      cout << "(" << freq[i].first << "," << freq[i].second << ")";
    }
    cout << endl;
    
    bool f = 1;
    while(cin >> str) {
      if(!f) cout << " ";
      else f = 0;
      cout << "(" << str << "," << parsor.gettimes(str) << ")"; 
    }
  } else {
    string str;
    CodeParsor parsor;
    while(getline(cin, str)) parsor.parse(str);
    vector < string > words (parsor.countword());
    for (int i = 0; i < words.size(); ++ i) {
      if(i) cout << " ";
      cout << words[i];
    }
  }
  return 0;
}
