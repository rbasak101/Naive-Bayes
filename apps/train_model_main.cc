#include <iostream>
#include <vector>
#include <string>
#include "core/model.h"
#include "core/datapoint.h"
#include <math.h>

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

int GetNumberOfLines(std::string filename) {
  ifstream aFile (filename);
  std::size_t lines_count =0;
  std::string line;
  while (std::getline(aFile , line))
    ++lines_count;
  return lines_count;
}

int main() {
  std::string file_load = "/Users/Rbasak101/Desktop/Cinder/my-projects/naivebayes-rbasak101/tests/model_save.txt";
  std::string file_test_images = "/Users/Rbasak101/Desktop/Cinder/my-projects/naivebayes-rbasak101/tests/testimagesandlabels.txt";
  Model model;
  model.LoadData(file_load);

  int lines = GetNumberOfLines(file_test_images);
  model.total_data_points = floor(lines / (model.kDimensions_ + 1));

  std::fstream test_file = std::fstream(file_test_images);
  std::vector<DataPoint> image_test_collection;

  // Reading data points
  for(int i = 1; i <= model.total_data_points; i ++) {
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
