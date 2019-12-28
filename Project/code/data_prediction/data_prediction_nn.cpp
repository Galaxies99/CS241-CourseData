# include <vector>
# include <iostream>
# include <cstdlib>
# include <cassert>
# include <cmath>
# include <fstream>
# include <sstream>

# include "../headfiles/data_structure.hpp"
# include "../headfiles/tools.hpp"
# include "../headfiles/exceptions.hpp"
# include "../headfiles/nn/data_manager.hpp"
# include "../headfiles/nn/nn.hpp"

using namespace std;
using namespace Data_Manager;
using namespace simple_nn;
using namespace Basic_Tools;
 
string station_name;

int main() {
  cout << "Please choose a station: \n";
  for (int i = 0; i < 12; ++ i) cout << "  " << (i + 1) << " - " << station_names[i] << endl;
  int id; cin >> id;
  if(id <= 0 || id > 12) {
    cout << "Input Error!\n";
    return 1;
  }  
  station_name = station_names[id - 1];
  
	DataManager Data(station_name);
	
	vector <int> topology;
	topology.push_back(15);
	topology.push_back(10);
	topology.push_back(5);
	topology.push_back(1);
  
  cout << ">>>>>>>>>>>>>>>>>>>>> Training >>>>>>>>>>>>>>>>>>>>>>>>>\n";
  
	Net myNet(topology);

	vector<double> inputVals, targetVals, resultVals;
	int trainingPass = 0;
	
	while(trainingPass < 30000000) {
		++trainingPass;
		
		if(trainingPass % 1000000 == 0) 
      cout << endl << "Pass" << trainingPass << endl;

		// Get new input data and feed it forward:
		if(Data.getNextInputs(inputVals) != topology[0])
			break;
		
		myNet.feedForward(inputVals);

		// Collect the net's actual results:
		myNet.getResults(resultVals);
		
		// Train the net what the outputs should have been:
		Data.getTargetOutputs(targetVals);
		
    assert(targetVals.size() == topology.back());

		myNet.backProp(targetVals);

		// Report how well the training is working, average over recnet
		if(trainingPass % 1000000 == 0)
      cout << "Net recent average error: "
		     << myNet.getRecentAverageError() << endl;
		     
	  Data.increaseTrainingCounts();
  }
  
  cout << ">>>>>>>>>>>>>>>>>>>>> Training End! >>>>>>>>>>>>>>>>>>>>>\n";
  cout << endl << endl;
  cout << ">>>>>>>>>>>>>>>>>>>>>>> Testing >>>>>>>>>>>>>>>>>>>>>>>>>\n";
	
	vector <Record_with_prediction> output; output.clear();
	int testingPass = 0;
	double aver_loss = 0.0;
	while(! Data.testingEof()) {
		if(Data.getNextInputs_test(inputVals) != topology[0])
			break;
		
		++ testingPass;
		
		myNet.feedForward(inputVals);
		// Collect the net's actual results:
		myNet.getResults(resultVals);
		output.push_back(Record_with_prediction(Data.getTestRecord(), abs(resultVals[0]) * 1000));
    // showVector("Outputs:", resultVals);
      
		// Train the net what the outputs should have been:
		Data.getTargetOutputs_test(targetVals);
		
		myNet.backProp(targetVals);
    // showVector("Targets:", targetVals);
		
    // Report how well the training is working, average over recnet
		aver_loss += myNet.getRecentAverageError();
		     
	  Data.increaseTestingCounts();
  }  
  
  aver_loss = aver_loss / testingPass;
  cout << "Average Loss: " << aver_loss << endl;
  
  string optfilename = station_name + "_nn_prediction.csv";
  cout << "\n\n Output to file " << optfilename << " ...\n";
  
  File_Oper f_out(optfilename, "w");
  
  double rms = 0.0;
  
  fprintf(f_out.fp, "year,month,day,hour,PM10,SO2,NO2,CO,O3,TEMP,PRES,DEWP,RAIN,wd,WSPM,PM2.5,PM2.5 (Prediction),\n");
  for (int i = 0; i < output.size(); ++ i) {
    fprintf(f_out.fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,", output[i].rec.year, output[i].rec.month, output[i].rec.day, output[i].rec.hour,
                                                  output[i].rec.PM10, output[i].rec.SO2, output[i].rec.NO2, output[i].rec.CO, output[i].rec.O3);
    fprintf(f_out.fp, "%.1lf,%.1lf,%.1lf,%.1lf,", output[i].rec.temp.get_data(), output[i].rec.pres.get_data(), output[i].rec.dewp.get_data(), output[i].rec.rain.get_data());
    fprintf(f_out.fp, "%s,%.1lf,%d,%d,\n", wind_to_string[output[i].rec.wd].c_str(), output[i].rec.wspm.get_data(), output[i].rec.PM25, output[i].prediction);
    rms += (output[i].prediction - output[i].rec.PM25) * (output[i].prediction - output[i].rec.PM25);
  }
  rms = rms / output.size();
  rms = sqrt(rms);
  
  cout << "RMS: " << rms << endl;
  
  cout << endl << "Done." << endl;
  cout << ">>>>>>>>>>>>>>>>>>>>> Testing End! >>>>>>>>>>>>>>>>>>>>>>\n";
  return 0;
}
