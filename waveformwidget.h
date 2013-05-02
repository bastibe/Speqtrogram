#ifndef WAVEFORMWIDGET_H
#define WAVEFORMWIDGET_H

#include <QWidget>
#include <QUrl>

class WaveformWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WaveformWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent* event);
    void setSoundFile(QString filename);
signals:
    
public slots:

private:
    QPainterPath maxWave;
    QPainterPath minWave;
};

#endif // WAVEFORMWIDGET_H
