#include <portaudio.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "devicelist.h"
#include "hostapilist.h"
#include <QFileDialog>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Pa_Initialize();

    ui->setupUi(this);
    ui->hostApiList->setModel(new HostApiList());
    ui->deviceList->setModel(new DeviceList());

    connect(ui->hostApiList, SIGNAL(currentIndexChanged(int)),
            ui->deviceList->model(), SLOT(updateHostApi(int)) );
    connect(ui->hostApiList, SIGNAL(currentIndexChanged(int)),
            &player, SLOT(updateHostApi(int)));
    connect(ui->deviceList, SIGNAL(currentIndexChanged(int)),
            &player, SLOT(updateDevice(int)));

    // Pre-select the default API
    ui->hostApiList->setCurrentIndex(Pa_GetDefaultHostApi());
    static_cast<DeviceList*>(ui->deviceList->model())->updateHostApi(Pa_GetDefaultHostApi());

    // Pre-select the default device for the given API
    const PaDeviceIndex first_device = Pa_HostApiDeviceIndexToDeviceIndex(Pa_GetDefaultHostApi(), 0);
    ui->deviceList->setCurrentIndex(Pa_GetDefaultOutputDevice()-first_device);

    ui->playButton->setIcon(qApp->style()->standardIcon(QStyle::SP_MediaPlay));
    ui->rewindButton->setIcon(qApp->style()->standardIcon(QStyle::SP_MediaSeekBackward));
    ui->fastForwardButton->setIcon(qApp->style()->standardIcon(QStyle::SP_MediaSeekForward));

    QAction* openAction = new QAction(qApp->style()->standardIcon(QStyle::SP_DirOpenIcon), tr("&Open..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open a sound file"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    ui->mainToolBar->addAction(openAction);

    QDir::setCurrent(QDir::homePath());
}

MainWindow::~MainWindow()
{
    delete ui;

    Pa_Terminate();
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Sound File"),
                                                    QDir::currentPath(),
                                                    tr("Sound Files (*.wav *.flac *.aiff *.ogg)"));
    QDir::setCurrent(QFileInfo(fileName).absolutePath());
    player.openSoundFile(fileName.toStdString());
}
