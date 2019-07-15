#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QKeyEvent>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    QSize sizeHint() const;

    void plotPoint(float x, float y, int a);
    void plotPoint(float x, float y);
    void line1(float x0, float y0, float x1, float y1);
    void line2(float x0, float y0, float x1, float y1);
    void circlePoints(float xc, float yc, float x, float y, int m, int a);
    void circ1(float x0, float y0, float r, float startAngle, float endAngle, int a);
    void circ2(float x0, float y0, float r, int m, int a);
    void drawBall(float x, float y, float modo);

    float winWidth;
    float winHeight;
    float posx, posy, v;
    float t;
    float r, g, b;
    int ponto1, ponto2;
    bool modo;

protected:
    void keyPressEvent(QKeyEvent *event);

private:

};

#endif // GLWIDGET_H
