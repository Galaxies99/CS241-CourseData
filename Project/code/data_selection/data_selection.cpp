# include <iostream>
# include <fstream>
# include <string>

# include "../headfiles/data_structure.hpp"
# include "../headfiles/exceptions.hpp"
# include "../headfiles/tools.hpp"

using namespace std;

string station_name;

int main() {
  cout << "Please input station name: ";
  cin >> station_name;
  Pre_Record_List pl(station_name);
  cout << "Reading data ...\n";
  try {
    File_Oper f_in("../../data/" + station_name +  "_pre.dat", "rb+");
    int n; f_in.readFile(&n, 0, sizeof(int));
    size_t offset = sizeof(int);
    Pre_Record temp;
    for (int i = 0; i < n; ++ i) {
      f_in.readFile(&temp, offset, sizeof(Pre_Record));
      pl.rec.push_back(temp);
      offset += sizeof(Pre_Record);
    }
  } catch(...) {
    cout << "Read file error!\n";
    return 1;
  }
  
  cout << "Read data from \"" << station_name << "_pre.dat\" successfully!\n\n";
  Data_Testing :: output_test(pl);
  
  cout << "\nFiltering ...\n";
  Record_List l(station_name);
  try {
    for (int i = 0; i < pl.rec.size(); ++ i) {
      pair <Record, bool> r(Pre_Record_Filter :: filter(pl.rec[i]));
      if(r.second == true) l.rec.push_back(r.first);
    }
  } catch(...) {
    cout << "Filter error!\n";
    return 1;
  }
  cout << "Filter successfully!\n\n";
  
  Data_Testing :: output_test(l);
  
  cout << "\nStoring data ...\n";
  int n = l.rec.size();
  try {
    File_Oper f_out("../../data/" + station_name + ".dat", "rb+");
    f_out.writeFile(&n, 0, sizeof(int));
    size_t offset = sizeof(int);
    for (int i = 0; i < n; ++ i) {
      f_out.writeFile(&l.rec[i], offset, sizeof(Record));
      offset += sizeof(Record);
    }
  } catch(...) {
    cout << "Write file Error! \n";
    return 1;
  }
  cout << "Store data as \"" << station_name << ".dat\" Successfully!\n";
  cout << "total count: " << n << " record(s).\n";
  return 0;
}



