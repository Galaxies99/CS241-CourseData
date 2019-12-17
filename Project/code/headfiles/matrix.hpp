# ifndef _MATRIX_HPP_
# define _MATRIX_HPP_

# include "exceptions.hpp"

# include <vector>

using std :: vector;

class Matrix {
    friend Matrix operator + (const Matrix &a, const Matrix &b);
    friend Matrix operator * (const Matrix &a, const Matrix &b);
    friend Matrix operator ^ (const Matrix &a, int b);
  private:
    int n, m;
    vector <vector <double> > p;
  
  public:
    Matrix(int n = 0, int m = 0) : n(n), m(m) {
      p.clear();
      if(n) {
        p.resize(n);
        for (int i = 0; i < n; ++ i)
          if(m) p[i].resize(m);
      }
      for (int i = 0; i < n; ++ i) 
        for (int j = 0; j < m; ++ j)
          p[i][j] = 0; 
    }
    
    void set_zero() {
      for (int i = 0; i < n; ++ i)
        for (int j = 0; j < m; ++ j) p[i][j] = 0;
    }
    
    void set_identity() {
      if(n != m) throw Matrix_Error();
      set_zero();
      for (int i = 0; i < n; ++ i) p[i][i] = 1;
    } 
    
    Matrix traverse() const {
      Matrix ret(a.m, a.n);
      for (int i = 0; i < ret.n; ++ i)
        for (int j = 0; j < ret.m; ++ j)
          ret(i, j) = p[j][i];
      return ret;
    }
    
    int get_n() const { return n; }
    int get_m() const { return m; }
    
    double operator() (const int &i, const int &j) const {
      if (i >= n || i < 0 || j >= m || j < 0) throw Matrix_Error();
      return p[i][j];
    }
    
    double& operator() (const int &i, const int &j) {
      if (i >= n || i < 0 || j >= m || j < 0) throw Matrix_Error();
      return p[i][j];
    }
    
    ~ Matrix() = default;
};

Matrix operator + (const Matrix &a, const Matrix &b) {
  if(a.n != b.n || a.m != b.m) throw Matrix_Error();
  Matrix ret(a.n, a.m);
  for (int i = 0; i < a.n; ++ i)
    for (int j = 0; j < a.m; ++ j)
      ret(i, j) = a(i, j) + b(i, j);
  return ret;
}

Matrix operator * (const Matrix &a, const Matrix &b) {
  if(a.m != b.n) throw Matrix_Error();
  Matrix ret(a.n, b.m);
  for (int i = 0; i < ret.n; ++ i)
    for (int j = 0; j < ret.m; ++ j)
      for (int k = 0; k < a.m; ++ k)
        ret(i, j) = ret(i, j) + a(i, k) * b(k, j);
  return ret; 
}

Matrix operator ^ (const Matrix &a, int b) {
  if(b < 0 || a.n != a.m) throw Matrix_Error();
  Matrix ret(a.n, a.m); ret.set_identity();
  while(b) {
    if(b & 1) ret = ret * a;
    a = a * a;
    b >>= 1;
  }
  return ret;
}

# endif 
