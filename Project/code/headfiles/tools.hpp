# ifndef _TOOLS_HPP_
# define _TOOLS_HPP_

# include <iostream>
# include <ctype.h>
# include <string>

# include "data_structure.hpp"
# include "exceptions.hpp"

using std :: string;
using std :: cout;

inline double abs(double x) {
  return x >= 0 ? x : -x;
}

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

namespace Data_Selection_Testing {
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

# endif
