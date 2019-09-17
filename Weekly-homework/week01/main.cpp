# include "std_lib_facilities.h"
# include <stack>

class Number {
  private:
    vector <int> p[2];
    bool sgn;
    
    inline void refresh() {
      for (int i = 0; i < 2; ++ i)
        while(p[i].size() && p[i][p[i].size() - 1] == 0) p[i].pop_back();
      if(p[0].size() == 0 && p[1].size() == 0) sgn = 0;
      if(p[0].size() == 0) p[0].push_back(0);
    }
    
    void expand(int type, int newsize) {
      int oldsize = p[type].size();
      if(oldsize > newsize) throw 233;
      p[type].resize(newsize);
      for (int i = oldsize; i < newsize; ++ i) p[type][i] = 0;
    }
    
    inline int get(int type, int dig) const {
      if(dig >= p[type].size()) return 0;
      else return p[type][dig];
    }
    
    inline void add(int id, int d) {
      if(id < 0) {
        id = - id - 1;
        if(id >= p[1].size()) throw 233;
        p[1][id] += d;
      } else {
        if(id >= p[0].size()) throw 233;
        p[0][id] += d;
      }
    }
    
	public:
	  Number() {
	    p[0].clear(); p[1].clear();
	    sgn = 0;
	    refresh();
    }
    
    Number(string str) {
      p[0].clear(); p[1].clear();
      sgn = 0;
      
      if(str[0] == '-') sgn = 1;
      
      int pos = sgn;
      for (; pos < str.size(); ++ pos)
        if(str[pos] == '.') break;
      
      for (int i = pos - 1; i >= sgn; -- i)
        p[0].push_back(str[i] - '0');
	    
	    for (int i = pos + 1; i < str.size(); ++ i)
	      p[1].push_back(str[i] - '0');
      
      refresh();
    }
    
    Number (const Number &num) {
      sgn = num.sgn;
      p[0].resize(num.p[0].size());
      p[1].resize(num.p[1].size());
      for (int i = 0; i < p[0].size(); ++ i) p[0][i] = num.p[0][i];
      for (int i = 0; i < p[1].size(); ++ i) p[1][i] = num.p[1][i];
      refresh();
    }
    
    Number& operator = (const Number &num) {
      sgn = num.sgn;
      p[0].resize(num.p[0].size());
      p[1].resize(num.p[1].size());
      for (int i = 0; i < p[0].size(); ++ i) p[0][i] = num.p[0][i];
      for (int i = 0; i < p[1].size(); ++ i) p[1][i] = num.p[1][i];
      refresh();
      return *this;
    }
    
    inline void prt() {
      this -> refresh();
      int cur = 0;
      if(sgn) ++ cur;
      cur += p[0].size();
      if(cur > 128) {
        printf("error");
        return ;
      }
      int res = 128;
      if(sgn) putchar('-'), -- res;
      for (int i = p[0].size() - 1; ~i; -- i) printf("%d", p[0][i]), -- res;
      if(p[1].size()) {
        if(res <= 0) return ;
        putchar('.');
        -- res;
        if(res == 0) return ;
        for (int i = 0; i < p[1].size(); ++ i) {
          printf("%d", p[1][i]);
          -- res;
          if(res == 0) return ;
        }
      }
    }
    
    friend int absCompare(const Number &a, const Number &b) {
      if(a.p[0].size() > b.p[0].size()) return 1;
      if(a.p[0].size() < b.p[0].size()) return -1;
      for (int i = a.p[0].size() - 1; ~i; -- i) {
        if(a.p[0][i] > b.p[0][i]) return 1;
        if(a.p[0][i] < b.p[0][i]) return -1;
      }
      for (int i = 0; i < a.p[1].size() && i < b.p[1].size(); ++ i) {
        if(a.p[1][i] > b.p[1][i]) return 1;
        if(a.p[1][i] < b.p[1][i]) return -1;
      }
      if(a.p[1].size() > b.p[1].size()) return 1;
      if(a.p[1].size() < b.p[1].size()) return -1;
      return 0;
    }
    
    friend bool operator > (const Number &a, const Number &b) {
      return absCompare(a, b) >= 0;
    }
    
    friend Number operator + (const Number &a, const Number &b) {
      if(a.sgn == b.sgn) {
        Number c; c.expand(1, max(a.p[1].size(), b.p[1].size()) + 3);
        int delta = 0;
        for (int i = c.p[1].size() - 1; ~i; --i) {
          c.p[1][i] = a.get(1, i) + b.get(1, i) + delta;
          if(c.p[1][i] >= 10) {
            delta = 1;
            c.p[1][i] -= 10;
          } else delta = 0;
        }
        
        c.expand(0, max(a.p[0].size(), b.p[0].size()) + 1);
        for (int i = 0; i < c.p[0].size(); ++ i) {
          c.p[0][i] = a.get(0, i) + b.get(0, i) + delta;
          if(c.p[0][i] >= 10) {
            delta = 1;
            c.p[0][i] -= 10;
          } else delta = 0;
        }
        
        c.sgn = a.sgn;
        c.refresh();
        return c;
      } else {
        int p = absCompare(a, b);
        if(p == 1) {
          Number c; c.expand(1, max(a.p[1].size(), b.p[1].size()) + 3);
          int delta = 0;
          for (int i = c.p[1].size() - 1; ~i; --i) {
            c.p[1][i] = a.get(1, i) - b.get(1, i) + delta;
            if(c.p[1][i] < 0) {
              delta = -1;
              c.p[1][i] += 10;
            } else delta = 0;
          }
          
          c.expand(0, max(a.p[0].size(), b.p[0].size()) + 3);
          for (int i = 0; i < c.p[0].size(); ++ i) {
            c.p[0][i] = a.get(0, i) - b.get(0, i) + delta;
            if(c.p[0][i] < 0) {
              delta = -1;
              c.p[0][i] += 10;
            } else delta = 0;
          }
          
          c.sgn = a.sgn;
          c.refresh();
          return c;
        } else {
          Number c; c.expand(1, max(a.p[1].size(), b.p[1].size()) + 3);
          int delta = 0;
          for (int i = c.p[1].size() - 1; ~i; --i) {
            c.p[1][i] = b.get(1, i) - a.get(1, i) + delta;
            if(c.p[1][i] < 0) {
              delta = -1;
              c.p[1][i] += 10;
            } else delta = 0;
          }
          
          c.expand(0, max(a.p[0].size(), b.p[0].size()) + 3);
          for (int i = 0; i < c.p[0].size(); ++ i) {
            c.p[0][i] = b.get(0, i) - a.get(0, i) + delta;
            if(c.p[0][i] < 0) {
              delta = -1;
              c.p[0][i] += 10;
            } else delta = 0;
          }
          
          c.sgn = b.sgn;
          c.refresh();
          return c;          
        }
      }
    }
    
    friend Number operator - (const Number &a, const Number &b) {
      Number tb(b);
      tb.sgn ^= 1;
      return a + tb;
    }
    
    friend Number operator * (const Number &a, const Number &b) {
      Number c;
      c.expand(0, a.p[0].size() + b.p[0].size() + 3);
      c.expand(1, a.p[1].size() + b.p[1].size() + 3);
      for (int i = 0; i < a.p[0].size(); ++ i)
        for (int j = 0; j < b.p[0].size(); ++ j)
          c.add(i + j, a.p[0][i] * b.p[0][j]);
      for (int i = 0; i < a.p[0].size(); ++ i)
        for (int j = 0; j < b.p[1].size(); ++ j)
          c.add(i - j - 1, a.p[0][i] * b.p[1][j]);
      for (int i = 0; i < a.p[1].size(); ++ i)
        for (int j = 0; j < b.p[0].size(); ++ j)
          c.add(j - i -  1, a.p[1][i] * b.p[0][j]);
      for (int i = 0; i < a.p[1].size(); ++ i)
        for (int j = 0; j < b.p[1].size(); ++ j)
          c.add(- i - j - 2, a.p[1][i] * b.p[1][j]);
      
      int delta = 0;
      for (int i = c.p[1].size() - 1; ~i; -- i) {
        c.p[1][i] += delta;
        if(c.p[1][i] >= 10) {
          delta = c.p[1][i] / 10;
          c.p[1][i] %= 10;
        } else delta = 0;
      }
      
      for (int i = 0; i < c.p[0].size(); ++ i) {
        c.p[0][i] += delta;
        if(c.p[0][i] >= 10) {
          delta = c.p[0][i] / 10;
          c.p[0][i] %= 10;
        } else delta = 0;
      } 
      if(a.sgn != b.sgn) c.sgn = 1;
      c.refresh();
      return c;
    }
    
    friend Number operator / (const Number &a, const Number &b) {
      if(a.p[1].size() || b.p[1].size()) {
        cout << "error";
        exit(0);
      }
      
      if(b.p[1].size() == 0 && b.p[0].size() == 1 && b.p[0][0] == 0) {
        cout << "error";
        exit(0);
      }
      
      Number x(a), y(b);
      
      int Sgn = (x.sgn != y.sgn);
      x.sgn = y.sgn = 0;
      
      Number c;
      stack <int> st;
      while(!st.empty()) st.pop();
      c.expand(0, 133);
      c.expand(1, 133);
      
      int beg = x.p[0].size() - y.p[0].size();
      if(x.p[0].size() < y.p[0].size()) {
        x.expand(0, y.p[0].size());
        for (int i = y.p[0].size() + beg - 1; ~i; -- i)
          x.p[0][i - beg] = x.p[0][i], x.p[0][i] = 0;
        x.refresh();
      }
      else if(x.p[0].size() > y.p[0].size()) {
        int delta = x.p[0].size() - y.p[0].size();
        for (int i = 0; i < delta; ++ i) st.push(x.p[0][i]);
        for (int i = delta; i < x.p[0].size(); ++ i)
          x.p[0][i - delta] = x.p[0][i];
        for (int i = y.p[0].size(); i < x.p[0].size(); ++ i) x.p[0][i] = 0;
        x.refresh();
      }
      
      int cnt;
      
      for (; beg >= -128; --beg) {
        cnt = 0;
        while(x > y) {
          for (int i = 0; i < y.p[0].size(); ++ i) {
            x.p[0][i] -= y.p[0][i];
            if(x.p[0][i] < 0) {
              x.p[0][i] += 10;
              x.p[0][i+1] --;
            }
          }
          x.refresh();
          ++cnt;
        //  cerr << cnt << endl;
        }
        c.add(beg, cnt);
        x.refresh();
        if(st.empty()) {
          x.p[0].resize(x.p[0].size() + 1);
          for (int i = x.p[0].size() - 1; ~i; -- i)
            x.p[0][i + 1] = x.p[0][i];
          x.p[0][0] = 0;
          x.refresh();
        } else {
          x.p[0].resize(x.p[0].size() + 1);
          for (int i = x.p[0].size() - 1; ~i; -- i)
            x.p[0][i + 1] = x.p[0][i];
          x.p[0][0] = st.top();
          st.pop();
          x.refresh();
        }
      }
      
      c.sgn = Sgn;
      c.refresh();
      return c;
    }
    
    ~ Number() = default;
};

inline int priority(char c) {
  if(c == '+' || c == '-') return 1;
  if(c == '*' || c == '/') return 2;
  return 0;
}

class Expression {
  private:
    string str;
    bool error;
    Number res;
    stack <Number> st;
    stack <char> op;
      
	public:
	  Expression(string _str) {
	    str = _str;
	    error = 0;
    }
    
    void work() {
      while(!st.empty()) st.pop();
      while(!op.empty()) op.pop();
      
      for (int i = 0; i < str.length(); ++ i) {
        if(! isdigit(str[i]) && str[i] != '<' && str[i] != '-') {
          error = 1;
          return ;
        }
        if(isdigit(str[i])) {
          int j = i;
          while(j + 1 < str.length() && (isdigit(str[j + 1]) || str[j + 1] == '.')) ++ j;
          Number p(str.substr(i, j - i + 1));
          i = j;
          st.push(p);
        } else if (str[i] == '-') {
          int j = i + 1;
          if(j >= str.length() || !isdigit(str[j])) {
            error = 1;
            return ;
          }
          while(j + 1 < str.length() && (isdigit(str[j + 1]) || str[j + 1] == '.')) ++ j;
          Number p(str.substr(i, j - i + 1));
          i = j;
          st.push(p);
        } else if (str[i] == '<') {
          if(i + 2 >= str.length() || str[i + 2] != '>') {
            error = 1;
            return ;
          }
          if(str[i + 1] != '+' && str[i + 1] != '-' && str[i + 1] != '*' && str[i + 1] != '/') {
            error = 1;
            return ;
          }
          
          while(!op.empty() && priority(op.top()) >= priority(str[i + 1])) {
            Number a, b;
            b = st.top(); st.pop();
            a = st.top(); st.pop();
            switch(op.top()) {
              case '+': st.push(a + b); break;
              case '-': st.push(a - b); break;
              case '*': st.push(a * b); break;
              case '/': st.push(a / b); break;
            }
            op.pop();
          }
          op.push(str[i + 1]); 
          i = i + 2;
        }
      }
      while(!op.empty()) {
        Number a, b;
        b = st.top(); st.pop();
        a = st.top(); st.pop();
        switch(op.top()) {
          case '+': st.push(a + b); break;
          case '-': st.push(a - b); break;
          case '*': st.push(a * b); break;
          case '/': st.push(a / b); break;
        }
        op.pop();
      }
      res = st.top(); 
    }
    
    void prt() {
      if(error) printf("error");
      else res.prt();
    }
    
    ~ Expression() = default;
};


int main() {		
  string str;
  getline(cin, str);
  Expression e(str);
  e.work();
  e.prt();
  return 0;
}

