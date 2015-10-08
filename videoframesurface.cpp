#include "videoframesurface.h"

VideoFrameSurface::VideoFrameSurface(const QString& filename, QObject *parent)
{
    lastFrame = new QImage(1280, 720, QImage::Format_RGB32);
    lastFrame->fill(Qt::black);

    //play video in the background
    playlist = new QMediaPlaylist(this);
    playlist->setPlaybackMode(QMediaPlaylist::PlaybackMode::Loop);
    playlist->addMedia(QUrl::fromLocalFile(filename));

    mediaPlayer = new QMediaPlayer(this);
    mediaPlayer->setVideoOutput(this);
    mediaPlayer->setPlaylist(playlist);
    mediaPlayer->setVolume(0);
    mediaPlayer->setPosition(100000);
    mediaPlayer->play();
}

bool VideoFrameSurface::present(const QVideoFrame& frame)
{
    if(frame.isValid())
    {
        QVideoFrame videoFrame(frame);
        if(videoFrame.map(QAbstractVideoBuffer::ReadOnly))
        {
            frameWriteMutex.lock();
            if ((lastFrame->width() != videoFrame.width()) || (lastFrame->height() != videoFrame.height())){
                delete lastFrame;
                lastFrame->detach();
                const QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(videoFrame.pixelFormat());
                lastFrame =  new QImage(videoFrame.width(), videoFrame.height(), imageFormat);
            }
            memcpy(lastFrame->bits(), videoFrame.bits(),videoFrame.mappedBytes());
            frameWriteMutex.unlock();
        }
        videoFrame.unmap();
    }
    return true;
}
QList<QVideoFrame::PixelFormat> VideoFrameSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const
{
    // Return the formats you will support
    return QList<QVideoFrame::PixelFormat>()
            << QVideoFrame::Format_RGB32
            << QVideoFrame::Format_ARGB32
               ;
}

VideoFrameSurface::~VideoFrameSurface()
{
    delete mediaPlayer;
    delete playlist;

}

QImage VideoFrameSurface::getLastFrame(){
    frameCheckMutex.lock();
    readcount++;
    if (readcount == 1)
        frameWriteMutex.lock();
    frameCheckMutex.unlock();

    QImage res = *lastFrame;

    frameCheckMutex.lock();
    readcount--;
    if (readcount == 0)
        frameWriteMutex.unlock();
    frameCheckMutex.unlock();
    return res;
}

