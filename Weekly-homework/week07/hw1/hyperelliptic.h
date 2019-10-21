# ifndef _HYPERELLIPTIC_H_
# define _HYPERELLIPTIC_H_

# include "Graph.h"
# include <assert.h>
# include <vector>
# include <cmath>

using namespace Graph_lib;

class Hyperelliptic : public Shape {
  private:
    double a, b, m, n;
    int N;

    int zoom;
    Point center;

    vector <Point> points;

    Color lcolor;
    Line_style ls;

    void calculate();
    Point prtPoint(double ox, double oy);
    void draw_lines() const;

  public:
    Hyperelliptic(double a, double b, double m, double n, int N = 2,
                  int zoom = 1, Point center = Point(300, 200));

    void resetN(int newN);
    void draw() const;

    ~ Hyperelliptic() { };
};

# endif
