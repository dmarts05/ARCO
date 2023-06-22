#ifndef IMAGEROTATORWINDOW_H
#define IMAGEROTATORWINDOW_H

#include <QDialog>

namespace Ui {
class ImageRotatorWindow;
}

class ImageRotatorWindow : public QDialog {
  Q_OBJECT

public:
  explicit ImageRotatorWindow(QWidget *parent = nullptr);
  ~ImageRotatorWindow();

private slots:
  void on_exitBtn_clicked();

  void on_selectInputFolderBtn_clicked();

  void on_selectOutputFolderBtn_clicked();

  void on_startBtn_clicked();

  void on_resetBtn_clicked();

private:
  Ui::ImageRotatorWindow *ui;
  QString inputFolderPath;
  QString outputFolderPath;
  QVector<QImage> images;

  void loadInputFolderImages();
  void saveImagesToOutputFolder();
};

#endif // IMAGEROTATORWINDOW_H
