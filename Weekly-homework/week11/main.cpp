# include "std_lib_facilities.h"
# include <vector>

using namespace std;

namespace Solver1 {
  int W, n;
  vector <int> w;
  void solve() {
    w.clear();
    cin >> W >> n; 
    for (int i = 0, _w; i < n; ++ i) {
      cin >> _w;
      w.push_back(_w); 
    }
    for (int i = 0; i < n; ++ i) {
      if(w[i] <= 0) {
        cout << "error";
        return ;
      }
    }
    for (int i = 0; i < n; ++ i) {
      if(w[i] > W) {
        cout << "out";
        return ;
      }
    }
    sort(w.begin(), w.end());
    int ans = 0;
    for (int i = n - 1, j = 0; i >= j; -- i) {
      if(i == j) {
        ++ ans;
        break;
      }
      if(w[i] + w[j] <= W) ++ ans, ++ j;
      else ++ ans;
    }
    cout << ans;
  }
}

namespace Solver2 {
  int n;
  vector <int> a;
  void solve() {
    cin >> n; a.resize(n);
    if(n > 100000 || n < 1) {
      cout << "error";
      return ;
    }
    int id = 0, t;
    while(cin >> t) {
      if(id >= n) {
        cout << "error";
        return ;
      }
      a[id] = t;
      ++ id;
    }
    bool spe = 1;
    for (int i = 0; i < n; ++ i) {
      spe &= (a[i] <= 0);
      if(a[i] < -1000 || a[i] > 1000) {
        cout << "error";
        return ;
      }
    }
    if(spe) {
      int mx = -2e9, be = 0;
      for (int i = 0; i < n; ++ i) {
        if(a[i] > mx) {
          mx = a[i];
          be = i;
        }
      }
      cout << mx << ' ' << be + 1 << ' ' << be + 1;
      return ;
    }
    int mx = 0, mxb, mxe;
    int s = 0, bg = 0;
    for (int i = 0; i < n; ++ i) {
      s += a[i];
      if(s < 0) s = 0, bg = i + 1;
      if(s > mx) {
        mx = s;
        mxb = bg;
        mxe = i;
      }
    }
    cout << mx << ' ' << mxb + 1 << ' ' << mxe + 1;
  }
}

namespace Solver3 {
  int n;
  string str, ans;
  vector < vector <int> > way;
  vector < vector <int> > f;
  
  int func(int l, int r) {
    if(l >= r) return 0;
    if(f[l][r] != -1) return f[l][r];
    if(str[l] == str[r]) {
      way[l][r] = 3;
      return f[l][r] = 1 + func(l + 1, r - 1);
    } else {
      int f1 = func(l + 1, r), f2 = func(l, r - 1);
      if(f1 >= f2) {
        way[l][r] = 1;
        return f[l][r] = f1;
      } else {
        way[l][r] = 2;
        return f[l][r] = f2;
      }
    }
  }
  
  string prt(int l, int r) {
    if(l >= r) return "";
    if(way[l][r] == 1) return prt(l + 1, r);
    if(way[l][r] == 2) return prt(l, r - 1);
    return str[l] + prt(l + 1, r - 1) + str[r];
  }
  
  void solve() {
    getline(cin, str);
    n = str.size();
    
    f.resize(n); way.resize(n);
    for (int i = 0; i < n; ++ i) way[i].resize(n), f[i].resize(n);
    for (int i = 0; i < n; ++ i)
      for (int j = 0; j < n; ++ j) way[i][j] = 0, f[i][j] = -1;
    
    func(0, n - 1);
    ans = prt(0, n - 1);
    cout << ans;
  }
}

int main() {
  int exercise = 3;
  
  if(exercise == 1) {
    Solver1 :: solve();
  }
  
  if(exercise == 2) {
    Solver2 :: solve();
  }
  
  if(exercise == 3) {
    Solver3 :: solve();
  }

  return 0;
}
