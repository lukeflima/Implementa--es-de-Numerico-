#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fparser/fparser.hh"
#include "methods.cpp"
#include "form.h"

FunctionParser fparser;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fparser.AddConstant("pi",3.14159265359);
    fparser.AddConstant("Pi",3.14159265359);
    fparser.AddConstant("PI",3.14159265359);
    fparser.AddConstant("pI",3.14159265359);
    fparser.AddConstant("e",2.7182818284);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_bissecao_clicked()
{
    QString func = ui->funcao->text();
    if(func == ""){
        ui->funcao->focusWidget();
        std::clog << "Nothing" << std::endl;
        return;
    }

    if(fparser.Parse(func.toStdString(), "x") != -1){
        std::clog << "Sintaxe de função invalida." << std::endl;
        return;
    }

    t_raiz raiz;
    Bissecao(func.toStdString(),MAXITER,1e-6,&raiz);

    std::clog << func.toStdString() << std::endl  << raiz.x << std::endl <<  raiz.Fx << std::endl << raiz.condErro << std::endl;

    Form msg;
    msg.setInf(func, raiz.x, raiz.Fx);
    msg.exec();
}

void MainWindow::on_secante_clicked()
{
    QString func = ui->funcao->text();
    if(func == ""){
        ui->funcao->focusWidget();
        std::clog << "Nothing" << std::endl;
        return;
    }

    if(fparser.Parse(func.toStdString(), "x") != -1){
        std::clog << "Sintaxe de função invalida." << std::endl;
        return;
    }

    t_raiz raiz;
    Secante(func.toStdString(),MAXITER,1e-6,&raiz);

    std::clog << func.toStdString() << std::endl  << raiz.x << std::endl <<  raiz.Fx << std::endl << raiz.condErro << std::endl;

    Form msg;
    msg.setInf(func, raiz.x, raiz.Fx);
    msg.exec();
}
