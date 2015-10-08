#ifndef FILTERDEMO_H
#define FILTERDEMO_H

#include <QMainWindow>

#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QVideoWidget>


#include <QWidget>
#include <QGridLayout>
#include <QTimer>

#include "videoframesurface.h"

#include "glwidget.h"
class FilterDemo : public QWidget
{
    Q_OBJECT

public:
    explicit FilterDemo();

    ~FilterDemo();

private slots:
    void setCurrentGlWidget();
    void update();


private:


    enum { NumRows = 3, NumColumns = 3 };
    GLWidget *glWidgets[NumRows][NumColumns];
    GLWidget *currentGlWidget;
    VideoFrameSurface* videoFrameSurface;
};

#endif // FILTERDEMO_H
