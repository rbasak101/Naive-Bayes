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
 double GetAccuracy(std::vector<int> answers, std::vector<DataPoint> test_collection) {
   double correct = 0;
   for(int i = 0; i < answers.size(); i++) {
     if(answers[i] == std::stoi(test_collection[i].answer_)) {
       correct += 1;
     }
   }
   return correct / answers.size();
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
    model.Print3DVector(0);
    REQUIRE(model.unshaded_frequency_matrix[5][5][16] == 0);
    REQUIRE(model.unshaded_frequency_matrix[5][5][15] == 1);
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

  TEST_CASE("Pior Class Probability") {
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
    double prior_prob_0 = model.ClassProbability(0, false);
    double prior_prob_1 = model.ClassProbability(1, false);
    double prior_prob_2 = model.ClassProbability(2, false);
    double prior_prob_3 = model.ClassProbability(3, false);
    double prior_prob_4 = model.ClassProbability(4, false);
    double prior_prob_5 = model.ClassProbability(5, false);
    double prior_prob_6 = model.ClassProbability(6, false);
    double prior_prob_7 = model.ClassProbability(7, false);
    double prior_prob_8 = model.ClassProbability(8, false);
    double prior_prob_9 = model.ClassProbability(9, false);

    REQUIRE(prior_prob_0 == 8.0 / 69.0);
    REQUIRE(prior_prob_1 == 9.0 / 69.0);
    REQUIRE(prior_prob_2 == 4.0 / 69.0);
    REQUIRE(prior_prob_3 == 8.0 / 69.0);
    REQUIRE(prior_prob_4 == 9.0 / 69.0);
    REQUIRE(prior_prob_5 == 5.0 / 69.0);
    REQUIRE(prior_prob_6 == 7.0 / 69.0);
    REQUIRE(prior_prob_7 == 5.0 / 69.0);
    REQUIRE(prior_prob_8 == 5.0 / 69.0);
    REQUIRE(prior_prob_9 == 9.0 / 69.0);
  }

  TEST_CASE("Prior Class Probability with Laplace") {
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
    double prior_prob_0 = model.ClassProbability(0, true);
    double prior_prob_1 = model.ClassProbability(1, true);
    double prior_prob_2 = model.ClassProbability(2, true);
    double prior_prob_3 = model.ClassProbability(3, true);
    double prior_prob_4 = model.ClassProbability(4, true);
    double prior_prob_5 = model.ClassProbability(5, true);
    double prior_prob_6 = model.ClassProbability(6, true);
    double prior_prob_7 = model.ClassProbability(7, true);
    double prior_prob_8 = model.ClassProbability(8, true);
    double prior_prob_9 = model.ClassProbability(9, true);

    REQUIRE(prior_prob_0 == 9.0 / 79.0);
    REQUIRE(prior_prob_1 == 10.0 / 79.0);
    REQUIRE(prior_prob_2 == 5.0 / 79.0);
    REQUIRE(prior_prob_3 == 9.0 / 79.0);
    REQUIRE(prior_prob_4 == 10.0 / 79.0);
    REQUIRE(prior_prob_5 == 6.0 / 79.0);
    REQUIRE(prior_prob_6 == 8.0 / 79.0);
    REQUIRE(prior_prob_7 == 6.0 / 79.0);
    REQUIRE(prior_prob_8 == 6.0 / 79.0);
    REQUIRE(prior_prob_9 == 10.0 / 79.0);
  }

  TEST_CASE("Feature Probability + Saving Model") {
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
    model.Print3DVector(1);

    SECTION("Class 0 pixels") {
      REQUIRE(model.shaded_frequency_matrix[0][6][15] == 8);
      REQUIRE(model.shaded_frequency_matrix[0][6][0] == 0);
      REQUIRE(model.shaded_frequency_matrix[0][6][12] == 3);

      REQUIRE(model.FeatureProbability(0, 6, 15, 1, 2, 1) == 0.9);
      REQUIRE(model.FeatureProbability(0, 6, 0, 1, 2, 1) == 0.1);
      REQUIRE(model.FeatureProbability(0, 6, 12, 1, 2, 1) == 0.4);
    }

    SECTION("Class 9 pixels") {
      REQUIRE(model.shaded_frequency_matrix[9][7][14] == 9);
      REQUIRE(model.shaded_frequency_matrix[9][0][0] == 0);
      REQUIRE(model.shaded_frequency_matrix[9][7][11] == 2);

      REQUIRE(model.FeatureProbability(9, 7, 14, 1, 2, 1)
              == Approx(0.9090909091).epsilon(.0000000001));
      REQUIRE(model.FeatureProbability(9, 0, 0, 1, 2, 1)
              == Approx(0.0909090909).epsilon(.0000000001));
      REQUIRE(model.FeatureProbability(9, 7, 11, 1, 2, 1)
              == Approx(0.2727272727).epsilon(.0000000001));
    }


    SECTION("Saving probabilities: Writing to file output") {
      // Saving probabilities: Writing to file output
      std::ofstream myfile;
      myfile.open("/Users/Rbasak101/Desktop/Cinder/my-projects/naivebayes-rbasak101/tests/output.txt");
      for(int i = 0; i < 10; i++) {
        double feature_prob = model.FeatureLogLikelihood(i, 1);
        myfile <<  "Feature prob for class " << i << ": " << feature_prob << "\n";
      }
      myfile.close();
    }

    SECTION("Saving Model: Writing to file temp_save") {
      std::ofstream save("/Users/Rbasak101/Desktop/Cinder/my-projects/naivebayes-rbasak101/tests/temp_save.txt");
      save << model;
      save.close();
    }

  }

  TEST_CASE("Loading Model") {
    std::string path = "../../../../../../tests/samples.txt";
    Model model(path);
    model.LoadData("/Users/Rbasak101/Desktop/Cinder/my-projects/naivebayes-rbasak101/tests/temp_save.txt");
    REQUIRE(model.shaded_frequency_matrix[9][7][14] == 9);
    REQUIRE(model.shaded_frequency_matrix[9][0][0] == 0);
    REQUIRE(model.shaded_frequency_matrix[9][7][11] == 2);

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

    model.Print3DVector(0);
    REQUIRE(model.unshaded_frequency_matrix[9][6][13] == 7);
    REQUIRE(model.unshaded_frequency_matrix[9][0][0] == 9);
    REQUIRE(model.unshaded_frequency_matrix[9][8][13] == 0);
  }

  TEST_CASE("Make Prediction w/o data loading") {
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
    data_file.close();
    model.Initialize3DVectors(collection);

    std::fstream test_file = std::fstream("../../../../../../tests/test_one.txt");
    DataPoint image1 = DataPoint();
    test_file >> image1;
    test_file.close();
//
    double highest = INT_MIN;
    int index = -1;
    for(int i = 0; i < 10; i++) {
      if(model.LikelihoodScores(image1)[i] > highest) {
        highest = model.LikelihoodScores(image1)[i];
        index = i;
      }
      std::cout << "Likelihood class "<< i << " " << model.LikelihoodScores(image1)[i] << std::endl;
    }
    std::cout << "Classified: " << index << std::endl;
  }

  TEST_CASE("Make Prediction w/ data loading") {
    std::string path = "../../../../../../tests/samples.txt";
    Model model(path);
    model.LoadData("/Users/Rbasak101/Desktop/Cinder/my-projects/naivebayes-rbasak101/tests/temp_save.txt");
//    std::cout << model.class_count_[0] << std::endl;
    std::fstream test_file = std::fstream("../../../../../../tests/test_one.txt");
    DataPoint image1 = DataPoint();
    test_file >> image1;
    test_file.close();

    double highest = INT_MIN;
    int index = -1;
    for(int i = 0; i < 10; i++) {
      std::vector<double> scores = model.LikelihoodScores(image1);
      if(scores[i] > highest) {
        highest = scores[i];
        index = i;
      }
      std::cout << "Likelihood class "<< i << " " << model.LikelihoodScores(image1)[i] << std::endl;
    }
    std::cout << "Classified: " << index << std::endl;
  }

  TEST_CASE("Make Predictions with test_set data via loading") {
    Model model;
    model.LoadData("/Users/Rbasak101/Desktop/Cinder/my-projects/naivebayes-rbasak101/tests/temp_save.txt");

    std::fstream test_file = std::fstream("../../../../../../tests/testimagesandlabels.txt");
    std::vector<DataPoint> test_collection;
    for(int i = 1; i <= 1000; i ++) {
      DataPoint image = DataPoint();
      test_file >> image;
      test_collection.push_back(image);
    }
    test_file.close(); // test datapoints loaded

    // Predicting
    std::vector<int> answers = model.PredictedAnswers(test_collection);
    REQUIRE(GetAccuracy(answers, test_collection) > .70);
    std::cout << "Accuracy: " << GetAccuracy(answers, test_collection) << std::endl;
  }

