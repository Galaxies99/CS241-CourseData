# ifndef _LINEAR_EQUATIONS_H_
# define _LINEAR_EQUATIONS_H_ 

# include <iostream>
# include <vector>
# include <string.h>
# include "Polynomial.hpp"

using namespace std;

pair < vector <double>, int > Gauss_Algorithm(const vector < vector <double> > &a, const vector <double> &b) {
  vector < vector <double> > A(a);
  vector <double> B(b);
  vector <double> res;
  if(a.size() != b.size()) throw "size error!";
  
  int n, m;
  n = A.size();
  m = A[0].size();
  
  bool flag = 0;
  res.resize(m);
  for (int i = 0; i < m; ++ i) {
    if(i >= n) break;
    int pos = -1;
    for (int j = i; j < n; ++ j)
      if(! Tools :: checkEq(A[j][i], 0.0, 1e-9)) { pos = j; break; }
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
      no &= (Tools :: checkEq(A[i][j], 0.0, 1e-9));
    no &= (Tools :: checkEq(B[i], 0.0, 1e-9) ^ 1);
    if(no) return make_pair(res, -1);
  }
  
  if(flag || m > n) return make_pair(res, 1);
  
  
  if(m < n) {
    for (int i = m; i < n; ++ i) {
      for (int j = 0; j < m; ++ j)
        if(! Tools :: checkEq(A[i][j], 0.0, 1e-9)) return make_pair(res, -1);
      if(! Tools :: checkEq(B[i], 0.0, 1e-9)) return make_pair(res, -1);
    }
  }
  
  for (int i = m - 1; ~i; -- i) {
    res[i] = B[i] / A[i][i];
    for (int j = 0; j < i; ++ j) 
      B[j] = B[j] - A[j][i] * res[i];
  }
  
  return make_pair(res, 0);
}


class LinearEquation {
    vector < vector <double> > A;
    vector < double > B;
    bool app[110];
    
    void add_into_equations(const vector < pair <int, double> > &_vec) {
      double b = 0.0;
      vector < pair <int, double> > vec(_vec);
      for (int i = 0; i < vec.size(); ++ i) {
        if(vec[i].first == 0) {
          b = b - vec[i].second;
          if(i != vec.size() - 1) swap(vec[i], vec[vec.size() - 1]);
          vec.pop_back();
          -- i;
        } else app[vec[i].first] = 1;
      }
      vector <double> tem;
      tem.resize(101);
      for (int i = 0; i < 101; ++ i) tem[i] = 0;
      for (int i = 0; i < vec.size(); ++ i) tem[vec[i].first] += vec[i].second;
      A.push_back(tem);
      B.push_back(b);
    }
    
    void refresh() {
      for (int i = 0; i < A[0].size(); ++ i) {
        bool flag = 1;
        for (int j = 0; j < A.size(); ++ j) 
          if(Tools :: checkEq(A[j][i], 0.0, 1e-9) == false) {
            flag = 0;
            break;
          }
        if(flag) {
          for (int k = 0; k < A.size(); ++ k) {
            for (int j = i+1; j < A[k].size(); ++ j)
              A[k][j - 1] = A[k][j];
            A[k].pop_back();
          }
          -- i;
        }
      } 
    }
  
  public:
    LinearEquation() = default;
    
    void start() {
      memset(app, 0, sizeof app);
      bool errorflag = 0;
      
      vector < pair <int, double> > tem;
      int right;
      string str;
      while(getline(cin, str)) { 
        if(str == "-") break;
        tem.clear();
        double cur = 0, base = 1.0;
        bool flag = (str[0] == '-');
        int r = 0;
        bool eq = 0;
        
        for (int i = flag; i < str.length(); ++ i) {
          if ('0' <= str[i] && str[i] <= '9') {
            int ps = (str[i] - '0');
            if(base == 1.0) cur = cur * 10 + ps;
            else {
              cur = cur + base * ps;
              base = base * 0.1;
            }
          } else if(str[i] == '.') {
            if(base != 1.0) errorflag = 1; 
            base = 0.1;
          } else if(str[i] == 'x') {
            if(i == 0 || str[i-1] == '+' || str[i-1] == '-' || str[i-1] == '=') cur = 1.0;
            if(i + 1 < str.length() && str[i + 1] == '_') {
              int j = i + 1;
              if(j + 1 == str.length() || !isdigit(str[j + 1])) errorflag = 1;
              else {
                while(j + 1 < str.length() && '0' <= str[j+1] && str[j+1] <= '9') {
                  ++ j;
                  r = r * 10 + (str[j] - '0');
                }
                if(j + 1 < str.length() && str[j+1] != '+' && str[j+1] != '-' && str[j+1] != '=') errorflag = 1;
                if(r > 100) errorflag = 1;
                i = j;
              } 
            } else errorflag = 1;
          } else if(str[i] == '+') {
            if(i && !isdigit(str[i-1])) errorflag = 1;
            else {
              if(flag) cur = -cur;
              if(eq) cur = -cur;
              tem.push_back(std :: make_pair(r, cur));
              flag = 0; cur = 0; base = 1.0; r = 0;
            }
          } else if(str[i] == '-') {
            if(i && str[i-1] == '=') flag = 1;
            else {
              if(i && !isdigit(str[i-1])) errorflag = 1;
              else {
                if(flag) cur = -cur;
                if(eq) cur = -cur;
                tem.push_back(std :: make_pair(r, cur));
                flag = 1; cur = 0; base = 1.0; r = 0;
              }
            } 
          } else if(str[i] == '=') {
            if(i && !isdigit(str[i-1])) errorflag = 1;
            else {
              if(flag) cur = -cur;
              if(eq) cur = -cur;
              tem.push_back(std :: make_pair(r, cur));
              flag = 0; cur = 0; base = 1.0; r = 0;
            }
            eq = 1;
          } else errorflag = 1;
          if(errorflag) break;
        }
        if(errorflag) break;
        if(flag) cur = -cur;
        if(eq) cur = -cur;
        tem.push_back(std :: make_pair(r, cur));
        add_into_equations(tem);
      }  
      if(errorflag) cout << "error"; 
      else refresh(), gauss();
    }
    
    void gauss() {
      /*
      for (int i = 0; i < A.size(); ++ i) {
        for (int j = 0; j < A[i].size(); ++ j) cout << A[i][j] << ' ';
        cout << "= " << B[i] << endl;
      }
      */
      try { 
        pair < vector <double>, int > ans(Gauss_Algorithm(A, B));
        if(ans.second != 0) cout << "error";
        else {
          int tot = 0;
          for (int i = 1; i <= 100; ++ i) tot += app[i];
          if(tot != ans.first.size()) cout << "error";
          else {
            for (int i = 0; i < ans.first.size(); ++ i) {
              if(i != 0) cout << " ";
              if(Tools :: output(ans.first[i]) == false) cout << "0.0000";
            }
          }
        }
      } catch(...) {
        cout << "error";
      } 
    }
    
    ~ LinearEquation() = default;
};

# endif 
