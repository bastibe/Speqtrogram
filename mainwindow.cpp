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

    // Pre-select the default API
    ui->hostApiList->setCurrentIndex(Pa_GetDefaultHostApi());
    static_cast<DeviceList*>(ui->deviceList->model())->updateHostApi(Pa_GetDefaultHostApi());

    // Pre-select the default device for the given API
    const PaDeviceIndex first_device = Pa_HostApiDeviceIndexToDeviceIndex(Pa_GetDefaultHostApi(), 0);
    ui->deviceList->setCurrentIndex(Pa_GetDefaultOutputDevice()-first_device);

    connect(ui->hostApiList, SIGNAL(currentIndexChanged(int)),
            ui->deviceList->model(), SLOT(updateHostApi(int)) );
}

MainWindow::~MainWindow()
{
    delete ui;

    Pa_Terminate();
}
