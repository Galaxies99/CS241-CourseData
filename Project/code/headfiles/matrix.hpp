# ifndef _MATRIX_HPP_
# define _MATRIX_HPP_

# include "exceptions.hpp"
# include "random.hpp"

# include <math.h>
# include <vector>
# include <iostream>

using std :: cout;
using std :: swap;
using std :: vector;

class Matrix {
    friend Matrix operator + (double a, const Matrix &b);
    friend Matrix operator + (const Matrix &a, double b);
    friend Matrix operator + (const Matrix &a, const Matrix &b);
    friend Matrix operator - (const Matrix &a);
    friend Matrix operator - (double a, const Matrix &b);
    friend Matrix operator - (const Matrix &a, double b);
    friend Matrix operator - (const Matrix &a, const Matrix &b);
    friend Matrix operator * (double a, const Matrix &b);
    friend Matrix operator * (const Matrix &a, double b);
    friend Matrix operator * (const Matrix &a, const Matrix &b);
    friend Matrix operator / (double a, const Matrix &b);
    friend Matrix operator / (const Matrix &a, double b);
    friend Matrix operator / (const Matrix &a, const Matrix &b);
    friend Matrix operator ^ (const Matrix &a, int b);
    friend Matrix inverse(const Matrix &a);
    friend Matrix transposition(const Matrix &a);
    friend Matrix exp(const Matrix &a);
    friend Matrix mul(const Matrix &a, const Matrix &b);
    friend Matrix pow(const Matrix &a, double b);
    friend double sum(const Matrix &a);
        
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
      set_zero();
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
    
    void set_all(double x) {
      for (int i = 0; i < n; ++ i)
        for (int j = 0; j < m; ++ j) p[i][j] = x;
    }
    
    void set_identity() {
      if(n != m) throw Matrix_Error();
      set_zero();
      for (int i = 0; i < n; ++ i) p[i][i] = 1;
    } 
    
    void set_uniform_random(double x = 0.0, double y = 1.0) {
      for (int i = 0; i < n; ++ i)
        for (int j = 0; j < m; ++ j) p[i][j] = simple_random :: uniform_random(x, y);
    }
    
    void set_guassian_random(double x = 0.0, double y = 1.0) {
      for (int i = 0; i < n; ++ i)
        for (int j = 0; j < m; ++ j) p[i][j] = simple_random :: guassian_random(x, y);
    }
    
    void output() const;

    double sum() const {
      double ret = 0.0;
      for (int i = 0; i < n; ++ i)
        for (int j = 0; j < m; ++ j) ret += p[i][j];
      return ret;
    }
    
    bool empty() const { return n == 0 || m == 0; }
    
    Matrix transposition() const;
    Matrix inverse() const;
    Matrix exp() const;
    Matrix mul(const Matrix &b) const;
    Matrix pow(double b) const;
    
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

double sum(const Matrix &a) {
  return a.sum();
}

void Matrix :: output() const {
  for (int i = 0; i < n; ++ i, cout << '\n')
    for (int j = 0; j < m; ++ j) cout << p[i][j] << ", ";
}

Matrix transposition(const Matrix &a) {
  return a.transposition();
}

Matrix Matrix :: transposition() const {
  Matrix ret(m, n);
    for (int i = 0; i < ret.n; ++ i)
      for (int j = 0; j < ret.m; ++ j)
        ret(i, j) = p[j][i];
  return ret;
}

Matrix inverse(const Matrix &a) {
  return a.inverse();
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

Matrix exp(const Matrix &a) {
  return a.exp();
}

Matrix Matrix :: exp() const {
  Matrix ret(*this);
  for (int i = 0; i < n; ++ i)
    for (int j = 0; j < m; ++ j)
      ret(i, j) = :: exp(ret(i, j));
  return ret;
}

Matrix mul(const Matrix &a, const Matrix &b) {
  return a.mul(b);
}

Matrix Matrix :: mul(const Matrix &b) const {
  if(n != b.get_n() || m != b.get_m()) throw Matrix_Error();
  Matrix ret(n, m);
  for (int i = 0; i < n; ++ i)
    for (int j = 0; j < m; ++ j)
      ret(i, j) = p[i][j] * b(i, j);
  return ret;
}

Matrix pow(const Matrix &a, double b) {
  return a.pow(b);
}

Matrix Matrix :: pow(double b) const {
  Matrix ret(*this);
  for (int i = 0; i < n; ++ i)
    for (int j = 0; j < m; ++ j)
      ret(i, j) = :: pow(p[i][j], b);
  return ret;
}

Matrix operator + (double a, const Matrix &b) {
  Matrix ret(b.n, b.m);
  for (int i = 0; i < ret.n; ++ i)
    for (int j = 0; j < ret.m; ++ j)
      ret(i, j) = a + b(i, j);
  return ret;
}

Matrix operator + (const Matrix &a, double b) {
  Matrix ret(a.n, a.m);
  for (int i = 0; i < ret.n; ++ i)
    for (int j = 0; j < ret.m; ++ j)
      ret(i, j) = a(i, j) + b;
  return ret;
}

Matrix operator + (const Matrix &a, const Matrix &b) {
  if(a.n != b.n || a.m != b.m) throw Matrix_Error();
  Matrix ret(a.n, a.m);
  for (int i = 0; i < ret.n; ++ i)
    for (int j = 0; j < ret.m; ++ j)
      ret(i, j) = a(i, j) + b(i, j);
  return ret;
}

Matrix operator - (const Matrix &a) {
  return 0.0 - a;
}

Matrix operator - (double a, const Matrix &b) {
  Matrix ret(b.n, b.m);
  for (int i = 0; i < ret.n; ++ i)
    for (int j = 0; j < ret.m; ++ j)
      ret(i, j) = a - b(i, j);
  return ret;
}

Matrix operator - (const Matrix &a, double b) {
  Matrix ret(a.n, a.m);
  for (int i = 0; i < ret.n; ++ i)
    for (int j = 0; j < ret.m; ++ j)
      ret(i, j) = a(i, j) - b;
  return ret;
}

Matrix operator - (const Matrix &a, const Matrix &b) {
  if(a.n != b.n || a.m != b.m) throw Matrix_Error();
  Matrix ret(a.n, a.m);
  for (int i = 0; i < ret.n; ++ i)
    for (int j = 0; j < ret.m; ++ j)
      ret(i, j) = a(i, j) - b(i, j);
  return ret;
}

Matrix operator * (double a, const Matrix &b) {
  Matrix ret(b.n, b.m);
  for (int i = 0; i < ret.n; ++ i)
    for (int j = 0; j < ret.m; ++ j)
      ret(i, j) = a * b(i, j);
  return ret; 
}

Matrix operator * (const Matrix &a, double b) {
  Matrix ret(a.n, a.m);
  for (int i = 0; i < ret.n; ++ i)
    for (int j = 0; j < ret.m; ++ j)
      ret(i, j) = a(i, j) * b;
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

Matrix operator / (double a, const Matrix &b) {
  Matrix ret(b.n, b.m);
  for (int i = 0; i < ret.n; ++ i)
    for (int j = 0; j < ret.m; ++ j)
      if(b(i, j) == 0) throw Matrix_Error();
      else ret(i, j) = a / b(i, j);
  return ret;
}

Matrix operator / (const Matrix &a, double b) {
  Matrix ret(a.n, a.m);
  if(b == 0) throw Matrix_Error();
  for (int i = 0; i < ret.n; ++ i)
    for (int j = 0; j < ret.m; ++ j)
      ret(i, j) = a(i, j) / b;
  return ret;
}

Matrix operator / (const Matrix &a, const Matrix &b) {
  if(a.n != b.n || a.m != b.m) throw Matrix_Error();
  Matrix ret(a.n, a.m);
  for (int i = 0; i < ret.n; ++ i)
    for (int j = 0; j < ret.m; ++ j)
      if(b(i, j) == 0) throw Matrix_Error();
      else ret(i, j) = a(i, j) / b(i, j);
  return ret;
}

Matrix operator ^ (const Matrix &_a, int b) {
  if(b < -1 || _a.n != _a.m) throw Matrix_Error();
  if(b == -1) return _a.inverse();
  Matrix a(_a), ret(_a.n, _a.m); ret.set_identity();
  while(b) {
    if(b & 1) ret = ret * a;
    a = a * a;
    b >>= 1;
  }
  return ret;
}

# endif 
