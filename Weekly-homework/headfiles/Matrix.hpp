# ifndef _MATRIX_H_
# define _MATRIX_H_

# include <vector>

class Matrix {
    friend Matrix operator * (const Matrix &a, const Matrix &b);

    friend Matrix operator ^ (const Matrix &a, int b);
    
  private:
    int n, m;
    std :: vector < std :: vector <double> > p;
  
  public:
    Matrix(int n = 0, int m = 0) {
      p.resize(n);
      for (int i = 0; i < n; ++ i) {
        p[i].resize(m);
        for (int j = 0; j < m; ++ j)
          p[i][j] = 0.0;
      }
    }
    
    Matrix(const Matrix &rhs) {
      n = rhs.n, m = rhs.m;
      initialize_with_vector(rhs.p);
    }
    
    Matrix& operator = (const Matrix &rhs) {
      n = rhs.n, m = rhs.m;
      initialize_with_vector(rhs.p);      
    }
    
    void initialize_with_elementary() {
      if(n != m) throw "size error!";
      for (int i = 0; i < n; ++ i) p[i][i] = 1;
    }
    
    void initialize_with_array(const double **arr) {
      for (int i = 0; i < n; ++ i)
        for (int j = 0; j < m; ++ j)
          p[i][j] = arr[i][j];
    }
    
    void initialize_with_vector(const std :: vector < std :: vector <double> > &vec) {
      if(vec.size() != n) throw "size error!";
      for (int i = 0; i < n; ++ i) {
        if(vec[i].size() != m) throw "size error!";
        for (int j = 0; j < m; ++ j)
          p[i][j] = vec[i][j];
      }
    }
    
    double& operator() (int i, int j) {
      if(i >= n || j >= m || i < 0 || j < 0) throw "range error!";
      return p[i][j];  
    }
    
    const double& operator() (int i, int j) const {
      if(i >= n || j >= m || i < 0 || j < 0) throw "range error!";
      return p[i][j];  
    }
    
    ~ Matrix() = default;
};

Matrix operator * (const Matrix &a, const Matrix &b) {
  if(a.m != b.n) throw "size error";
  Matrix c(a.n, b.m);
  for (int i = 0; i < c.n; ++ i)
    for (int j = 0; j < c.m; ++ j)
      for (int k = 0; k < a.m; ++ k)
        c(i, j) += a(i, k) * b(k, j);
  return c; 
}

Matrix operator ^ (const Matrix &a, int b) {
  if(a.n != a.m) throw "size error!";
  Matrix c(a.n, a.m), t(a);
  c.initialize_with_elementary();
  while(b) {
    if(b & 1) c = c * t;
    t = t * t;
    b >>= 1;
  } 
  return c;
}

# endif 
