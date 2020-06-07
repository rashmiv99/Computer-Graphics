#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QRgb value=qRgb(0,255,0);
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void DDA(float,float,float,float,QImage&);
    //void Bresenham_circle(int,int,int,QImage&);
    void on_pushButton_clicked();
    int sign(float);
    void DDA_circle(int,int,int,int,QImage&);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
