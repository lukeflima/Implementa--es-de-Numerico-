#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fparser/fparser.hh"

extern FunctionParser fparser;

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
    void on_bissecao_clicked();

    void on_secante_clicked();

    void on_newton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
