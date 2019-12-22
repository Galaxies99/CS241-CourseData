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
      void train(const Matrix &input, const Matrix &input_target, double loss_threshold);
      void test(const Matrix &input, const Matrix &input_target);
      int predict(const Matrix &input);
      
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
  
  void Net :: train(const Matrix &input, const Matrix &input_target, double loss_threshold) {
    if (input.empty()) {
      cout << "Train set is empty!\n";
      return;
    }
    if(input.get_n() != layer[0].get_n()) {
      cout << "Train Matrix doesn't fit in the layer 0's neuron number!\n";
      return;
    }
    
    cout << ">>>>>>>>>>>>>>>>> begin training >>>>>>>>>>>>>>>>>>\n";
    
    Matrix sample;
    if(input.get_m() == 1) { 
      target = input_target;
      sample = input;
      layer[0] = sample;
      forward();
      int train_num = 0;
      while(loss > loss_threshold) {
        backward();
        forward();
        ++ train_num;
        cout << "Train " << train_num << " times, loss: " << loss << '\n';
      }
      cout << "\nEnd of training. Total counts: " << train_num << " times.\n";
      cout << "\nFinally loss: " << loss << '\n';
      cout << "\n>>>>>>>>>>>>>> trained successfully >>>>>>>>>>>>>>>\n";
    } else {
      double batch_loss = loss_threshold + 1.0;
      int train_num = 0;
      while(batch_loss > loss_threshold) {
        batch_loss = 0;
        for (int i = 0; i < input.get_m(); ++ i) {
          target = input_target.get_col(i);
          sample = input.get_col(i);
          layer[0] = sample;
          forward();
          backward();
          batch_loss += loss;
        }
        ++ train_num;
        cout << "Train " << train_num << " times, loss sum: " << batch_loss << '\n';
        if (train_num == 4) break;
        if (train_num % 100 == 0) learning_rate *= fine_tune_factor; 
      }
      cout << "\nEnd of training. Total counts: " << train_num << " times.\n";
      cout << "\nFinally loss: " << loss << '\n';
      cout << "\n>>>>>>>>>>>>>> trained successfully >>>>>>>>>>>>>>>\n";
    }
  }
  
  void Net :: test(const Matrix &input, const Matrix &input_target) {
    if (input.empty()) {
      cout << "Test set is empty!\n";
      return;
    }
    if(input.get_n() != layer[0].get_n()) {
      cout << "Test Matrix doesn't fit in the layer 0's neuron number!\n";
      return;
    }
    
    cout << ">>>>>>>>>>>>>>>>> begin testing >>>>>>>>>>>>>>>>>>\n";
    
    if(input.get_m() == 1) {
      Matrix sample;
      sample = input;
      int predict_number = predict(sample);
      int target_number = input_target.getMaxX(0);
      cout << "Predicted Number: " << predict_number << ".\n";
      cout << "Target Number: " << target_number << ".\n";
      cout << "Loss: " << loss << ".\n";
      cout << ">>>>>>>>>>>>>>>>> end of testing >>>>>>>>>>>>>>>>>\n";
    } else {
      double batch_loss = 0;
      int right_sum = 0;
      Matrix sample;
      for (int i = 0; i < input.get_m(); ++ i) {
        sample = input.get_col(i);
        int predict_number = predict(sample);
        batch_loss += loss;
        int target_number = input_target.getMaxX(i);
        if(target_number == predict_number) ++ right_sum;
      }
      accuracy = 1.0 * right_sum / input.get_m();
      cout << "Accuracy: " << accuracy << ".\n";
      cout << "Average Loss: " << loss << ".\n";
      cout << ">>>>>>>>>>>>>>>>> end of testing >>>>>>>>>>>>>>>>>\n";
    }
  }
  
  int Net :: predict(const Matrix &input) {
    if (input.empty()) {
      cout << "Input is empty!\n";
      return -1;
    }
    if(input.get_n() != layer[0].get_n()) {
      cout << "Test Matrix doesn't fit in the layer 0's neuron number!\n";
      return -1;
    }  
    
    layer[0] = input;
    forward();
    
    Matrix layer_out = layer[layer.size() - 1];
    
    return layer_out.getMaxX(0); 
  }
  
}

# endif 
