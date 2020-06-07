#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMouseEvent>
#include<QtDebug>
#include<cmath>
#include<QColorDialog>
static QImage img(400,400,QImage::Format_RGB888);
int ver,a[20],b[20];
bool start;
QRgb col=qRgb(255,255,255);
QColor colour;
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
         dda(a[0],b[0],a[ver],b[ver]);
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


void MainWindow::mouseDoubleClickEvent(QMouseEvent *ev)
{
    int p=ev->pos().x();
     int q=ev->pos().y();
     QRgb old=qRgb(0,0,0);
     seedfill(p,q,old,col);
     ui->label->setPixmap(QPixmap::fromImage(img));
}
void MainWindow::seedfill(int x,int y,QRgb old,QRgb col)
{
    QRgb curr=img.pixel(x,y);
    if(curr==old)
    {
        img.setPixel(x,y,col);
        seedfill(x,y+1,old,col);
        seedfill(x-1,y,old,col);
        seedfill(x,y-1,old,col);
        seedfill(x+1,y,old,col);
    }
}
//void MainWindow:: QPushButton { background-color: red; border: none; }
void MainWindow::on_pushButton_clicked()
{

   col=qRgb(255,0,0);
}

void MainWindow::on_pushButton_2_clicked()
{
    col=qRgb(0,255,0);
}

void MainWindow::on_pushButton_3_clicked()
{
    col=qRgb(0,0,255);
}


QColor MainWindow::getCol()
{
    colour = QColorDialog::getColor();
    return colour;
}

void MainWindow::on_pushButton_7_clicked() //colour
{

    QColor col1 = getCol();
    col = col1.rgb();
}

void MainWindow::on_pushButton_4_clicked()
{
    col=qRgb(255,255,0);
}

void MainWindow::on_pushButton_5_clicked()
{
    col=qRgb(255,170,255);
}

void MainWindow::on_pushButton_6_clicked()
{
    col=qRgb(138,138,138);
}
