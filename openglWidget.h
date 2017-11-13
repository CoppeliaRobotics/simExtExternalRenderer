#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include "openglBase.h"
#include <QGLWidget>

class COpenglWidget : public QGLWidget, public COpenglBase
{
    Q_OBJECT
public:
    explicit COpenglWidget(int associatedObjectHandle,QWidget *parent = 0);
    ~COpenglWidget();

    void initGL();
    void makeContextCurrent();
    void doneCurrentContext();

    void showAtGivenSizeAndPos(int resX,int resY,int posX,int posY);
    void getWindowResolution(int& resX,int& resY);

protected:
    void resizeEvent(QResizeEvent* rEvent);

    void paintGL();
    void paintEvent(QPaintEvent* event);
};
#endif // OPENGLWIDGET_H
