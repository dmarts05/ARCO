#ifndef RADIXSORTWINDOW_H
#define RADIXSORTWINDOW_H

#include <QDialog>
#include <vector>

namespace Ui {
class RadixSortWindow;
}

class RadixSortWindow : public QDialog {
  Q_OBJECT

public:
  explicit RadixSortWindow(QWidget *parent = nullptr);
  ~RadixSortWindow();

private slots:
  void on_exitBtn_clicked();

  void on_selectInputFileBtn_clicked();

  void on_startBtn_clicked();

  void on_selectOutputFileBtn_clicked();

  void on_resetBtn_clicked();

private:
  Ui::RadixSortWindow *ui;
  std::vector<int> numbers;
  QString inputFilePath;
  QString outputFilePath;

  void loadInputFileNumbers();
  void saveNumbersToOutputFile();
};

#endif // RADIXSORTWINDOW_H
