# ifndef _PREDICTION_HPP_
# define _PREDICTION_HPP_

# include "tools.hpp"
# include "data_structure.hpp"
# include "exceptions.hpp"

namespace Data_Prediction_LinearModel {
  void solver(const Record_List& train_data, const Record_List& test_data) {
    Matrix A(train_data.rec.size(), 15), B(train_data.rec.size(), 1);
    for (int i = 0; i < train_data.rec.size(); ++ i) {
      A(i, 0) = train_data.rec[i].temp.get_data();
      A(i, 1) = train_data.rec[i].pres.get_data();
      A(i, 2) = train_data.rec[i].dewp.get_data();
      A(i, 3) = train_data.rec[i].rain.get_data();
      A(i, 4) = train_data.rec[i].wd;
      A(i, 5) = train_data.rec[i].wspm.get_data();
      A(i, 6) = train_data.rec[i].PM10;
      A(i, 7) = train_data.rec[i].SO2;
      A(i, 8) = train_data.rec[i].NO2;
      A(i, 9) = train_data.rec[i].CO;
      A(i, 10) = train_data.rec[i].O3;
      A(i, 11) = train_data.rec[i].hour;
      A(i, 12) = train_data.rec[i].month;
      A(i, 13) = train_data.rec[i].year;
      A(i, 14) = train_data.rec[i].day;
      B(i, 0) = train_data.rec[i].PM25;
    }
    Matrix AT = A.transposition();
    cout << "Matrix multiplying ......\n";
    Matrix ATA = AT * A;
    cout << "Matrix inversing ......\n";
    Matrix ATA_inv = ATA.inverse();
    cout << "Generating theta ......\n";
    Matrix theta = ATA_inv * AT * B;
    // theta.output();
    cout << "Testing ...";
    
    Matrix C(test_data.rec.size(), 15), D(test_data.rec.size(), 1);
    for (int i = 0; i < test_data.rec.size(); ++ i) {
      C(i, 0) = test_data.rec[i].temp.get_data();
      C(i, 1) = test_data.rec[i].pres.get_data();
      C(i, 2) = test_data.rec[i].dewp.get_data();
      C(i, 3) = test_data.rec[i].rain.get_data();
      C(i, 4) = test_data.rec[i].wd;
      C(i, 5) = test_data.rec[i].wspm.get_data();
      C(i, 6) = test_data.rec[i].PM10;
      C(i, 7) = test_data.rec[i].SO2;
      C(i, 8) = test_data.rec[i].NO2;
      C(i, 9) = test_data.rec[i].CO;
      C(i, 10) = test_data.rec[i].O3;
      C(i, 11) = test_data.rec[i].hour;
      C(i, 12) = test_data.rec[i].month;
      C(i, 13) = test_data.rec[i].year;
      C(i, 14) = test_data.rec[i].day;
      D(i, 0) = test_data.rec[i].PM25; 
    }
    
    Matrix E = C * theta;
    double aver = 0, aver2;
    int max_loss = 0;
    
    for (int i = 0; i < test_data.rec.size(); ++ i) {
      int predict_number = static_cast <int> (E(i, 0) + 0.5);
      if(predict_number < 0) predict_number = 0;
      int loss = abs(predict_number - D(i, 0));
      aver += loss;
      aver2 += loss * loss; 
    }
    
    aver /= test_data.rec.size();
    aver2 /= test_data.rec.size();
    aver2 = sqrt(aver2);
    cout << "Average Loss: " << aver << '\n';
    cout << "Average RMS Loss: " << aver2 << '\n';
  } 
}


namespace Data_Prediction_Model_ArgumentsSample {
  void solver(const Record_List& train_data, const Record_List& test_data) {
    Matrix A(train_data.rec.size(), 21), B(train_data.rec.size(), 1);
    for (int i = 0; i < train_data.rec.size(); ++ i) {
      A(i, 0) = train_data.rec[i].temp.get_original_data();
      A(i, 1) = train_data.rec[i].pres.get_original_data();
      A(i, 2) = train_data.rec[i].dewp.get_original_data();
      A(i, 3) = train_data.rec[i].rain.get_original_data();
      A(i, 4) = train_data.rec[i].wd;
      A(i, 5) = train_data.rec[i].wspm.get_original_data();
      A(i, 6) = train_data.rec[i].PM10;
      A(i, 7) = train_data.rec[i].SO2;
      A(i, 8) = train_data.rec[i].NO2;
      A(i, 9) = train_data.rec[i].CO;
      A(i, 10) = train_data.rec[i].O3;
      A(i, 11) = train_data.rec[i].hour;
      A(i, 12) = train_data.rec[i].month;
      A(i, 13) = train_data.rec[i].year;
      A(i, 14) = train_data.rec[i].day;
      A(i, 15) = A(i, 2) * A(i, 2);
      A(i, 16) = (A(i, 0) <= 5);
      A(i, 17) = (A(i, 2) <= 5);
      A(i, 18) = (A(i, 6) >= 200);
      A(i, 19) = (A(i, 7) >= 10);
      A(i, 20) = (A(i, 9) > 1600);
      B(i, 0) = train_data.rec[i].PM25;
    }
    Matrix AT = A.transposition();
    cout << "Matrix multiplying ......\n";
    Matrix ATA = AT * A;
    cout << "Matrix inversing ......\n";
    Matrix ATA_inv = ATA.inverse();
    cout << "Generating theta ......\n";
    Matrix theta = ATA_inv * AT * B;
    theta.output();
    cout << "Testing ...";
    
    Matrix C(test_data.rec.size(), 21), D(test_data.rec.size(), 1);
    for (int i = 0; i < test_data.rec.size(); ++ i) {
      C(i, 0) = test_data.rec[i].temp.get_original_data();
      C(i, 1) = test_data.rec[i].pres.get_original_data();
      C(i, 2) = test_data.rec[i].dewp.get_original_data();
      C(i, 3) = test_data.rec[i].rain.get_original_data();
      C(i, 4) = test_data.rec[i].wd;
      C(i, 5) = test_data.rec[i].wspm.get_original_data();
      C(i, 6) = test_data.rec[i].PM10;
      C(i, 7) = test_data.rec[i].SO2;
      C(i, 8) = test_data.rec[i].NO2;
      C(i, 9) = test_data.rec[i].CO;
      C(i, 10) = test_data.rec[i].O3;
      C(i, 11) = test_data.rec[i].hour;
      C(i, 12) = test_data.rec[i].month;
      C(i, 13) = test_data.rec[i].year;
      C(i, 14) = test_data.rec[i].day;
      C(i, 15) = C(i, 2) * C(i, 2);
      C(i, 16) = (C(i, 0) <= 5); 
      C(i, 17) = (C(i, 2) <= 5);
      C(i, 18) = (C(i, 6) >= 200);
      C(i, 19) = (C(i, 7) >= 100);
      C(i, 20) = (C(i, 9) > 1600);
      D(i, 0) = test_data.rec[i].PM25; 
    }
    
    Matrix E = C * theta;
    double aver = 0, aver2;
    int max_loss = 0;
    
    for (int i = 0; i < test_data.rec.size(); ++ i) {
      int predict_number = static_cast <int> (E(i, 0) + 0.5);
      if(predict_number < 0) predict_number = 0;
      int loss = abs(predict_number - D(i, 0));
      aver += loss;
      aver2 += loss * loss; 
    }
    
    aver /= test_data.rec.size();
    aver2 /= test_data.rec.size();
    aver2 = sqrt(aver2);
    cout << "Average Loss: " << aver << '\n';
    cout << "Average RMS Loss: " << aver2 << '\n';
  } 
}

# endif 
