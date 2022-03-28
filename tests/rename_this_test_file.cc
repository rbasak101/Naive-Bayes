#include <catch2/catch.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
//#include "core/parse.h"
#include "core/datapoint.h"
#include <core/rename_this_file.h>

using namespace naivebayes;
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
  TEST_CASE("File Reading using operator: 1 datapoint ") {
    std::fstream data_file = std::fstream("../../../../../../tests/data.txt");
    std::vector<DataPoint> collection;
    DataPoint image1 = DataPoint();
    data_file >> image1;
    collection.push_back(image1);
    data_file.close();
    REQUIRE(image1.answer_ == "5");
    REQUIRE(image1.image_1d.size() == 784);
    int plus_num = count(image1.image_1d.begin(), image1.image_1d.end(), '+');
    int hash_num = count(image1.image_1d.begin(), image1.image_1d.end(), '#');
    REQUIRE(plus_num == 64);
    REQUIRE(hash_num == 84);

//    std::vector<std::vector<int>> matrix;
//    matrix.resize(28, std::vector<int>(28));
//
//    for(int i = 0; i < image1.image_1d.size(); i++) {
//      std::cout << image1.image_1d[i] << std::endl;
//    }

  }

  TEST_CASE("File Reading using operator: multiple datapoints ") {
    std::fstream data_file = std::fstream("../../../../../../tests/data.txt");
    std::vector<DataPoint> collection;
    for(int i = 1; i <= 5000; i++) {
      DataPoint image1 = DataPoint();
      data_file >> image1;
      collection.push_back(image1);
    }

    data_file.close();
    REQUIRE(collection[0].answer_ == "5");
    REQUIRE(collection[0].image_1d.size() == 784);
    int plus_num = count(collection[0].image_1d.begin(), collection[0].image_1d.end(), '+');
    int hash_num = count(collection[0].image_1d.begin(), collection[0].image_1d.end(), '#');
    REQUIRE(plus_num == 64);
    REQUIRE(hash_num == 84);
    std::cout << "Indexing: "<< collection[0].image_1d[185] << std::endl;
//    REQUIRE(collection[0].image_1d[185])


    REQUIRE(collection[2].answer_ == "4");
    REQUIRE(collection[2].image_1d.size() == 784);
    plus_num = count(collection[2].image_1d.begin(), collection[2].image_1d.end(), '+');
    hash_num = count(collection[2].image_1d.begin(), collection[2].image_1d.end(), '#');
    REQUIRE(plus_num == 70);
    REQUIRE(hash_num == 46);


    plus_num = count(collection[4999].image_1d.begin(), collection[4999].image_1d.end(), '+');
    hash_num = count(collection[4999].image_1d.begin(), collection[4999].image_1d.end(), '#');
    REQUIRE(collection[4999].answer_ == "2");
    REQUIRE(collection[4999].image_1d.size() == 784);
    REQUIRE(plus_num == 59);
    REQUIRE(hash_num == 75);


    REQUIRE(collection.size() == 5000);
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
