#ifndef NAIVE_BAYES_DATAPOINT_H
#define NAIVE_BAYES_DATAPOINT_H
#include <vector>
#include <string>
#include <istream>
#include <fstream>
#include <iostream>

using std::istream;
namespace naivebayes {
  class DataPoint {
   public:
    DataPoint();
    int kDimensions_ = 28;
    std::string answer_;                   // int or string
    std::vector<std::vector<char>> image_;  // 0 means empty, 1 means taken
    std::vector<char> image_1d;            // 0 means empty, 1 means taken
    friend istream& operator>>(istream& is, DataPoint& point);
  };

}
#endif  // NAIVE_BAYES_DATAPOINT_H