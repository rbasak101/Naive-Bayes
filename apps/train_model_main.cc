#include <iostream>
#include <vector>
#include <string>
#include "core/model.h"
#include "core/datapoint.h"

using namespace std;
using namespace naivebayes;

double GetAccuracy(std::vector<int> answers, std::vector<DataPoint> test_collection) {
  double correct = 0;
  for(int i = 0; i < answers.size(); i++) {
    if(answers[i] == std::stoi(test_collection[i].answer_)) {
      correct += 1;
    }
  }
  return correct / answers.size();
}

int main() {
  Model model;
  model.LoadData("/Users/Rbasak101/Desktop/Cinder/my-projects/naivebayes-rbasak101/tests/temp_save.txt");
  model.total_data_points = 1000;

  std::fstream test_file = std::fstream("/Users/Rbasak101/Desktop/Cinder/my-projects/naivebayes-rbasak101/tests/testimagesandlabels.txt");
  std::cout << test_file.is_open() << std::endl;
  std::vector<DataPoint> image_test_collection;

  // Reading data points
  for(int i = 1; i <= 1000; i ++) {
    DataPoint image = DataPoint();
    test_file >> image;
    image_test_collection.push_back(image);
  }
  test_file.close();

  // Predicting
  std::vector<int> answers = model.PredictedAnswers(image_test_collection);
  std::cout << "Accuracy: " << GetAccuracy(answers, image_test_collection) * 100 << "%" << std::endl;
  return 0;
}
