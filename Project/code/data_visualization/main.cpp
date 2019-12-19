# include "../headfiles/GUI/Simple_window.h"
# include "../headfiles/GUI/Graph.h"
# include "../headfiles/GUI/Chart.hpp"
# include "../headfiles/GUI/std_lib_facilities.h"

# include "../headfiles/data_structure.hpp"
# include "../headfiles/exceptions.hpp"
# include "../headfiles/tools.hpp"

# include <iostream>
# include <fstream>
# include <string>

using namespace std;

string station_name;

int main() {
  cout << "Please input station name: ";
  cin >> station_name;
  Record_List l(station_name);

  cout << "Reading data ...\n";
  try {
    File_Oper f_in("../../data/" + station_name +  ".dat", "rb+");
    int n; f_in.readFile(&n, 0, sizeof(int));
    size_t offset = sizeof(int);
    Record temp;
    for (int i = 0; i < n; ++ i) {
      f_in.readFile(&temp, offset, sizeof(Record));
      l.rec.push_back(temp);
      offset += sizeof(Record);
    }
  } catch(...) {
    cout << "Read file error!\n";
    return 1;
  }

  cout << "Read data from \"" << station_name << ".dat\" successfully!\n\n";
  Data_Testing :: output_test(l);

  int op;
  cout << endl << endl;
  try {
    cout << "Select data to visualize: \n";
    for (int i = 1; i <= 12; ++ i) {
      cout << "  " << i << " - " << op_to_string[i];
      if(i == 11) cout << " (Pie Chart)";
      else cout << " (Line Chart)";
      cout << ";\n";
    }
    for (int i = 1; i <= 12; ++ i) {
      cout << "  " << i + 12 << " - " << op_to_string[i];
      if(i == 11) cout << " (Radar Chart)";
      else cout << " (Bar Chart)";
      if(i == 12) cout << ".\n";
      else cout << ";\n";
    }
    cin >> op;
    if(op < 1 || op > 24) throw Option_Error();
  } catch(...) {
    cout << "Option error!\n";
    return 1;
  }

  if(op == 11 || op == 23) {
    cout << "Preparing & Constructing Data ... \n";
    vData v;
    try {
      v = Visualization_Data_Constructing :: construct_wind_data(op, l);
    } catch(...) {
      cout << "Input Date Error or No Data!\n";
      return 1;
    }

    int width = 700;
    Point tl(50, 50);
    Simple_window win(tl, width, 600, "Data Visualization");

    Chart c(width, station_name, v);
    win.attach (c);

    win.wait_for_button();
  } else {
    cout << "Preparing Data ... \n";
    vector <Pre_vData> pv;
    try {
      pv = Visualization_Data_Constructing :: construct_pre_data(op, l);
    } catch(...) {
      cout << "Input Date Error!\n";
      return 1;
    }

    vData v;
    cout << "Constructing figure ... \n";
    try {
      v = Visualization_Data_Constructing :: construct_data(op, pv);
    } catch(...) {
      cout << "No Data!\n";
      return 1;
    }

    cout << "\nFigure constructing completed! \n";

    int width, height;
    if(op <= 12) width = max(static_cast <int> (v.p.size()) * 3 + 200, 800);
    else width = 1100;
    Point tl(50, 50);
    Simple_window win(tl, width, 750, "Data Visualization");

    Chart c(width, station_name, v);
    win.attach (c);

    win.wait_for_button();
  }
  return 0;
}
