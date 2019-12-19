# ifndef _RANDOM_HPP_
# define _RANDOM_HPP_

# include <stdlib.h>
# include <math.h>

namespace simple_random {
  const double PI = acos(-1.0);
  
  double standard_uniform_random() {
    return 1.0 * rand() / RAND_MAX;
  }
  
  double uniform_random(double x, double y) {
    return x + (y - x) * standard_uniform_random();
  }
  
  double standard_guassian_random() {
    static double U, V;
    static int phase = 0;
    double ret;
    
    if(phase == 0) {
      U = rand() / (RAND_MAX + 1.0);
      V = rand() / (RAND_MAX + 1.0);
      ret = sqrt(-2.0 * log(U)) * sin (2.0 * PI * V);
    } else ret = sqrt(-2.0 * log(U)) * cos(2.0 * PI * V);
    
    phase = 1 - phase;
    return ret;
  }
  
  double guassian_random(double mu, double sigma) {
    return mu + sigma * standard_guassian_random();
  }
}

# endif
