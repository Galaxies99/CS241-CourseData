# ifndef _CALCULATOR_NUMBER_HPP_
# define _CALCULATOR_NUMBER_HPP_

# include <map>
# include <cctype>
# include <iostream>

# include "exception.hpp"

class Number {
    friend std :: ostream& operator << (std :: ostream &os, const Number& num);
    friend Number negative (const Number &a);
    friend Number operator + (const Number &a, const Number &b);
    friend Number operator - (const Number &a, const Number &b);
    friend Number operator * (const Number &a, const Number &b);
    friend Number operator / (const Number &a, const Number &b);
    friend Number operator ^ (const Number &a, const Number &b);
    friend Number shift(const Number &a, int b);
    friend Number abs (const Number &a);
    friend int to_int(const Number &a);
    friend bool abs_lt(const Number &a, const Number &b);
    friend bool operator < (const Number &a, const Number &b);
    friend bool operator > (const Number &a, const Number &b);
    friend bool operator == (const Number &a, const Number &b);
    friend bool operator <= (const Number &a, const Number &b);
    friend bool operator >= (const Number &a, const Number &b);
    
  private:
    bool sgn;
    std :: map <int, int> num;
    
    void refresh_zero() {
      for (std :: map <int, int> :: iterator it = num.begin(); it != num.end(); ++ it) 
        if (it -> second == 0) num.erase(it);
      if(num.size() == 0) sgn = 0;
    }
    
    void add(int digit, int c) {
      num[digit] = num[digit] + c;
    }
    
    void refresh_digit() {
      for (std :: map <int, int> :: iterator it = num.begin(); it != num.end(); ++ it) {
        if(it -> second < 0) {
          it -> second += 10;
          add(it -> first + 1, -1);
        }
        if(it -> second >= 10) {
          add(it -> first + 1, it -> second / 10);
          it -> second %= 10;
        }
      }
      refresh_zero();
    }
    
  public:
    Number() { num.clear(); sgn = 0; }   
    Number(int n) {
      num.clear(); sgn = 0;
      if(n < 0) sgn = 1, n = -n;
      int bse = 0;
      while(n) {
        num[bse] = n % 10;
        n /= 10;
        ++ bse;
      }
      refresh_zero();
    }
    Number(double n, int after_zero_digits = 8) {
      num.clear(); sgn = 0;
      if(n < 0) sgn = 1, n = -n;
      int z = static_cast <int> (n), bse = 0;
      while(z) {
        num[bse ++] = z % 10;
        z /= 10;
      }
      n -= z;
      for (int i = 1; i <= after_zero_digits; ++ i) {
        n = n * 10;
        z = static_cast <int> (n);
        num[-i] = z;
        n -= z;
      }
      refresh_zero();
    }
    Number(const std :: string &_str) {
      num.clear(); sgn = 0;
      std :: string str = _str;
      if(str[0] == '-') {
        sgn = 1;
        str = str.substr(1, std :: string :: npos);
      }
      if(str.find('.') == std :: string :: npos) {
        int bse = 0;
        for (int i = str.length() - 1; ~i; -- i) {
          if(! isdigit(str[i])) throw Initialize_Number_Error();
          num[bse ++] = static_cast <int> (str[i] - '0');
        }
      } else {
        int pos = str.find('.');
        int bse = 0;
        for (int i = pos - 1; ~i; -- i) {
          if(! isdigit(str[i])) throw Initialize_Number_Error();
          num[bse ++] = static_cast <int> (str[i] - '0');
        }
        bse = -1;
        for (int i = pos + 1; i < str.length(); ++ i) {
          if(! isdigit(str[i])) throw Initialize_Number_Error();
          num[bse--] = static_cast <int> (str[i] - '0');
        }
      }
      refresh_zero();
    }
    Number(const Number &rhs) {
      num.clear();
      sgn = rhs.sgn;
      for (std :: map <int, int> :: const_iterator it = rhs.num.begin(); it != rhs.num.end(); ++ it) 
        num.insert(*it);
    }
    Number& operator = (const Number &rhs) {
      num.clear();
      sgn = rhs.sgn;
      for (std :: map <int, int> :: const_iterator it = rhs.num.begin(); it != rhs.num.end(); ++ it) 
        num.insert(*it);
      return *this;     
    }
    
    ~ Number() = default;
};

std :: ostream& operator << (std :: ostream &os, const Number& n) {
  std :: map <int, int> :: const_iterator it = n.num.end(); 
  if(it == n.num.begin()) {
    os << '0';
    return os;
  } 
  if(n.sgn) os << '-';
  -- it;
  int last_digit = 0;
  if(it -> first < 0) {
    os << '0' << '.';
    -- last_digit; 
    while(last_digit -- > it -> first) os << '0';
    os << it -> second;
    ++ last_digit;
  } else {
    os << it -> second;
    last_digit = it -> first;
  }
  while(it != n.num.begin()) {
    -- it;
    -- last_digit; 
    while(last_digit > it -> first) {
      if(last_digit == -1) os << '.';
      os << '0';
      -- last_digit;
    } 
    if(last_digit == -1) os << '.';
    os << it -> second;
  }
  -- last_digit;
  while(last_digit >= 0) {
    os << '0';
    -- last_digit;
  } 
  return os;
}

Number abs(const Number &a) {
  Number res(a);
  res.sgn = 0;
  return res;
}

Number negative(const Number &a) {
  Number res(a);
  if(res.num.size() == 0) return res;
  res.sgn ^= 1;
  return res;
}

// Only allow -999999999 ~ 999999999
int to_int(const Number &a) {
  int res = 0, bse = 1;
  for (std :: map <int, int> :: const_iterator it = a.num.begin(); it != a.num.end(); ++ it) {
    if(it -> first < 0 || it -> first > 8) throw To_Int_Error();
    bse = 1;
    for (int i = 0; i < it -> first; ++ i) bse *= 10;
    res += it -> second * bse;
  }
  if(a.sgn) res = -res;
  return res;
}

bool abs_lt(const Number &a, const Number &b) {
  std :: map <int, int> :: const_iterator ita = a.num.end(), itb = b.num.end();
  if(itb == b.num.begin()) return false;
  if(ita == a.num.begin()) return true;
  for (-- ita, -- itb; ; -- ita, -- itb) {
    if(ita -> first != itb -> first) return ita -> first < itb -> first;
    if(ita -> second != itb -> second) return ita -> second < itb -> second;
    if(ita == a.num.begin() || itb == b.num.begin()) break;
  }
  if(itb == b.num.begin()) return false;
  return true;
}

bool operator < (const Number &a, const Number &b) {
  if(a.sgn != b.sgn) return a.sgn > b.sgn;
  if(a.sgn == 0) return abs_lt(a, b);  
  else return abs_lt(a, b) ^ 1;
}

bool operator > (const Number &a, const Number &b) {
  return negative(a) < negative(b);
}

bool operator == (const Number &a, const Number &b) {
  if(a.sgn != b.sgn) return false;
  std :: map <int, int> :: const_iterator ita = a.num.begin(), itb = b.num.begin();
  for (; ita != a.num.end() && itb != b.num.end(); ++ ita, ++ itb) 
    if(*ita != *itb) return false;
  if (ita == a.num.end() && itb == b.num.end()) return true;
  return false;
}

bool operator <= (const Number &a, const Number &b) {
  return (a < b) || (a == b);
}

bool operator >= (const Number &a, const Number &b) {
  return (a > b) || (a == b);
}

Number operator + (const Number &a, const Number &b) {
  Number res;
  if(a.sgn == b.sgn) {
    res.sgn = a.sgn;
    for (std :: map <int, int> :: const_iterator it = a.num.begin(); it != a.num.end(); ++ it)
      res.add(it -> first, it -> second);
    for (std :: map <int, int> :: const_iterator it = b.num.begin(); it != b.num.end(); ++ it)
      res.add(it -> first, it -> second);
    res.refresh_digit();
    return res;
  }
  if(abs_lt(a, b)) {
    res.sgn = b.sgn;
    for (std :: map <int, int> :: const_iterator it = a.num.begin(); it != a.num.end(); ++ it)
      res.add(it -> first, - it -> second);
    for (std :: map <int, int> :: const_iterator it = b.num.begin(); it != b.num.end(); ++ it)
      res.add(it -> first, it -> second);
  } else {
    res.sgn = a.sgn;
    for (std :: map <int, int> :: const_iterator it = a.num.begin(); it != a.num.end(); ++ it)
      res.add(it -> first, it -> second);
    for (std :: map <int, int> :: const_iterator it = b.num.begin(); it != b.num.end(); ++ it)
      res.add(it -> first, - it -> second);
  }
  res.refresh_digit(); 
  return res;
}

Number operator - (const Number &a, const Number &b) {
  return a + negative(b);  
}

Number operator * (const Number &a, const Number &b) {
  Number res;
  if(a.sgn == b.sgn) res.sgn = 0;
  else res.sgn = 1;
  for (std :: map <int, int> :: const_iterator ita = a.num.begin(); ita != a.num.end(); ++ ita)
    for (std :: map <int, int> :: const_iterator itb = b.num.begin(); itb != b.num.end(); ++ itb)
      res.add(ita -> first + itb -> first, ita -> second * itb -> second);
  res.refresh_digit();
  return res;
} 

Number shift(const Number &a, int b) {
  Number res;
  res.sgn = a.sgn;
  for (std :: map <int, int> :: const_iterator it = a.num.begin(); it != a.num.end(); ++ it)
    res.num[it -> first + b] = it -> second;
  return res;
}

Number operator / (const Number &a, const Number &b) {
  if(b == Number(0)) throw Div_Zero_Error(); 
  if(a == Number(0)) return a;
  Number res;
  if(a.sgn == b.sgn) res.sgn = 0;
  else res.sgn = 1;
  int bse = (-- a.num.end()) -> first - (-- b.num.end()) -> first;
  Number A = shift(a, -bse);
  while(bse >= -256) {
    int t = 0;
    while(A >= b) {
      A = A - b;
      ++ t;
    }
    res.add(bse, t);
    if(A == Number(0)) break; 
    -- bse;
    A = shift(A, 1);
  }
  res.refresh_digit();
  return res;
}

Number operator ^ (const Number &a, const Number &b) {
  int y;
  try {
    y = to_int(b);
  } catch(...) {
    throw Pow_Error();
  } 
  Number res(1), x(a);
  if(y < 0) y = -y;
  while(y) {
    if(y & 1) res = res * x;
    x = x * x;
    y >>= 1;
  } 
  if(b.sgn) res = Number(1) / res;
  res.refresh_digit();
  return res; 
}

# endif
