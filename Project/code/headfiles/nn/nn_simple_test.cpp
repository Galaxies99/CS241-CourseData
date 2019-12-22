# include "Net.hpp"
# include "function.hpp"
# include "../matrix.hpp"
# include "../random.hpp"
# include <bits/stdc++.h>

using namespace std;
using namespace simple_nn;

int main() {
  vector <int> layer_neuron_num = {1, 10, 30, 50, 100};
  Net net;
  net.initNet(layer_neuron_num);
  net.initWeight(0, 0, 0.01);
  net.initBias(0.5);
  
  Matrix input(1, 20), output(100, 20);
  for (int i = 0; i < 20; ++ i) {
    for (int j = 0; j < 1; ++ j)
      cin >> input(j, i);
    int c;
    cin >> c;
    for (int j = 0; j < 100; ++ j) output(j, i) = (j == c);
  }
  
  Matrix test_input(1, 1), test_output(100, 1);
  for (int i = 0; i < 1; ++ i) {
    for (int j = 0; j < 1; ++ j)
      cin >> test_input(j, i);
    int c;
    cin >> c;
    for (int j = 0; j < 100; ++ j) test_output(j, i) = (j == c);
  }
  
  net.learning_rate = 0.3;
  net.output_interval = 2;
  net.activation_function = "sigmoid";
  
  
  net.train(input, output, 0.005);
  net.test(test_input, test_output);
  
  return 0;
}
