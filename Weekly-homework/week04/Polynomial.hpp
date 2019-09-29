# ifndef _POLYNOMIAL_H_
# define _POLYNOMIAL_H_

# include <cctype>
# include <string>
# include <vector>
# include <stdio.h>
# include <iostream>
# include <algorithm>

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

class Polynomial {
  private:
    std :: vector < std :: pair < int, double > > p;
    
    void refresh(double eps = 1e-9) {
      sort(p.begin(), p.end());
      std :: vector < std :: pair < int, double > > tem;
      tem.clear();
      for (int i = 0; i < p.size(); ++ i) {
        int j = i; 
        double cur = p[i].second;
        while(j + 1 < p.size() && p[j + 1].first == p[i].first) {
          ++ j;
          cur += p[j].second;
        }
        i = j;
        if(Tools :: checkEq(cur, 0.0, eps)) continue;
        tem.push_back(std :: make_pair(p[i].first, cur));
      }
      p.clear();
      for (int i = 0; i < tem.size(); ++ i) p.push_back(tem[i]);
    }
    
    void add(int a, double b, bool refresh_open = 1) {
      p.push_back(std :: make_pair(a, b));
      if(refresh_open) refresh();
    }
    
  public:
    bool errorflag;
    Polynomial() { errorflag = 0; p.clear(); }
    Polynomial(const std :: string &str) {
      set(str);
    }
    
    void set(const std :: string &str) {
      errorflag = 0; p.clear();
      double cur = 0, base = 1.0;
      bool flag = (str[0] == '-');
      int r = 0;
      for (int i = flag; i < str.length(); ++ i) {
        if ('0' <= str[i] && str[i] <= '9') {
          int ps = (str[i] - '0');
          if(base == 1.0) cur = cur * 10 + ps;
          else {
            cur = cur + base * ps;
            base = base * 0.1;
          }
        } else if(str[i] == '.') {
          if(base != 1.0) {
            errorflag = 1;
            return ;
          }
          base = 0.1;
        } else if(str[i] == 'x') {
          if(i == 0 || str[i-1] == '+' || str[i-1] == '-') cur = 1.0;
          if(i + 1 < str.length() && str[i + 1] == '^') {
            int j = i + 1;
            if(j + 1 == str.length() || !isdigit(str[j + 1])) {
              errorflag = 1;
              return ;
            }
            while(j + 1 < str.length() && '0' <= str[j+1] && str[j+1] <= '9') {
              ++ j;
              r = r * 10 + (str[j] - '0');
            }
            if(j + 1 < str.length() && str[j+1] != '+' && str[j+1] != '-') {
              errorflag = 1;
              return ;
            }
            i = j;
          } else {
            if(i+1 < str.length() && str[i + 1] != '+' && str[i + 1] != '-') {
              errorflag = 1;
              return ;
            }
            r = 1;
          }
        } else if(str[i] == '+') {
          if(i && !isdigit(str[i-1]) && str[i-1] != 'x') {
            errorflag = 1;
            return ;
          }
          if(flag) cur = -cur;
          p.push_back(std :: make_pair(r, cur));
          flag = 0; cur = 0; base = 1.0; r = 0;
        } else if(str[i] == '-') {
          if(i && !isdigit(str[i-1]) && str[i-1] != 'x') {
            errorflag = 1;
            return ;
          }
          if(flag) cur = -cur;
          p.push_back(std :: make_pair(r, cur));
          flag = 1; cur = 0; base = 1.0; r = 0;
        } else errorflag = 1;
      }
      if(flag) cur = -cur;
      p.push_back(std :: make_pair(r, cur));
      refresh();
    }
    
    Polynomial(const Polynomial& rhs) {
      p.clear();
      for (int i = 0; i < rhs.p.size(); ++ i) p.push_back(rhs.p[i]);
    }
    
    void diff() {
      for (int i = 0; i < p.size(); ++ i) {
        if(p[i].first == 0) {
          p[i].second = 0;
          continue;
        }
        p[i].second *= p[i].first;
        p[i].first --;
      }
      refresh();
    }
    
    void prt() {
      bool flag = 1;
      refresh();
      for (int i = p.size() - 1; ~i; -- i) {
        if(p[i].second > 0 && flag != 1) std :: cout << "+";
        if(Tools :: output(p[i].second) == true) {
          flag = 0;
          if(p[i].first > 1) std :: cout << "x^" << p[i].first;
          else if(p[i].first == 1) std :: cout << "x";
        }
      }
      if(flag) std :: cout << "0.0000";
    }
    
    friend std :: pair < std :: pair <Polynomial, Polynomial>, bool> operator / (const Polynomial &a, const Polynomial &b) {
      Polynomial res(a), div;
      if(b.p.size() == 0) return std :: make_pair(std :: make_pair(div, res), false);
      if(res.p.size() == 0) return std :: make_pair(std :: make_pair(res, res), true); 
      
      int an = res.p.size(), bn = b.p.size();
      while(an && res.p[an - 1].first >= b.p[bn - 1].first) {
        int delta = res.p[an - 1].first - b.p[bn - 1].first;
        double r = res.p[an - 1].second / b.p[bn - 1].second;
        div.add(delta, r, 0);
        
        for (int i = 0; i < bn; ++ i)
          res.add(b.p[i].first + delta, - r * b.p[i].second, 0);
        res.refresh();
        
        an = res.p.size(), bn = b.p.size();
      }
      div.refresh();
      
      return std :: make_pair(std :: make_pair(div, res), true);
    } 
    
    double getfunc(double x) const {
      double res = 0;
      for (int i = 0; i < p.size(); ++ i) {
        double t = p[i].second;
        for (int j = 0; j < p[i].first; ++ j)
          t = t * x;
        res += t;
      }
      return res; 
    } 
    
    ~ Polynomial() = default;
};

# endif
