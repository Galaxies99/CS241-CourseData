# ifndef _INTERPOLATION_HPP_
# define _INTERPOLATION_HPP_

# include <iostream>
# include <vector>

namespace Tools {
  inline double Abs(double x) {
    return x >= 0 ? x : -x;
  } 
  inline bool checkEq(double x, double y, double eps) {
    return Abs(x - y) < eps;
  }
  inline bool output(double p) {
    std :: string out = ""; 
    int pc = p * 10000, z = p;
    if(pc == 0) return false;
    if(p < 0) {
      z = -z; pc = -pc;
      out = out + "-";
    }
    out = out + std :: to_string(z) + ".";
    pc -= z * 10000;
    if(pc < 10) out = out + "000";
    else if(pc < 100) out = out + "00";
    else if(pc < 1000) out = out + "0";
    out = out + std :: to_string(pc);
    std :: cout << out;
    return true;
  }
}

class NewtonInterpolation {
  private:
    int n;
    std :: vector < std :: vector <double> > tab;
    std :: vector < std :: pair <double, double> > p;
  
    std :: vector <double> x;
    std :: vector <double> poly;
    
  public:
    NewtonInterpolation() { n = 0; tab.clear(); p.clear(); }
    NewtonInterpolation(const std :: vector <std :: pair <double, double> > &_p) {
      initialize(_p);
    }
    
    void initialize(const std :: vector < std :: pair <double, double> > &_p) {
      p = _p; n = p.size();
      tab.resize(n);
      for (int i = 0; i < n; ++ i) tab[i].resize(n);
      for (int i = 0; i < n; ++ i) tab[0][i] = p[i].second;
      for (int i = 1; i < n; ++ i)
        for (int j = i; j < n; ++ j)
          tab[i][j] = (tab[i - 1][j] - tab[i - 1][j - 1]) / (p[j].first - p[j - i].first);
      
      std :: vector <double> t;
      x.resize(n); poly.resize(n); t.resize(n);
      poly[0] = tab[0][0]; x[0] = 1.0;
      for (int i = 1; i < n; ++ i) x[i] = poly[i] = 0; 
      for (int i = 1; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) t[j] = 0;
        for (int j = 1; j < n; ++ j) t[j] = x[j - 1];
        for (int j = 0; j < n; ++ j) t[j] = t[j] - p[i - 1].first * x[j];
        for (int j = 0; j < n; ++ j) x[j] = t[j];
        for (int j = 0; j < n; ++ j) poly[j] += tab[i][i] * x[j]; 
      }
    }
    
    void initialize_same(const std :: vector < std :: pair <double, double> > &_p) {
      p = _p; n = p.size();
      double D;
      if(n > 1) D = p[n - 1].first - p[n - 2].first;
      tab.resize(n);
      for (int i = 0; i < n; ++ i) tab[i].resize(n);
      for (int i = 0; i < n; ++ i) tab[0][i] = p[i].second;
      for (int i = 1; i < n; ++ i)
        for (int j = i; j < n; ++ j)
          tab[i][j] = (tab[i - 1][j] - tab[i - 1][j - 1]) / (D * i);
      
      std :: vector <double> t;
      x.resize(n); poly.resize(n); t.resize(n);
      poly[0] = tab[0][0]; x[0] = 1.0;
      for (int i = 1; i < n; ++ i) x[i] = poly[i] = 0; 
      for (int i = 1; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) t[j] = 0;
        for (int j = 1; j < n; ++ j) t[j] = x[j - 1];
        for (int j = 0; j < n; ++ j) t[j] = t[j] - p[i - 1].first * x[j];
        for (int j = 0; j < n; ++ j) x[j] = t[j];
        for (int j = 0; j < n; ++ j) poly[j] += tab[i][i] * x[j]; 
      }
    }
    
    void insert(const std :: pair <double, double> p0) {
      p.push_back(p0); ++ n;
      tab.resize(n);
      for (int i = 0; i < n; ++ i) tab[i].resize(n);
      tab[0][n - 1] = p0.second;
      for (int i = 1; i < n; ++ i) 
        tab[i][n - 1] = (tab[i - 1][n - 1] - tab[i - 1][n - 2]) / (p[n - 1].first - p[n - 1 - i].first);
      x.resize(n); poly.resize(n);
      if(n == 1) poly[0] = tab[0][0], x[0] = 1.0;
      else {
        std :: vector <double> t; t.resize(n);
        for (int j = 0; j < n; ++ j) t[j] = 0;
        for (int j = 1; j < n; ++ j) t[j] = x[j - 1];
        for (int j = 0; j < n - 1; ++ j) t[j] = t[j] - p[n - 2].first * x[j];
        for (int j = 0; j < n; ++ j) x[j] = t[j];
        for (int j = 0; j < n; ++ j) poly[j] += tab[n - 1][n - 1] * x[j]; 
      }
    }
    
    double getfunc(double x, int times = -1) {
      if(times == -1) times = n - 1;
      if(times >= n) throw "invalid!";
      double ret = 0.0;
      for (int i = 0; i <= times; ++ i) {
        double t = tab[i][i];
        for (int j = 0; j < i; ++ j) t = t * (x - p[j].first);
        ret += t;
      }
      return ret;
    }
    
    void output_poly() {
      bool ok = 0;
      for (int i = n - 1; ~i; -- i) {
        if(Tools :: checkEq(poly[i], 0.0, 1e-8) == false) {
          if(ok && poly[i] > 0) std :: cout << '+';
          Tools :: output(poly[i]);
          if(i > 1) std :: cout << "x^" << i;
          if(i == 1) std :: cout << 'x';
          ok = 1;
        } 
      }
      if(ok == 0) std :: cout << "0.0000";
    } 
    
    ~ NewtonInterpolation() = default;
};

# endif 
