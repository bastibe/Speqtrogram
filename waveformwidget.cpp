#include "waveformwidget.h"
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include "sndfile.hh"
#include <QDebug>

WaveformWidget::WaveformWidget(QWidget *parent) :
    QWidget(parent)
{
}

void WaveformWidget::setSoundFile(QString filename)
{
    QPainterPath waveformMax(QPointF(0,0));
    QPainterPath waveformMin(QPointF(0,0));
    SndfileHandle soundFile(filename.toStdString());
    if (soundFile.error()) qDebug() << soundFile.strError();

    QDesktopWidget *desk = QApplication::desktop();
    int totalPixelCount = (desk->screenGeometry().width()*desk->screenCount());
    sf_count_t framesPerPixel = soundFile.frames()/totalPixelCount;
    Q_ASSERT(framesPerPixel >= 1);
    float samples[framesPerPixel*soundFile.channels()];
    sf_count_t totalFrames = 0;
    while (soundFile.readf(samples, framesPerPixel) != 0) {
        float maximum = 0;
        float minimum = 0;
        for (int f=0; f<framesPerPixel; f++) {
            for (int c=0; c<soundFile.channels(); c++) {
                maximum = samples[f*c+c] > maximum ? samples[f*c+c] : maximum;
                minimum = samples[f*c+c] < minimum ? samples[f*c+c] : minimum;
            }
        }
        waveformMax.lineTo(double(totalFrames)/(framesPerPixel*totalPixelCount), maximum);
        waveformMin.lineTo(double(totalFrames)/(framesPerPixel*totalPixelCount), minimum);
        totalFrames += framesPerPixel;
    }
    maxWave.swap(waveformMax);
    minWave.swap(waveformMin);
}

void WaveformWidget::paintEvent(QPaintEvent *event)
{
    (void)event;
    QPainter painter(this);
    painter.setBrush(Qt::white);
    painter.drawRect(QRect(QPoint(),this->size()));

    QColor lightBlue = QColor(Qt::blue);
    lightBlue.setAlphaF(0.5);
    painter.setBrush(QBrush(lightBlue));
    painter.setPen(QPen(QBrush(Qt::blue), 0));

    painter.scale(width(), height()/2);
    painter.translate(0,1);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawPath(maxWave);
    painter.drawPath(minWave);
}
