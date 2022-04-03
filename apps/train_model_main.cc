#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <core/rename_this_file.h>
#include "core/model.h"
#include "core/datapoint.h"
using namespace std;
using namespace naivebayes;
// TODO: You may want to change main's signature to take in argc and argv
int main() {
  // TODO: Replace this with code that reads the training data, trains a model,
  // and saves the trained model to a file.

  std::cout << "Welcome to " << naivebayes::Placeholder().GetBestClass()
            << std::endl;

//  std::string path = "../../../../../../tests/data.txt";
//  Model model(path);
//  std::fstream data_file = std::fstream(path);

//  std::vector<DataPoint> collection;
//  int num = model.total_data_points;
//  for(int i = 1; i <= num; i++) {
//    DataPoint image = DataPoint();
//    data_file >> image;
//    collection.push_back(image);
//  }
//  REQUIRE(collection.size() == num);
//  std::cout << collection.size()  << std::endl;
//  model.Initialize3DVectors(collection);
//  model.Print3DVector(1);

//  model.LoadData("/Users/Rbasak101/Desktop/Cinder/my-projects/naivebayes-rbasak101/tests/temp_save.txt");
//
//  std::fstream test_file = std::fstream("../../../../../../tests/testimagesandlabels.txt");
//  std::vector<DataPoint> test_collection;
//  for(int i = 1; i <= 1000; i ++) {
//    DataPoint image = DataPoint();
//    test_file >> image;
//    test_collection.push_back(image);
//  }
//  test_file.close();
//
//  // Predicting
//  std::cout << test_collection.size() << std::endl;
//  std::vector<int> answers;
//  for(int i = 0; i < test_collection.size() - 1; i++) {
//    int prediction = -1;
//    double highest = INT_MIN;
//    for(int c = 0; c < 10; c++) {
//      std::vector<double> scores = model.LikelihoodScores(test_collection[i]);
//      if(scores[c] > highest) {
//        highest = model.LikelihoodScores(test_collection[i])[c];
//        prediction = c;
//      }
//    }
//    answers.push_back(prediction);
//    //      std::cout << "pred: " << prediction << std::endl;
//  }
//  std::cout << answers.size() << std::endl;
//  //    REQUIRE(answers.size() == 1000);
//
//  double correct = 0;
//  for(int i = 0; i < answers.size(); i++) {
//    if(answers[i] == std::stoi(test_collection[i].answer_)) {
//      correct += 1;
//    }
//  }
//  std::cout << "Accuracy: " << correct / answers.size() << std::endl;


  return 0;
}
