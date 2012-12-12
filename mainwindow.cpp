#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "devicelist.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushme->setText("Push me!");
    ui->comboBox->setModel(new DeviceList());
}

MainWindow::~MainWindow()
{
    delete ui;
}
