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
	�㷨���������ܲ������»����Ͳ������»���������£�����ѡ��ȴ�ʱ��̵Ļ���ʹ�á�
	�㷨������֤����
	  ���ǿ��ǵ�����һ̨��������ʹ��ʱ��ֻ�Ϳ����͹ر�ʱ����ء��� b[i] ��ʾ���� i ��
	  ����ʱ�䣬e[i] ��ʾ���� i ��Ԥ�ڹر�ʱ�䡣
	  1. �������»���������£�����ѡ��ȴ�ʱ��̵Ļ���ѡ�á��ڲ������»���������£�
	     ��Ҫ��������ʵ���Ͼ��ǽ�һ̨���õĻ�����Ԥ�ڹر�ʱ���Ϊ������Ľ���ʱ�䡣
		 ����֮��ѡ������һ̨�����������ʱ��ռ�������������֮��
		 ������������ڵ�ǰ���п�ѡ��Ļ�����˵����ȫ��ͬ�ģ�����̨������һ������
		 ��Ȼ��ˣ�����ѡ��һ̨�ȴ�ʱ����̵Ļ���������񣬿���ʹ�������ȴ�ʱ�䳤�Ļ���
		 �����׻����ǰ�ػ��Ļ��ᣨ�������û�������������Ϳ�����ǰ�ػ��ˣ���
		 ��ˣ�ѡ��ȴ�ʱ��̵Ļ������š�
      2. ����ڲ���Ҫ�����»���������¿����»�����Ȼ���š���֤�����赱ǰ���� i ���ж�ѡ����
	     �����»��� j����֮������� j ��ɵ���������Ϊ list(j)�������� i ��ɵ���������Ϊ list(i)
		 ����Խ��� list(i) �� list(j) �õ��²��ԣ�����ԭ������ i ���ķָ����� j ����ԭ��
		 ���� j ���ķָ����� i ��������Ȼ�����������»������ٿ�������Ȼ���š�
	  ���ϣ��㷨�����Ե�֤��
	*/
  }
  
  return 0;
}
 
