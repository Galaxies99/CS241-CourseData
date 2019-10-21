# ifndef _RIGHT_TRIANGLE_H_
# define _RIGHT_TRIANGLE_H_

# include "Graph.h"
# include <assert.h>
# include <vector>
# include <cmath>

using namespace Graph_lib;
using namespace std;

const double _MYPI_ = acos(-1.0);

class RightTriangle : public Shape {
  private:
    vector <Point> points;
    double a, b;
    Point c;
    double angle;              // angle means the longest edge's angle
    int zoom;

    Color lcolor;
    Line_style ls;

    Point zoomPoint(double ox, double oy);
    void calculate();

    void draw_lines() const;

  public:
    RightTriangle(Point c, double a, double b, double angle = 0.0, int zoom = 1);

    void resetAngle(double angle);

    ~ RightTriangle() { }
};

# endif
