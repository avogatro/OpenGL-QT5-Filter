/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "glwidget.h"


GLWidget::GLWidget (VideoFrameSurface* frameSource,QWidget *parent)
    : QOpenGLWidget(parent),
      clearColor(Qt::black),
      xRot(0),
      yRot(0),
      zRot(0),
      program(0)
{
    memset(textures, 0, sizeof(textures));

    videoFrameSurface = frameSource;

}

GLWidget::~GLWidget()
{
    makeCurrent();
    vbo.destroy();
    for (int i = 0; i < 6; ++i)
        delete textures[i];
    delete program;
    delete texture2;

    doneCurrent();

}


void GLWidget::rotateBy(int xAngle, int yAngle, int zAngle)
{
    xRot += xAngle;
    yRot += yAngle;
    zRot += zAngle;
    update();
}

void GLWidget::setClearColor(const QColor &color)
{
    clearColor = color;
    update();
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    makeObject();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D) ;
#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1



        program = new QOpenGLShaderProgram;
        program->addShaderFromSourceFile(QOpenGLShader::Vertex, vertexShaderFilename);


        // Compile fragment shade
        program->addShaderFromSourceFile(QOpenGLShader::Fragment, fragementShaderFilename);


        program->bindAttributeLocation("vertex", PROGRAM_VERTEX_ATTRIBUTE);
        program->bindAttributeLocation("texCoord", PROGRAM_TEXCOORD_ATTRIBUTE);
        program->bindAttributeLocation("texCoord1", PROGRAM_TEXCOORD_ATTRIBUTE);
        program->link();

        program->bind();

        program->setUniformValue("texture", 0);



//        const float ambientLight[] = { 0.2, 0.2, 0.2, 1.0 };
//        const float specularLight[] = { 1.0, 1.0, 1.0, 1.0 };
//        const float specularity[] = { 1.0, 1.0, 1.0, 1.0 };
//        const float shininess[] = { 60.0 };
//        QVector4D lightPosition = { 0.0, 50.0, 50.0, 1.0 };

//        program->setUniformValue("lightSource",lightPosition);

}

void GLWidget::paintGL() {
    glClearColor(clearColor.redF(), clearColor.greenF(), clearColor.blueF(), clearColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 matrix;


    const auto aratio = float( this->width() ) / float( this->height() );
    matrix.setToIdentity();
    matrix.ortho( -aratio, aratio, +1.0f, -1.0f, 4.0f, 15.0f);

    matrix.translate(0.0f, 0.0f, -10.0f);
    matrix.rotate(xRot / 16.0f, 1.0f, 0.0f, 0.0f);
    matrix.rotate(yRot / 16.0f, 0.0f, 1.0f, 0.0f);
    matrix.rotate(zRot / 16.0f, 0.0f, 0.0f, 1.0f);

    program->setUniformValue("matrix", matrix);
    program->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
    program->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
    program->setAttributeBuffer(PROGRAM_VERTEX_ATTRIBUTE, GL_FLOAT, 0, 3, 5 * sizeof(GLfloat));
    program->setAttributeBuffer(PROGRAM_TEXCOORD_ATTRIBUTE, GL_FLOAT, 3 * sizeof(GLfloat), 2, 5 * sizeof(GLfloat));



    program->setUniformValue("lightPos", QVector3D(-1.0,0.0,-1.0));
    program->setUniformValue("mambient", QVector3D(0.2,0.2,0.0));
    program->setUniformValue("mdiffuse", QVector3D(0.3,0.3,0.3));
    program->setUniformValue("mspecular", QVector3D(0.2,0.2,0.2));
    program->setUniformValue("lambient", QVector3D(0.2,0.2,0.2));
    program->setUniformValue("ldiffuse", QVector3D(0.6,0.6,0.6));
    program->setUniformValue("lspecular", QVector3D(0.6,0.6,0.6));
    program->setUniformValue("shininess", 0.1f);


    QTime current = QTime::currentTime();
    uint msecs =current.msecsSinceStartOfDay();

    program->setUniformValue("time", float(msecs/1000.0f));
    program->setUniformValue("resolution", QVector2D(textures[0]->width(),textures[0]->height()));
    //texture
    QImage image = this->videoFrameSurface->getLastFrame();
    if (image.width() != textures[0]->width() || image.height() != textures[0]->height())
        makeObject();

    //actually faster then setdata, because of warning ouput
    textures[0]->destroy();
    textures[0]->create();
    textures[0]->setData(image);
   // textures[0] = new QOpenGLTexture(image);


    //textures[0]->bind(t1);






    glActiveTexture(GL_TEXTURE1 );

    glBindTexture(GL_TEXTURE_2D, texture2->textureId());

    program->setUniformValue("texture1", 1);

    glActiveTexture(GL_TEXTURE0 );

    //glUniform1i(t1, 0);

    for (int i = 0; i < 6; ++i) {
        textures[i]->bind();
        glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
    }


}

void GLWidget::resizeGL(int width, int height)
{
    if (height == 0) {
        height = 1;
    }

    QMatrix4x4 pMatrix;
    pMatrix.setToIdentity();
    pMatrix.perspective(60.0f, (float) width / (float) height, 0.001f, 1000);
    glViewport(0, 0, width, height);
    makeObject();

}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        rotateBy(8 * dy, 8 * dx, 0);
    } else if (event->buttons() & Qt::RightButton) {
        rotateBy(8 * dy, 0, 8 * dx);
    }
    lastPos = event->pos();
}

void GLWidget::mouseReleaseEvent(QMouseEvent * /* event */)
{
    emit clicked();
}

void GLWidget::makeObject()
{
    static const int coords[6][4][3] = {
        { { +1, -1, -1 }, { -1, -1, -1 }, { -1, +1, -1 }, { +1, +1, -1 } },
        { { +1, +1, -1 }, { -1, +1, -1 }, { -1, +1, +1 }, { +1, +1, +1 } },
        { { +1, -1, +1 }, { +1, -1, -1 }, { +1, +1, -1 }, { +1, +1, +1 } },
        { { -1, -1, -1 }, { -1, -1, +1 }, { -1, +1, +1 }, { -1, +1, -1 } },
        { { +1, -1, +1 }, { -1, -1, +1 }, { -1, -1, -1 }, { +1, -1, -1 } },
        { { -1, -1, +1 }, { +1, -1, +1 }, { +1, +1, +1 }, { -1, +1, +1 } }
    };

    for (int j = 0; j < 6; ++j)
        textures[j] = new QOpenGLTexture(QImage(QString(":/assets/images/side%1.png").arg(j + 1)).mirrored());

    //delete textures[0];

    QImage image = videoFrameSurface->getLastFrame();
    texture2 =new  QOpenGLTexture(QImage(QString(":/assets/images/texture2.jpg")).mirrored());

    QVector<GLfloat> vertData;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 4; ++j) {
            // vertex position
             float w = float(image.width())/1000.0f;
             float h = float(image.height())/1000.0f;
            vertData.append(w * coords[i][j][0]);
            vertData.append(h * coords[i][j][1]);
            vertData.append(h * coords[i][j][2]);
            // texture coordinate
            vertData.append(j == 0 || j == 3);
            vertData.append(j == 0 || j == 1);
        }
    }



    vbo.create();
    vbo.bind();
    vbo.allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));
}
void GLWidget::setVertexShader(QString filename)
{
   this->vertexShaderFilename = filename;
}

void GLWidget::setFragmentShader(QString filename)
{
  this ->fragementShaderFilename = filename;
}
