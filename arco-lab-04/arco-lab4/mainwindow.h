#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "alu.h"
#include "commonenums.h"
#include "qlineedit.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief The MainWindow class represents the main window of the application.
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  /**
   * @brief Constructor for the MainWindow class.
   * @param parent Pointer to the parent QWidget, default is nullptr.
   */
  MainWindow(QWidget *parent = nullptr);

  /**
   * @brief Destructor for the MainWindow class.
   */
  ~MainWindow();

private slots:
  /**
   * @brief Slot for the "=" button clicked event.
   */
  void on_calculateButton_clicked();

  /**
   * @brief Slot for the "Reset" button clicked event.
   */
  void on_resetButton_clicked();

private:
  Ui::MainWindow *ui; ///< Pointer to the UI object for the main window.
  ALU alu; ///< Object representing the ALU for performing operations.

  /**
   * @brief Checks if a string represents a float number that is out of bounds.
   * @param valueStr The string to be checked.
   * @return Returns true if the string represents a float number that is out of
   * bounds, false otherwise.
   */
  bool isValidFloatOutOfBounds(std::string valueStr);

  /**
   * @brief Converts the text entered in a QLineEdit widget to a float.
   * @param lineEdit Pointer to the QLineEdit widget.
   * @param value Reference to a float variable where the converted value will
   * be stored.
   * @return Returns true if the conversion is successful, false otherwise.
   */
  bool getFloatFromLineEdit(QLineEdit *lineEdit, float &value);

  /**
   * @brief Retrieves the selected operation from the operation combo box.
   * @return Returns the selected operation as an instance of the Operation enum
   * class. If an invalid operation is selected, Operation::INVALID is returned.
   * @note The combo box should be populated with valid operation strings ("+",
   * "*", "/") for this function to work correctly.
   * @see Operation
   */
  Operation getOperationFromComboBox();

  /**
   * @brief Converts a float to its IEEE 754 binary representation.
   * @param value The float to be converted.
   * @return Returns a binary string representing the IEEE 754 binary
   * of the value.
   */
  std::string getIEEE754Representation(float value);

  /**
   * @brief Converts a string representing an IEEE 754 binary
   * to its hexadecimal representation.
   * @param binaryStr The string representing the IEEE 754 binary
   * to be converted.
   * @return Returns a hexadecimal string representing IEEE 754 binary.
   */
  std::string getHexRepresentation(const std::string &binaryStr);

  /**
   * @brief Shows an error message in a QMessageBox.
   * @param title The title of the error message.
   * @param message The error message to be displayed.
   */
  void showErrorMessage(const QString &title, const QString &message);
};
#endif // MAINWINDOW_H
