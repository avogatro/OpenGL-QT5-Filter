#ifndef VIDEOFRAMESURFACE_H
#define VIDEOFRAMESURFACE_H

#include <thread>
#include <QMutex>

#include <QAbstractVideoSurface>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QVideoWidget>

#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>

#include <QBuffer>
#include <QOpenGLBuffer>
#include <QList>

//interface to grab images from a video source

class VideoFrameSurface : public QAbstractVideoSurface
{
//use mutex to solve reader writer problem
public:
    VideoFrameSurface(const QString& filename, QObject *parent = 0);
    ~VideoFrameSurface();
    bool present(const QVideoFrame& frame);
    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const;

    QImage getLastFrame();
signals:

public slots:

private:
    QMediaPlaylist *playlist;
    QMediaPlayer *mediaPlayer;

    QImage* lastFrame;
    QMutex frameWriteMutex;
    QMutex frameCheckMutex;
    int readcount = 0;
};

#endif // VIDEOFRAMESURFACE_H
