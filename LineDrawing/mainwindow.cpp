#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtGui>
#include<cmath>

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

int sign(int x){
    if(x>0)
        return 1;
    else if(x<0)
        return -1;
    else
        return 0;
}

int Integer(int x){
    return (int)x;
}

QImage image(300, 300, QImage::Format_RGB888);

void MainWindow::on_ddaButton_clicked()
{
    QString sx1 = ui->x1->text();
    QString sy1 = ui->y1->text();
    QString sx2 = ui->x2->text();
    QString sy2 = ui->y2->text();

    float x1 = sx1.toFloat();
    float y1 = sy1.toFloat();
    float x2 = sx2.toFloat();
    float y2 = sy2.toFloat();

    dda_algo(x1, y1, x2, y2);

}

void MainWindow::on_bresButton_clicked()
{
    QString sx1 = ui->x1->text();
    QString sy1 = ui->y1->text();
    QString sx2 = ui->x2->text();
    QString sy2 = ui->y2->text();

    int x1 = sx1.toFloat();
    int y1 = sy1.toFloat();
    int x2 = sx2.toFloat();
    int y2 = sy2.toFloat();

    bres_algo(x1, y1, x2, y2);

}

void MainWindow::on_pushButton_clicked()
{
    ui->imageLabel->clear();
    ui->imageLabel->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->x1->clear();
    ui->y1->clear();
    ui->x2->clear();
    ui->y2->clear();
}

void MainWindow:: dda_algo(float x1, float y1, float x2, float y2)
{

    float len, dx, dy, x, y;

    if(abs(x2-x1) > abs(y2-y1)){
        len = abs(x2-x1);
    }else{
        len = abs(y2-y1);
    }

    dx= (x2-x1)/len;
    dy = (y2-y1)/len;

    x = x1 + 0.5*sign(dx);
    y = y1 + 0.5*sign(dy);

    int i=1;
    while(i<=len){
        image.setPixel(floor(x), floor(y), qRgb(255,255,255));
        x = x + dx;
        y = y + dy;
        i++;
    }

    ui->imageLabel->setPixmap(QPixmap::fromImage(image));
    ui->imageLabel->show();
}

void MainWindow::bres_algo(float x1, float y1, float x2, float y2)
{

    int x=x1;
    int y=y1;
    int dx = abs(x2-x1);
    int dy = abs(y2-y1);
    int s1 = sign(x2-x1);
    int s2 = sign(y2-y1);
    int inter;
    float m,e;

    if(dy>dx){
        int temp = dx;
        dx=dy;
        dy = temp;
        inter = 1;
    }else{
        inter = 0;
    }

    m=(float)dy/dx;
    e=m-0.5;

    for(int i=1; i<=dx; i++){
        image.setPixel(x, y, qRgb(255,255,255));
        while(e>0){
            if(inter == 1)
                x=x+s1;
            else
                y=y+s2;
            e=e-2*dx;
        }
        if(inter == 1)
            y=y+s2;
        else
            x=x+s1;
        e=e+2*dy;
    }
    ui->imageLabel->setPixmap(QPixmap::fromImage(image));
    ui->imageLabel->show();
}

void MainWindow::on_patternButton_clicked()
{
    QString sx1 = ui->x1->text();
    QString sy1 = ui->y1->text();
    QString sx2 = ui->length->text();
    QString sy2 = ui->height->text();

    float x1 = sx1.toFloat();
    float y1 = sy1.toFloat();
    float len = sx2.toFloat();
    float het = sy2.toFloat();

    float het1 = het/2;
    float len1 = len/2;

    bres_algo(x1, y1, x1+len, y1);
    bres_algo(x1+len, y1, x1+len, y1+het);
    bres_algo(x1, y1+het, x1+len, y1+het);
    bres_algo(x1, y1, x1, y1+het);

    dda_algo(x1, y1+het1, x1+len1, y1);
    dda_algo(x1+len1, y1, x1+len, y1+het1);
    dda_algo(x1+len, y1+het1, x1+len1, y1+het);
    dda_algo(x1+len1, y1+het, x1, y1+het1);

    bres_algo(x1+(len/4), y1+(het/4), x1+(3*len/4), y1+(het/4));
    bres_algo(x1+(3*len/4), y1+(het/4), x1+(3*len/4), y1+(3*het/4));
    bres_algo(x1+(3*len/4), y1+(3*het/4), x1+(len/4), y1+(3*het/4));
    bres_algo(x1+(len/4), y1+(3*het/4), x1+(len/4), y1+(het/4));
}
