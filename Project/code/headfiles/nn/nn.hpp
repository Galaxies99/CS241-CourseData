# ifndef _NN_HPP_
# define _NN_HPP_

# include <iostream> 
# include <vector>
# include <assert.h>
# include <math.h>

using std :: vector;
using std :: cout;
using std :: endl;
using std :: string;

namespace simple_nn {
  
  struct Connection {
  	double weight;
  	double deltaWeight;
  };
  
  class Neuron;
  
  typedef vector<Neuron> Layer;
  
  // ****************** class Neuron ******************
  class Neuron {
    public:
    	Neuron(int numOutputs, int myIndex);
    	void setOutputVal(double val) { m_outputVal = val; }
    	double getOutputVal(void) const { return m_outputVal; }
    	void feedForward(const Layer &prevLayer);
    	void calcOutputGradients(double targetVals);
    	void calcHiddenGradients(const Layer &nextLayer);
    	void updateInputWeights(Layer &prevLayer);
    private:
    	static double eta; // [0.0...1.0] overall net training rate
    	static double alpha; // [0.0...n] multiplier of last weight change [momentum]
    	static double transferFunction(double x);
    	static double transferFunctionDerivative(double x);
    	// randomWeight: 0 - 1
    	static double randomWeight(void) { return rand() / double(RAND_MAX); }
    	double sumDOW(const Layer &nextLayer) const;
    	double m_outputVal;
    	vector <Connection> m_outputWeights;
    	int m_myIndex;
    	double m_gradient;
  };
  
  double Neuron :: eta = 0.15; // overall net learning rate
  double Neuron :: alpha = 0.5; // momentum, multiplier of last deltaWeight, [0.0..n]
  
  // The weights to be updated are in the Connection container
  // in the nuerons in the preceding layer
  void Neuron :: updateInputWeights(Layer &prevLayer) {
  	for(int n = 0; n < prevLayer.size(); ++n) {
  		Neuron &neuron = prevLayer[n];
  		double oldDeltaWeight = neuron.m_outputWeights[m_myIndex].deltaWeight;
      // Individual input, magnified by the gradient and train rate, 
      // also add momentum = a fraction of the previous delta weight
  		double newDeltaWeight = eta * neuron.getOutputVal() * m_gradient + alpha * oldDeltaWeight;
  		neuron.m_outputWeights[m_myIndex].deltaWeight = newDeltaWeight;
  		neuron.m_outputWeights[m_myIndex].weight += newDeltaWeight;
  	}
  }
  
  // Sum our contributions of the errors at the nodes we feed
  double Neuron :: sumDOW(const Layer &nextLayer) const {
  	double sum = 0.0;
  	for (int n = 0; n < nextLayer.size() - 1; ++n)
  		sum += m_outputWeights[n].weight * nextLayer[n].m_gradient;
  	return sum;
  }
  
  void Neuron :: calcHiddenGradients(const Layer &nextLayer) {
  	double dow = sumDOW(nextLayer);
  	m_gradient = dow * Neuron::transferFunctionDerivative(m_outputVal);
  }
  
  void Neuron :: calcOutputGradients(double targetVals) {
  	double delta = targetVals - m_outputVal;
  	m_gradient = delta * Neuron::transferFunctionDerivative(m_outputVal);
  }
  
  double Neuron :: transferFunction(double x) {
  	return tanh(x);
  }
  
  double Neuron :: transferFunctionDerivative(double x) {
  	return 1.0 - x * x;
  }
  
  // Sum the previous layer's outputs (which are our inputs)
  // Include the bias node from the previous layer.
  void Neuron :: feedForward(const Layer &prevLayer) {
  	double sum = 0.0;
  	for(int n = 0 ; n < prevLayer.size(); ++n)
  		sum += prevLayer[n].getOutputVal() * prevLayer[n].m_outputWeights[m_myIndex].weight;
  	m_outputVal = Neuron::transferFunction(sum);
  }
  
  Neuron :: Neuron(int numOutputs, int myIndex) {
  	for(int c = 0; c < numOutputs; ++c) {
  		m_outputWeights.push_back(Connection());
  		m_outputWeights.back().weight = randomWeight();
  	}
  	m_myIndex = myIndex;
  }
  
  // ****************** class Net ******************
  class Net {
    public:
    	Net(const vector <int> &topology);
    	void feedForward(const vector <double> &inputVals);
    	void backProp(const vector <double> &targetVals);
    	void getResults(vector <double> &resultVals) const;
    	double getRecentAverageError(void) const { return m_recentAverageError; }
    
    private:
    	vector <Layer> m_layers; //m_layers[layerNum][neuronNum]
    	double m_error;
    	double m_recentAverageError;
    	static double m_recentAverageSmoothingFactor;
  };
  
  double Net :: m_recentAverageSmoothingFactor = 100.0; // Number of training samples to average over
  
  void Net :: getResults(vector <double> &resultVals) const {
  	resultVals.clear();
  	for(int n = 0; n < m_layers.back().size() - 1; ++n)
  	  resultVals.push_back(m_layers.back()[n].getOutputVal());
  }
  
  void Net :: backProp(const std::vector <double> &targetVals) {
    // Calculate overal net error (RMS of output neuron errors)
    Layer &outputLayer = m_layers.back();
  	m_error = 0.0;
  	for(int n = 0; n < outputLayer.size() - 1; ++n) {
  		double delta = targetVals[n] - outputLayer[n].getOutputVal();
  		m_error += delta *delta;
  	}
  	m_error /= outputLayer.size() - 1;
  	m_error = sqrt(m_error);
  	
  	// Implement a recent average measurement. 
  	m_recentAverageError = 
  			(m_recentAverageError * m_recentAverageSmoothingFactor + m_error)
  			/ (m_recentAverageSmoothingFactor + 1.0);
  	
    // Calculate output layer gradients
  	for(int n = 0; n < outputLayer.size() - 1; ++n)
  		outputLayer[n].calcOutputGradients(targetVals[n]);
  		
  	// Calculate gradients on hidden layers
  
  	for(int layerNum = m_layers.size() - 2; layerNum > 0; --layerNum) {
  		Layer &hiddenLayer = m_layers[layerNum];
  		Layer &nextLayer = m_layers[layerNum + 1];
  		for(int n = 0; n < hiddenLayer.size(); ++n)
  			hiddenLayer[n].calcHiddenGradients(nextLayer);
  	}
  
  	// For all layers from outputs to first hidden layer,
  	// update connection weights
  
  	for(int layerNum = m_layers.size() - 1; layerNum > 0; --layerNum) {
  		Layer &layer = m_layers[layerNum];
  		Layer &prevLayer = m_layers[layerNum - 1];
  		for(int n = 0; n < layer.size() - 1; ++n) 
        layer[n].updateInputWeights(prevLayer);
  	}
  }
  
  void Net :: feedForward(const vector <double> &inputVals) {
  	// Check the num of inputVals euqal to neuronnum expect bias
  	assert(inputVals.size() == m_layers[0].size() - 1);
  
  	// Assign {latch} the input values into the input neurons
  	for(int i = 0; i < inputVals.size(); ++i) m_layers[0][i].setOutputVal(inputVals[i]); 
    
  	// Forward propagate
  	for(int layerNum = 1; layerNum < m_layers.size(); ++layerNum){
  		Layer &prevLayer = m_layers[layerNum - 1];
  		for(int n = 0; n < m_layers[layerNum].size() - 1; ++n)
  			m_layers[layerNum][n].feedForward(prevLayer);
  	}
  }
  
  Net :: Net(const vector <int> &topology) {
  	int numLayers = topology.size();
  	for(int layerNum = 0; layerNum < numLayers; ++layerNum){
  		m_layers.push_back(Layer());
  		// numOutputs of layer[i] is the numInputs of layer[i+1]
  		// numOutputs of last layer is 0
  		int numOutputs = layerNum == topology.size() - 1 ? 0 :topology[layerNum + 1];
  
  		// We have made a new Layer, now fill it ith neurons, and
  		// add a bias neuron to the layer:
  		for(int neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum)
  			m_layers.back().push_back(Neuron(numOutputs, neuronNum));
  
   		// Force the bias node's output value to 1.0. It's the last neuron created above
  		m_layers.back().back().setOutputVal(1.0);
  	}
  }
}

# endif
