# ifndef _TRIANGLE_BINARY_TREE_H_
# define _TRIANGLE_BINARY_TREE_H_

# include "Binary_tree.h"

class TriangleBinary_tree : public Binary_tree {
  private:
    void draw_lines() const;

  public:
    TriangleBinary_tree(int levels = 0, int print_d = 16) : Binary_tree(levels, print_d) {}

    ~ TriangleBinary_tree() { }
};

# endif
