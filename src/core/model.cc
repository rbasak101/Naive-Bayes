#include <string>
#include <vector>
#include "core/model.h"
#include <istream>
#include <array>
#include <ostream>
#include <math.h>
#include <sstream>
//#include <stream>
namespace naivebayes {

void Model::Print3DVector(int shaded) {
  std::cout << "Traversing 3d vector" << std::endl;
  if (shaded == 1) {
    for (int c = 0; c < shaded_frequency_matrix.size(); c++) {
      for (int i = 0; i < shaded_frequency_matrix[c].size(); i++) {
        for (int j = 0; j < shaded_frequency_matrix[c][i].size(); j++) {
          std::cout << shaded_frequency_matrix[c][i][j] << " ";
        }
        std::cout << std::endl;
      }
      std::cout << std::endl;
    }
  } else {
    for (int c = 0; c < unshaded_frequency_matrix.size(); c++) {
      for (int i = 0; i < unshaded_frequency_matrix[c].size(); i++) {
        for (int j = 0; j < unshaded_frequency_matrix[c][i].size(); j++) {
          std::cout << unshaded_frequency_matrix[c][i][j] << " ";
        }
        std::cout << std::endl;
      }
      std::cout << std::endl;
    }
  }
}
Model::Model() {

}

Model::Model(std::string file) {
  file_path_ = file;
  total_data_points = 0;
  //    for(int i = 0; i < kNumberOfDigits; i++) {
  //      class_count_.push_back(0);                // Make size 10 (had issues declaring fixed size)
  //    }
  InitializeClassCount();
}

void Model::InitializeClassCount() {
  std::fstream data_file = std::fstream(file_path_);
  std::string temp;
  int line = 1;
  while (std::getline(data_file, temp)) {
    if (line % 29 == 1) {  // Counting number of data points
      total_data_points += 1;
      //        std::cout << temp << std::endl;
      int num = std::stoi(temp);
      class_count_[num] += 1;
      //        std::cout << "freq of " << num << ": " << class_count_[num] << std::endl;
    }
    if (line == 2) {  // find size of image once
      kDimensions_ = temp.size();
    }
    line += 1;
  }
}

void Model::Initialize3DVectors(std::vector<DataPoint> collection) {
  //    std::cout << "Size of collection: " << collection.size() << std::endl;
  //    std::vector<std::vector<std::vector<double>>>
  //        matrix{10, std::vector< std::vector<double> >(kDimensions_ , std::vector<double>(kDimensions_, 0))};
  this->shaded_frequency_matrix = std::vector<std::vector<std::vector<double>>>(
      10, std::vector<std::vector<double>>(
              kDimensions_, std::vector<double>(kDimensions_, 0)));

  this->unshaded_frequency_matrix =
      std::vector<std::vector<std::vector<double>>>(
          10, std::vector<std::vector<double>>(
                  kDimensions_, std::vector<double>(kDimensions_, 0)));

  //    std::vector<std::vector<std::vector<double>>>
  //        matrix2{10, std::vector< std::vector<double> >(kDimensions_ , std::vector<double>(kDimensions_, 0))};
  //    unshaded_frequency_matrix = matrix2;

  for (auto& datapoint : collection) {
    int answer = std::stoi(datapoint.answer_);
    for (int row = 0; row < datapoint.image_.size(); row++) {
      for (int col = 0; col < datapoint.image_[row].size(); col++) {
        //          std::string empty = " ";
        //          char e = empty[0]; // cant compare " " directly for some reason
        if (datapoint.image_[row][col] != ' ') {
          shaded_frequency_matrix[answer][row][col] += 1;
        } else {
          unshaded_frequency_matrix[answer][row][col] += 1;
        }
      }
    }
  }
}

double Model::ClassProbability(int c, bool laplace) {
  if (laplace) {
    double numerator = class_count_[c] + kClass_;  //
    double denominator = vClass_ * kClass_ + total_data_points;
    return numerator / denominator;
  }
  double numerator = class_count_[c];
  double denominator = total_data_points;
  return numerator / denominator;
}

double Model::FeatureProbability(int c, int row, int col, int k, int v,
                                 int shaded) {
  double numerator = 0;
  double denominator = 0;
  if (shaded == 1) {
    numerator = shaded_frequency_matrix[c][row][col] + k;
    denominator = class_count_[c] + v * k;
    return numerator / denominator;
  }
  numerator = unshaded_frequency_matrix[c][row][col] + k;
  denominator = class_count_[c] + v * k;
  return numerator / denominator;
}

double Model::FeatureLogLikelihood(int c, int shaded) {
  double answer = 0;
  std::cout << "inside feature prob " << shaded_frequency_matrix[0].size()
            << " " << shaded_frequency_matrix[0][0].size() << std::endl;
  if (shaded == 1) {
    for (int i = 0; i < shaded_frequency_matrix[0].size(); i++) {
      for (int j = 0; j < shaded_frequency_matrix[0][0].size(); j++) {
        answer += log(FeatureProbability(c, i, j, kFeature_, vFeature_, 1));
        std::cout << "Prob for pixel: " << i << ", " << j << ": "
                  << FeatureProbability(c, i, j, 1, 2, 1) << std::endl;
        std::cout << "Answer: " << answer << std::endl;
      }
    }
    double denominator = log(ClassProbability(c, true));
    return denominator + answer;
  }

  for (int i = 0; i < unshaded_frequency_matrix[0].size(); i++) {
    for (int j = 0; j < unshaded_frequency_matrix[0][0].size(); j++) {
      answer += log(FeatureProbability(c, i, j, kFeature_, vFeature_, 1));
    }
  }
  double denominator = log(ClassProbability(c, true));
  return denominator + answer;
}

ostream& operator<<(ostream& out, const Model& model) {
  //    out << "Model Data \n" ;
  //    out << "Saving 3D shaded matrix: \n" ;
  out << model.kDimensions_ << std::endl;
  for (int c = 0; c < model.shaded_frequency_matrix.size(); c++) {
    for (int i = 0; i < model.shaded_frequency_matrix[c].size(); i++) {
      for (int j = 0; j < model.shaded_frequency_matrix[c][i].size(); j++) {
        out << model.shaded_frequency_matrix[c][i][j] << " ";
      }
//      out << std::endl;
    }
    out << std::endl;
  }
  out << std::endl;
  for (int i = 0; i < model.class_count_.size(); i++) {
    out << model.class_count_[i] << std::endl;
  }
//  out << std::endl;

  for (int c = 0; c < model.unshaded_frequency_matrix.size(); c++) {
    for (int i = 0; i < model.unshaded_frequency_matrix[c].size(); i++) {
      for (int j = 0; j < model.unshaded_frequency_matrix[c][i].size(); j++) {
        out << model.unshaded_frequency_matrix[c][i][j] << " ";
      }
      //      out << std::endl;
    }
    out << std::endl;
  }
  return out;
}

istream& operator>>(istream& is, const Model& model) {
  return is;
}

void Model::LoadData(std::string file) {
  //    Model model = Model();
  std::string line;
  std::ifstream infile(file);
  getline(infile, line);
  int dim = std::stoi(line);
  this->kDimensions_ = dim;

  std::vector<std::vector<std::vector<double>>> shaded_matrix;

  for(int a = 1; a <= kNumberOfDigits; a++){
    getline(infile, line);
//    std::cout << "line: " << line << std::endl;
    std::string line_string = line;
    std::stringstream iss(line_string);
    int number;
    std::vector<double> row_;
    while (iss >> number) {
      row_.push_back(number);
    }

    std::vector<std::vector<double>> two_d;
    two_d.resize(kDimensions_);
    for(int i = 0; i < kDimensions_; i++) {
      two_d[i].resize(kDimensions_);
    }
    for(int i = 0; i < row_.size(); i++) {
      int r = i / kDimensions_;
      int c = i % kDimensions_;
      two_d[r][c] = row_[i];
    }
    shaded_matrix.push_back(two_d);
  }

  this->shaded_frequency_matrix = shaded_matrix;
  getline(infile, line);
  for(int i = 0; i < kNumberOfDigits; i++) {
    getline(infile, line);
    this->class_count_[i] = std::stoi(line);
  }

  std::vector<std::vector<std::vector<double>>> unshaded_matrix;
  for(int a = 1; a <= kNumberOfDigits; a++){
    getline(infile, line);
    //    std::cout << "line: " << line << std::endl;
    std::string line_string = line;
    std::stringstream iss(line_string);
    int number;
    std::vector<double> row_;
    while (iss >> number) {
      row_.push_back(number);
    }

    std::vector<std::vector<double>> two_d;
    two_d.resize(kDimensions_);
    for(int i = 0; i < kDimensions_; i++) {
      two_d[i].resize(kDimensions_);
    }
    for(int i = 0; i < row_.size(); i++) {
      int r = i / kDimensions_;
      int c = i % kDimensions_;
      two_d[r][c] = row_[i];
    }
    unshaded_matrix.push_back(two_d);
  }
  this->unshaded_frequency_matrix = unshaded_matrix;

}

  std::vector<double> Model::LikelihoodScores(const DataPoint &dataPoint) {
    std::vector<std::vector<char>> image = dataPoint.image_;
    std::vector<double> scores;
    for(int c = 0; c < kNumberOfDigits; c++) {
      double answer = 0;
      for(int i = 0; i < image.size(); i++) {
        for(int j = 0; j < image[0].size(); j++) {
          if(image[i][j] != ' ') { // shaded
            answer += log(FeatureProbability(c, i, j, kFeature_, vFeature_, 1));
          } else {
            answer += log(FeatureProbability(c, i, j, kFeature_, vFeature_, 0));
          }
        }
      }
      double denominator = log(ClassProbability(c, true));
      scores.push_back(answer + denominator);
    }
    return scores;
//    return answer + denominator;
  }
}