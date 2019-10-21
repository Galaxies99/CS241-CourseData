#include "Simple_window.h"
#include "Graph.h"
#include "std_lib_facilities.h"
#include "righttriangle.h"
#include <iostream>

int main() {
    Point tl(100, 100);
    Simple_window win(tl, 600, 400, "RightTriangle");

    /********************************* Basic Settings ************************************/
    // To center the graph, the offset must be set.
    double offsetX = 300, offsetY = 200;

    // The length of the edges of the triangle.
    double A = 100.0, B = 50.0;

    // The colors
    Color colors[8] = {Color :: red, Color :: blue, Color :: green, Color :: yellow,
                       Color :: white, Color :: black, Color :: magenta, Color :: cyan};

    /******************************** Math Calculation ***********************************/
    double C = sqrt(A * A + B * B);
    double Ar = C / 2 / tan(_MYPI_ / 8);
    double beta = _MYPI_ / 2 - 2 * atan(A / B);
    double dCx = C / 2 * cos(beta), dCy = C / 2 * sin(beta);
    double px = Ar - dCx, py = -dCy;
    double R = sqrt(px * px + py * py);
    double theta = atan(fabs(py) / px);
    if(py < 0) theta = -theta;
    double angle = 0, angle_step = _MYPI_ / 4;

    /******************************** Graph Picturing ************************************/
    Shape *tri[8];
    for (int i = 0; i < 8; ++ i) {
        Point p(static_cast <int> (R * cos(theta) + offsetX), static_cast <int> (R * sin(theta) + offsetY));
        tri[i] = new RightTriangle(p, A, B, angle);
        tri[i] -> set_color(colors[i]);
        win.attach(*tri[i]);
        angle += angle_step;
        theta += angle_step;
    }

    win.wait_for_button();

    for (int i = 0; i < 8; ++ i) delete tri[i];
    return 0;
}
