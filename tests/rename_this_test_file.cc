#include <catch2/catch.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
//#include "core/parse.h"
#include "core/datapoint.h"
#include <core/rename_this_file.h>
#include "core/model.h"

using namespace naivebayes;

 int GetCharNum(std::vector<std::vector<char>> image_, std::string x) {
   int num = 0;
   for(int i = 0; i < image_.size(); i++) {
     for(int j = 0; j < image_[i].size(); j++) {
       if(image_[i][j] == x[0]) {
         num += 1;
       }
     }
   }
   return num;
 }

  TEST_CASE("File Reading using operator: 1 datapoint ") {
    std::fstream data_file = std::fstream("../../../../../../tests/data.txt");
    std::vector<DataPoint> collection;
    DataPoint image1 = DataPoint();

    data_file >> image1;
    collection.push_back(image1);
    data_file.close();

    REQUIRE(image1.answer_ == "5");
    REQUIRE(image1.image_.size() * image1.image_[0].size() == 784);

    REQUIRE(GetCharNum(image1.image_, "+") == 64);
    REQUIRE(GetCharNum(image1.image_, "#") == 84);
  }


  TEST_CASE("File Reading using operator: all datapoints ") {
    std::fstream data_file = std::fstream("../../../../../../tests/data.txt");
    std::vector<DataPoint> collection;
    for(int i = 1; i <= 5000; i++) {
      DataPoint image1 = DataPoint();
      data_file >> image1;
      collection.push_back(image1);
    }

    data_file.close();

    REQUIRE(collection[2].answer_ == "4");
    REQUIRE(collection[2].image_.size() * collection[2].image_[0].size() == 784);

    REQUIRE(GetCharNum(collection[2].image_, "+") == 70);
    REQUIRE(GetCharNum(collection[2].image_, "#") == 46);

    REQUIRE(collection[4999].answer_ == "2");
    REQUIRE(collection[4999].image_.size() * collection[4999].image_[0].size() == 784);
    REQUIRE(GetCharNum(collection[4999].image_, "+") == 59);
    REQUIRE(GetCharNum(collection[4999].image_, "#") == 75);

    REQUIRE(collection.size() == 5000);
  }

  TEST_CASE("Model constructor: Class Count + total datapoints") {
    std::string path = "../../../../../../tests/samples.txt";
    Model model(path);
//
//    for(int i = 0; i < model.class_count_.size(); i++) {
//      std::cout << model.class_count_[i];
//    }
//    std::cout <<  std::endl;
    REQUIRE(model.class_count_[0] == 8);
    REQUIRE(model.class_count_[1] == 9);
    REQUIRE(model.class_count_[2] == 4);
    REQUIRE(model.class_count_[3] == 8);
    REQUIRE(model.class_count_[4] == 9);
    REQUIRE(model.class_count_[5] == 5);
    REQUIRE(model.class_count_[6] == 7);
    REQUIRE(model.class_count_[7] == 5);
    REQUIRE(model.class_count_[8] == 5);
    REQUIRE(model.class_count_[9] == 9);

    REQUIRE(model.total_data_points == 69);
  }

  TEST_CASE("Different dimension: 3 x 3 image") {
    std::string path = "../../../../../../tests/one_3x3.txt";
    Model model(path);
    std::fstream data_file = std::fstream(path);

    REQUIRE(model.kDimensions_ == 3);

    std::vector<DataPoint> collection;

    DataPoint image1 = DataPoint();
    image1.kDimensions_ = model.kDimensions_;
    data_file >> image1;
    collection.push_back(image1);
    model.Initialize3DVectors(collection);

    model.Print3DVector(1);
    std::cout << "---------------------------" << std::endl;
    model.Print3DVector(0);

    REQUIRE(collection.size() == 1);
    REQUIRE(model.shaded_frequency_matrix[1][0][1] == 1);
    REQUIRE(model.shaded_frequency_matrix[1][1][1] == 1);
    REQUIRE(model.shaded_frequency_matrix[1][2][1] == 1);
    REQUIRE(model.shaded_frequency_matrix[1][2][2] == 0);
    REQUIRE(model.shaded_frequency_matrix[1][2][0] == 0);

    REQUIRE(model.unshaded_frequency_matrix[1][0][1] == 0);
    REQUIRE(model.unshaded_frequency_matrix[1][1][1] == 0);
    REQUIRE(model.unshaded_frequency_matrix[1][2][1] == 0);
    REQUIRE(model.unshaded_frequency_matrix[1][2][2] == 1);
    REQUIRE(model.unshaded_frequency_matrix[1][2][0] == 1);

  }

  TEST_CASE("Counting frequency of shaded coordinates of number 5") {
    std::string path = "../../../../../../tests/five.txt";
    Model model(path);
    std::fstream data_file = std::fstream(path);

    std::vector<DataPoint> collection;
    DataPoint image = DataPoint();
    data_file >> image;
    collection.push_back(image);

    REQUIRE(collection.size() == 1);
    REQUIRE(model.kDimensions_ == 28);

    model.Initialize3DVectors(collection);
    REQUIRE(model.shaded_frequency_matrix[5][5][16] == 1);
    REQUIRE(model.shaded_frequency_matrix[5][5][15] == 0);

    model.Print3DVector(1);
    // Visual Test
  }

  TEST_CASE("Counting frequency of unshaded coordinates of number 5") {
    std::string path = "../../../../../../tests/five.txt";
    Model model(path);
    std::fstream data_file = std::fstream(path);

    std::vector<DataPoint> collection;
    DataPoint image = DataPoint();
    data_file >> image;
    collection.push_back(image);

    REQUIRE(collection.size() == 1);
    REQUIRE(model.kDimensions_ == 28);

    model.Initialize3DVectors(collection);
    REQUIRE(model.shaded_frequency_matrix[5][5][16] == 0);
    REQUIRE(model.shaded_frequency_matrix[5][5][15] == 1);

    model.Print3DVector(0);
    // Visual Test
  }

  TEST_CASE("Counting frequency of shaded coordinates (Multiple)") {
    std::string path = "../../../../../../tests/samples.txt";
    Model model(path);
    std::fstream data_file = std::fstream(path);

    std::vector<DataPoint> collection;
    int num = model.total_data_points;
    for(int i = 1; i <= num; i++) {
      DataPoint image = DataPoint();
      data_file >> image;
      collection.push_back(image);
    }
    REQUIRE(collection.size() == num);

    model.Initialize3DVectors(collection);
    // Visual Test
    model.Print3DVector(1);
  }

  TEST_CASE("Counting frequency of unshaded coordinates (Multiple)") {
    std::string path = "../../../../../../tests/samples.txt";
    Model model(path);
    std::fstream data_file = std::fstream(path);

    std::vector<DataPoint> collection;
    int num = model.total_data_points;
    for(int i = 1; i <= num; i++) {
      DataPoint image = DataPoint();
      data_file >> image;
      collection.push_back(image);
    }
    REQUIRE(collection.size() == num);

    model.Initialize3DVectors(collection);
    // Visual Test
    model.Print3DVector(0);
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