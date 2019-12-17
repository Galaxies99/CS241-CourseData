# ifndef _CHART_HPP_
# define _CHART_HPP_

# include "Graph.h"
# include "../data_structure.hpp"
# include "../exceptions.hpp"
# include "../tools.hpp"
# include <iostream>
# include <assert.h>
# include <vector>
# include <cmath>

using namespace std;

const Graph_lib :: Color col[] = {Graph_lib :: Color :: red, Graph_lib :: Color :: blue, Graph_lib :: Color :: green, Graph_lib :: Color :: yellow, Graph_lib :: Color :: white,
                                  Graph_lib :: Color :: black, Graph_lib :: Color :: magenta, Graph_lib :: Color :: cyan, Graph_lib :: Color :: dark_red,
                                  Graph_lib :: Color :: dark_blue, Graph_lib :: Color :: dark_green, Graph_lib :: Color :: dark_yellow,
                                  Graph_lib :: Color :: dark_blue, Graph_lib :: Color :: dark_magenta, Graph_lib :: Color :: dark_cyan};

class Chart : public Graph_lib :: Shape {
  private:
    int window_width;
    string station_name;
    vData v;
    void draw_lines() const;

  public:
    Chart(int window_width, const string& station_name, const vData &v) :
      window_width(window_width), station_name(station_name), v(v) {}

    ~ Chart() { };
};

void Chart :: draw_lines() const {
  int n = v.p.size();

  // Title
  string title_name = "Beijing (" + station_name + " station) " + op_to_string[v.op] + " Data Figure";
  Graph_lib :: Text title(Point((window_width - 800) / 2 + 200, 60), title_name);
  title.set_color(Graph_lib :: Color :: black);
  title.set_font(Graph_lib :: Font(FL_TIMES_BOLD));
  title.set_font_size(20);
  title.draw();

  // Second Title
  string second_title_name = "(from " + to_string(v.y1) + "." + to_string(v.m1) + "." + to_string(v.d1) + " to " +
                             to_string(v.y2) + "." + to_string(v.m2) + "." + to_string(v.d2) + ")";
  Graph_lib :: Text stitle(Point((window_width - 800) / 2 + 320, 90), second_title_name);
  stitle.set_color(Graph_lib :: Color :: black);
  stitle.set_font(Graph_lib :: Font(FL_TIMES_BOLD_ITALIC));
  stitle.set_font_size(14);
  stitle.draw();

  if(v.op != 11) {
    // Axis X
    Graph_lib :: Line x_axis(Point(100, 700), Point(window_width - 100, 700));
    x_axis.set_color(Graph_lib :: Color :: black);
    x_axis.draw();

    // Axis X label
    Graph_lib :: Text x_axis_label(Point(window_width - 90, 700), "Time");
    x_axis_label.set_color(Graph_lib :: Color :: black);
    x_axis_label.set_font(Graph_lib :: Font(FL_TIMES_ITALIC));
    x_axis_label.draw();

    // Axis Y
    Graph_lib :: Line y_axis(Point(100, 700), Point(100, 150));
    y_axis.set_color(Graph_lib :: Color :: black);
    y_axis.draw();

    // Axis Y label
    string axis_y_label_text = op_to_string[v.op] + " (" + op_to_unit[v.op] + ")";
    Graph_lib :: Text y_axis_label(Point(70, 130), axis_y_label_text);
    y_axis_label.set_color(Graph_lib :: Color :: black);
    y_axis_label.set_font(Graph_lib :: Font(FL_TIMES_ITALIC));
    y_axis_label.draw();

    double max_y = -2e9, min_y = 2e9;
    for (int i = 0; i < v.p.size(); ++ i) max_y = max(max_y, v.p[i]), min_y = min(min_y, v.p[i]);

    // Axis Y label2
    for (int i = 0; i <= 11; ++ i) {
      double cr = (max_y - min_y) / 11 * i + min_y;
      string ct = Chart_Tools :: double_to_string(cr, 3);
      Graph_lib :: Text t(Point(40, 700 - i * (550 / 11) + 3), ct);
      t.set_color(Graph_lib :: Color :: black);
      t.draw();
    }

    int delta;
    if(window_width == 800) delta = 600 / v.p.size();
    else delta = 3;
    for (int i = 1; i < v.p.size(); ++ i) {
      Graph_lib :: Line l(Point((i - 1) * delta + 100, 700 - 550.0 * (v.p[i - 1] - min_y) / (max_y - min_y)),
                          Point(i * delta + 100, 700 - 550.0 * (v.p[i] - min_y) / (max_y - min_y)));
      l.set_color(Graph_lib :: Color :: red);
      l.draw();
    }
  } else {
    double tot = 0;
    for (int i = 0; i < 16; ++ i) tot += v.p[i];
    vector <int> t;
    for (int i = 0; i < 16; ++ i)
      if(v.p[i] != 0.0) t.push_back(static_cast <int> (v.p[i] / tot * 100.0 * PI));
    int n = t.size();
    int cur = 0, cx = 270, cy = 330;
    for (int i = 0; i < n; ++ i) {
      Graph_lib :: Closed_polyline pl;
      pl.add(Point(cx, cy));
      for (int j = 0; j <= t[i]; ++ j, ++ cur) pl.add(Point(cx + 200 * cos(cur / 50.0), cy + 200 * sin(cur / 50.0)));
      -- cur;
      if(i == n - 1) pl.add(Point(cx + 200, cy));
      pl.set_color(Graph_lib :: Color :: black);
      pl.set_fill_color(col[i]);
      pl.draw();
    }

    Graph_lib :: Rectangle rblank(Point(500, 150), 110, 20 * n);
    rblank.set_color(Graph_lib :: Color :: black);
    rblank.set_fill_color(Graph_lib :: Color :: white);
    rblank.draw();

    for (int i = 0; i < n; ++ i) {
      Graph_lib :: Rectangle rec(Point(520, 155 + i * 20), 30, 10);
      rec.set_color(Graph_lib :: Color :: black);
      rec.set_fill_color(col[i]);
      rec.draw();
      int cnt = 0, pos = 0;
      for (int j = 0; j < 16; ++ j) {
        if(v.p[j] != 0) ++ cnt;
        if(cnt == i + 1) {
          pos = j;
          break;
        }
      }
      Graph_lib :: Text t(Point(565, 165 + i * 20), wind_to_string[pos]);
      t.set_color(Graph_lib :: Color :: black);
      t.set_font(Graph_lib :: Font(FL_TIMES_BOLD_ITALIC));
      t.set_font_size(12);
      t.draw();
    }



  }

}

# endif

