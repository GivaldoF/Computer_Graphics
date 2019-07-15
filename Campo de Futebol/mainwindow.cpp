#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sliderRed_valueChanged(int value)
{
    this->ui->GLwidget->r = value;
}

void MainWindow::on_sliderGreen_valueChanged(int value)
{
     this->ui->GLwidget->g = value;
}

void MainWindow::on_sliderBlue_valueChanged(int value)
{
     this->ui->GLwidget->b = value;
}

void MainWindow::on_radioSimples_toggled(bool checked)
{
    this->ui->GLwidget->modo = checked;
}

void MainWindow::on_sliderEspessura_valueChanged(int value)
{
    this->ui->GLwidget->t = value;
}

void MainWindow::on_btnAtualizar_clicked()
{
    int pt1 = this->ui->GLwidget->ponto1;
    int pt2 = this->ui->GLwidget->ponto2;

    this->ui->lblPonto1->setText(QString::number(pt1));
    this->ui->lblPonto2->setText(QString::number(pt2));
}
