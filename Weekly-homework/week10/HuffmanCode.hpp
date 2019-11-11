# ifndef _HUFFMAN_CODE_HPP_
# define _HUFFMAN_CODE_HPP_

# include <vector>
# include <string>
# include <queue>

using std :: priority_queue;
using std :: greater;
using std :: string;
using std :: vector;
using std :: pair;

class HuffmanCode {
  private:
    vector <int> freq, par, code;
    priority_queue < pair <int, int> , vector < pair <int, int> >, greater < pair <int, int> > > q;
    void freqCounter(const string &str) {
      freq.resize(256);
      for (int i = 0; i < 256; ++ i) freq[i] = 0;
      for (int i = 0; i < str.length(); ++ i) freq[str[i]] ++;
    }
    
    void huffmanSolver() {
      par.resize(512); code.resize(512);
      for (int i = 0; i < 512; ++ i) par[i] = 0, code[i] = 0;
      while(!q.empty()) q.pop();
      for (int i = 0; i < 256; ++ i)
        if(freq[i]) q.push(std :: make_pair(freq[i], i));
      if(q.size() == 1) {
        for (int i = 0; i < 256; ++ i)
          if(freq[i]) code[i] = 1;
      } else {
        int id = 256;
        while(q.size() > 1) {
          pair <int, int> top1 = q.top(); q.pop();
          pair <int, int> top2 = q.top(); q.pop();
          par[top1.second] = id;
          par[top2.second] = id;
          q.push(std :: make_pair(top1.first + top2.first, id));
          ++ id;
        }
        for (int i = id; i >= 0; -- i) {
          if(i < 256) {
            if(freq[i] == 0) code[i] = 0;
            else code[i] = code[par[i]] + 1;
          } else {
            if(par[i] == 0) code[i] = 0;
            else code[i] = code[par[i]] + 1;
          }
        }
      }
    }
  
  public:
    HuffmanCode(const string &str) {
      freqCounter(str);
      huffmanSolver();
    }
    
    int HuffmanLength() const {
      int len = 0;
      for (int i = 0; i < 256; ++ i) 
        len += code[i] * freq[i];
      return len;
    }
    
    ~ HuffmanCode() = default;
}; 

# endif
