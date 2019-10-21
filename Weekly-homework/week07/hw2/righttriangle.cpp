# include "righttriangle.h"

RightTriangle :: RightTriangle(Point c, double a, double b, double angle, int zoom) :
  c(c), a(a), b(b), angle(angle), zoom(zoom), lcolor(fl_color()), ls(0) {
    assert(a > 0);
    assert(b > 0);
    calculate();
  }

void RightTriangle :: resetAngle(double newAngle = 0.0) {
  angle = newAngle;
  calculate();
}

Point RightTriangle :: zoomPoint(double ox, double oy) {
  int x = static_cast <int> (ox * zoom);
  int y = static_cast <int> (oy * zoom);
  return Point(x, y);
}

void RightTriangle :: calculate() {
  points.clear();
  double beta = atan(a / b);
  points.push_back(zoomPoint(c.x, c.y));
  points.push_back(zoomPoint(c.x + a * cos(angle - beta), c.y + a * sin(angle - beta)));
  points.push_back(zoomPoint(c.x + b * cos(angle - beta + _MYPI_ / 2), c.y + b * sin(angle - beta + _MYPI_ / 2)));
}


void RightTriangle :: draw_lines() const {
  if(color().visibility())
    for (int i = 0; i <= 2; ++ i) {
      int j = i + 1;
      if(j == 3) j = 0;
      fl_line(points[i].x, points[i].y, points[j].x, points[j].y);
    }
}
