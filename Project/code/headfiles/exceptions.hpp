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

# endif
