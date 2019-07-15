#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void gol();

private slots:
    void on_sliderRed_valueChanged(int value);

    void on_sliderGreen_valueChanged(int value);

    void on_sliderBlue_valueChanged(int value);

    void on_radioSimples_toggled(bool checked);

    void on_sliderEspessura_valueChanged(int value);

    void on_btnAtualizar_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
