# ifndef _TOKEN_EXERCISE_HPP_
# define _TOKEN_EXERCISE_HPP_

# include <algorithm>
# include <vector> 
# include <string>
# include <cctype>
# include <map>

namespace Tools {
  std :: string simplize(const std :: string &str) {
    std :: string ret = str;
    for (int i = 0; i < str.size(); ++ i)
      if(isupper(ret[i])) ret[i] = tolower(ret[i]);
    return ret;
  }
  inline bool cmp(std :: pair <std :: string, int> a, std :: pair <std :: string, int> b) {
    if(a.second != b.second) return a.second > b.second;
    else return a.first < b.first;
  }
  inline bool checkWord(const std :: string &str) {
    bool ok = 0;
    for (int i = 0; i < str.size(); ++ i)
      ok |= (str[i] != '-' && str[i] != '_');
    return ok;
  } 
}


class TokenParsor {
  private:
    std :: map <std :: string, int> tokens;
    std :: map <std :: string, std :: string> token_name;
    std :: vector < std :: pair <std :: string, int> > freq; 
    
  public:
    TokenParsor() {
      tokens.clear();
      token_name.clear();
    }
    
    void parse(const std :: string &str) {
      std :: string cur = "";
      for (int i = 0; i < str.length(); ++ i) {
        if(isalpha(str[i]) || isdigit(str[i]) || str[i] == '-' || str[i] == '_') cur += str[i];
        else {
          if(cur == "") continue;
          if(Tools :: checkWord(cur) == false) {
            cur = "";
            continue;
          }
          std :: string symb = Tools :: simplize(cur);
          if(tokens.find(symb) == tokens.end()) {
            tokens[symb] = 1;
            token_name[symb] = cur;
          } else {
            tokens[symb] ++;
            token_name[symb] = std :: max(token_name[symb], cur);
          }
          cur = "";
        }
      }
      if(Tools :: checkWord(cur)) {
        std :: string symb = Tools :: simplize(cur);
        if(tokens.find(symb) == tokens.end()) {
          tokens[symb] = 1;
          token_name[symb] = cur;
        } else {
          tokens[symb] ++;
          token_name[symb] = std :: max(token_name[symb], cur);
        }
        cur = "";
      }
    }
    
    int getwords() {
      int words = 0;
      for (std :: map <std :: string, int> :: iterator it = tokens.begin(); it != tokens.end(); ++ it)
        words += it -> second;
      return words;
    }
    
    std :: vector < std :: pair <std :: string, int> > & getfreq() {
      freq.clear();
      for (std :: map <std :: string, int> :: iterator it = tokens.begin(); it != tokens.end(); ++ it)
        freq.push_back(std :: make_pair(token_name[it -> first], it -> second));
      std :: sort(freq.begin(), freq.end(), Tools :: cmp);
      return freq;
    }
    
    int gettimes(const std :: string &str) {
      std :: string symb = Tools :: simplize(str);
      return tokens[symb];
    }
};

# endif
