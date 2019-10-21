# include "Binary_tree.h"

Binary_tree :: Binary_tree(int levels, int print_d) : levels(levels), print_d(print_d) { calculate(); }

void Binary_tree :: resetLevels(int newLevels) {
  levels = newLevels;
  assert(levels >= 0);
  calculate();
}

Point Binary_tree :: getPoint(double ox, double oy) {
  int x = static_cast <int> (ox);
  int y = static_cast <int> (oy);
  return Point(x, y);
}

void Binary_tree :: calculate() {
  points.clear(); nodes.clear();
  if(levels == 0) return;
  int mxson = (1 << levels - 1);
  int total_height = print_d * ((levels << 1) - 1);
  int last_width = print_d * ((mxson << 1) - 1);
  int curx = total_height;
  int cury = 50, y_step = print_d;

  for (int i = levels; i >= 1; -- i) {
    int cy = cury;
    for (int j = 1; j <= (1 << i - 1); ++ j) {
      nodes.push_back(Point(curx - print_d / 2, cy + print_d / 2));
      cy += print_d + y_step;
    }
    if (i != 1) {
      cy = cury;
      for (int j = 1; j <= (1 << i - 1); ++ j) {
        if(j & 1) {
          points.push_back(Point(curx - print_d, cy + print_d / 2));
          points.push_back(Point(curx - print_d * 2, cy + print_d + y_step / 2));
        } else {
          points.push_back(Point(curx - print_d, cy + print_d / 2));
          points.push_back(Point(curx - print_d * 2, cy - y_step / 2));
        }
        cy += print_d + y_step;
      }
    }
    cury += print_d / 2 + y_step / 2;
    curx -= print_d * 2;
    y_step = y_step * 2 + print_d;
  }
}

void Binary_tree :: draw_lines() const {
  if(color().visibility()) {
    for (int i = 0; i + 1 < points.size(); i += 2)
      fl_line(points[i].y, points[i].x + 50, points[i+1].y, points[i+1].x + 50);
    for (int i = 0; i < nodes.size(); ++ i)
      fl_arc(nodes[i].y - print_d / 2, nodes[i].x - print_d / 2 + 50, print_d, print_d, 0, 360);
  }
}
