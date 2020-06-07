#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
#include<cmath>

using namespace std;

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

QImage image(400, 400, QImage::Format_RGB888);
QRgb col=qRgb(254,254,254);
QRgb old=qRgb(0,0,0);

void MainWindow :: clearImage()
{
    for(int i=0; i<400; i++)
    {
        for(int j=0; j<400; j++)
        {
            image.setPixel(i,j,qRgb(0,0,0));
        }
    }
}

int sign(int x){
    if(x>0)
        return 1;
    else if(x<0)
        return -1;
    else
        return 0;
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
}

void MainWindow::seedfill(int x,int y,QRgb old,QRgb col)
{
    QRgb curr=image.pixel(x,y);
    if(curr==old)
    {
        image.setPixel(x,y,col);
        seedfill(x,y+1,old,col);
        seedfill(x-1,y,old,col);
        seedfill(x,y-1,old,col);
        seedfill(x+1,y,old,col);
    }
}

void MainWindow::drawBoard()
{
    for(int i=0; i<10; i++)
    {
        bres_algo(x1[i], y1[i], x2[i], y2[i]);
    }

    for(int i=0; i<8; i++)
    {
        seedfill(fx[i], fy[i], old, col);
    }

    ui->imageLabel->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::rotateBoard()
{
    int nx1[10], ny1[10], nx2[10], ny2[10], nfx[8], nfy[8];

   // rotating the border lines
    for(int i=0; i<10; i++)
    {
        nx1[i] = (((x1[i]-200)-(y1[i]-200))/sqrt(2));
        nx1[i] = nx1[i]+200;
        ny1[i] = (((x1[i]-200)+(y1[i]-200))/sqrt(2));
        ny1[i] = ny1[i]+200;
        nx2[i] = (((x2[i]-200)-(y2[i]-200))/sqrt(2));
        nx2[i] = nx2[i]+200;
        ny2[i] = (((x2[i]-200)+(y2[i]-200))/sqrt(2));
        ny2[i] = ny2[i]+200;
    }

    // rotating the seeds
    for(int i=0; i<8; i++)
    {
        nfx[i] = ((fx[i]-200)-(fy[i]-200))/sqrt(2);
        nfx[i] = nfx[i]+200;
        nfy[i] = ((fx[i]-200)+(fy[i]-200))/sqrt(2);
        nfy[i] = nfy[i]+200;
    }

    // draw the rotated chess board
    for(int i=0; i<10; i++)
    {
        image.setPixel(nx1[i], ny1[i], qRgb(255,255,255));
        image.setPixel(nx2[i], ny2[i], qRgb(255,255,255));
        bres_algo(nx1[i], ny1[i], nx2[i], ny2[i]);
    }
    for(int i=0; i<8; i++)
    {
        seedfill(nfx[i], nfy[i], old, col);
    }

     ui->imageLabel->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_drawButton_clicked()
{
    clearImage();

    drawBoard();
}

void MainWindow::on_rotateButton_clicked()
{
    clearImage();

    rotateBoard();
}
