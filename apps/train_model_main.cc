#include <iostream>
#include <fstream>
#include <core/rename_this_file.h>
using namespace std;
// TODO: You may want to change main's signature to take in argc and argv
int main() {
  // TODO: Replace this with code that reads the training data, trains a model,
  // and saves the trained model to a file.

  std::cout << "Welcome to " << naivebayes::Placeholder().GetBestClass()
            << std::endl;

  string text("1 2 3 4 55");
  string path("/Users/Rbasak101/Desktop/Cinder/my-projects/naivebayes-rbasak101/tests/output.txt");


  ofstream MyFile(path);
  MyFile << "jednece rfueion fe .\n";
  std::cout << "Finished" << std::endl;
  MyFile.close();
  return 0;
}
