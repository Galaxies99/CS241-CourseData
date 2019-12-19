# ifndef _MATRIX_HPP_
# define _MATRIX_HPP_

# include "exceptions.hpp"

# include <vector>
# include <iostream>

using std :: cout;
using std :: swap;
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
    
    Matrix(const Matrix &rhs) {
      n = rhs.n; m = rhs.m;
      p.clear();
      if(n) {
        p.resize(n);
        for (int i = 0; i < n; ++ i)
          if(m) p[i].resize(m);
      }
      for (int i = 0; i < n; ++ i) 
        for (int j = 0; j < m; ++ j)
          p[i][j] = rhs(i, j);
    }
    
    Matrix& operator =(const Matrix &rhs) {
      n = rhs.n; m = rhs.m;
      p.clear();
      if(n) {
        p.resize(n);
        for (int i = 0; i < n; ++ i)
          if(m) p[i].resize(m);
      }
      for (int i = 0; i < n; ++ i) 
        for (int j = 0; j < m; ++ j)
          p[i][j] = rhs(i, j);
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
    
    void output() const;
    Matrix traverse() const;
    Matrix inverse() const;
    
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

void Matrix :: output() const {
  for (int i = 0; i < n; ++ i, cout << '\n')
    for (int j = 0; j < m; ++ j) cout << p[i][j] << ", ";
}

Matrix Matrix :: traverse() const {
  Matrix ret(m, n);
    for (int i = 0; i < ret.n; ++ i)
      for (int j = 0; j < ret.m; ++ j)
        ret(i, j) = p[j][i];
  return ret;
}

Matrix Matrix :: inverse() const {
  Matrix a(*this);
  if(n != m) throw Matrix_Error();
  Matrix ret(n, n);
  ret.set_identity();
  for (int i = 0; i < n; ++ i) {
    int pos = i;
    for (; pos < n; ++ pos) 
      if(a(pos, i) != 0) break;
    if(pos == n) throw Matrix_Error();
    if(pos != i) {
      for (int j = 0; j < n; ++ j) {
        swap(a(pos, j), a(i, j));
        swap(ret(pos, j), ret(i, j));
      }
    }
    for (int j = i + 1; j < n; ++ j) {
      double c = - a(j, i) / a(i, i);
      for (int k = 0; k < n; ++ k) 
        ret(j, k) = ret(j, k) + c * ret(i, k);
      for (int k = i; k < n; ++ k) 
        a(j, k) = a(j, k) + c * a(i, k);
    }
  }
  
  for (int i = n - 1; ~i; -- i) {
    for (int j = i + 1; j < n; ++ j) {
      for (int k = 0; k < n; ++ k)
        ret(i, k) = ret(i, k) - a(i, j) * ret(j, k);
      a(i, j) = 0;
    }
    
    for (int k = 0; k < n; ++ k)
      ret(i, k) = ret(i, k) / a(i, i);
    
    a(i, i) = 1;
  }
  return ret;
}

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

Matrix operator ^ (const Matrix &_a, int b) {
  if(b < 0 || _a.n != _a.m) throw Matrix_Error();
  Matrix a(_a), ret(_a.n, _a.m); ret.set_identity();
  while(b) {
    if(b & 1) ret = ret * a;
    a = a * a;
    b >>= 1;
  }
  return ret;
}

# endif 
