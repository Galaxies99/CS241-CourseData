# ifndef _CALCULATOR_EXPRESSION_HPP_
# define _CALCULATOR_EXPRESSION_HPP_

# include <stack>
# include <string>
# include <iostream>

# include "number.hpp"
# include "exception.hpp"

namespace Expression_Priority {
  int getPriority(char ch) {
    if(ch == '(') return -999;
    if(ch == 'p' || ch == 'n') return 4;
    if(ch == '^') return 3;
    if(ch == '*' || ch == '/') return 2;
    if(ch == '+' || ch == '-') return 1;
  }
}

namespace Expression_Calculate {
  Number calc(Number a, Number b, char op) {
    switch(op) {
      case '+': return a + b;
      case '-': return a - b;
      case '*': return a * b;
      case '/': return a / b;
      default: throw Expression_Invalid();
    } 
  }
}

class Expression {
  private:
    Number res;
    std :: stack <Number> st;
    std :: stack <char> opt;
    void stPush(const Number &d) {
      Number c(d);
      while(!opt.empty() && (opt.top() == 'p' || opt.top() == 'n')) {
        if(opt.top() == 'n') c = negative(c);
        opt.pop();
      }
      st.push(c);
    }
  
  public:
    Expression() = default;
    Expression(const std :: string &str) { res = parse(str); }
    Number parse(const std :: string &str);
    void output(std :: ostream &os) { os << res; }
    ~ Expression() = default;
};

Number Expression :: parse(const std :: string &str) {
  while(!st.empty()) st.pop();
  while(!opt.empty()) opt.pop();
  bool number_prefix = 1;
  std :: string num;
  for (int i = 0; i < str.length(); ++ i) {
    if(isdigit(str[i])) {
      num = "";
      num.append(1, str[i]);
      int j = i;
      while(j + 1 < str.length() && (isdigit(str[j + 1]) || str[j + 1] == '.')) 
        num.append(1, str[++ j]);
      i = j;
      Number c(num);
      stPush(c); 
      number_prefix = 0;
    } else if(str[i] == '+' || str[i] == '-') {
      if(number_prefix == 1) {
        if(str[i] == '+') opt.push('p');
        if(str[i] == '-') opt.push('n');
      } else {
        while (!opt.empty() && Expression_Priority :: getPriority(opt.top()) >= 1) {
          if(st.size() < 2) throw Expression_Invalid();
          Number a = st.top(); st.pop();
          Number b = st.top(); st.pop(); 
          Number c = Expression_Calculate :: calc(b, a, opt.top());
          opt.pop();
          stPush(c);
        }
        opt.push(str[i]);
        number_prefix = 1;
      }
    } else if(str[i] == '*' || str[i] == '/' || str[i] == '^') {
      if(number_prefix == 1) throw Expression_Invalid();
      while (!opt.empty() && Expression_Priority :: getPriority(opt.top()) >= Expression_Priority :: getPriority(str[i])) {
        if(st.size() < 2) throw Expression_Invalid();
        Number a = st.top(); st.pop();
        Number b = st.top(); st.pop(); 
        Number c = Expression_Calculate :: calc(b, a, opt.top());
        opt.pop();
        stPush(c);
      }
      opt.push(str[i]);
      number_prefix = 1;
    } else if(str[i] == '(') {
      opt.push('(');
      number_prefix = 1;
    } else if(str[i] == ')') {
      if(number_prefix == 1) throw Expression_Invalid();
      while(!opt.empty() && opt.top() != '(') {
        if(st.size() < 2) throw Expression_Invalid();
        Number a = st.top(); st.pop();
        Number b = st.top(); st.pop(); 
        Number c = Expression_Calculate :: calc(b, a, opt.top());
        opt.pop();
        stPush(c);
      }
      if(opt.empty()) throw Expression_Invalid();
      Number c = st.top(); st.pop();
      opt.pop();
      stPush(c);
      number_prefix = 0;
    } else throw Expression_Invalid();
  }
  while (!opt.empty()) {
    if(st.size() < 2) throw Expression_Invalid();
    Number a = st.top(); st.pop();
    Number b = st.top(); st.pop(); 
    Number c = Expression_Calculate :: calc(b, a, opt.top());
    opt.pop();
    stPush(c);
  }
  if(st.size() != 1) throw Expression_Invalid();
  return st.top();
}

# endif
