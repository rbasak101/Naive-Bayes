#include <catch2/catch.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
//#include "core/parse.h"
#include "core/datapoint.h"
#include <core/rename_this_file.h>

namespace naivebayes {
  // TEST_CASE("File Reading") {
  //   ifstream data_file("../../../../../../tests/data.txt");
  //   cout << __fs::filesystem::current_path() << endl;
  //   if(!data_file) {
  //     cout << "Error opening" << endl;
  //   }
  //
  //   string line;
  //   DataPoint image1;
  //   if(data_file.is_open()) {
  //     cout << "Opened" << endl;
  //     int line_num = 1;
  //
  //     while(line_num <= 29) {
  //       if(line_num % 29 == 1) {
  //         getline(data_file, line);
  //         char l = line[0];
  //         image1.answer_ = l;
  //       } else {
  //         getline(data_file, line);
  //
  //         cout << line << endl;
  //         for(int i = 0; i < line.size(); i++) {
  //           image1.image_1d.push_back(line[i]);
  //         }
  //       }
  //       line_num ++;
  //     }
  //   }
  //
  //   cout << "End-of-file reached.." << endl;
  //   int plus_num = count(image1.image_1d.begin(), image1.image_1d.end(), '+'); int hash_num = count(image1.image_1d.begin(), image1.image_1d.end(), '#');
  //
  //   data_file.close();
  //   REQUIRE(image1.answer_ == '5');
  //   REQUIRE(plus_num == 64);
  //   REQUIRE(hash_num == 84);
  //   REQUIRE(image1.image_1d.size() == 784);
  // }
  //  NSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEE

  //
  TEST_CASE("File Reading II") {
    //  DataPoint a;
    //  fstream data_file("../../../../../../tests/data.txt");
    //  data_file >> a;

    std::string file_path = "../../../../../../tests/data.txt";
    std::fstream file_stream = std::fstream(file_path);
    DataPoint ir = DataPoint();
    file_stream >> ir;
    file_stream.close();
    REQUIRE(ir.answer_ == "5");
    REQUIRE(ir.image_1d.size() == 784);
    //
    //  vector<DataPoint> list;
    //  if(!data_file) {
    //    cout << "Error opening" << endl;
    //  }
    //  if(data_file.is_open()) {
    //    for(int i = 1; i <= 1000; i++) {
    //      DataPoint a;
    //      cin >> a;
    //      list.push_back(a);
    //    }
    //  }
    //
    //  data_file.close();
  }
}






/*
TODO: Rename this test file. You'll also need to modify CMakeLists.txt.

You can (and should) create more test files; this project is too big
for all tests to be in the same file. Remember that, for each file (foo.cc)
containing non-trivial code, you should have a corresponding test file
(foo_test.cc)

Make sure to add any files that you create to CMakeLists.txt.

TODO Delete this comment and the placeholder test before submitting your code.
*/
