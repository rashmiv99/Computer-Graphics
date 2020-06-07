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

void MainWindow:: dda_solid(float x1, float y1, float x2, float y2)
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
    for(i=0;i<=len;i++){

        image.setPixel(floor(x), floor(y), qRgb(255,255,255));

        x = x + dx;
        y = y + dy;

    }

    ui->label_5->setPixmap(QPixmap::fromImage(image));
    ui->label_5->show();
}

void MainWindow:: dda_thick(float x1, float y1, float x2, float y2)
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
    for(i=0;i<=len;i++){

        image.setPixel(floor(x), floor(y), qRgb(255,255,255));

        x = x + dx;
        y = y + dy;


    }

    ui->label_5->setPixmap(QPixmap::fromImage(image));
    ui->label_5->show();
}

void MainWindow:: dda_dot(float x1, float y1, float x2, float y2)
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
    for(i=0;i<=len;i++){
        if(i%2==0)
        {
        image.setPixel(floor(x), floor(y), qRgb(255,255,255));
        }
        x = x + dx;
        y = y + dy;

    }

    ui->label_5->setPixmap(QPixmap::fromImage(image));
    ui->label_5->show();
}

void MainWindow:: dda_dash(float x1, float y1, float x2, float y2)
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
    for(i=0;i<=len;i++){
        if(i%6==0)
        {
        image.setPixel(floor(x), floor(y), qRgb(0,0,0));
        }
        else
        {
        image.setPixel(floor(x), floor(y), qRgb(255,255,255));
        }
        x = x + dx;
        y = y + dy;

    }

    ui->label_5->setPixmap(QPixmap::fromImage(image));
    ui->label_5->show();
}

void MainWindow:: dda_dashdot(float x1, float y1, float x2, float y2)
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
   // int temp=0;

   int max=10,gap=15,cnt=0,flag=1;
    for(int i=1;i<=len;i++){
        if(cnt<max){
            image.setPixel(floor(x), floor(y), qRgb(255,255,255));
            cnt++;
        }else
            if(cnt<gap){
                cnt++;
            }else
                if(flag){
                    image.setPixel(floor(x), floor(y), qRgb(255,255,255));
                    cnt=max;
                    flag=0;
                }else
                {
                    flag=1;
                    cnt=0;
                }
        x = x + dx;
        y = y + dy;



   /* if(!(temp==5||temp==6)&&!(temp==8||temp==9))
         image.setPixel(floor(x), floor(y), qRgb(255,255,255));
    x = x + dx;
    y = y + dy;
    temp++;
    if(temp==10)
    {
        temp=0;
    }*/

    }

    ui->label_5->setPixmap(QPixmap::fromImage(image));
    ui->label_5->show();
}

//dotted
void MainWindow::on_pushButton_clicked()
{
    QString sx1 = ui->x1->text();
    QString sy1 = ui->y1->text();
    QString sx2 = ui->x2->text();
    QString sy2 = ui->y2->text();

    float x1 = sx1.toFloat();
    float y1 = sy1.toFloat();
    float x2 = sx2.toFloat();
    float y2 = sy2.toFloat();

    dda_dot(x1, y1, x2, y2);

}
//solid
void MainWindow::on_pushButton_5_clicked()
{
    QString sx1 = ui->x1->text();
    QString sy1 = ui->y1->text();
    QString sx2 = ui->x2->text();
    QString sy2 = ui->y2->text();

    float x1 = sx1.toFloat();
    float y1 = sy1.toFloat();
    float x2 = sx2.toFloat();
    float y2 = sy2.toFloat();

    dda_solid(x1, y1, x2, y2);

}
//dash

void MainWindow::on_pushButton_2_clicked()
{
    QString sx1 = ui->x1->text();
    QString sy1 = ui->y1->text();
    QString sx2 = ui->x2->text();
    QString sy2 = ui->y2->text();

    float x1 = sx1.toFloat();
    float y1 = sy1.toFloat();
    float x2 = sx2.toFloat();
    float y2 = sy2.toFloat();

    dda_dash(x1, y1, x2, y2);

}
//dashdot



void MainWindow::on_pushButton_3_clicked()
{
    QString sx1 = ui->x1->text();
    QString sy1 = ui->y1->text();
    QString sx2 = ui->x2->text();
    QString sy2 = ui->y2->text();

    float x1 = sx1.toFloat();
    float y1 = sy1.toFloat();
    float x2 = sx2.toFloat();
    float y2 = sy2.toFloat();

    dda_dashdot(x1, y1, x2, y2);
}
//thick
void MainWindow::on_pushButton_4_clicked()
{
    QString sx1 = ui->x1->text();
    QString sy1 = ui->y1->text();
    QString sx2 = ui->x2->text();
    QString sy2 = ui->y2->text();
     QString swidth = ui->y2->text();

    float x1 = sx1.toFloat();
    float y1 = sy1.toFloat();
    float x2 = sx2.toFloat();
    float y2 = sy2.toFloat();
    float width = swidth.toFloat();

    float l,yinc,xinc,dx,dy,x,y;
        //int w3;

        QRgb value;
        float w1 = ((width-1)/2);
        float w2 = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
        float w3 = abs(x2-x1);
        float w4= abs(y2-y1);

        if(x1==x2)
        {
            int wy = (w1*w2)/w4;
            for(int i = wy ;i>-wy;i--){
            dda_thick(x1+i,y1,x2+i,y2);
            dda_thick(x1-i,y1,x2-i,y2);
            }
        }
        else{
        int wy = (w1*w2)/w3;

        for(int i = wy ;i>-wy;i--){
        dda_thick(x1,y1+i,x2,y2+i);
        dda_thick(x1,y1-i,x2,y2-i);

        }
        }


       /* dx=x2-x1;
        dy=y2-y1;

        if(abs(dx)>=abs(dy))
              l=abs(dx);
        else
              l=abs(dy);

        xinc=dx/l;
        yinc=dy/l;

        x=x1+0.5*sign(xinc);
        y=y1+0.5*sign(yinc);*/


        value=qRgb(255,255,255);
        /*for(int i=0;i<=l;i++)
        {
             image.setPixel(int(x),int(y),value);
             image.setPixel(int(x+1),int(y),value);
             image.setPixel(int(x+2),int(y),value);


             x=x+xinc;
             y=y+yinc;
        }*/

        /*for(int i=0;i<=l;i++)
        {
            for(int j=0;j<width;j++)
            {
             image.setPixel(int(x+j),int(y+j),value);
             //image.setPixel(int(x+1),int(y),value);
             //image.setPixel(int(x+2),int(y),value);
           }

             x=x+xinc;
             y=y+yinc;
        }*/

        ui->label_5->setPixmap(QPixmap::fromImage(image));
    }


