# ifndef _CALCULATOR_EXCEPTION_HPP_
# define _CALCULATOR_EXCEPTION_HPP_

# include <string>

class Exception {
  public:
    Exception() = default;
    virtual const char* what() const = 0;
    ~ Exception() = default;
};

class Initialize_Number_Error : public Exception {
  public:
    Initialize_Number_Error() = default;
    const char* what() const {
      return "Initialize Number Error!";
    }
    ~ Initialize_Number_Error() = default;
};

class Div_Zero_Error : public Exception {
  public:
    Div_Zero_Error() = default;
    const char* what() const {
      return "Div Zero Error!";
    }    
    ~ Div_Zero_Error() = default;
};

class To_Int_Error : public Exception {
  public:
    To_Int_Error() = default;
    const char* what() const {
      return "To Int Error!";
    }    
    ~ To_Int_Error() = default;
};

class Pow_Error : public Exception {
  public:
    Pow_Error() = default;
    const char* what() const {
      return "Pow Error!";
    }    
    ~ Pow_Error() = default;
};

class Expression_Invalid : public Exception {
  public:
    Expression_Invalid() = default;
    const char* what() const {
      return "Expression Invalid!";
    }
    ~ Expression_Invalid() = default;
};

class Unknown_Error : public Exception {
  public:
    Unknown_Error() = default;
    const char* what() const {
      return "Unknown Error!";
    }    
    ~ Unknown_Error() = default;
}; 

# endif
