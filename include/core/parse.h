//
//#ifndef NAIVE_BAYES_PARSE_H
//#define NAIVE_BAYES_PARSE_H
//#include <vector>
//#include <string>
//#include <iostream>
//#include <fstream>
//#include <filesystem>
//#include <string>
//#include "datapoint.h"
//using namespace std;
//
//class Parser {
//  public:
//    Parser() = default;
//    vector<DataPoint> data_points_;
//    friend istream& operator >> (istream& is, DataPoint& point) {
//      is >> point.answer_;
//      for(int i = 1; i <= 29; i++) {
//        data_points_.push_back()
//      }
//      return is;
//    }
//
//
//};

//istream& operator >> (istream& is, DataPoint& point) {
//  is >> point.answer_;
//  string line;
//  getline(is, line);
//  char num1 = line[0];
//  point.answer_ = num1;
//  for(int i = 1; i <= 28; i++) {
//    string line2;
//    getline(is, line2);
//    for(int j = 0; j < line2.size(); j++) {
//      point.image_1d.push_back(line2[i]);
//    }
//  }
//  return is;
//}

//#endif  // NAIVE_BAYES_PARSE_H
