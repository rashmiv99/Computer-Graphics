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

    void bres_algo(float, float, float, float);

    void seedfill(int ,int ,QRgb ,QRgb );

    void clearImage();

    void rotateBoard();

    void drawBoard();

    int x1[10] = {100,100,100,100,100,100,150,200,250,300};
    int y1[10] = {100,150,200,250,300,100,100,100,100,100};
    int x2[10] = {300,300,300,300,300,100,150,200,250,300};
    int y2[10] = {100,150,200,250,300,300,300,300,300,300};

    int fx[8] = {125,225,175,275,125,225,175,275};
    int fy[8] = {125,125,175,175,225,225,275,275};

private slots:

    void on_drawButton_clicked();

    void on_rotateButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
