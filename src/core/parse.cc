//#include "main.h"
#include <iostream>
#include <fstream>
#include <string>
#include "core/datapoint.h"
#include <vector>
//#include "core/parse.h"
//using namespace std;



//istream& Parser::operator >> (istream& is, DataPoint& point) {
//  return is;
//  vector<DataPoint> data_points;
//  ifstream data_file("../../../../../../tests/data.txt");
//  cout << __fs::filesystem::current_path() << endl;
//  if(!data_file) {
//    cout << "Error opening" << endl;
//  }
//  vector<string> list;
//  string line;
//  if(data_file.is_open()) {
//    cout << "Opened" << endl;
//
//    int line_num = 1;
//    while(getline(data_file, line)) {
//      cout << line << endl;
//      if(line_num % 29 == 1) {
//        DataPoint a;
//        a.answer_ = data_file.get();
//      }
//
//      data_file.get();
//      line_num += 1;
//    }
//  }
//
//  data_file.close();
//  return DataPoint();
//}


//DataPoint d;
//while(is >> d){
//}


//int main() {
//    ifstream data_file("data.txt");
//    data_file.open("/Users/Rbasak101/Desktop/mnistdatatraining/data.txt");
//
//
//    string line;
//    while(data_file >> line) {
//      cout << line << endl;
//    }
//


//    while(getline(data_file, line)) {
//      cout << line;
//    }
//    data_file.close();

//    return 0;
//};
