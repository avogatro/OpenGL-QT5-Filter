#include "filterdemo.h"

FilterDemo::FilterDemo()

{


    QGridLayout *mainLayout = new QGridLayout;

    videoFrameSurface = new VideoFrameSurface(QString("D:/sintel_trailer-720p.ogv"));

    for (int i = 0; i < NumRows; ++i) {
        for (int j = 0; j < NumColumns; ++j) {
            QColor clearColor;
            clearColor.setRgb(0,0,0,255);
            int a = i*NumColumns+j;
            switch (a){
            case 0:
                glWidgets[i][j] = new GLWidget(videoFrameSurface);

                break;
            case 1:
                 glWidgets[i][j] = new GLWidget(videoFrameSurface);
                 glWidgets[i][j]->setVertexShader(":/assets/shader/1shaderv.glsl");
                 glWidgets[i][j]->setFragmentShader(":/assets/shader/1shaderf.glsl");
                break;
            case 2:
                 glWidgets[i][j] = new GLWidget(videoFrameSurface);
                 glWidgets[i][j]->setVertexShader(":/assets/shader/1shaderv.glsl");
                 glWidgets[i][j]->setFragmentShader(":/assets/shader/2shaderf.glsl");
                break;

            case 3:
                 glWidgets[i][j] = new GLWidget(videoFrameSurface);
                 glWidgets[i][j]->setVertexShader(":/assets/shader/1shaderv.glsl");
                 glWidgets[i][j]->setFragmentShader(":/assets/shader/3shaderf.glsl");
                break;
            case 4:
                 glWidgets[i][j] = new GLWidget(videoFrameSurface);
                 glWidgets[i][j]->setVertexShader(":/assets/shader/1shaderv.glsl");
                 glWidgets[i][j]->setFragmentShader(":/assets/shader/4shaderf.glsl");
                break;
            case 5:
                 glWidgets[i][j] = new GLWidget(videoFrameSurface);
                 glWidgets[i][j]->setVertexShader(":/assets/shader/5shaderv.glsl");
                 glWidgets[i][j]->setFragmentShader(":/assets/shader/5shaderf.glsl");
                break;
            case 6:
                 glWidgets[i][j] = new GLWidget(videoFrameSurface);
                 glWidgets[i][j]->setVertexShader(":/assets/shader/1shaderv.glsl");
                 glWidgets[i][j]->setFragmentShader(":/assets/shader/6shaderf.glsl");
                break;
            case 7:
                 glWidgets[i][j] = new GLWidget(videoFrameSurface);
                 glWidgets[i][j]->setVertexShader(":/assets/shader/1shaderv.glsl");
                 glWidgets[i][j]->setFragmentShader(":/assets/shader/7shaderf.glsl");
                break;
            case 8:
                 glWidgets[i][j] = new GLWidget(videoFrameSurface);
                 glWidgets[i][j]->setVertexShader(":/assets/shader/1shaderv.glsl");
                 glWidgets[i][j]->setFragmentShader(":/assets/shader/8shaderf.glsl");
                break;

            default:
                 glWidgets[i][j] = new GLWidget(videoFrameSurface);

            }


            glWidgets[i][j]->setClearColor(clearColor);
            //glWidgets[i][j]->rotateBy(+42 * 16, +42 * 16, -21 * 16);
            mainLayout->addWidget(glWidgets[i][j], i, j);

            connect(glWidgets[i][j], SIGNAL(clicked()),
                    this, SLOT(setCurrentGlWidget()));
        }
    }
    setLayout(mainLayout);
    this->resize(720,720);
    currentGlWidget = glWidgets[0][0];
    currentGlWidget->resize(720,720);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(20);


}

FilterDemo::~FilterDemo()
{


        delete videoFrameSurface;

    for (int i = 0; i < NumRows; ++i) {
        for (int j = 0; j < NumColumns; ++j) {
                delete glWidgets[i][j];
            }
        }
}

void FilterDemo::setCurrentGlWidget()
{
    currentGlWidget = qobject_cast<GLWidget *>(sender());
}

void FilterDemo::update()
{
    if (currentGlWidget)
    {
        for (int i = 0; i < NumRows; ++i) {
            for (int j = 0; j < NumColumns; ++j) {
                    glWidgets[i][j]->update();
                }
            }
    }

}
