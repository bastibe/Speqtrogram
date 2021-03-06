#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "devicelist.h"
#include "hostapilist.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>
#include <QGraphicsPathItem>
#include "sndfile.hh"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->waveformView->setMinimumHeight(20);
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
    connect(ui->playButton, SIGNAL(clicked()), &player, SLOT(playPause()));
    connect(&player, SIGNAL(isPlaying(bool)), this, SLOT(changePlayButtonState(bool)));
    ui->rewindButton->setIcon(qApp->style()->standardIcon(QStyle::SP_MediaSeekBackward));
    connect(ui->rewindButton, SIGNAL(clicked()), &player, SLOT(rewind()));
    ui->fastForwardButton->setIcon(qApp->style()->standardIcon(QStyle::SP_MediaSeekForward));
    connect(ui->fastForwardButton, SIGNAL(clicked()), &player, SLOT(fastForward()));

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
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Sound File"),
                                                    QDir::currentPath(),
                                                    tr("Sound Files (*.wav *.flac *.aiff *.ogg)"));
    QDir::setCurrent(QFileInfo(fileName).absolutePath());
    player.openSoundFile(fileName.toStdString());
    ui->waveformView->setSoundFile(fileName);
}

void MainWindow::changePlayButtonState(bool isPlaying)
{
    ui->playButton->setIcon(isPlaying ? qApp->style()->standardIcon(QStyle::SP_MediaPause) :
                                        qApp->style()->standardIcon(QStyle::SP_MediaPlay));
}
