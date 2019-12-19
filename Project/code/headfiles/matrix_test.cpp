# include <stdio.h>
# include <string.h>
# include <iostream>
# include "matrix.hpp"
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

const int M = 5e5 + 10;
const int mod = 1e9 + 7;

inline int getint() {
  int x=0, f=1; char ch = getchar();
  while(ch < '0' || ch > '9') {
  	if(ch == '-') f = -1;
	  ch = getchar();
  }
  while(ch >= '0' && ch <= '9') {
  	x = (x<<3) + (x<<1) + ch - '0';
	  ch = getchar();
  }
  return x*f;
}

int n, m;

int main() {
  cin >> n >> m;
  Matrix a(n, m);
  for (int i = 0; i < n; ++ i)
    for (int j = 0; j < m; ++ j) cin >> a(i, j);
  
  Matrix b = a.exp();
  b.output();

  return 0;
}



