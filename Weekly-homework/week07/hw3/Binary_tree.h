# ifndef _BINARY_TREE_H_
# define _BINARY_TREE_H_

# include "Graph.h"
# include <assert.h>
# include <math.h>

using namespace Graph_lib;
using namespace std;

class Binary_tree : public Shape {
  protected:
    int levels;
    int print_d;
    vector <Point> points;
    vector <Point> nodes;

    Point getPoint(double ox, double oy);
    void calculate();
    virtual void draw_lines() const;

  public:
    Binary_tree(int levels = 0, int print_d = 16);

    void resetLevels(int newLevels);

    virtual ~ Binary_tree() { }
};

# endif
