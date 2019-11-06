# include "Simple_window.h"
# include "Graph.h"
# include "AnalogClock.h"
# include "std_lib_facilities.h"
# include <iostream>

int main() {
  Point tl(100, 100);
  Simple_window win(tl, 600, 700, "Analog Clock");

  AnalogClock cl;
  win.attach(cl);

  win.wait_for_button();

  return 0;
}
