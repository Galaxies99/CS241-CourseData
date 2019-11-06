# include "Simple_window.h"
# include "Graph.h"
# include "BarChart.h"
# include "std_lib_facilities.h"
# include <iostream>

int main() {
  Point tl(100, 100);
  Simple_window win(tl, 1010, 600, "Temperature Bar Chart");

  BarChart c;
  c.file_load();

  win.attach (c);

  win.wait_for_button();
  return 0;
}
