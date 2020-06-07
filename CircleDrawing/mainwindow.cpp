#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>

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


void MainWindow::on_pushButton_clicked()
{
    QImage image(400,400, QImage::Format_RGB888);

    QString s;
    s=ui->lineEdit->text();

    float side=s.toFloat();
    //side=200;
    float p=(side/2)*1.732;


    float x1,y1,x2,y2,x3,y3;
    float r1,r2;

    x1=200;
    y1=100;

    x2=200+(side/2);
    y2=100+p;

    x3=200-(side/2);
    y3=100+p;

    r1=(p/3);
    r2=(2*p)/3;


    DDA(x1,y1,x2,y2,image);
    DDA(x2,y2,x3,y3,image);
    DDA(x1,y1,x3,y3,image);

    DDA_circle(0,0,r1,r2,image);
    DDA_circle(0,0,r2,r2,image);

    //ui->label_2->setFixedSize(400,400);
    ui->label_2->setPixmap(QPixmap::fromImage(image));
    ui->label_2->show();
}

int MainWindow::sign(float x)
{
    if(x>0)
        return 1;
    else if(x<0)
        return -1;
    else
        return 0;
}



void MainWindow::DDA(float x1,float y1,float x2,float y2,QImage &image)
{



    float length;

    float dx,dy;

    if(abs(x2-x1)>abs(y2-y1))
        length=abs(x2-x1);
    else
        length=abs(y2-y1);

    dx=(x2-x1)/length;
    dy=(y2-y1)/length;

    float x,y;
    x=x1+0.5*sign(dx);
    y=y1+0.5*sign(dy);






    for(int i=1;i<=length;i++)
    {
        image.setPixel(floor(x),floor(y),value);
        x=x+dx;
        y=y+dy;
    }
}

void MainWindow::DDA_circle(int x,int y, int radius,int r2, QImage &image)
{
    y=y+radius;
    int d,d_1;
    int delta=2*(1-radius);
    int limit=0;

    image.setPixel(200+x,100+y+r2,value);

    while(y>limit)
    {
        if(delta<0)
        {
            d=(2*delta) + (2*y) -1;

            if(d<=0)
            {
                x=x+1;
                delta=delta+(2*x)+1;
            }
            else
            {
                x=x+1;
                y=y-1;
                delta=delta+(2*x)-2*y+2;
            }
        }
        else if(delta>0)
        {
            d_1=2*delta-2*x-1;

            if(d_1<=0)
            {
                x=x+1;
                y=y-1;
                delta=delta+2*x-2*y+2;
            }
            else
            {
                y=y-1;
                delta=delta-2*y+1;
            }
        }
        else
        {
            x=x+1;
            y=y-1;
            delta=delta+2*x-2*y+2;
        }
        image.setPixel(200+x,100+y+r2,value);
        image.setPixel(200+x,100-y+r2,value);
        image.setPixel(200-x,100-y+r2,value);
        image.setPixel(200-x,100+y+r2,value);
    }
}


