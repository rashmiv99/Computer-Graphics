#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
#include<QMouseEvent>
#include<QtDebug>
#include<cmath>

using namespace std;

QRgb col=qRgb(255,0,0);

static QImage img(400,400,QImage::Format_RGB888);

int ver,a[10],b[10];
bool start;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     ver=0;
   start=true;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dda(float x1,float y1,float x2,float y2)
{
    float x,y,dx,dy,l,i=1;
    QRgb value;
    value=qRgb(255,255,255);

    l=std::abs((int)(x2-x1))>std::abs((int)(y2-y1))?std::abs((int)(x2-x1)):std::abs((int)(y2-y1));
    dx=(x2-x1)/l;
    dy=(y2-y1)/l;

    x=x1+0.5f;
    y=y1+0.5f;
    do
    {
       img.setPixel(static_cast<int>(x),static_cast<int>(y),value);
       x = x + dx;
       y = y + dy;
       i++;
      }while(i <= l);

    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    if(start==true)
    {
        int p=ev->pos().x();
        int q=ev->pos().y();
        a[ver]=p;
        b[ver]=q;
        if(ev->button()==Qt::RightButton)
        {
            a[ver]=a[0];
            b[ver]=b[0];
            cout<<endl<<a[0]<<" "<<b[0]<<endl;
            dda(a[0],b[0],a[ver-1],b[ver-1]);
            start=false;
        }
        else {
            if(ver>0)
            {
                    dda(a[ver],b[ver],a[ver-1],b[ver-1]);
            }
        }
        ver++;
    }
}

void MainWindow :: clearImage()
{
    for(int i=0; i<400; i++)
    {
        for(int j=0; j<400; j++)
        {
            img.setPixel(i,j,qRgb(0,0,0));
        }
    }
}

void MainWindow :: Rotation()
{
    int newA[10], newB[10];

    float angle = ui->theta->text().toFloat();
    int x = ui->x->text().toInt();
    int y = ui->y->text().toInt();

    angle = (angle*3.142*-1)/180;

    float cosVal = cos(angle);
    float sinVal = sin(angle);

    for(int i=0; i<ver; i++)
    {
        newA[i] = (a[i]-(200+x))*cosVal - (b[i]-(200-y))*sinVal;
        newB[i] = (a[i]-(200+x))*sinVal + (b[i]-(200-y))*cosVal;
    }

    for(int i=0; i<ver; i++)
    {
        a[i]=newA[i]+(200+x);
        b[i]=newB[i]+(200-y);
    }

    for(int i=0; i<ver-1; i++)
        dda(a[i],b[i],a[i+1],b[i+1]);

}

void MainWindow::on_rotate_arbitrary_clicked()
{
    clearImage();

    Rotation();
}

void MainWindow::on_rotate_x_axis_clicked()
{
    clearImage();

    for(int i=0; i<ver; i++)
    {
        if(b[i]<200)
        {
            b[i] = 200+abs(200-b[i]);
        }
        else
        {
            b[i] = 200-abs(200-b[i]);
        }
    }

    for(int i=0; i<ver-1; i++)
        dda(a[i],b[i],a[i+1],b[i+1]);
}

void MainWindow::on_rotate_y_axis_clicked()
{
    clearImage();

    for(int i=0; i<ver; i++)
    {
        if(a[i]<200)
        {
            a[i] = 200+abs(200-a[i]);
        }
        else{
            a[i] = 200-abs(200-a[i]);
        }
    }

    for(int i=0; i<ver-1; i++)
        dda(a[i],b[i],a[i+1],b[i+1]);
}

void MainWindow::on_rotate_xy_axis_clicked()
{
    clearImage();

    int newA[10], newB[10];
    for(int i=0; i<ver; i++)
    {
        newA[i] = 200+(200-b[i]);
        newB[i] = 200+(200-a[i]);
        a[i]=newA[i];
        b[i]=newB[i];
    }

    for(int i=0; i<ver-1; i++)
        dda(a[i],b[i],a[i+1],b[i+1]);
}
