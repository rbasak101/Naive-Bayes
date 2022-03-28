#include <string>
#include <vector>
#include "core/datapoint.h"
#include <istream>


namespace naivebayes {

DataPoint::DataPoint() {
  this->answer_ = "Y";
}

istream& operator>>(istream& is, DataPoint& point) {
  //  is >> point.answer_;
  std::string line;
  getline(is, line);
  //  char num1 = line[0];
  point.answer_ = line;
    for(int i = 1; i <= 28; i++) {
      std::string line2;
      getline(is, line2);
      for(int j = 0; j < line2.size(); j++) {
        point.image_1d.push_back(line2[j]);
      }
    }
  return is;
}

}