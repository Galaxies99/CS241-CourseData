# include "TriangleBinary_tree.h"

void TriangleBinary_tree :: draw_lines() const {
  if(color().visibility()) {
    for (int i = 0; i + 1 < points.size(); i += 2)
      fl_line(points[i].y, points[i].x + 250, points[i+1].y, points[i+1].x + 250);
    for (int i = 0; i < nodes.size(); ++ i) {
      fl_line(nodes[i].y, nodes[i].x - print_d / 2 + 250, nodes[i].y - print_d / 2, nodes[i].x + print_d / 2 + 250);
      fl_line(nodes[i].y - print_d / 2, nodes[i].x + print_d / 2 + 250, nodes[i].y + print_d / 2, nodes[i].x + print_d / 2 + 250);
      fl_line(nodes[i].y + print_d / 2, nodes[i].x + print_d / 2 + 250, nodes[i].y, nodes[i].x - print_d / 2 + 250);
    }
  }
}

