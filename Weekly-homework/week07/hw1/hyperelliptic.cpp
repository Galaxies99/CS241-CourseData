# include "hyperelliptic.h"

Hyperelliptic :: Hyperelliptic(double a, double b, double m, double n, int N,
                  int zoom, Point center) :
  a(a), b(b), m(m), n(n), N(N), zoom(zoom), center(center),
  lcolor(fl_color()), ls(0) {
    assert(!(N & 1));
    assert(N != 0);
    calculate();
  }

void Hyperelliptic :: resetN(int newN) {
  N = newN;
  assert(!(N & 1));
  assert(N != 0);
  calculate();
}

Point Hyperelliptic :: zoomPoint(double ox, double oy) {
  int x = static_cast <int> (ox * zoom);
  int y = static_cast <int> (oy * zoom);
  x += center.x;
  y += center.y;
  return Point(x, y);
}

void Hyperelliptic :: calculate() {
  points.clear();
  // range is [-a, a]
  double x = -a, step = a * 2 / (N >> 1);
  for (int i = 0; i <= (N >> 1); ++ i) {
    double y1 = pow(1 - pow(fabs(x / a), n), 1.0 / m) * b;
    double y2 = -y1;
    points.push_back(zoomPoint(x, y1));
    if(i != 0 && i != (N >> 1)) points.push_back(zoomPoint(x, y2));
    x += step;
  }
}

void Hyperelliptic :: draw_lines() const {
  if(color().visibility())
    for (int i = 0; i < points.size(); ++ i)
      for (int j = i + 1; j < points.size(); ++ j)
        fl_line(points[i].x, points[i].y, points[j].x, points[j].y);
}


