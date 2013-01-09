#include <portaudio.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "devicelist.h"
#include "hostapilist.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Pa_Initialize();

    ui->setupUi(this);
    ui->pushme->setText("Push me!");
    ui->hostApiList->setModel(new HostApiList());
    ui->deviceList->setModel(new DeviceList());

    connect(ui->hostApiList, SIGNAL(currentIndexChanged(int)),
            ui->deviceList->model(), SLOT(updateHostApi(int)) );
}

MainWindow::~MainWindow()
{
    delete ui;

    Pa_Terminate();
}
