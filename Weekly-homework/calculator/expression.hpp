# ifndef _CALCULATOR_EXPRESSION_HPP_
# define _CALCULATOR_EXPRESSION_HPP_

# include <map>
# include <string>
# include <iostream>

# include "number.hpp"
# include "exception.hpp"

class Expression {
  private:
    Number res;
  
  public:
    Expression() = default;
    Expression(const std :: string &str) { parse(str); }
    void parse(const std :: string &str);
    void output(std :: ostream &os) { os << res; }
    ~ Expression() = default;
};

void Expression :: parse(const std :: string &str) {
  // TODO parse
    
}

# endif
