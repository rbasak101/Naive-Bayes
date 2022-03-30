#include <string>
#include <vector>
#include "core/model.h"
#include <istream>
#include <array>
#include <ostream>
namespace naivebayes {

  void Model::Print3DVector(int shaded) {
    std::cout << "Traversing 3d vector" << std::endl;
    if(shaded == 1) {
      for(int c = 0; c < shaded_frequency_matrix.size(); c++) {
        for(int i = 0; i < shaded_frequency_matrix[c].size(); i++) {
          for(int j = 0; j < shaded_frequency_matrix[c][i].size(); j++) {
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
      class_count_.push_back(0);                // Make size 10 (had issues declaring fixed size)
    }
    InitializeClassCount();
  }

  void Model::InitializeClassCount() {
    std::fstream data_file = std::fstream(file_path_);
    std::string temp;
    int line = 1;
    while(std::getline(data_file, temp)) {
      if(line % 29 == 1) {    // Counting number of data points
        total_data_points += 1;
//        std::cout << temp << std::endl;
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

  double Model::ClassProbability(int c, bool laplace) {
    if(laplace) {
      double numerator = class_count_[c] + kClass_;   //
      double denominator = vClass_*kClass_ + total_data_points;
      return numerator / denominator;
    }
    double numerator = class_count_[c];
    double denominator = total_data_points;
    return numerator / denominator;
  }

  double Model::FeatureProbability(int c, int row, int col, int k , int v, int shaded){
    double numerator = 0;
    double denominator = 0;
    if(shaded == 1) {
      numerator = shaded_frequency_matrix[c][row][col] + 1;
      denominator = class_count_[c] + v*k;
//      std::cout << "Shaded Numerator: " << numerator << std::endl;
//      std::cout << "Denominator: " << denominator << std::endl;
      return numerator / denominator;
    }
    numerator = unshaded_frequency_matrix[c][row][col] + 1;
    denominator = class_count_[c] + v*k;
//    std::cout << "Unshaded Numerator: " << numerator << std::endl;
//    std::cout << "Denominator: " << denominator << std::endl;
    return numerator / denominator;
  }

  double Model::FeatureProbabilities(int c, int shaded) {
    double answer = 1;
    std::cout << "inside feature prob " << shaded_frequency_matrix[0].size() << " " << shaded_frequency_matrix[0][0].size() << std::endl;
    if(shaded == 1) {
      for(int i = 0; i < shaded_frequency_matrix[0].size(); i++) {
        for(int j = 0; j < shaded_frequency_matrix[0][0].size(); j++) {
          answer *= FeatureProbability(c,i,j,1,2,1);
          std::cout << "Prob for pixel: " << i << ", " << j << ": " << FeatureProbability(c,i,j,1,2,1) <<std::endl;
          std::cout << "Answer: " << answer << std::endl;
        }
      }
      return answer;
    }
    for(int i = 0; i < unshaded_frequency_matrix[0].size(); i++) {
      for(int j = 0; j < unshaded_frequency_matrix[0][0].size(); j++) {
        answer *= FeatureProbability(c,i,j,1,2,1);
      }
    }
    return answer;
  }

  ostream& operator <<(ostream & out, const Model &model) {
    out << "Model Data \n" ;
    out << "Saving 3D shaded matrix: \n" ;
    for(int c = 0; c < model.shaded_frequency_matrix.size(); c++) {
      for(int i = 0; i < model.shaded_frequency_matrix[c].size(); i++) {
        for(int j = 0; j < model.shaded_frequency_matrix[c][i].size(); j++) {
          out << model.shaded_frequency_matrix[c][i][j] << " ";
        }
        out << std::endl;
      }
      out << std::endl;
    }

    for(int i = 0; i < model.class_count_.size(); i++){
      out << model.class_count_[i] << " ";
    }
    out << std::endl;
    return out;
  }

}