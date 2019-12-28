# ifndef _DATA_STRUCTURE_HPP_
# define _DATA_STRUCTURE_HPP_

# include <iostream>
# include <vector>
# include <string>
# include "exceptions.hpp"

using std :: vector;
using std :: string;
using std :: cout;

/** Wind Directions **/
enum Wind {
  N = 0, NNE, NE, ENE, E, ESE, SE, SSE,
  S, SSW, SW, WSW, W, WNW, NW, NNW
};

string station_names[] = {"Aotizhongxin", "Changping", "Dingling", "Dongsi",
                          "Guanyuan", "Gucheng", "Huairou", "Nongzhanguan",
                          "Shunyi", "Tiantan", "Wanliu", "Wanshouxigong"};

string wind_to_string[] = {"N", "NNE", "NE", "ENE", "E", "ESE", "SE", "SSE",
                           "S", "SSW", "SW", "WSW", "W", "WNW", "NW", "NNW"};

string op_to_string[] = {"", "PM2.5", "PM10", "SO2", "NO2", "CO", "O3", "Temperature", "Pressure",
                             "Dew point", "Rain", "Wind", "Wind speed"};

string op_to_unit[] = {"", "ug/m^3", "ug/m^3", "ug/m^3", "ug/m^3", "ug/m^3", "ug/m^3", "deg Celcius", "hPa", "deg Celcius", "mm", "", "m/s"};

/** Data Storage Basic Structure **/
template <typename T>
class Data {
  private:
    T dat;
    bool is_rec;

  public:
    Data(T dat, bool is_rec) : dat(dat), is_rec(is_rec) {}
    Data(const Data <T> &rhs) : dat(rhs.get_data()), is_rec(rhs.get_rec_type()) {}

    const T& get_data() const { return dat; }
    bool get_rec_type() const { return is_rec; }
    void output() const {
      if(is_rec == 0) cout << "NA";
      else cout << dat;
    }

    ~ Data() = default;
};

/** The structure for only_one_digit_after_point number **/
const double oDouble_Eps = 1e-8;
struct oDouble {
  private:
    int dat;

  public:
    oDouble(const double &_dat) {
      if(abs((static_cast <int> (_dat * 10)) / 10.0 - _dat) >= oDouble_Eps) throw oDouble_Initialize_Error();
      dat = static_cast <int> (_dat * 10);
    }
    oDouble(const oDouble &rhs) : dat(rhs.get_original_data()) {}

    double get_data() const { return static_cast <double> (dat) / 10.0; }
    const int& get_original_data() const { return dat; }

    ~ oDouble() = default;
};

/** Pre_Record: only read, do not deal with data. **/
struct Pre_Record {
  int No, year, month, day, hour;
  Data <double> PM25, PM10, SO2, NO2, CO, O3;
  Data <double> temp, pres, dewp, rain;
  Data <Wind> wd;
  Data <double> wspm;

  Pre_Record() : No(0), year(0), month(0), day(0), hour(0),
                 PM25(0, 0), PM10(0, 0), SO2(0, 0), NO2(0, 0), CO(0, 0), O3(0, 0),
                 temp(0, 0), pres(0, 0), dewp(0, 0), rain(0, 0), wd(Wind :: N, 0), wspm(0, 0) {}

  Pre_Record(int No, int year, int month, int day, int hour, Data <double> PM25, Data <double> PM10,
             Data <double> SO2, Data <double> NO2, Data <double> CO, Data <double> O3,
             Data <double> temp, Data <double> pres, Data <double> dewp, Data <double> rain,
             Data <Wind> wd, Data <double> wspm) :
               No(No), year(year), month(month), day(day), hour(hour), PM25(PM25), PM10(PM10),
               SO2(SO2), NO2(NO2), CO(CO), O3(O3), temp(temp), pres(pres), dewp(dewp), rain(rain),
               wd(wd), wspm(wspm) {}

  void output() const {
    cout << No << "," << year << "," << month << "," << day << "," << hour << ",";
    PM25.output(); cout << ","; PM10.output(); cout << ","; SO2.output(); cout << ",";
    NO2.output(); cout << ","; CO.output(); cout << ","; O3.output(); cout << ",";
    temp.output(); cout << ","; pres.output(); cout << ","; dewp.output(); cout << ",";
    rain.output(); cout << ",";
    if(wd.get_rec_type() == 0) cout << "NA,";
    else cout << wind_to_string[wd.get_data()] << ",";
    wspm.output();
  }

  ~ Pre_Record() = default;
};

/** Record: the record after dealing with dirty data **/
struct Record {
  int No;
  int year, month, day, hour;
  int PM25, PM10, SO2, NO2, CO, O3;
  oDouble temp, pres, dewp, rain;
  Wind wd;
  oDouble wspm;

  Record() : No(0), year(0), month(0), day(0), hour(0),
             PM25(0), PM10(0), SO2(0), NO2(0), CO(0), O3(0),
             temp(0), pres(0), dewp(0), rain(0), wd(Wind :: N), wspm(0) {}

  Record(int No, int year, int month, int day, int hour, int PM25, int PM10, int SO2, int NO2, int CO,
         int O3, oDouble temp, oDouble pres, oDouble dewp, oDouble rain, Wind wd, oDouble wspm) :
           No(No), year(year), month(month), day(day), hour(hour), PM25(PM25), PM10(PM10),
           SO2(SO2), NO2(NO2), CO(CO), O3(O3), temp(temp), pres(pres), dewp(dewp), rain(rain),
           wd(wd), wspm(wspm) {}

  void output() const {
    cout << No << "," << year << "," << month << "," << day << "," << hour << ",";
    cout << PM25 << "," << PM10 << "," << SO2 << "," << NO2 << "," << CO << "," << O3 << ",";
    cout << temp.get_data() << "," << pres.get_data() << "," << dewp.get_data() << "," << rain.get_data() << ",";
    cout << wind_to_string[wd] << ",";
    cout << wspm.get_data();
  }

  ~ Record() = default;
};

/** Record List **/
struct Record_List {
  vector <Record> rec;
  string station;

  Record_List(const string &station) : station(station) {}
  ~ Record_List() = default;
};

/** Pre_Record List **/
struct Pre_Record_List {
  vector <Pre_Record> rec;
  string station;

  Pre_Record_List(const string &station) : station(station) {}
  ~ Pre_Record_List() = default;
};

/** File Operation **/
struct File_Oper {
  FILE *fp;
  File_Oper(const string &str, const char* file_open_type) {
    fp = fopen(str.c_str(), file_open_type);
    if (fp == nullptr) {
      fp = fopen(str.c_str(), "w");
      fclose(fp);
      fp = fopen(str.c_str(), file_open_type);
    }
  }

  void readFile(void *place, size_t offset, size_t sz, size_t num = 1) {
    if (fseek(fp, offset, SEEK_SET)) throw File_Error();
    fread(place, sz, num, fp);
  }

  void writeFile(void *place, size_t offset, size_t sz, size_t num = 1) {
    if (fseek(fp, offset, SEEK_SET)) throw File_Error();
    fwrite(place, sz, num, fp);
  }

  ~ File_Oper() {
    if (fp != nullptr) fclose(fp);
  }
};

/** pre visualization data **/
struct Pre_vData {
  int year, month, day, hour;
  int dat, div;

  Pre_vData(int year, int month, int day, int hour, int dat, int div = 1) :
    year(year), month(month), day(day), hour(hour), dat(dat), div(div) {}

  ~ Pre_vData() = default;
};

/** visualization data **/
struct vData {
  vector <double> p;
  int y1, m1, d1, h1, y2, m2, d2, h2;
  int op, e;

  vData() { p.clear(); }

  vData(int y1, int m1, int d1, int h1, int y2, int m2, int d2, int h2, int op, int e) :
    y1(y1), m1(m1), d1(d1), h1(h1), y2(y2), m2(m2), d2(d2), h2(h2), op(op), e(e) { p.clear(); }

  vData(int y1, int m1, int d1, int h1, int y2, int m2, int d2, int h2, int op, int e, vector <double> p) :
    y1(y1), m1(m1), d1(d1), h1(h1), y2(y2), m2(m2), d2(d2), h2(h2), op(op), p(p), e(e) {}

  ~ vData() = default;
};

/** Record_with_prediction **/
struct Record_with_prediction {
  Record rec;
  int prediction;
  Record_with_prediction(const Record &rec, int prediction) : rec(rec), prediction(prediction) {}
  ~ Record_with_prediction() = default;
};

# endif
