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
    void dda_dot(float x1, float y1, float x2, float y2);
    void dda_dash(float x1, float y1, float x2, float y2);
    void dda_dashdot(float x1, float y1, float x2, float y2);
    void dda_solid(float x1, float y1, float x2, float y2);
    void dda_thick(float x1, float y1, float x2, float y2,float w);

    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
