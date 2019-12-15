# include <iostream>
# include <fstream>
# include <string>

# include "../headfiles/data_structure.hpp"
# include "../headfiles/exceptions.hpp"
# include "../headfiles/tools.hpp"

using namespace std;

const int MAXN = 10000 + 5;

string station_name, s;
char *str;
  
int main() {
  cin >> station_name;
  Pre_Record_List l(station_name);
  cout << "Reading data ...\n";
  try {
    File_Oper f_in("../../data/PRSA_Data_" + station_name + "_20130301-20170228.csv", "r");
    str = new char [MAXN];  
    // ignore the first line
    int line = 1;
    fscanf(f_in.fp, "%s", str);
    while(~ fscanf(f_in.fp, "%s", str))
      l.rec.push_back(Pre_Record_Generator :: solver(static_cast <string> (str)));
    delete []str;
  } catch(...) {
    cout << "Read file error! \n";
    return 1;
  }
  cout << "Read data Successfully!\n"; 
  cout << "total count: " << l.rec.size() << " Pre_Record(s).\n";
  cout << "\nStoring data ...\n";
  int n = l.rec.size();
  try {
    File_Oper f_out("../../data/" + station_name + "_pre.dat", "rb+");
    f_out.writeFile(&n, 0, sizeof(int));
    size_t offset = sizeof(int);
    for (int i = 0; i < n; ++ i) {
      f_out.writeFile(&l.rec[i], offset, sizeof(Pre_Record));
      offset += sizeof(Pre_Record);
    }
  } catch(...) {
    cout << "Write file Error! \n";
    return 1;
  }
  cout << "Store data as \"" << station_name << "_pre.dat\" successfully!\n"; 
  cout << "total count: " << n << " Pre_Record(s).\n";
  return 0;
}
