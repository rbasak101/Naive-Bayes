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
    std::string answer_;                        // int or string
    std::vector<std::vector<int>> image_;  // 0 means empty, 1 means taken
    std::vector<int> image_1d;             // 0 means empty, 1 means taken
    friend istream& operator>>(istream& is, DataPoint& point);
  };
}
#endif  // NAIVE_BAYES_DATAPOINT_H