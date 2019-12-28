# ifndef _DATA_MANAGER_HPP_
# define _DATA_MANAGER_HPP_

# include "../data_structure.hpp"
# include "../tools.hpp"

namespace Data_Manager {
  class DataManager {
    public:
  	  DataManager(const string &station_name);
  	  // Returns the number of input values read from the file:
  	  int getNextInputs(vector<double> &inputVals);
  	  int getTargetOutputs(vector<double> &targetOutputVals);
      int increaseTrainingCounts();
      int getNextInputs_test(vector<double> &inputVals);
      int getTargetOutputs_test(vector<double> &targetOutputVals);
      int increaseTestingCounts();
      bool testingEof() const;
      Record getTestRecord() const;  
    private:
  	  Record_List train_data, test_data;
  	  int train_data_num, test_data_num;
  };
  
  DataManager :: DataManager(const string &station_name) : train_data(station_name), test_data(station_name) {
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
      exit(-1);
    }
  
    cout << "Read data from \"" << station_name << ".dat\" successfully!\n\n";
    Data_Testing :: output_test(l);  
    
    cout << "\n\nSelecting Training Data & Testing Data ...\n";
    cout << "  Randomly choose 90% of the data as training data, the rest are testing data.\n"; 
    
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
    cout << "\n\n";
    train_data_num = 0;
    test_data_num = 0;
  }
  
  int DataManager :: getNextInputs(vector<double> &inputVals) {
    inputVals.clear();
    // regularazation
    inputVals.push_back((train_data.rec[train_data_num].year - 2012) / 6.0);
    inputVals.push_back((train_data.rec[train_data_num].month + 1) / 14.0);
    inputVals.push_back((train_data.rec[train_data_num].day + 1) / 33.0);
    inputVals.push_back((train_data.rec[train_data_num].hour + 1) / 26.0);
    inputVals.push_back((train_data.rec[train_data_num].temp.get_data() + 40.0) / 80.0);
    inputVals.push_back((train_data.rec[train_data_num].pres.get_data() - 960) / 100.0);
    inputVals.push_back((train_data.rec[train_data_num].dewp.get_data() + 40.0) / 80.0);
    inputVals.push_back((train_data.rec[train_data_num].rain.get_data()) / 100.0);
    inputVals.push_back((train_data.rec[train_data_num].wd) / 20.0);
    inputVals.push_back((train_data.rec[train_data_num].wspm.get_data()) / 20.0);
    inputVals.push_back((train_data.rec[train_data_num].PM10) / 1000.0);
    inputVals.push_back((train_data.rec[train_data_num].SO2) / 500.0);
    inputVals.push_back((train_data.rec[train_data_num].NO2) / 500.0);
    inputVals.push_back((train_data.rec[train_data_num].CO) / 15000.0);
    inputVals.push_back((train_data.rec[train_data_num].O3) / 700.0);
    return inputVals.size();
  }
  
  int DataManager :: getTargetOutputs(vector<double> &targetOutputVals) {
    targetOutputVals.clear();
    // regularazation
    targetOutputVals.push_back((train_data.rec[train_data_num].PM25) / 1000.0);
    return targetOutputVals.size();
  }
  
  int DataManager :: increaseTrainingCounts() {
    ++ train_data_num;
    if(train_data_num == train_data.rec.size()) train_data_num = 0;
    return train_data_num;
  }
  
  int DataManager :: getNextInputs_test(vector<double> &inputVals) {
    inputVals.clear();
    // regularazation
    inputVals.push_back((test_data.rec[test_data_num].year - 2012) / 6.0);
    inputVals.push_back((test_data.rec[test_data_num].month + 1) / 14.0);
    inputVals.push_back((test_data.rec[test_data_num].day + 1) / 33.0);
    inputVals.push_back((test_data.rec[test_data_num].hour + 1) / 26.0);
    inputVals.push_back((test_data.rec[test_data_num].temp.get_data() + 40.0) / 80.0);
    inputVals.push_back((test_data.rec[test_data_num].pres.get_data() - 960) / 100.0);
    inputVals.push_back((test_data.rec[test_data_num].dewp.get_data() + 40.0) / 80.0);
    inputVals.push_back((test_data.rec[test_data_num].rain.get_data()) / 100.0);
    inputVals.push_back((test_data.rec[test_data_num].wd) / 20.0);
    inputVals.push_back((test_data.rec[test_data_num].wspm.get_data()) / 20.0);
    inputVals.push_back((test_data.rec[test_data_num].PM10) / 1000.0);
    inputVals.push_back((test_data.rec[test_data_num].SO2) / 500.0);
    inputVals.push_back((test_data.rec[test_data_num].NO2) / 500.0);
    inputVals.push_back((test_data.rec[test_data_num].CO) / 15000.0);
    inputVals.push_back((test_data.rec[test_data_num].O3) / 700.0);
    return inputVals.size();
  }
  
  int DataManager :: getTargetOutputs_test(vector<double> &targetOutputVals) {
    targetOutputVals.clear();
    // regularazation
    targetOutputVals.push_back((test_data.rec[test_data_num].PM25) / 1000.0);
    return targetOutputVals.size();
  }
  
  int DataManager :: increaseTestingCounts() {
    ++ test_data_num;
    return test_data_num;
  }
  
  Record DataManager :: getTestRecord() const {
    return test_data.rec[test_data_num];
  }
  
  bool DataManager :: testingEof() const {
    return test_data_num >= test_data.rec.size();
  }
}

# endif 
