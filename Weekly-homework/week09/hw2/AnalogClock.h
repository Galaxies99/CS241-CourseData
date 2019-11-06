# ifndef _ANALOGCLOCK_H_
# define _ANALOGCLOCK_H_

# include "Graph.h"
# include "std_lib_facilities.h"
# include <time.h>
# include <math.h>
# include <iostream>

class AnalogClock : public Graph_lib :: Shape {
  private:
    void draw_lines() const;

  public:
    AnalogClock() {}

    ~ AnalogClock() {}
};


# endif
