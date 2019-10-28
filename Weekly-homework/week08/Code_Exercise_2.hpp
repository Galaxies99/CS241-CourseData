# ifndef _CODE_EXERCISE_HPP_
# define _CODE_EXERCISE_HPP_

# include <set> 
# include <vector>
# include <string>
# include <cctype>
# include <algorithm>

namespace Sign {
  std :: string sgn[] = {
    "alignas", "alignof", "and", "and_eq",
    "asm", "atomic_cancel", "atomic_commit", "atomic_noexcept",
    "auto", "bitand", "bitor", "bool",
    "break", "case", "catch", "char",
    "char8_t", "char16_t", "char32_t", "class",
    "compl", "concept", "const", "consteval",
    "constexpr", "constinit", "const_cast", "continue",
    "co_await", "co_return", "co_yield", "decltype",
    "default", "define", "defined", "delete",
    "do", "double", "dynamic_cast", "elif",
    "else", "error", "endif", "enum",
    "explicit", "export", "extern", "false",
    "final", "float", "for", "friend",
    "goto", "if", "ifdef", "ifndef",
    "import", "include", "inline", "int",
    "line", "long", "module", "mutable",
    "namespace", "new", "noexcept", "not",
    "not_eq", "nullptr", "operator", "or",
    "or_eq", "override", "pragma", "private",
    "protected", "public", "reflexpr", "register",
    "reinterpret_cast", "requires", "return", "short",
    "signed", "sizeof", "static", "static_assert",
    "static_cast", "struct", "switch", "synchronized",
    "template", "this", "thread_local", "throw",
    "xor_eq", "true", "try", "typedef",
    "typeid", "typename", "undef", "union",
    "unsigned", "using", "virtual", "void",
    "volatile", "wchar_t", "while", "xor"
  };
  const int SIGN_N = 112;
  
  bool checkWord(const std :: string &str) {
    for (int i = 0; i < SIGN_N; ++ i)
      if(str == sgn[i]) return true;
    return false;
  }
  
}

class CodeParsor {
  private:
    std :: set < std :: string > s;
    std :: vector < std :: string > rec;
    bool in_comment;
  public:
    CodeParsor() {
      s.clear();
      in_comment = 0;
    }
    
    void parse(const std :: string &str) {
      std :: string cur = "";
      bool in_quotation1 = 0, in_quotation2 = 0; 
      int beg = 0;
      for (int i = 0; i < str.length(); ++ i) {
        if(isalpha(str[i]) || isdigit(str[i]) || str[i] == '_') cur += str[i];
        else {
          if(in_comment == 0 && cur != "" && Sign :: checkWord(cur) == false) s.insert(cur);
          cur = "";
          
          if(str[i] == '\"' && in_comment == 0 && in_quotation2 == 0) {
            in_quotation1 ^= 1;
          } 
          
          if(str[i] == '\'' && in_comment == 0 && in_quotation1 == 0) {
            in_quotation2 ^= 1;
          } 
          
          if(str[i] == '/' && in_quotation1 == 0 && in_quotation2 == 0) {
            if(i + 1 < str.length()) {
              if(str[i + 1] == '/' && in_comment == 0) return ;
              if(str[i + 1] == '*' && in_comment == 0) {
                in_comment = 1;
                ++ i;
              }
            }
          } else if(str[i] == '*' && in_quotation1 == 0 && in_quotation2 == 0) {
            if(in_comment == 1 && i + 1 < str.length() && str[i + 1] == '/') {
              in_comment = 0;
              ++ i;
            }
          } else if(str[i] == '\\' && (in_quotation1 || in_quotation2)) {
            if(i + 1 < str.length()) {
              if (str[i+1] == 'n') ++ i;
            }
          }
        }
      }
      if(in_comment == 0 && cur != "" && Sign :: checkWord(cur) == false) s.insert(cur);
    }
    
    std :: vector <std :: string>& countword() {
      rec.clear();
      for (std :: set < std :: string > :: iterator it = s.begin(); it != s.end(); ++ it)
        rec.push_back(*it);
      return rec;
    }
    
    
};

# endif
