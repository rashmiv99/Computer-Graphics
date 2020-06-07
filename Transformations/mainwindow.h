#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

   void on_pushButton_3_clicked();
    void dda(float x1,float y1,float x2,float y2);
    void mousePressEvent(QMouseEvent *ev);
    void translate();
    void scale();
    void rotate();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
