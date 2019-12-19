# ifndef _NN_NET_HPP_
# define _NN_NET_HPP_

# include "function.hpp"
# include "../matrix.hpp"
# include "../exceptions.hpp"
# include "../random.hpp"

# include <vector>
# include <string>

using std :: cout;
using std :: vector;
using std :: string; 

namespace simple_nn {
  class Net {
    public:
      vector <int> layer_neuron_num;
      string activation_function;
      int output_interval;
      double learning_rate;
      double accuracy;
      vector <int> loss_vec;
      double fine_tune_factor;
      
    private:
      vector <Matrix> layer, weights, bias, delta_err;
      Matrix output_err, target, board;
      double loss;
      
      Matrix activation_func(const Matrix &x) const;
      
    public:
      Net(const string &activation_function = "sigmoid", int output_interval = 10, double fine_tune_factor = 1.01) :
        activation_function(activation_function), output_interval(output_interval), fine_tune_factor(fine_tune_factor) {
        accuracy = 0.0;
      } 
      
      ~ Net() = default;
      
      void initNet(vector <int> _layer_neuron_num);
      void initWeight(int type, double a, double b);
      void initBias(double _bias);      
      void set_activation_function(const string &new_activation_function);
      void forward();
      void backward();
  };

  void Net :: initNet(vector <int> _layer_neuron_num) {
    layer_neuron_num = _layer_neuron_num;
    layer.resize(layer_neuron_num.size());
    for (int i = 0; i < layer.size(); ++ i)
      layer[i] = Matrix(layer_neuron_num[i], 1);
    weights.resize(layer.size() - 1);
    bias.resize(layer.size() - 1);
    for (int i = 0; i < layer.size() - 1; ++ i) {
      weights[i] = Matrix(layer_neuron_num[i + 1], layer_neuron_num[i]);
      bias[i] = Matrix(layer_neuron_num[i + 1], 1);
    } 
  }
  
  void Net :: initWeight(int type = 0, double a = 0.0, double b = 1.0) {
    for (int i = 0; i < weights.size(); ++ i)
      if(type == 0) weights[i].set_guassian_random(a, b);
      else weights[i].set_uniform_random(a, b);
  }
  
  void Net :: initBias(double _bias) {
    for (int i = 0; i < bias.size(); ++ i)
      bias[i].set_all(_bias);
  }
  
  void Net :: forward() {
    for (int i = 0; i < layer_neuron_num.size() - 1; ++ i) {
      Matrix p = weights[i] * layer[i] + bias[i];
      layer[i + 1] = activation_func(p);
    }
    simple_nn_func :: loss_func(layer[layer.size() - 1], target, output_err, loss);
  }
  
  void Net :: backward() {
    delta_err.resize(layer.size() - 1);
    for (int i = delta_err.size() - 1; ~i; -- i) {
      Matrix dx = simple_nn_func :: derivative_func(layer[i + 1], activation_function);
      if(i == delta_err.size() - 1) delta_err[i] = mul(dx, output_err);
      else delta_err[i] = mul(dx, (weights[i + 1].transposition()) * delta_err[i + 1]); 
    }
    for (int i = 0; i < weights.size(); ++ i) {
      Matrix delta_weights = learning_rate * (delta_err[i] * layer[i].transposition());
      Matrix delta_bias = learning_rate * delta_err[i];
      weights[i] = weights[i] + delta_weights;
      bias[i] = bias[i] + delta_bias;
    }
  }
  
  // accuracy_threshold
  void Net :: train(const Matrix &input, const Matrix &target, double accuracy_threshold) {
    if (input.empty()) throw Unexpected_Error();
    
    cout << ">>>>>>>>>>>>>>>>> begin training >>>>>>>>>>>>>>>>>>\n";
    
    
  }

  void Net :: set_activation_function(const string &new_activation_function) {
    activation_function = new_activation_function;
  }
  
  Matrix Net :: activation_func(const Matrix &x) const {
    Matrix fx;
    if (activation_function == "sigmoid") fx = simple_nn_func :: sigmoid(x);
    else if (activation_function == "tanh") fx = simple_nn_func :: tanh(x);
    else if (activation_function == "ReLU") fx = simple_nn_func :: ReLU(x);
    else throw Func_Error();
    return fx;
  }
  
}

# endif 
