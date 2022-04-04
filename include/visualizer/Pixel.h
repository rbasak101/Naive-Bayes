//
// Created by Ron Basak on 4/3/22.
//
#pragma once

#include "cinder/gl/gl.h"
#ifndef NAIVE_BAYES_PIXEL_H
#define NAIVE_BAYES_PIXEL_H
namespace naivebayes {
  class Pixel {
   public:
    glm::vec2 top_left_;
    glm::vec2 bottom_right_;
    ci::Color color;
    int shaded;
//    ci::Rectf pixel_bounding_box(top_left_, bottom_right_);
//    ci::gl::drawSolidRect(pixel_bounding_box);
  };


}
#endif  // NAIVE_BAYES_PIXEL_H
