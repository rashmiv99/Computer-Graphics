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

    void on_ddaButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_bresButton_clicked();

    void dda_algo(float, float, float, float);

    void bres_algo(float, float, float, float);

    void on_patternButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
