#include "mainwindow.h"
#include "imagerotatorwindow.h"
#include "radixsortwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_showRadixSortBtn_clicked() {
  RadixSortWindow radixSortWindow;
  radixSortWindow.setModal(true);
  radixSortWindow.exec();
}

void MainWindow::on_showImageRotatorBtn_clicked() {
  ImageRotatorWindow imageRotatorWindow;
  imageRotatorWindow.setModal(true);
  imageRotatorWindow.exec();
}
