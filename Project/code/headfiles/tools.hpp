# ifndef _TOOLS_HPP_
# define _TOOLS_HPP_

# include <iostream>
# include <ctype.h>
# include <string>
# include <math.h>

# include "matrix.hpp"
# include "data_structure.hpp"
# include "exceptions.hpp"

using std :: vector;
using std :: string;
using std :: cout;
using std :: cin;
using std :: endl;

const double PI = acos(-1.0);

namespace Pre_Record_Generator {
  int to_int(const string &s) {
    int ret = 0;
    for (int i = 0; i < s.length(); ++ i) {
      if (! isdigit(s[i])) throw toInt_Initialize_Error();
      ret = ret * 10 + s[i] - '0';
    }
    return ret;
  }
  int cut_int(string &str) {
    static size_t pos;
    pos = str.find(',');
    if(pos == string :: npos) throw Record_Initialize_Error();
    string ret = str.substr(0, pos); str = str.substr(pos + 1);
    return to_int(ret);
  }

  Data <double> to_data_double(const string &s) {
    double ret = 0.0, bse = 1.0, sig = 1.0;
    int beg = 0;
    if(s.length() == 0) return Data <double> (0.0, 0);
    if(s[0] == '-') sig = -1.0, beg = 1;
    for (int i = beg; i < s.length(); ++ i) {
      if(! isdigit(s[i]) && s[i] != '.') return Data <double> (0.0, 0);
      if(s[i] == '.') {
        if(bse != 1.0) return Data <double> (0.0, 0);
        bse = 0.1;
      } else {
        if(bse == 1.0) ret = ret * 10 + (s[i] - '0');
        else {
          ret = ret + bse * (s[i] - '0');
          bse = bse * 0.1;
        }
      }
    }
    return Data <double> (sig * ret, 1);
  }
  Data <double> cut_data_double(string &str) {
    static size_t pos;
    pos = str.find(',');
    if(pos == string :: npos) throw Record_Initialize_Error();
    string ret = str.substr(0, pos); str = str.substr(pos + 1);
    return to_data_double(ret);
  }

  Data <Wind> cut_wd(string &str) {
    static size_t pos;
    pos = str.find(',');
    if(pos == string :: npos) throw Record_Initialize_Error();
    string ret = str.substr(0, pos); str = str.substr(pos + 1);

    if(ret == "NA") return Data <Wind> (Wind :: N, 0);

    if(ret.length() == 0) throw Record_Initialize_Error();
    if(ret[0] != '\"') throw Record_Initialize_Error();
    if(ret[ret.length() - 1] != '\"') throw Record_Initialize_Error();

    ret = ret.substr(1, ret.length() - 2);

    if(ret == "N") return Data <Wind> (Wind :: N, 1);
    else if(ret == "NNE") return Data <Wind> (Wind :: NNE, 1);
    else if(ret == "NE") return Data <Wind> (Wind :: NE, 1);
    else if(ret == "ENE") return Data <Wind> (Wind :: ENE, 1);
    else if(ret == "E") return Data <Wind> (Wind :: E, 1);
    else if(ret == "ESE") return Data <Wind> (Wind :: ESE, 1);
    else if(ret == "SE") return Data <Wind> (Wind :: SE, 1);
    else if(ret == "SSE") return Data <Wind> (Wind :: SSE, 1);
    else if(ret == "S") return Data <Wind> (Wind :: S, 1);
    else if(ret == "SSW") return Data <Wind> (Wind :: SSW, 1);
    else if(ret == "SW") return Data <Wind> (Wind :: SW, 1);
    else if(ret == "WSW") return Data <Wind> (Wind :: WSW, 1);
    else if(ret == "W") return Data <Wind> (Wind :: W, 1);
    else if(ret == "WNW") return Data <Wind> (Wind :: WNW, 1);
    else if(ret == "NW") return Data <Wind> (Wind :: NW, 1);
    else if(ret == "NNW") return Data <Wind> (Wind :: NNW, 1);
    else throw Record_Initialize_Error();
  }

  struct Pre_Record solver(const string &s) {
    string str(s);
    int No, year, month, day, hour;

    No = cut_int(str);
    year = cut_int(str);
    month = cut_int(str);
    day = cut_int(str);
    hour = cut_int(str);

    Data <double> PM25(cut_data_double(str));
    Data <double> PM10(cut_data_double(str));
    Data <double> SO2(cut_data_double(str));
    Data <double> NO2(cut_data_double(str));
    Data <double> CO(cut_data_double(str));
    Data <double> O3(cut_data_double(str));
    Data <double> temp(cut_data_double(str));
    Data <double> pres(cut_data_double(str));
    Data <double> dewp(cut_data_double(str));
    Data <double> rain(cut_data_double(str));
    Data <Wind> wd(cut_wd(str));
    Data <double> wspm(cut_data_double(str));
    return Pre_Record(No, year, month, day, hour, PM25, PM10, SO2, NO2, CO, O3, temp, pres, dewp, rain, wd, wspm);
  }
}

namespace Pre_Record_Filter {
  const double eps = 1e-8;

  inline bool chk_data_valid(const Data <double> &p, int prod) {
    double p_r = (static_cast <int> (p.get_data() * prod)) / static_cast <double> (prod);
    if(abs(p_r - p.get_data()) < eps) return true;
    else return false;
  }

  inline bool is_valid(const Pre_Record &pl) {
    /** invalid: have 'NA' in data, data missing **/
    if (pl.PM25.get_rec_type() == false ||
      pl.PM10.get_rec_type() == false ||
      pl.SO2.get_rec_type() == false ||
      pl.NO2.get_rec_type() == false ||
      pl.CO.get_rec_type() == false ||
      pl.O3.get_rec_type() == false ||
      pl.temp.get_rec_type() == false ||
      pl.pres.get_rec_type() == false ||
      pl.dewp.get_rec_type() == false ||
      pl.rain.get_rec_type() == false ||
      pl.wd.get_rec_type() == false ||
      pl.wspm.get_rec_type() == false) return false;
    /** invalid: unexpected digits **/
    if (chk_data_valid(pl.PM25, 1) == false ||
        chk_data_valid(pl.PM10, 1) == false ||
        chk_data_valid(pl.SO2, 1) == false ||
        chk_data_valid(pl.NO2, 1) == false ||
        chk_data_valid(pl.CO, 1) == false ||
        chk_data_valid(pl.O3, 1) == false ||
        chk_data_valid(pl.temp, 10) == false ||
        chk_data_valid(pl.pres, 10) == false ||
        chk_data_valid(pl.dewp, 10) == false ||
        chk_data_valid(pl.rain, 10) == false ||
        chk_data_valid(pl.wspm, 10) == false) return false;
    if(pl.PM10.get_data() < pl.PM25.get_data()) return false;
    return true;
  }

  struct Record get_Record(const Pre_Record &pl) {
    Record l;
    l.No = pl.No; l.year = pl.year; l.month = pl.month;
    l.day = pl.day; l.hour = pl.hour;
    l.PM25 = static_cast <int> (pl.PM25.get_data());
    l.PM10 = static_cast <int> (pl.PM10.get_data());
    l.SO2 = static_cast <int> (pl.SO2.get_data());
    l.NO2 = static_cast <int> (pl.NO2.get_data());
    l.CO = static_cast <int> (pl.CO.get_data());
    l.O3 = static_cast <int> (pl.O3.get_data());
    l.temp = oDouble(pl.temp.get_data());
    l.pres = oDouble(pl.pres.get_data());
    l.dewp = oDouble(pl.dewp.get_data());
    l.rain = oDouble(pl.rain.get_data());
    l.wd = pl.wd.get_data();
    l.wspm = oDouble(pl.wspm.get_data());
    return l;
  }

  std :: pair <struct Record, bool> filter(const Pre_Record &pl) {
    if (is_valid(pl) == false) return std :: make_pair(Record(), 0);
    else return std :: make_pair(get_Record(pl), 1);
  }
}

namespace Data_Testing {
  void output_test(const Pre_Record_List &pl, bool prt = 0) {
    cout << "total count: " << pl.rec.size() << " pre_record(s). \n";
    if (prt) {
      for (int i = 0; i < pl.rec.size(); ++ i) {
        pl.rec[i].output();
        cout << '\n';
      }
    }
  }
  void output_test(const Record_List &l, bool prt = 0) {
    cout << "total count: " << l.rec.size() << " record(s). \n";
    if (prt) {
      for (int i = 0; i < l.rec.size(); ++ i) {
        l.rec[i].output();
        cout << '\n';
      }
    }
  }
}

namespace Visualization_Data_Constructing {
  int days_of_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  inline bool is_leap_year(int y) {
    return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0;
  }

  inline int get_day_of_month(int y, int m) {
    if(m == 2) return is_leap_year(y) ? 29 : 28;
    else return days_of_month[m];
  }

  bool check_date(int y, int m, int d) {
    if(y <= 0 || m <= 0 || d <= 0 || m > 12 || d > 31) return false;
    if(y < 2013 || y > 2017) return false;
    if(y == 2013 && m < 3) return false;
    if(y == 2017 && m > 2) return false;
    if(d > get_day_of_month(y, m)) return false;
    return true;
  }

  bool in_date(int y1, int m1, int d1, int y2, int m2, int d2, int y3, int m3, int d3) {
    // without checking validation.
    if(y1 > y2) return false;
    if(y1 == y2 && m1 > m2) return false;
    if(y1 == y2 && m1 == m2 && d1 > d2) return false;
    if(y2 > y3) return false;
    if(y2 == y3 && m2 > m3) return false;
    if(y2 == y3 && m2 == m3 && d2 > d3) return false;
    return true;
  }

  vector <Pre_vData> construct_pre_data(int op, const Record_List &l) {
    int y1, m1, d1, y2, m2, d2;
    cout << "\nInput data range (left) (yyyy mm dd): ";
    cin >> y1 >> m1 >> d1;
    if(check_date(y1, m1, d1) == false) throw Input_Date_out_of_bound();
    cout << "\nInput data range (right) (yyyy mm dd): ";
    cin >> y2 >> m2 >> d2;
    if(check_date(y2, m2, d2) == false) throw Input_Date_out_of_bound();
    if(y1 > y2) throw Input_Date_Invalid();
    if(y1 == y2 && m1 > m2) throw Input_Date_Invalid();
    if(y1 == y2 && m1 == m2 && d1 > d2) throw Input_Date_Invalid();

    vector <Pre_vData> ret; ret.clear();
    for (int i = 0; i < l.rec.size(); ++ i) {
      if(in_date(y1, m1, d1, l.rec[i].year, l.rec[i].month, l.rec[i].day, y2, m2, d2)) {
        int _dat, _div;
        switch(op) {
          case 1: case 13: _dat = l.rec[i].PM25, _div = 1; break;
          case 2: case 14: _dat = l.rec[i].PM10, _div = 1; break;
          case 3: case 15: _dat = l.rec[i].SO2, _div = 1; break;
          case 4: case 16: _dat = l.rec[i].NO2, _div = 1; break;
          case 5: case 17: _dat = l.rec[i].CO, _div = 1; break;
          case 6: case 18: _dat = l.rec[i].O3, _div = 1; break;
          case 7: case 19: _dat = l.rec[i].temp.get_original_data(), _div = 10; break;
          case 8: case 20: _dat = l.rec[i].pres.get_original_data(), _div = 10; break;
          case 9: case 21: _dat = l.rec[i].dewp.get_original_data(), _div = 10; break;
          case 10: case 22: _dat = l.rec[i].rain.get_original_data(), _div = 10; break;
          case 12: case 24: _dat = l.rec[i].wspm.get_original_data(), _div = 10; break;
          default: throw Unexpected_Error();
        }
        ret.push_back(Pre_vData(l.rec[i].year, l.rec[i].month, l.rec[i].day, l.rec[i].hour, _dat, _div));
      }
    }
    return ret;
  }

  vData construct_data(int op, const vector <Pre_vData> &pv) {
    if(pv.size() == 0) throw No_Data_Error();
    int n = pv.size(), e = 1;
    vector <double> p;
    if (n <= 50 || op > 12) {
      for (int i = 0; i < n; ++ i) p.push_back(1.0 * pv[i].dat / pv[i].div);
    } else {
      int cnt = 0;
      while(1.0 * n / e > 400) ++ e;
      double cur = 0.0;
      for (int i = 0; i < n; ++ i) {
        if(op == 10) cur = std :: max(cur, 1.0 * pv[i].dat / pv[i].div);
        else cur += 1.0 * pv[i].dat / pv[i].div;
        ++ cnt;
        if(cnt == e) {
          if(op != 10) cur /= e;
          p.push_back(cur);
          cur = 0, cnt = 0;
        }
      }
      if(cnt) {
        if(op != 10) cur /= cnt;
        p.push_back(cur);
        cur = 0, cnt = 0;
      }
    }
    return vData(pv[0].year, pv[0].month, pv[0].day, pv[0].hour,
                 pv[n-1].year, pv[n-1].month, pv[n-1].day, pv[n-1].hour, op, e, p);
  }

  vData construct_wind_data(int op, const Record_List &l) {
    int y1, m1, d1, y2, m2, d2;
    cout << "\nInput data range (left) (yyyy mm dd): ";
    cin >> y1 >> m1 >> d1;
    if(check_date(y1, m1, d1) == false) throw Input_Date_out_of_bound();
    cout << "\nInput data range (right) (yyyy mm dd): ";
    cin >> y2 >> m2 >> d2;
    if(check_date(y2, m2, d2) == false) throw Input_Date_out_of_bound();
    if(y1 > y2) throw Input_Date_Invalid();
    if(y1 == y2 && m1 > m2) throw Input_Date_Invalid();
    if(y1 == y2 && m1 == m2 && d1 > d2) throw Input_Date_Invalid();

    vector <double> p; p.resize(16);
    bool hv = 0;
    for (int i = 0; i < 16; ++ i) p[i] = 0;
    for (int i = 0; i < l.rec.size(); ++ i)
      if(in_date(y1, m1, d1, l.rec[i].year, l.rec[i].month, l.rec[i].day, y2, m2, d2)) p[l.rec[i].wd] ++, hv = 1;
    if(hv == 0) throw No_Data_Error();
    return vData(y1, m1, d1, 0, y2, m2, d2, 23, op, 1, p);
  }
}

namespace Chart_Tools {
  string double_to_string(double x, int dig) {
    string ret = "";
    if(x < 0) ret += "-", x = abs(x);
    int c = static_cast <int> (x); x -= c;
    ret += std :: to_string(c) + ".";
    for (int i = 0; i < dig; ++ i) {
      x *= 10; c = static_cast <int> (x); x -= c;
      ret += std :: to_string(c);
    }
    return ret;
  }
}

namespace Basic_Tools {
  void showVector(string label, vector<double> &v) {
  	cout << label << " ";
  	for(int i = 0; i < v.size(); ++i) cout << v[i] << " ";
  	cout << endl;
  }
}

# endif
