# ifndef _NODE_RECOGNITION_HPP_
# define _NODE_RECOGNITION_HPP_

# include <cctype>
# include <vector>
# include <iostream>
# include <algorithm>

class LineParsor {
    std :: vector < std :: pair <int, int> > ret;
  public:
    LineParsor() = default;
    
    const std :: vector < std :: pair <int, int> >& parse(const std :: string &str) {
      std :: vector <int> tem;
      ret.clear();
      for (int i = 0; i < str.length(); ++ i) {
        if(str[i] == '<') {
          int j = i + 1;
          while(j < str.length() && str[j] != '>') ++ j;
          if(j == str.length()) throw "> not found!";
          
          tem.clear();
          int temp = 0;
          for (int k = i + 1; k < j; ++ k) {
            if(str[k] != ' ' && !isdigit(str[k])) throw "invalid input!";
            if(isdigit(str[k])) temp = temp * 10 + str[k] - '0';
            if(str[k] == ' ') {
              if(isdigit(str[k - 1])) {
                tem.push_back(temp);
                temp = 0;
              }
            }
          }
          if(isdigit(str[j - 1])) {
            tem.push_back(temp);
            temp = 0;
          }
          
          if(tem.size() > 2) throw "invalid input!";
          if(tem.size() == 1) ret.push_back(std :: make_pair(tem[0], -1));
          if(tem.size() == 2) ret.push_back(std :: make_pair(tem[0], tem[1])); 
          
          i = j;
        } else if(str[i] != ' ') throw "invalid input!"; 
      }
      return ret;
    }
    
    ~ LineParsor() = default;
};

enum SubGraphType {Node = 0, Binary, Tree, Graph};
 
class GraphParsor {
  private:   
    struct SubGraph {
      SubGraphType type;
      int w, sz;
      
      SubGraph(SubGraphType _type, int _w, int _sz) { type = _type; w = _w; sz = _sz; }
      void prt(std :: ostream &os) {
        os << "--";
        switch(type) {
          case Node: os << "Node. "; break;
          case Binary: os << "Binary tree. "; break;
          case Tree: os << "Tree. "; break;
          case Graph: os << "Graph. "; break;
          default: throw "error!";
        }
        os << "Weight: " << w << ". Size: " << sz << ".";
      }
      friend bool operator < (const SubGraph &a, const SubGraph &b) {
        return a.type < b.type || (a.type == b.type && a.w < b.w) || (a.type == b.type && a.w == b.w && a.sz < b.sz);
      }
      ~SubGraph() = default;
    };
    
    std :: vector < std :: pair < int, int > > edge;
    std :: vector < SubGraph > ans;
    int mx_vid;
    bool *vvalid;
    bool *vis, *rvis;
    bool *un_mark; 
    std :: vector <int> *G, *Gr; 
    
    std :: pair < std :: pair <int, int>, bool > chkBinary(int x) {
      vis[x] = 1;
      int a = x, b = 1;
      bool c = (G[x].size() <= 2);
      for (int i = 0; i < G[x].size(); ++ i) {
        std :: pair < std :: pair <int, int>, bool > t = chkBinary(G[x][i]);
        a += t.first.first, b += t.first.second;
        c &= t.second;
      }
      return std :: make_pair(std :: make_pair(a, b), c); 
    }
    
    std :: pair <int, int> chkGraph(int x) {
      vis[x] = 1;
      int a = x, b = 1;
      for (int i = 0; i < G[x].size(); ++ i) {
        int y = G[x][i];
        if(vis[y]) continue;
        std :: pair < int, int > t = chkGraph(y);
        a += t.first; b += t.second;
      }
      for (int i = 0; i < Gr[x].size(); ++ i) {
        int y = Gr[x][i];
        if(vis[y]) continue;
        std :: pair < int, int > t = chkGraph(y);
        a += t.first; b += t.second;
      }
      return std :: make_pair(a, b);
    }
    
    bool chkTreeStrong(int x, int fa = -1) {
      rvis[x] = 1;
      bool c = (G[x].size() <= 2);
      if(fa == -1) c &= (Gr[x].size() == 0);
      else c &= (Gr[x].size() == 1 && Gr[x][0] == fa);
      for (int i = 0; i < G[x].size(); ++ i) {
        if(rvis[G[x][i]]) return false;
        bool t = chkTreeStrong(G[x][i], x);
        c &= t;
      }
      return c; 
    }
    
    void parse() {
      for (int i = 0; i < edge.size(); ++ i) {
        if(edge[i].second == -1) {
          un_mark[edge[i].first] = 1;
          continue;
        }
        G[edge[i].second].push_back(edge[i].first);
        Gr[edge[i].first].push_back(edge[i].second);
        un_mark[edge[i].first] = 1;
      }
      for (int i = 0; i < edge.size(); ++ i) {
        if(edge[i].second != -1) continue;
        int x = edge[i].first;
        if(G[x].size() == 0) {
          vis[x] = 1;
          ans.push_back(SubGraph(Node, x, 1));
          continue;
        }
        std :: pair < std :: pair <int, int>, bool > t = chkBinary(x);
        if(t.second == false) ans.push_back(SubGraph(Tree, t.first.first, t.first.second));
        else ans.push_back(SubGraph(Binary, t.first.first, t.first.second));
      }
      for (int i = 0; i <= mx_vid; ++ i) {
        if(vvalid[i] && !un_mark[i] && !vis[i]) {
          rvis = new bool[mx_vid + 3];
          for (int j = 0; j <= mx_vid; ++ j) rvis[j] = vis[j];
          bool flag = chkTreeStrong(i);
          if(flag == true) {
            std :: pair < std :: pair <int, int>, bool > t = chkBinary(i);
            if(t.second == false) ans.push_back(SubGraph(Tree, t.first.first, t.first.second));
            else ans.push_back(SubGraph(Binary, t.first.first, t.first.second));
          }
          if(rvis != nullptr) delete [] rvis;
        }
      }
      for (int i = 0; i <= mx_vid; ++ i) {
        if(vvalid[i] && !vis[i]) {
          std :: pair <int, int> t = chkGraph(i);
          ans.push_back(SubGraph(Graph, t.first, t.second));
        }
      }
      sort(ans.begin(), ans.end());
    }
    
  public:
    GraphParsor(const std :: vector < std :: pair <int, int> > e) : edge(e) {
      ans.clear();
      mx_vid = -1;
      for (int i = 0; i < edge.size(); ++ i) {
        mx_vid = std :: max(mx_vid, edge[i].first);
        mx_vid = std :: max(mx_vid, edge[i].second);
      }
      
      vvalid = new bool[mx_vid + 3];
      vis = new bool[mx_vid + 3];
      un_mark = new bool[mx_vid + 3];
      G = new std :: vector<int> [mx_vid + 3];
      Gr = new std :: vector<int> [mx_vid + 3];
      for (int i = 0; i <= mx_vid; ++ i) vvalid[i] = vis[i] = un_mark[i] = 0, G[i].clear(), Gr[i].clear();
            
      for (int i = 0; i < edge.size(); ++ i) {
        vvalid[edge[i].first] = 1;
        if(edge[i].second != -1) vvalid[edge[i].second] = 1;
      }
      parse();
    }
    
    void output(std :: ostream& os) {
      os << "We have recognized " << ans.size() << " graph";
      if(ans.size() >= 2) os << "s";
      os << "."; 
      for (int i = 0; i < ans.size(); ++ i) {
        os << "\n";
        ans[i].prt(os);
      }
    }
    
    ~ GraphParsor() {
      if(vvalid != nullptr) delete []vvalid;
      if(vis != nullptr) delete []vis; 
      if(un_mark != nullptr) delete []un_mark;
      if(G != nullptr) delete []G;
      if(Gr != nullptr) delete []Gr;
    }
};


# endif 
