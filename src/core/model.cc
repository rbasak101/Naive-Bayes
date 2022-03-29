#include <string>
#include <vector>
#include "core/model.h"
#include <istream>
#include <array>
namespace naivebayes {

  void Model::Print3DVector(int shaded) {
    std::cout << "Traversing 3d vector" << std::endl;
    if(shaded == 1) {
      for(int c = 0; c < shaded_frequency_matrix.size(); c++) {
        for(int i = 0; i < shaded_frequency_matrix[c].size(); i++) {
          for(int j = 0; j < shaded_frequency_matrix[c][i].size(); j++) {
            //          if(shaded_frequency_matrix[c][i][j] == 1) {
            //            std::cout << "coord: " << c << " " << i << " " << j << std::endl;
            //            std::cout << shaded_frequency_matrix[c][i][j] << " ";
            //          }
            std::cout << shaded_frequency_matrix[c][i][j] << " ";
          }
          std::cout << std::endl;
        }
        std::cout << std::endl;
      }
    } else {
      for(int c = 0; c < unshaded_frequency_matrix.size(); c++) {
        for(int i = 0; i < unshaded_frequency_matrix[c].size(); i++) {
          for(int j = 0; j < unshaded_frequency_matrix[c][i].size(); j++) {
            std::cout << unshaded_frequency_matrix[c][i][j] << " ";
          }
          std::cout << std::endl;
        }
        std::cout << std::endl;
      }
    }

  }

  Model::Model(std::string file) {
    file_path_ = file;
    total_data_points = 0;
    for(int i = 0; i < kNumberOfDigits; i++) {
      class_count_.push_back(0); // Make size 10 (had issues declaring fixed size)
    }
    InitializeClassCount();
  }

  void Model::InitializeClassCount() {
    std::fstream data_file = std::fstream(file_path_);
    std::string temp;
    int line = 1;
    while(std::getline(data_file, temp)) {
      if(line % 29 == 1) {
        total_data_points += 1;
        std::cout << temp << std::endl;
        int num = std::stoi(temp);
        class_count_[num] += 1;
//        std::cout << "freq of " << num << ": " << class_count_[num] << std::endl;
      }
      if(line == 2) { // find size of image once
        kDimensions_ = temp.size();
      }
      line += 1;
    }

  }

  void Model::Initialize3DVectors(std::vector<DataPoint> collection) {
//    std::cout << "Size of collection: " << collection.size() << std::endl;
    std::vector<std::vector<std::vector<double>>>
        matrix{10, std::vector< std::vector<double> >(kDimensions_ , std::vector<double>(kDimensions_, 0))};
    shaded_frequency_matrix = matrix;

    std::vector<std::vector<std::vector<double>>>
        matrix2{10, std::vector< std::vector<double> >(kDimensions_ , std::vector<double>(kDimensions_, 0))};
    unshaded_frequency_matrix = matrix2;

    for(auto &datapoint: collection) {
      int answer = std::stoi(datapoint.answer_);
      for(int row = 0; row < datapoint.image_.size(); row++) {
        for(int col = 0; col < datapoint.image_[row].size(); col++) {
          std::string empty = " ";
          char e = empty[0];                                                      // cant compare " " directly for some reason
          if(datapoint.image_[row][col] != e) {
            shaded_frequency_matrix[answer][row][col] += 1;
          } else {
            unshaded_frequency_matrix[answer][row][col] += 1;
          }
        }
      }
    }
  }

  void Model::LaplaceSmoothingPoint(int k, int V, int c, int row, int col, int shaded) {
    if(shaded == 1) {
      shaded_frequency_matrix[c][row][col] += k;
    } else {
      unshaded_frequency_matrix[c][row][col] += k;
    }
    class_count_[c] += k*V;
  }

  void Model::LaplaceSmoothingClass(int k, int V, int c) {
    class_count_[c] += k*V;
  }

}