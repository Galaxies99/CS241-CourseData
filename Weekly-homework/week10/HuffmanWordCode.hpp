# ifndef _HUFFMAN_WORD_CODE_HPP
# define _HUFFMAN_WORD_CODE_HPP

# include <string>
# include <vector>
# include <cctype>
# include <queue>
# include <map>

using std :: priority_queue;
using std :: greater;
using std :: string;
using std :: vector;
using std :: pair;
using std :: map;

class HuffmanWordCode {
  private:
    int prelength;
    map <string, int> _freq;
    vector <int> freq, par, code;
    priority_queue < pair <int, int> , vector < pair <int, int> >, greater < pair <int, int> > > q;
    
    void freqCounter(const string &str) {
      _freq.clear(); freq.clear();
      prelength = 0;
      for (int i = 0; i < str.length(); ++ i) {
        if(isalpha(str[i])) {
          string word = "" + str[i];
          int j = i + 1;
          while(j < str.length() && isalpha(str[j])) word = word + str[j++];
          _freq[word] ++;          
          i = j - 1;
        } else ++ prelength;
      }
      for (map <string, int> :: iterator it = _freq.begin(); it != _freq.end(); ++ it)
        freq.push_back(it -> second);
    }
    
    void huffmanSolver() {
      int n = freq.size();
      par.resize(n + n); code.resize(n + n);
      for (int i = 0; i < n + n; ++ i) par[i] = 0, code[i] = 0;
      while(!q.empty()) q.pop();
      for (int i = 0; i < n; ++ i)
        q.push(std :: make_pair(freq[i], i));
      if(q.size() == 1) code[0] = 1;
      else {
        int id = n;
        while(q.size() > 1) {
          pair <int, int> top1 = q.top(); q.pop();
          pair <int, int> top2 = q.top(); q.pop();
          par[top1.second] = id;
          par[top2.second] = id;
          q.push(std :: make_pair(top1.first + top2.first, id));
          ++ id;
        }
        for (int i = id; i >= 0; -- i) {
          if(i < n) {
            code[i] = code[par[i]] + 1;
          } else {
            if(par[i] == 0) code[i] = 0;
            else code[i] = code[par[i]] + 1;
          }
        }
      }
    }
    
  public:
    HuffmanWordCode(const string &str) {
      freqCounter(str);
      huffmanSolver();
    }
    
    int HuffmanLength() const {
      int len = 0;
      for (int i = 0; i < freq.size(); ++ i) 
        len += code[i] * freq[i];
      return len + 8 * prelength;
    }
    
    ~ HuffmanWordCode() = default;
};

# endif 
