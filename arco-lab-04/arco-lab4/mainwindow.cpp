#include "mainwindow.h"
#include "ieeeconverternamespace.h"
#include "ieeefloat.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <algorithm>
#include <bitset>
#include <limits>
#include <regex>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

bool MainWindow::isValidFloatOutOfBounds(std::string valueStr) {
  // Regex pattern to match a float number with overflow
  std::regex pattern(R"([-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?)");

  // Match the string against the pattern
  return std::regex_match(valueStr, pattern);
}

bool MainWindow::getFloatFromLineEdit(QLineEdit *lineEdit, float &value) {
  bool isValid;
  std::string valueStr = lineEdit->text().toStdString();

  // Convert the string to float
  value = lineEdit->text().toFloat(&isValid);

  // If the string is not a valid float, check if it is a valid float with
  // overflow
  isValid = isValid || isValidFloatOutOfBounds(valueStr);

  return isValid;
}

Operation MainWindow::getOperationFromComboBox() {
  std::string opStr = ui->operationComboBox->currentText().toStdString();
  if (opStr == "+") {
    return Operation::ADDITION;
  } else if (opStr == "*") {
    return Operation::MULTIPLICATION;
  } else if (opStr == "/") {
    return Operation::DIVISION;
  } else {
    return Operation::INVALID;
  }
}

std::string MainWindow::getIEEE754Representation(float value) {
  // Convert the float number to its IEEE 754 representation
  IEEEFloat ieeeF = IEEEConverter::floatToIEEE(value);

  // Return binary string
  return IEEEConverter::IEEEToBinary(ieeeF);
}

std::string MainWindow::getHexRepresentation(const std::string &binaryStr) {
  // Convert the float number to its IEEE 754 representation
  IEEEFloat ieeeF = IEEEConverter::binaryToIEEE(binaryStr);

  // Return hex string
  return IEEEConverter::IEEEToHex(ieeeF);
}

void MainWindow::showErrorMessage(const QString &title,
                                  const QString &message) {
  QMessageBox::critical(this, title, message, QMessageBox::Ok);
}

void MainWindow::on_calculateButton_clicked() {
  float op1, op2;

  // Get input values from line edits and convert them to float
  if (!getFloatFromLineEdit(ui->op1RealLineEdit, op1)) {
    showErrorMessage("Error", "Op1 holds an invalid value.");
    return;
  }

  if (!getFloatFromLineEdit(ui->op2RealLineEdit, op2)) {
    showErrorMessage("Error", "Op2 holds an invalid value.");
    return;
  }

  // Get IEEE 754 representation of op1 and op2. Update UI with those values
  std::string op1IeeeStr = getIEEE754Representation(op1);
  ui->op1IEEELineEdit->setText(QString::fromStdString(op1IeeeStr));

  std::string op2IeeeStr = getIEEE754Representation(op2);
  ui->op2IEEELineEdit->setText(QString::fromStdString(op2IeeeStr));

  // Get hexadecimal representation of op1 and op2. Update UI with those values
  std::string op1HexStr = getHexRepresentation(op1IeeeStr);
  ui->op1HexLineEdit->setText(QString::fromStdString(op1HexStr));

  std::string op2HexStr = getHexRepresentation(op2IeeeStr);
  ui->op2HexLineEdit->setText(QString::fromStdString(op2HexStr));

  // Get operation to perform
  Operation op = getOperationFromComboBox();
  if (op == Operation::INVALID) {
    showErrorMessage("Error", "Invalid operation selected.");
    return;
  }

  // Perform operation and store result
  IEEEFloat resultIeeeF, op1IeeeF, op2IeeeF;
  op1IeeeF = IEEEConverter::floatToIEEE(op1);
  op2IeeeF = IEEEConverter::floatToIEEE(op2);

  resultIeeeF = alu.operate(op1IeeeF, op2IeeeF, op);

  // Get result real number and update UI
  float result = resultIeeeF.number;
  // Check if result is NaN and update UI accordingly
  QString resultStr = result == std::numeric_limits<float>::quiet_NaN()
                          ? "nan"
                          : QString::number(result);
  ui->resultsRealLineEdit->setText(resultStr);

  // Get IEEE 754 representation of result. Update UI with those values
  std::string resultIeeeStr = getIEEE754Representation(result);
  ui->resultsIEEELineEdit->setText(QString::fromStdString(resultIeeeStr));

  // Get hexadecimal representation of result. Update UI with those values
  std::string resultHexStr = getHexRepresentation(resultIeeeStr);
  ui->resultsHexLineEdit->setText(QString::fromStdString(resultHexStr));
}

void MainWindow::on_resetButton_clicked() {
  // Clear input line edits
  ui->op1RealLineEdit->clear();
  ui->op2RealLineEdit->clear();

  // Clear results line edits
  ui->op1IEEELineEdit->clear();
  ui->op2IEEELineEdit->clear();
  ui->op1HexLineEdit->clear();
  ui->op2HexLineEdit->clear();
  ui->resultsRealLineEdit->clear();
  ui->resultsIEEELineEdit->clear();
  ui->resultsHexLineEdit->clear();

  // Reset operation combo box
  ui->operationComboBox->setCurrentIndex(0);
}
