# ifndef _NN_FUNCTION_HPP_
# define _NN_FUNCTION_HPP_

# include <string>
# include "../matrix.hpp"
# include "../exceptions.hpp"

using std :: string;

namespace simple_nn_func {
  Matrix sigmoid(const Matrix &x) {
    return 1.0 / (1.0 + exp(-x));
  }
  
  Matrix tanh(const Matrix &x) {
    return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
  }
  
  Matrix ReLU(const Matrix &x) {
    Matrix ret(x);
    for (int i = 0; i < ret.get_n(); ++ i)
      for (int j = 0; j < ret.get_m(); ++ j)
        if(ret(i, j) < 0) ret(i, j) = 0;
    return ret;
  }
  
  Matrix derivative_func(const Matrix &x, string func_type) {
    Matrix dx;
    if(func_type == "sigmoid") {
      dx = mul(sigmoid(x), 1 - sigmoid(x));
    } else if(func_type == "tanh") {
      dx = 1 - pow(tanh(x), 2);
    } else if(func_type == "ReLU") {
      dx = x;
      for (int i = 0; i < dx.get_n(); ++ i)
        for (int j = 0; j < dx.get_m(); ++ j)
          if(x(i, j) > 0) dx(i, j) = 1; 
    } else throw Func_Error();
    return dx;
  }
  
  void loss_func(const Matrix &opt, const Matrix &tar, Matrix &error_mat, double &loss) {
    if(tar.empty()) throw Matrix_Error();
    error_mat = tar - opt;
    loss = sum(pow(error_mat, 2)) / tar.get_n();
  }
}

# endif
