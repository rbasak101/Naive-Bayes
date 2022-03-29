#ifndef NAIVE_BAYES_TRAIN_MODEL_H
#define NAIVE_BAYES_TRAIN_MODEL_H
#include <string>
#include <vector>
#include "core/datapoint.h"
#include <istream>
#include <array>

namespace naivebayes {

  class Model {
    public:
      Model(std::string file_path);

      int total_data_points;
      std::string file_path_;
      std::vector<int> class_count_;        // Can't create with fixed size of 10 using std::vector<int> class_count_(10)
      int kNumberOfDigits = 10;
      int kDimensions_ = 28;
      std::vector<std::vector<std::vector<double>>>
          shaded_frequency_matrix{10, std::vector< std::vector<double> >(kDimensions_ , std::vector<double>(kDimensions_, 0))};
      // stores # of images or data_points where in class c (i,j) is shaded

      void Print3DVector();
      void InitializeClassCount();
      void Initialize3DVector(std::vector<DataPoint> collection);

  };

}



#endif  // NAIVE_BAYES_TRAIN_MODEL_H
