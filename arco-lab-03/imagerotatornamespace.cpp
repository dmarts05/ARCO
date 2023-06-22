#include "imagerotatornamespace.h"
#include <QElapsedTimer>

namespace ImageRotatorNamespace {
// Transform approach
void rotateImages90ClockWise(QVector<QImage> &input, QVector<QImage> &output) {
  for (int i = 0; i < input.size(); ++i) {
    output[i] = input[i].transformed(QTransform().rotate(90));
  }
}

// Pixel by pixel approach
// void rotateImages90ClockWise(QVector<QImage> &input,
//                             QVector<QImage> &output) {
//  // Loop over each input image
//  for (int i = 0; i < input.size(); i++) {
//    // Get the width and height of the input image
//    int width = input[i].width();
//    int height = input[i].height();

//    // Create a new QImage object with the dimensions of the rotated image
//    // Width and height are swapped because the image is being
//    // rotated 90 degrees clockwise.
//    QImage rotatedImage(height, width, input[i].format());

//    // Loop over each pixel in the input image
//    for (int y = 0; y < height; y++) {
//      for (int x = 0; x < width; x++) {
//        // Get the pixel at (x,y) in the input image
//        QRgb pixel = input[i].pixel(x, y);

//        // Set the pixel at the rotated position in the output image
//        // The new position is calculated as (height - y - 1, x)
//        // This is because the image is being rotated 90 degrees clockwise
//        // and the rows are being flipped horizontally
//        rotatedImage.setPixel(height - y - 1, x, pixel);
//      }
//    }

//    // Set the output image to the rotated image
//    output[i] = rotatedImage;
//  }
//}

std::vector<double> benchmark(QVector<QImage> &images, int numberOfRuns) {
  // Rotate images 90 degrees and measure the time it takes for
  // numberOfRuns times
  std::vector<double> times;
  QElapsedTimer timer;
  QVector<QImage> rotatedImages(images.size());
  for (int i = 0; i < numberOfRuns; i++) {
    // Measure rotating time
    timer.start();
    rotateImages90ClockWise(images, rotatedImages);
    double elapsedTime = timer.nsecsElapsed() / 1000000.0;

    // Add time to vector
    times.push_back(elapsedTime);
  }

  return times;
}
} // namespace ImageRotatorNamespace
