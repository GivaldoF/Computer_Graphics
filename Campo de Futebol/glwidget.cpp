#include "glwidget.h"
#include <GL/glut.h>
#include <math.h>
#include "mainwindow.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    this->winWidth = 1200;
    this->winHeight = 500;
    this->t = 1;
    this->v = 10;
    this->posx = winWidth/2;
    this->posy = winHeight/2;
    this->ponto1 = 0;
    this->ponto2 = 0;
    this->r= 255, g = 255, b = 255;

    this->modo = 0;
}

QSize GLWidget::sizeHint() const
{
    return QSize(winWidth, winHeight);
}

void GLWidget::initializeGL(){
    glClearColor(0.1, 0.5, 0.1, 1);
    glViewport(0, 0, winWidth, winHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, 1.0, -1.0f);
    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::plotPoint(GLfloat x, GLfloat y, int a){
    glPointSize(a);
    glColor3f(r/255, g/255, b/255);
    glBegin(GL_POINTS);
        glVertex2f(x,y);
    glEnd();
}
void GLWidget::plotPoint(GLfloat x, GLfloat y){
    glPointSize(t);
    glBegin(GL_POINTS);
        glVertex2f(x,y);
    glEnd();
}

// Desenha uma reta usando a equação da reta, dando o ponto inicial e o ponto final e sua espessura e sua cor RGB
// y = y0 + m(x-x0)
// sempre x0 < x1 e qndo vertical y0 < y1
void GLWidget::line1(GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1){
    float c=1;

    if(x1 < x0) { // Inverte os pontos
        line1(x1, y1, x0, y0);
    }
    if(y1 < y0){
        y0 *= -1;
        y1 *= -1;
        c *= -1;
    }

    GLfloat x, y;
    GLfloat m = (y1 - y0)/(x1-x0);
    if(abs(y1-y0) <= abs(x1-x0)){
        for(x=x0; x<x1; x += 0.1f){
            y = y0 + m*(x - x0);
            plotPoint(x, y*c);
        }
    }else{
        for(y=y0; y<y1; y += 0.1f){
            x = (y - y0)/m + x0;
            plotPoint(x, y*c);
        }
    }
}

// Desenha uma reta usando o algoritimo do ponto-médio (Bresenham)
void GLWidget::line2(GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1){
    int dx = x1 - x0;
    int dy = y1 - y0;
    int inclinacao=0;
    if(dx<0) // caso ponto final < ponto inicial
    {
        line2(x1, y1, x0, y0);
        return;
    }
    if(dy<0)
        inclinacao = -1;
    else
        inclinacao = 1;

    int x, y, d;

    x = x0;
    y = y0;

    plotPoint(x,y);
    if(dx >= inclinacao*dy){    // m<=1
        if(dy<0){ // caso y2<y1
            d = 2*dy+dx;
            while(x<x1){
                if(d<0){ // escolhido é o I
                    d += 2*(dy+dx);
                    x++;
                    y--;
                }
                else{ // escolhido é o S
                    d+=2*dy;
                    x++; // varia apenas no eixo x
                }
                plotPoint(x,y);
            }
        }
        else{ // caso y1<y2
            d=2*dy-dx;
            while(x<x1){
                if(d<0){ // escolhido é o I
                    d+=2*dy;
                    x++; // varia apenas no eixo x
                }
                else{ // escolhido é o S
                    d+=2*(dy-dx);
                    x++;
                    y++;
                }
        plotPoint(x,y);
            }
        }
    }
    else{ // |m|>1
        if(dy<0){ // caso y2<y1
            d=dy+2*dx;
            while(y > y1){
                if(d<0){
                    d += 2*dx;
                    y--; // varia apenas no eixo y
                }
                else{
                    d+=2*(dy+dx);
                    x++;
                    y--;
                }
        plotPoint(x,y);
            }
        }
        else{ // caso y1<y2
            d=dy-2*dx;
            while(y<y1){
                if(d<0){
                    d+=2*(dy-dx);
                    x++;
                    y++;
                }
                else{
                    d+=-2*dx;
                    y++; // varia apenas no eixo y
                }
                plotPoint(x,y);
                }
            }
        }
    plotPoint(x,y);
}

void GLWidget::circlePoints(GLfloat xc, GLfloat yc, GLfloat x, GLfloat y, int m, int a){

    if(m == 0){
        plotPoint(xc + x, yc + y, a);
        plotPoint(xc - x, yc + y, a);
        plotPoint(xc + x, yc - y, a);
        plotPoint(xc - x, yc - y, a);
        plotPoint(xc + y, yc + x, a);
        plotPoint(xc - y, yc + x, a);
        plotPoint(xc + y, yc - x, a);
        plotPoint(xc - y, yc - x, a);
    }else if(m == 1){ // Direita
        plotPoint(xc - x, yc + y, a);
        plotPoint(xc - y, yc + x, a);
        plotPoint(xc - x, yc - y, a);
        plotPoint(xc - y, yc - x, a);
    }else if(m==2){ // esquerda
        plotPoint(xc + x, yc + y, a);
        plotPoint(xc + y, yc + x, a);
        plotPoint(xc + y, yc - x, a);
        plotPoint(xc + x, yc - y, a);
    }

}

void GLWidget::circ1(GLfloat x0, GLfloat y0, GLfloat r, GLfloat startAngle, GLfloat endAngle, int a){
    GLfloat x, y, o;
    for(o = startAngle; o <= endAngle; o += 0.01f){
        x = x0 + r*cos(o);
        y = y0 + r*sin(o);
        plotPoint(x,y, a);
    }
}

void GLWidget::circ2(float x0, float y0, float r, int m, int a){
    float x, y;
    float d;

    x = 0;
    y = r;
    d = 3 - 2*r;

    circlePoints(x0, y0,x, y,m, a);

    while(y>=x){
        x += 1;
        if(d<0){
            d = d + 2*x + 3;
        }else{
            d = d + 2*(x-y) + 5;
            y -= 1;
        }
        circlePoints(x0,y0,x,y,m, a);
    }
}

void GLWidget::drawBall(float x, float y, float modo){
    glColor3f(1, 1, 1);
    if(modo == 0){
        circ1(x, y, 10, 0, 2*M_PI, 3);
        circ1(x, y, 7, 0, 2*M_PI, 3);
        circ1(x, y, 4, 0, 2*M_PI, 3);
        circ1(x, y, 1, 0, 2*M_PI, 3);
    }else{
        circ2(x,y, 10, 0, 3);
        circ2(x,y, 7, 0, 3);
        circ2(x,y, 4, 0, 3);
        circ2(x,y, 1, 0, 3);
    }

    if(x < 40 and (y < 325 and y > 175)){
        ponto1++;
        posx = winWidth/2;
        posy = 250;
    }else if(x > 1160 and (y < 325 and y > 175)){
        ponto2++;
        posx = winWidth/2;
        posy = 250;
    }
}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);

    if(modo == 1){
        drawBall(posx, posy, 0);
        glColor3f(r/255, g/255, b/255);
        // Borda
        line1(40, 40, 1160, 40); // Linha de baixo
        line1(40,460, 1160, 460); // Linha de Cima
        line1(1160,40, 1160, 460); // Linha Direita
        line1(40,40, 40, 460); // Linha Esquerda

        // Meio
        line1(600, 40, 600, 460);

        // Grande area direita
        line1(960, 400, 1160, 400); // Linha de Cima
        line1(960, 100, 1160, 100); // Linha de Baixo
        line1(960, 100, 960, 400); // Linha da Esquerda

        // Grande area esquerda
        line1(40, 400, 240, 400); // Linha de Cima
        line1(40, 100, 240, 100); // Linha de Baixo
        line1(240, 100, 240, 400); // Linha da Esquerda


        // Pequena area direita
        line1(1080, 350, 1160, 350); // Linha de Cima
        line1(1080, 150, 1160, 150); // Linha de Baixo
        line1(1080, 150, 1080, 350); // Linha da Esquerda

        // Semi circulo da area direito
        circ1(990, 250, 70, M_PI/2 + 0.5f, 3*M_PI/2 - 0.5f, t);

        // Semi circulo da area esquerda
        circ1(205, 250, 70, -(M_PI)/2 + 0.5f, M_PI/2 - 0.5f, t);

        // Pequena area esquerda
        line1(40, 350, 120, 350); // Linha de Cima
        line1(40, 150, 120, 150); // Linha de Baixo
        line1(120, 150, 120, 350); // Linha da Esquerda

        // Gol da direita
        line1(1160, 325, winWidth, 325); // Linha de Cima
        line1(1160, 175, winWidth, 175); // Linha de Baixo
        line1(winWidth - (t/2), 175, winWidth - (t/2), 325); // Linha da Esquerda

        // Gol da esquerda
        line1(t/2, 325, 40, 325); // Linha de Cima
        line1(t/2, 175, 40, 175); // Linha de Baixo
        line1(t/2, 175, t/2, 325); // Linha da Esquerda

        // Meio de campo
        circ1(600, 250, 85, 0, 2*(M_PI), t);

        // Circulo pequeno do meio de campo
        circ1(600, 250, 3, 0, 2*(M_PI), 5);
    }else{
        drawBall(posx, posy, 1);
        glColor3f(r/255, g/255, b/255);
         // Borda
        line2(40,40, 1160, 40); // Linha de baixo
        line2(40,460, 1160, 460); // Linha de Cima
        line2(1160,40, 1160, 460); // Linha Direita
        line2(40,40, 40, 460); // Linha Esquerda

        // Meio
        line2(600, 40, 600, 460);

        // Grande area direita
        line2(960, 400, 1160, 400); // Linha de Cima
        line2(960, 100, 1160, 100); // Linha de Baixo
        line2(960, 100, 960, 400); // Linha da Esquerda

        // Grande area esquerda
        line2(40, 400, 240, 400); // Linha de Cima
        line2(40, 100, 240, 100); // Linha de Baixo
        line2(240, 100, 240, 400); // Linha da Esquerda


        // Pequena area direita
        line2(1080, 350, 1160, 350); // Linha de Cima
        line2(1080, 150, 1160, 150); // Linha de Baixo
        line2(1080, 150, 1080, 350); // Linha da Esquerda
         // Pequena area esquerda
        line2(40, 350, 120, 350); // Linha de Cima
        line2(40, 150, 120, 150); // Linha de Baixo
        line2(120, 150, 120, 350); // Linha da Esquerda

        // Gol da direita
        line2(1160, 325, winWidth, 325); // Linha de Cima
        line2(1160, 175, 1200, 175); // Linha de Baixo
        line2(winWidth - (t/2), 175, winWidth - (t/2), 325); // Linha da Esquerda

        // Gol da esquerda
        line2(t/2, 325, 40, 325); // Linha de Cima
        line2(t/2, 175, 40, 175); // Linha de Baixo
        line2(t/2, 175, t/2, 325); // Linha da Esquerda

        // Meio de campo
        circ2(winWidth/2, 250, 85, 0,t);

        // Circulo pequeno meio de campo
        circ2(600, 250, 3, 0, 5);

        // Semi circulo da area direita
        circ2(960, 250, 42, 1, t);

        // Semi circulo da area esquerda
        circ2(240, 250, 42, 2, t);
    }

    // Penaltis

        plotPoint(180, 250, 10); // Penalti esquerdo
        plotPoint(1020, 250, 10); // Penalti direito
}

#include <mainwindow.h>
void GLWidget::keyPressEvent(QKeyEvent *event){
    if(event->key() ==Qt::Key_D){
        posx += v;
    }
    if(event->key() ==Qt::Key_A){
        posx -= v;
    }
    if(event->key() ==Qt::Key_W){
        posy +=v ;
    }
    if(event->key() ==Qt::Key_S){
        posy -= v;
    }

    if(posx < 40 and (posy < 325 and posy > 175)){
            ponto1++;
            posx = winWidth/2;
            posy = 250;

    }else if(posx > 1160 and (posy < 325 and posy > 175)){
            ponto2++;
            posx = winWidth/2;
            posy = 250;
    }

    if(posx < 40 && !(posx < 40 and (posy < 325 and posy > 175))){
        posx = 40;
    }
    if(posx > 1160 && !(posx > 1160 and (posy < 325 and posy > 175))){
        posx = 1160;
    }
    if(posy < 40){
        posy = 40;
    }
    if(posy > 460){
        posy = 460;
    }

    updateGL();
}

void GLWidget::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glLoadIdentity(); // Atualiza os objetos da janela
    glOrtho(0.0, GLdouble (w), 0.0, GLdouble (h), -1.0, 1.0);

}
