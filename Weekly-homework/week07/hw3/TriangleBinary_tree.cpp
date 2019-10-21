# include "TriangleBinary_tree.h"

void TriangleBinary_tree :: draw_nodes() const {
  for (int i = 0; i < nodes.size(); ++ i) {
    fl_line(nodes[i].y, nodes[i].x - print_d / 2 + offset, nodes[i].y - print_d / 2, nodes[i].x + print_d / 2 + offset);
    fl_line(nodes[i].y - print_d / 2, nodes[i].x + print_d / 2 + offset, nodes[i].y + print_d / 2, nodes[i].x + print_d / 2 + offset);
    fl_line(nodes[i].y + print_d / 2, nodes[i].x + print_d / 2 + offset, nodes[i].y, nodes[i].x - print_d / 2 + offset);
  }
}

