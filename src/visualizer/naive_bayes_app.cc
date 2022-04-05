#include <visualizer/naive_bayes_app.h>

namespace naivebayes {

namespace visualizer {

NaiveBayesApp::NaiveBayesApp()
    : sketchpad_(glm::vec2(kMargin, kMargin), kImageDimension,
                 kWindowSize - 2 * kMargin) {
  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
  model_.LoadData("/Users/Rbasak101/Desktop/Cinder/my-projects/naivebayes-rbasak101/tests/temp_save.txt");

}

void NaiveBayesApp::draw() {
  ci::Color8u background_color(255, 246, 148);  // light yellow
  ci::gl::clear(background_color);

  sketchpad_.Draw();

  ci::gl::drawStringCentered(
      "Press Delete to clear the sketchpad. Press Enter to make a prediction.",
      glm::vec2(kWindowSize / 2, kMargin / 2), ci::Color("black"));

  ci::gl::drawStringCentered(
      "Prediction: " + std::to_string(current_prediction_),
      glm::vec2(kWindowSize / 2, kWindowSize - kMargin / 2), ci::Color("blue"));
}

void NaiveBayesApp::mouseDown(ci::app::MouseEvent event) {
  sketchpad_.HandleBrush(event.getPos());
}

void NaiveBayesApp::mouseDrag(ci::app::MouseEvent event) {
  sketchpad_.HandleBrush(event.getPos());
}

void NaiveBayesApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_RETURN: {
      std::cout << "Pressed entered" << std::endl;
      DataPoint entered;
      entered.image_ = sketchpad_.GetBoard();
      std::vector<DataPoint> input;
      input.push_back(entered);
      current_prediction_ = model_.PredictedAnswers(input)[0];
      break;
    }
    case ci::app::KeyEvent::KEY_DELETE: {
      std::cout << "Pressed delete" << std::endl;
      sketchpad_.Clear();
      break;
    }
  }
}

}  // namespace visualizer

}  // namespace naivebayes
