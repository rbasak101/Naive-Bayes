#ifndef NAIVE_BAYES_TRAIN_MODEL_H
#define NAIVE_BAYES_TRAIN_MODEL_H
#include <string>
#include <vector>
#include "core/datapoint.h"
#include <istream>
#include <array>
#include <iostream>
#include <iosfwd>
#include <math.h>

namespace naivebayes {
using std::ostream;
  class Model {
    public:
      /**
       * Takes in file path of data and initializes class_count_, file_path_,
       * and total_data_points
       * @param file_path
       */
      Model(std::string file_path);
      Model();
      int total_data_points; // Number of datapoints | datapoint includes 2d vector and actual digit
      std::string file_path_;
      std::vector<int> class_count_ = std::vector<int>(10, 0);
      //std::vector<int> class_count_;        // Keeps track of the frequencies of each digit.
                                            // Index = digit, class_count_[i] = number of class i occurrences
      // Can't create with fixed size of 10 using std::vector<int> class_count_(10)
      int kNumberOfDigits = 10;
      int kDimensions_;
      std::vector<std::vector<std::vector<double>>>    // 1D for digit, 2D for image. Keeps track of F(i,j) frequency that are shaded
          shaded_frequency_matrix;
      std::vector<std::vector<std::vector<double>>>  // 1D for digit, 2D for image. Keeps track of F(i,j) frequency that are unshaded
          unshaded_frequency_matrix;

      int kClass_ = 1;
      int vClass_ = 10;
      int kFeature_ = 1;
      int vFeature_ = 2;

      /**
       * Helper function to print 3D vector. Used for debugging
       * if shaded == 1, prints shaded matrix. else prints the unshaded matrix
       * @param shaded
       */
      void Print3DVector(int shaded);

      /**
       * Calculates class frequency and stores them inside class_count_
       */
      void InitializeClassCount();

      /**
       * Takes in vector of datapoints and initializes both shaded and unshaded matrices
       * @param collection
       */
      void Initialize3DVectors(std::vector<DataPoint> collection);

      /**
       * Calculates P(class = c)
       * @param c represents class
       * @param laplace if smoothing is desired
       * @return
       */
      double ClassProbability(int c, bool laplace);

      /**
       *
       * @param c represents class
       * @param row
       * @param col
       * @param k smoothing constant
       * @param v smoothing constant
       * @param shaded if 1 using shaded matrix, else unshaded
       * @return Feature probability for 1 pixel or tile
       */
      double FeatureProbability(int c, int row, int col, int k , int v, int shaded);

      /**
       * @param c
       * @param shaded
       * @return LOG of cumulative probability, using FeatureProbability(...) as helper
       * and ClassProbability(...)
       *
       */
      double FeatureLogLikelihood(int c, int shaded);

      friend ostream& operator<<(ostream& is, const Model& model);

      friend istream& operator>>(istream& is, const Model& model);

      void LoadData(std::string file);

  };
}



#endif  // NAIVE_BAYES_TRAIN_MODEL_H






//      std::vector<std::vector<std::vector<double>>>
//          shaded_frequency_matrix{10, std::vector< std::vector<double> >(kDimensions_ , std::vector<double>(kDimensions_, 0))};
// stores # of images or data_points where in class c (i,j) is shaded