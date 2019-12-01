# include <map>
# include <string>
# include <vector> 
# include <cctype>
# include <stdio.h>
# include <cstring>
# include <assert.h>
# include <iostream>
# include <algorithm>
 
using namespace std;

struct pa {
  string id;
  int s, t;
  pa() {}
  pa(string id, int s, int t) : id(id), s(s), t(t) {}
  friend bool operator < (pa a, pa b) {
    return a.s < b.s || (a.s == b.s && a.t < b.t);
  }
};

int n;
string str;

map <string, bool> ider;
vector <pa> p;
vector <int> core;

struct new_core {
  int b, e;
  vector <int> id;
  new_core() {} 
};

vector <new_core> newCore; 

void dealData() {
  for (int i = 0; i < str.size(); ++ i) {
    if(str[i] == '<') {
      int j = i + 1;
      string id = "";
      while(j < str.size() && str[j] != ' ') {
        if(id == "" && str[j] != 'e') throw 233;
        if(id != "" && !isdigit(str[j])) throw 233; 
        id += str[j];
        ++ j;
      }
      if(ider[id] == 1) throw 233;
      ider[id] = 1;
      if(j == str.size()) throw 233;
      int s = 0, t = 0;
      ++ j;
      while(j < str.size() && str[j] != ' ') {
        if(!isdigit(str[j])) throw 233;
        s = s * 10 + str[j] - '0';
        ++ j;
      } 
      if(j == str.size()) throw 233;
      ++ j;
      while(j < str.size() && str[j] != '>') {
        if(!isdigit(str[j])) throw 233;
        t = t * 10 + str[j] - '0';
        ++ j;
      }
      if(j == str.size()) throw 233;
      p.push_back(pa(id, s, t));
      i = j;
      if(s >= t) throw 233; 
    } else throw 233;
  }
}

int main() {
  bool exercise_1 = false;
  getline(cin, str);
  try {
    dealData();
  } catch(...) {
    cout << "error";
    return 0;
  }
  // for (int i = 0; i < p.size(); ++ i) cout << p[i].id << ' ' << p[i].s << ' ' << p[i].t << endl;
  sort(p.begin(), p.end());
  
  for (int i = 0; i < p.size(); ++ i) {
    int id = -1;
    for (int j = 0; j < core.size(); ++ j) 
      if(core[j] <= p[i].s) {
        id = j;
        break;
      } 
    if(id == -1) {
      core.push_back(p[i].t);
    } else {
      core[id] = p[i].t; 
    }
  }
  int n = core.size();
  
  if(exercise_1 == true) {
    cout << n;
  } else {
    newCore.resize(n); int m = 0;
    for (int i = 0; i < p.size(); ++ i) {
      int id = -1;
      for (int j = 0; j < m; ++ j) {
        if(newCore[j].e <= p[i].s) {
          if(id == -1) id = j;
          else if(p[i].s - newCore[j].e < p[i].s - newCore[id].e) id = j;
        }
      }
      if(id == -1) {
        newCore[m].b = p[i].s;
        newCore[m].e = p[i].t;
        newCore[m].id.push_back(i);
        ++ m;
      } else {
        newCore[id].e = p[i].t;
        newCore[id].id.push_back(i);
      }
    }
    assert(n == m);
    int tot = 0;
    for (int i = 0; i < n; ++ i) 
      tot += newCore[i].e - newCore[i].b;
    cout << tot << endl;
    for (int i = 0; i < n; ++ i) {
      for (int j = 0; j < newCore[i].id.size(); ++ j) {
        if(j == 0) cout << "{";
        else cout << ",";
        cout << p[newCore[i].id[j]].id;
      }
      cout << "}";
	    if(i != n - 1) cout << ' ';
    }
	/*
	算法描述：在能不开启新机器就不开启新机器的情况下，优先选择等待时间短的机器使用。
	算法最优性证明：
	  我们考虑到对于一台机器，其使用时间只和开启和关闭时间相关。用 b[i] 表示机器 i 的
	  开启时间，e[i] 表示机器 i 的预期关闭时间。
	  1. 不开启新机器的情况下，优先选择等待时间短的机器选用。在不开启新机器的情况下，
	     需要做的事情实际上就是将一台可用的机器的预期关闭时间改为新任务的结束时间。
		 换言之，选择任意一台机器，将其的时间占用至新任务结束之后。
		 这个操作，对于当前所有可选择的机器来说是完全相同的（给哪台机器都一样）。
		 既然如此，我们选择一台等待时间最短的机器完成任务，可以使得其他等待时间长的机器
		 更容易获得提前关机的机会（后面如果没有任务分配给他就可以提前关机了）。
		 因此，选择等待时间短的机器更优。
      2. 如果在不必要开启新机器的情况下开启新机器显然不优。反证，假设当前机器 i 空闲而选择了
	     开启新机器 j，设之后给机器 j 完成的任务序列为 list(j)，给机器 i 完成的任务序列为 list(i)
		 则可以交换 list(i) 和 list(j) 得到新策略，即把原来机器 i 做的分给机器 j 做，原来
		 机器 j 做的分给机器 i 做，则显然这样可以让新机器更迟开机，显然更优。
	  综上，算法最优性得证。
	*/
  }
  
  return 0;
}
 
