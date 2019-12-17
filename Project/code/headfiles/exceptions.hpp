# ifndef _EXCEPTIONS_HPP_
# define _EXCEPTIONS_HPP_

class Exception {
  public:
    Exception() = default;
    virtual const char* what() const = 0;
    ~ Exception() = default;
};

class oDouble_Initialize_Error : public Exception {
  public:
    oDouble_Initialize_Error() = default;
    const char* what() const {
      return "Initialize oDouble Number Error!";
    }
    ~ oDouble_Initialize_Error() = default;
};

class toInt_Initialize_Error : public Exception {
  public:
    toInt_Initialize_Error() = default;
    const char* what() const {
      return "Initialize Int Error!";
    }
    ~ toInt_Initialize_Error() = default;
};

class Record_Initialize_Error : public Exception {
  public:
    Record_Initialize_Error() = default;
    const char* what() const {
      return "Initialize Record Error!";
    }
    ~ Record_Initialize_Error() = default;
}; 

class File_Error : public Exception {
  public:
    File_Error() = default;
    const char* what() const {
      return "File Error!";
    }
    ~ File_Error() = default;
};

class Option_Error : public Exception {
  public:
    Option_Error() = default;
    const char* what() const {
      return "Option Error!";
    }
    ~ Option_Error() = default;
};

class Input_Date_out_of_bound : public Exception {
  public:
    Input_Date_out_of_bound() = default;
    const char* what() const {
      return "Input out of bound!";
    }
    ~ Input_Date_out_of_bound() = default;
};

class Input_Date_Invalid : public Exception {
  public:
    Input_Date_Invalid() = default;
    const char* what() const {
      return "Input Date Invalid!";
    }
    ~ Input_Date_Invalid() = default;
};

class Unexpected_Error : public Exception {
  public:
    Unexpected_Error() = default;
    const char* what() const {
      return "Unexpected Error!";
    }
    ~ Unexpected_Error() = default;
};

class No_Data_Error : public Exception {
  public:
    No_Data_Error() = default;
    const char* what() const {
      return "No Data!";
    }
    ~ No_Data_Error() = default;
};

# endif
