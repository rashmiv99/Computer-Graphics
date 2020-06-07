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

    void dda(float ,float ,float ,float );

    void mousePressEvent(QMouseEvent *);

    void clearImage();

    void Rotation();

private slots:

    void on_rotate_arbitrary_clicked();

    void on_rotate_x_axis_clicked();

    void on_rotate_y_axis_clicked();

    void on_rotate_xy_axis_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
