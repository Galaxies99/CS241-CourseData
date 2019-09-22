# include <vector>
# include <stdio.h>
# include <string.h>
# include <iostream>
# include "Polynomial.hpp"

using namespace std;

int n, m;
vector < vector <double> > A;
vector <double> B;

// Solve Equation A * x = B
pair < vector <double>, int > Gauss_Algorithm(const vector < vector <double> > &a, const vector <double> &b) {
  vector < vector <double> > A(a);
  vector <double> B(b);
  vector <double> res;
  if(a.size() != b.size()) throw "size error!";
  
  bool flag = 0;
  res.resize(m);
  for (int i = 0; i < m; ++ i) {
    if(i >= n) break;
    int pos = -1;
    for (int j = i; j < n; ++ j)
      if(! Tools :: checkEq(A[j][i], 0.0, 1e-7)) { pos = j; break; }
    if(pos == -1) {
      flag = 1;
      continue;
    }
    
    for (int j = 0; j < m; ++ j) swap(A[i][j], A[pos][j]);
    swap(B[i], B[pos]);
    
    for (int j = i + 1; j < n; ++ j) {
      double c = A[j][i] / A[i][i];
      for (int k = 0; k < m; ++ k) A[j][k] = A[j][k] - c * A[i][k];
      B[j] = B[j] - c * B[i];
    }
  }
  
  for (int i = 0; i < n; ++ i) {
    bool no = 1;
    for (int j = 0; j < m; ++ j)
      no &= (Tools :: checkEq(A[i][j], 0.0, 1e-7));
    no &= (Tools :: checkEq(B[i], 0.0, 1e-7) ^ 1);
    if(no) return make_pair(res, -1);
  }
  
  if(flag || m > n) return make_pair(res, 1);
  
  if(m < n) {
    for (int i = m; i < n; ++ i) {
      for (int j = 0; j < m; ++ j)
        if(! Tools :: checkEq(A[i][j], 0.0, 1e-7)) return make_pair(res, -1);
      if(! Tools :: checkEq(B[i], 0.0, 1e-7)) return make_pair(res, -1);
    }
  }
  
  for (int i = m - 1; ~i; -- i) {
    res[i] = B[i] / A[i][i];
    for (int j = 0; j < i; ++ j) 
      B[j] = B[j] - A[j][i] * res[i];
  }
  
  return make_pair(res, 0);
}

int main() {
  cin >> n >> m;
  A.resize(n); B.resize(n);
  for (int i = 0; i < n; ++ i) A[i].resize(m);
  for (int i = 0; i < n; ++ i) {
    for (int j = 0; j < m; ++ j) cin >> A[i][j];
    cin >> B[i];
  }
  
  pair < vector <double>, int > ans(Gauss_Algorithm(A, B));
  
  if(ans.second == -1) printf("No solution!");
  else if(ans.second == 1) printf("Multiple solutions!");
  else {
    printf("Only one solution: ");
    for (int i = 0; i < m; ++ i) {
      cout << ans.first[i];
      if(i != m-1) cout << ' ';
    }
  }
  
  return 0;
}



