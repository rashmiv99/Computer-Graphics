#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include<QMouseEvent>
using namespace std;

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

const int INSIDE = 0; // 0000
const int LEFT = 1; // 0001
const int RIGHT = 2; // 0010
const int BOTTOM = 8; // 1000
const int TOP = 4; // 0010

int x_max, y_max, x_min, y_min;

int MainWindow:: computeCode(double x, double y)
{
    int code = INSIDE;

    if (x < x_min)	 // to the left of rectangle
        code |= LEFT;
    else if (x > x_max) // to the right of rectangle
        code |= RIGHT;
    if (y < y_min)	 // below the rectangle
        code |= BOTTOM;
    else if (y > y_max) // above the rectangle
        code |= TOP;

    return code;
}

void MainWindow:: cohenSutherlandClip(double x1, double y1, double x2, double y2)
{
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    bool accept = false;

    while (true)
    {
        if ((code1 == 0) && (code2 == 0))
        {
            accept = true;
            break;
        }
        else if (code1 & code2)
        {
            break;
        }
        else
        {
            int code_out;
            double x, y;

            if (code1 != 0)
                code_out = code1;
            else
                code_out = code2;

            if (code_out & TOP)
            {
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
            }
            else if (code_out & BOTTOM)
            {
                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
            }
            else if (code_out & RIGHT)
            {
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
            }
            else if (code_out & LEFT)
            {
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
            }

            if (code_out == code1)
            {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            }
            else
            {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }
    if (accept)
    {
        dda(x1, y1, x2, y2);
    }
}

void MainWindow::on_pushButton_clicked()
{
    clearImage();

    x_min = 200+(ui->x1->text().toInt());
    y_max = 200-(ui->y1->text().toInt());
    x_max = 200+(ui->x2->text().toInt());
    y_min = 200-(ui->y2->text().toInt());

    dda(x_min, y_min, x_max, y_min);
    dda(x_max, y_min, x_max, y_max);
    dda(x_min, y_max, x_max, y_max);
    dda(x_min, y_max, x_min, y_min);

    for(int i=0; i<ver-1; i++)
    {
        cohenSutherlandClip(a[i], b[i], a[i+1], b[i+1]);
    }
}

void MainWindow::dda(float x1,float y1,float x2,float y2)
{
    float x,y,dx,dy,l,i=1;
    QRgb value=qRgb(255,255,255);

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
