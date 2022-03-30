#include <string>
#include <vector>
#include "core/datapoint.h"
#include <istream>

namespace naivebayes {

  DataPoint::DataPoint() {
    this->answer_ = "-1";
  }

  istream& operator>>(istream& is, DataPoint& point) {
    std::string line;
    getline(is, line);
    point.answer_ = line;

      for(int i = 1; i <= point.kDimensions_; i++) {
        std::string line2;
        getline(is, line2);
        std::vector<char> row;
//        std::cout << "Found line "<< i << ": " << line2 << " size: " << line2.size() << std::endl;
        for(int j = 0; j < line2.size(); j++) {
          row.push_back(line2[j]);
        }
        point.image_.push_back(row);
      }
    return is;
  }
}
