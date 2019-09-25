# ifndef _CALCULATOR_EXCEPTION_HPP_
# define _CALCULATOR_EXCEPTION_HPP_

# include <string>

class Exception {
  public:
    Exception() = default;
    virtual const char* what() = 0;
    ~ Exception() = default;
};

class Initialize_Number_Error : public Exception {
  public:
    Initialize_Number_Error() = default;
    const char* what() {
      return "Initialize Number Error!";
    }
    ~ Initialize_Number_Error() = default;
};

class Div_Zero_Error : public Exception {
  public:
    Div_Zero_Error() = default;
    const char* what() {
      return "Div Zero Error!";
    }    
    ~ Div_Zero_Error() = default;
};

class To_Int_Error : public Exception {
  public:
    To_Int_Error() = default;
    const char* what() {
      return "To Int Error!";
    }    
    ~ To_Int_Error() = default;
};

class Pow_Error : public Exception {
  public:
    Pow_Error() = default;
    const char* what() {
      return "Pow Error!";
    }    
    ~ Pow_Error() = default;
};

class Unknown_Error : public Exception {
  public:
    Unknown_Error() = default;
    const char* what() {
      return "Unknown Error!";
    }    
    ~ Unknown_Error() = default;
}; 

# endif
