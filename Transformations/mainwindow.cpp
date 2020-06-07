#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMouseEvent>
#include<QtDebug>
#include<cmath>
#include<QColorDialog>
static QImage img(500,500,QImage::Format_RGB888);
float a[20],b[20];
int ver;
bool start;
QRgb col=qRgb(255,255,255);
QColor colour;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ver=0;
    start=true;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::dda(float x1,float y1,float x2,float y2)
{

    float x,y,dx,dy,l,i=1;
    QRgb value;
    value=qRgb(0,255,0);

    l=std::abs(x2-x1)>std::abs(y2-y1)?std::abs(x2-x1):std::abs(y2-y1);
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


    ui->label_3->setPixmap(QPixmap::fromImage(img));

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
         //dda(a[0],b[0],a[ver],b[ver]);
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

void MainWindow::translate()
{
    QString s,s1;
    s=ui->lineEdit->text();
    s1=ui->lineEdit_2->text();
    float tx=s.toFloat();
    float ty=s1.toFloat();
    float m,n,v,d;
    for(int i=0;i<ver-1;i++)
    {
        m=a[i]+tx;
        n=b[i]+ty;
        v=a[i+1]+tx;
        d=b[i+1]+ty;
        dda(m,n,v,d);
    }

}
void MainWindow::scale()
{
    QString s2,s3;
    s2=ui->lineEdit_3->text();
    s3=ui->lineEdit_4->text();
    float sx=s2.toFloat();
    float sy=s3.toFloat();
    float m,n,v,d;
    for(int i=0;i<ver-1;i++)
    {
        m=a[i]*sx;
        n=b[i]*sy;
        v=a[i+1]*sx;
        d=b[i+1]*sy;
        dda(m,n,v,d);
    }

}
void MainWindow::rotate()
{
QString s2;
s2=ui->lineEdit_5->text();
float t=s2.toFloat();
float t1=t*3.142/180;
float a1[20],b1[20];
for(int i=0;i<ver;i++)
{
    a1[i]=((a[i]-250)*cos(t1))-((b[i]-250)*sin(t1));
    b1[i]=((a[i]-250)*sin(t1))+((b[i]-250)*cos(t1));
}
for(int i=0;i<ver-1;i++)
{
    dda(a1[i]+250,b1[i]+250,a1[i+1]+250,b1[i+1]+250);
}
}


//Translation
void MainWindow::on_pushButton_clicked()
{
translate();
}

//Scaling
void MainWindow::on_pushButton_2_clicked()
{
scale();
}

//Rotation
void MainWindow::on_pushButton_3_clicked()
{
rotate();
}
