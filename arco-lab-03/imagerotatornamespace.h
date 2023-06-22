#ifndef IMAGEROTATORNAMESPACE_H
#define IMAGEROTATORNAMESPACE_H

#include <QImage>
#include <vector>

namespace ImageRotatorNamespace {
void rotateImages90ClockWise(QVector<QImage> &input, QVector<QImage> &output);
std::vector<double> benchmark(QVector<QImage> &images, int numberOfRuns);
}; // namespace ImageRotatorNamespace

#endif // IMAGEROTATORNAMESPACE_H
