# include "../headfiles/data_structure.hpp"
# include "../headfiles/exceptions.hpp"
# include "../headfiles/tools.hpp"
# include "../headfiles/matrix.hpp"

# include <iostream>
# include <fstream>
# include <cstdlib>
# include <string>
# include <time.h> 

using namespace std;

string station_name;

int main() {
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
  
  cout << "\n\nSelecting Training Data & Testing Data ...\n";
  cout << "  Randomly choose 90% of the data as training data, the rest are testing data.\n";  
  
  Record_List train_data(station_name), test_data(station_name);
  
  for (int i = 0; i < l.rec.size(); ++ i) {
    int rnd = rand() % 10;
    if(rnd != 0) train_data.rec.push_back(l.rec[i]);
    else test_data.rec.push_back(l.rec[i]);
  }
  
  cout << "Select successfully.\n";
  cout << "Training data: ";
  Data_Testing :: output_test(train_data);
  cout << "Testing data: ";
  Data_Testing :: output_test(test_data);
  
  Data_Prediction_LinearModel :: solver(train_data, test_data);
  
  return 0;
} 
