# include "BarChart.h"

void BarChart :: file_load() {
  int cnt[13];
  char no_use1[20], no_use2[20];
  int y, m, d; double tem;

  FILE *fp = fopen("NewYork.csv", "r");
  newyork.resize(13);
  for (int i = 1; i <= 12; ++ i) newyork[i] = 0, cnt[i] = 0;
  fscanf(fp, "%s,%s,\n", no_use1, no_use2);
  while(~fscanf(fp, "%d/%d/%d,%lf ,", &y, &m, &d, &tem)) newyork[m] += tem, cnt[m] ++;
  for (int i = 1; i <= 12; ++ i) if(cnt[i]) newyork[i] /= cnt[i];
  fclose(fp);

  fp = fopen("Austin.csv", "r");
  austin.resize(13);
  for (int i = 1; i <= 12; ++ i) austin[i] = 0, cnt[i] = 0;
  fscanf(fp, "%s,%s,\n", no_use1, no_use2);
  while(~fscanf(fp, "%d/%d/%d,%lf ,", &y, &m, &d, &tem)) austin[m] += tem, cnt[m] ++;
  for (int i = 1; i <= 12; ++ i) if(cnt[i]) austin[i] /= cnt[i];
  fclose(fp);
}

const int Xsize_per_month = 65, Ysize_per_deg = 10;

void BarChart :: draw_lines() const {
  // Title
  Graph_lib :: Text title(Point(300, 60), "The Bar Chart of temperature in New York and Austin");
  title.set_color(Graph_lib :: Color :: black);
  title.set_font(Graph_lib :: Font(FL_TIMES_BOLD_ITALIC));
  title.set_font_size(20);
  title.draw();

  // Second Title
  Graph_lib :: Text stitle(Point(500, 90), "(In year 2016)");
  stitle.set_color(Graph_lib :: Color :: black);
  stitle.set_font(Graph_lib :: Font(FL_TIMES_BOLD_ITALIC));
  stitle.set_font_size(14);
  stitle.draw();

  // Axis X
  Graph_lib :: Axis AX(Graph_lib :: Axis :: x, Point(100, 500), 830);
  AX.set_color(Graph_lib :: Color :: black);
  AX.draw();

  // Axis X label
  Graph_lib :: Text AXlabel(Point(910, 530), "Month");
  AXlabel.set_color(Graph_lib :: Color :: black);
  AXlabel.set_font(Graph_lib :: Font(FL_TIMES_ITALIC));
  AXlabel.draw();

  // Axis y
  Graph_lib :: Axis AY(Graph_lib :: Axis :: y, Point(100, 500), 400, 8, "Temperature (Celcius)");
  AY.set_color(Graph_lib :: Color :: black);
  AY.label.set_font(Graph_lib :: Font(FL_TIMES_ITALIC));
  AY.draw();

  // Axis y Text
  for (int i = 0, y = 500; i <= 40; i += 5, y -= Ysize_per_deg * 5) {
    Graph_lib :: Text t(Point(75, y + 5), to_string(i));
    t.set_color(Graph_lib :: Color :: black);
    t.draw();
  }

  // Draw Block
  int cur_x = 100, cur_y = 500;
  cur_x += 15;
  for (int i = 1; i <= 12; ++ i) {
    cur_x += 10;

    // Draw Block of Austin
    double ht_austin = austin[i];
    int hts_austin = ht_austin * 10;
    Graph_lib :: Rectangle au(Point(cur_x, cur_y - hts_austin), 20, hts_austin);
    au.set_color(Graph_lib :: Color :: red); au.set_fill_color(Graph_lib :: Color :: red);
    au.draw();

    // Draw Number of Austin
    string austin_text = to_string(hts_austin);
    austin_text.insert(austin_text.length() - 1, 1, '.');
    Graph_lib :: Text t_austin(Point(cur_x - 3, cur_y - hts_austin - 10), austin_text);
    t_austin.set_color(Graph_lib :: Color :: red);
    t_austin.draw();

    cur_x += 25;

    // Draw Block of New York
    double ht_newyork = newyork[i];
    int hts_newyork = ht_newyork * 10;
    Graph_lib :: Rectangle ny(Point(cur_x, cur_y- hts_newyork), 20, hts_newyork);
    ny.set_color(Graph_lib :: Color :: blue); ny.set_fill_color(Graph_lib :: Color :: blue);
    ny.draw();

    // Draw Number of New York
    string newyork_text = to_string(hts_newyork);
    newyork_text.insert(newyork_text.length() - 1, 1, '.');
    Graph_lib :: Text t_newyork(Point(cur_x - (newyork_text.size() >= 4) * 3, cur_y - hts_newyork - 10), newyork_text);
    t_newyork.set_color(Graph_lib :: Color :: blue);
    t_newyork.draw();

    // Axis X Text
    Graph_lib :: Text t_axis(Point(cur_x - 7 - (i >= 10) * 3, cur_y + 20), to_string(i));
    t_axis.set_color(Graph_lib :: Color :: black);
    t_axis.draw();

    cur_x += 30;
  }

  // Others
  Graph_lib :: Rectangle rblank(Point(700, 100), 200, 100);
  rblank.set_color(Graph_lib :: Color :: black);
  rblank.set_fill_color(Graph_lib :: Color :: white);
  rblank.draw();

  Graph_lib :: Rectangle raustin(Point(720, 120), 80, 20);
  raustin.set_color(Graph_lib :: Color :: red);
  raustin.set_fill_color(Graph_lib :: Color :: red);
  raustin.draw();

  Graph_lib :: Rectangle rnewyork(Point(720, 160), 80, 20);
  rnewyork.set_color(Graph_lib :: Color :: blue);
  rnewyork.set_fill_color(Graph_lib :: Color :: blue);
  rnewyork.draw();

  Graph_lib :: Text taustin(Point(820, 135), "Austin");
  taustin.set_color(Graph_lib :: Color :: black);
  taustin.set_font(Graph_lib :: Font(FL_TIMES_ITALIC));
  taustin.draw();

  Graph_lib :: Text tnewyork(Point(820, 175), "New York");
  tnewyork.set_color(Graph_lib :: Color :: black);
  tnewyork.set_font(Graph_lib :: Font(FL_TIMES_ITALIC));
  tnewyork.draw();
}


