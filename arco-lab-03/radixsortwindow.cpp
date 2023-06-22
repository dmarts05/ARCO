#include "radixsortwindow.h"
#include "radixsortnamespace.h"
#include "ui_radixsortwindow.h"
#include <QElapsedTimer>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QVector>
#include <stdexcept>

RadixSortWindow::RadixSortWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::RadixSortWindow) {
  ui->setupUi(this);
}

RadixSortWindow::~RadixSortWindow() { delete ui; }

void RadixSortWindow::loadInputFileNumbers() {
  // Open file for reading
  QFile file(this->inputFilePath);
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    // Reset numbers vector before adding new numbers
    this->numbers.clear();

    QTextStream in(&file);

    // Load numbers in vector
    while (!in.atEnd()) {
      QString line = in.readLine();
      int number = line.toInt();
      this->numbers.push_back(number);
    }

    file.close();
  } else {
    // I/O error
    throw std::runtime_error("Could not open file for reading.");
  }
}

void RadixSortWindow::saveNumbersToOutputFile() {
  // Open the file for writing
  QFile file(this->outputFilePath);
  if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    // Write the numbers to the file
    QTextStream out(&file);
    for (const auto &number : this->numbers) {
      out << number << "\n";
    }

    file.close();
  } else {
    // I/O error
    throw std::runtime_error("Could not open file for writing.");
  }
}

void RadixSortWindow::on_exitBtn_clicked() { close(); }

void RadixSortWindow::on_selectInputFileBtn_clicked() {
  // Get input file from user
  this->inputFilePath =
      QFileDialog::getOpenFileName(this, tr("Open File With Numbers"),
                                   QDir::homePath(), tr("Text Files (*.txt)"));
}

void RadixSortWindow::on_selectOutputFileBtn_clicked() {
  // Get output file from user
  this->outputFilePath = QFileDialog::getOpenFileName(
      this, tr("Open Output File"), QDir::homePath(), tr("Text Files (*.txt)"));
}

void RadixSortWindow::on_startBtn_clicked() {
  // Check if there is an input file and an output file
  if (this->inputFilePath.isEmpty()) {
    // Show no input file found error
    QMessageBox::critical(this, "Error", "You need to provide an input file.");
  } else if (this->outputFilePath.isEmpty()) {
    // Show no input file found error
    QMessageBox::critical(this, "Error", "You need to provide an output file.");
  } else {
    // All requirements met for running the algorithm
    // Load numbers from file
    try {
      loadInputFileNumbers();
    } catch (std::runtime_error &e) {
      QMessageBox::critical(this, "Error", "Could not open file for reading.");
      return;
    }

    // Create vector of the 5 time fields
    QVector<QLineEdit *> timeFields{this->ui->t1LineEdit, this->ui->t2LineEdit,
                                    this->ui->t3LineEdit, this->ui->t4LineEdit,
                                    this->ui->t5LineEdit};

    // Run benchmark
    std::vector<double> times =
        RadixSortNamespace::benchmark(numbers, timeFields.size());

    // Update time fields with benchmark results
    for (std::size_t i = 0; i < times.size(); i++) {
      timeFields[i]->setText(QString::number(times[i], 'f', 6) + " ms");
    }

    // Update average field with benchmark results average
    double average = std::accumulate(times.begin(), times.end(), 0.0) /
                     static_cast<double>(times.size());
    this->ui->averageLineEdit->setText(QString::number(average, 'f', 6) +
                                       " ms");

    // Save sorted numbers in output file
    RadixSortNamespace::radixSort(this->numbers);
    saveNumbersToOutputFile();
  }
}

void RadixSortWindow::on_resetBtn_clicked() {
  // UI resets
  QVector<QLineEdit *> textFields{
      this->ui->t1LineEdit, this->ui->t2LineEdit, this->ui->t3LineEdit,
      this->ui->t4LineEdit, this->ui->t5LineEdit, this->ui->averageLineEdit};

  for (auto &textField : textFields) {
    textField->clear();
  }

  // Other resets
  this->inputFilePath.clear();
  this->outputFilePath.clear();
  this->numbers.clear();
}
