#include "imagerotatorwindow.h"
#include "imagerotatornamespace.h"
#include "ui_imagerotatorwindow.h"
#include <QFileDialog>
#include <QMessageBox>

ImageRotatorWindow::ImageRotatorWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::ImageRotatorWindow) {
  ui->setupUi(this);
}

ImageRotatorWindow::~ImageRotatorWindow() { delete ui; }

void ImageRotatorWindow::loadInputFolderImages() {
  QDir folder(this->inputFolderPath);

  // Filter the folder to only include image files
  QStringList filters;
  filters << "*.png"
          << "*.jpg";
  folder.setNameFilters(filters);

  // Get a list of all the image files in the directory
  QStringList imageFiles = folder.entryList();

  // Reset images vector before adding new images
  this->images.clear();

  // Load images in vector
  for (const QString &imageFile : imageFiles) {
    QString imagePath = folder.filePath(imageFile);
    QImage image(imagePath);
    images.append(image);
  }
}

void ImageRotatorWindow::saveImagesToOutputFolder() {

  // Save each image to the output folder
  for (int i = 0; i < this->images.size(); i++) {
    QString imagePath =
        this->outputFolderPath + "/" + QString::number(i + 1) + ".png";
    images[i].save(imagePath);
  }
}

void ImageRotatorWindow::on_exitBtn_clicked() { close(); }

void ImageRotatorWindow::on_selectInputFolderBtn_clicked() {
  // Get input folder from user
  this->inputFolderPath = QFileDialog::getExistingDirectory(
      this, tr("Select Input Folder"), QDir::homePath());
}

void ImageRotatorWindow::on_selectOutputFolderBtn_clicked() {
  // Get output folder from user
  this->outputFolderPath = QFileDialog::getExistingDirectory(
      this, tr("Select Output Folder"), QDir::homePath());
}

void ImageRotatorWindow::on_startBtn_clicked() {
  // Check if there is an input folder and an output folder
  if (this->inputFolderPath.isEmpty()) {
    // Show no input file found error
    QMessageBox::critical(this, "Error",
                          "You need to provide an input folder.");
  } else if (this->outputFolderPath.isEmpty()) {
    // Show no input file found error
    QMessageBox::critical(this, "Error",
                          "You need to provide an output folder.");
  } else {
    // All requirements met for running the algorithm
    // Load images from folder
    loadInputFolderImages();

    // Create vector of the 5 time fields
    QVector<QLineEdit *> timeFields{this->ui->t1LineEdit, this->ui->t2LineEdit,
                                    this->ui->t3LineEdit, this->ui->t4LineEdit,
                                    this->ui->t5LineEdit};

    // Run benchmark
    std::vector<double> times =
        ImageRotatorNamespace::benchmark(this->images, timeFields.size());

    // Update time fields with benchmark results
    for (std::size_t i = 0; i < times.size(); i++) {
      timeFields[i]->setText(QString::number(times[i], 'f', 6) + " ms");
    }

    // Update average field with benchmark results average
    double average = std::accumulate(times.begin(), times.end(), 0.0) /
                     static_cast<double>(times.size());
    this->ui->averageLineEdit->setText(QString::number(average, 'f', 6) +
                                       " ms");

    // Save rotated images in output folder
    ImageRotatorNamespace::rotateImages90ClockWise(this->images, this->images);
    saveImagesToOutputFolder();
  }
}

void ImageRotatorWindow::on_resetBtn_clicked() {
  // UI resets
  QVector<QLineEdit *> textFields{
      this->ui->t1LineEdit, this->ui->t2LineEdit, this->ui->t3LineEdit,
      this->ui->t4LineEdit, this->ui->t5LineEdit, this->ui->averageLineEdit};

  for (auto &textField : textFields) {
    textField->clear();
  }

  // Other resets
  this->inputFolderPath.clear();
  this->outputFolderPath.clear();
  this->images.clear();
}
