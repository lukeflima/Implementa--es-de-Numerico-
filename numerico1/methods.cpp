#include <string>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "fparser/fparser.hh"
#include "mainwindow.h"

#define MAXITER 20

typedef struct t_saida{
    double a, b;
    int condErro, iter;
} t_saida;

typedef struct t_raiz{
    double x, Fx;
    int condErro, iter;
} t_raiz;

void LocRaiz(std::string funcao,double z , int maxIter, t_saida *saida){
    /* valores da variavel*/
    double a[1];
    double b[1];
    /* iterador*/
    int iter=0;
    int R;
    int condErro;
    /* imagens dos valores*/
    double Fa;
    double Fb;
    double Aureo = 2/(sqrt(5)-1);
    /*parser de funções*/
    /* seta os valores de a e b*/
    if(z == 0)
    {
        a[0] = -0.05;
        b[0] = 0.05;

    }
    else
    {
        a[0] = 0.95*z;
        b[0] = 1.05*z;
    }

    /*faz o parsing da função*/
    if(fparser.Parse(funcao,"x") != -1){
        std::cout << "Parser error!" << std::endl;
        exit(EXIT_FAILURE);
    }

    /*calcula as imagens de a e b*/
    Fa = fparser.Eval(a);
    Fb = fparser.Eval(b);

    /*iterações para tentar cercar a raiz*/
    while(Fa*Fb > 0 && iter<maxIter)
    {
        if(fabs(Fa) < fabs(Fb) )
        {
            a[0] = a[0] - Aureo*(b[0]-a[0]);
            Fa = fparser.Eval(a);
        }
        else
        {
            b[0] = b[0] + Aureo*(b[0]-a[0]);
            Fb = fparser.Eval(b);
        }
        iter++;
    }

    R = Fa*Fb;
    /* calculo da condErro*/
    if(R>=0 || iter >= maxIter)
    {
        condErro =1;
    }
    else
    {
        condErro = 0;
    }


    saida->a = a[0];
    saida->b = b[0];
    saida->condErro = condErro;
    saida->iter = iter;
}

void MetodoNewton(std::string funcao, int MaxIter, double tole, t_raiz *raiz){ //fdx derivada de fx_inicial
    if(fparser.Parse(funcao,"x") != -1){
        std::cout << "Parser error!" << std::endl;
        exit(EXIT_FAILURE);
    }

    t_saida saida;
    LocRaiz(funcao, 0, MaxIter, &saida);

    bool repeat = true;
    int cont = 0;
    while(repeat){
        double x[1] = {saida.a};
        double Fx = fparser.Eval(x);
        double DFx;
        int iter=0;
        double h = 1e-12;
        double y[1] = {x[0]+h};
        double z[1] = {x[0]-h};
        DFx =  (fparser.Eval(y) - fparser.Eval(z))/(2*h);

        while(fabs(Fx)>=tole && iter < MaxIter){
            x[0]=x[0]-(Fx/DFx);
            Fx = fparser.Eval(x);
            y[0] = x[0]+ h;
            z[0] = x[0] -h;
            DFx =  (fparser.Eval(y) - fparser.Eval(z))/(2*h);

            iter++;
        }

        raiz->x = x[0];
        raiz->condErro = ((iter <= MaxIter ) && (fabs(Fx) <= tole)) ? 0:1;
        raiz->iter = iter;
        raiz->Fx = Fx;

        if(raiz->condErro == 1){
            if(cont > 5) repeat = false;
            else{
                repeat = true;
                cont++;
                std::clog << "New " << cont << std::endl;
                LocRaiz(funcao,x[0],MaxIter,&saida);
            }
        }
    }
}

void Bissecao(std::string funcao, int MaxIter, double tole, t_raiz *raiz){
    t_saida saida;
    LocRaiz(funcao,0,MaxIter,&saida);

    bool repeat = true;
    int cont = 0;
    double a[1], b[1], x[1], dx, Fx=1;
    int iter = 0, condErro;
    while(repeat){
        a[0] = saida.a;
        b[0] = saida.b;
        dx = fabs(a[0]-b[0])/2;

        /*  */
        if(fparser.Parse(funcao,"x") != -1){
            std::cout << "Parser error!" << std::endl;
            exit(EXIT_FAILURE);
        }

        /* imagens dos valores*/
        double Fa = fparser.Eval(a);
        double Fb = fparser.Eval(b);

        while(dx > tole && fabs(Fx) > tole && iter < MaxIter){
            x[0] = (a[0]+b[0])/2;
            Fx = fparser.Eval(x);
            if(Fa*Fx < 0){
                b[0] = x[0];
                Fb = Fx;
            }else{
                a[0] = x[0];
                Fa = Fx;
            }
            dx = dx/2;
            iter++;
        }
        if(Fx>tole || iter>MaxIter)
        {
            condErro = 1;
            if(iter >= MaxIter){
                iter = 0;
                Fx =1 ;
                if(cont > 5){
                    repeat = false;
                }else{
                    repeat = true;
                    cont++;
                    std::clog << "Bissecao: " << cont << std::endl;
                    LocRaiz(funcao,x[0],MaxIter,&saida);
                }
            }
        }
        else
        {
            condErro = 0;
            repeat = false;
        }

    }

    raiz->x = x[0];
    raiz->condErro = condErro;
    raiz->iter = iter;
    raiz->Fx = Fx;
}

int Secante(std::string funcao, int MaxIter, double tole, t_raiz *raiz){

    t_saida saida;
    LocRaiz(funcao,0, MaxIter, &saida);
        if(fparser.Parse(funcao,"x") != -1){
            std::cout << "Parser error!" << std::endl;
            exit(EXIT_FAILURE);
        }

        double a[1] = {saida.a};
        double b[1] = {saida.b};
        int iter=0;
        int R;
        int condErro;
        double x[1];

        /* imagens dos valores*/
        double Fa = fparser.Eval(a);
        double Fb = fparser.Eval(b);
        double Fx;
        double Fy;
        double y[1];
        bool repeat = true;
        int cont = 0;
        do{
        while( (b[0]-a[0]) > tole && iter<= MaxIter)
        {
            a[0] = saida.a;
            b[0] = saida.b;
            Fa = fparser.Eval(a);
            Fb = fparser.Eval(b);
            x[0] = b[0]-(Fb)*((b[0]-a[0])/(Fb-Fa));
            Fx =  fparser.Eval(x);


            if(Fa*Fx < 0)
            {
                b[0]=x[0];
                Fb = Fx;
            }
            else
            {
                a[0] = x[0];
                Fa = Fx;
            }

            y[0] =((a[0] + b[0])*0.5);
            Fy = fparser.Eval(y);

            if((b[0]-a[0]) < tole && fabs(Fy) < tole )
            {
                raiz->x = y[0];
                raiz->Fx = Fy;
                raiz->iter = iter;
                raiz->condErro =1;
                return -1;
            }
            if(fabs(Fx) < tole)
            {
                raiz->x = x[0];
                raiz->Fx = Fx;
                raiz->iter = iter;
                raiz->condErro =0;
                return 0;
            }

            iter++;
        }

        if(condErro){
            if(cont > 5) repeat = false;
            else{
                LocRaiz(funcao, x[0], MaxIter, &saida);
                cont++;
                std::clog << "secante" << std::endl;
            }
        }

        }while(repeat);

        raiz->x = x[0];
        raiz->condErro = 1;
        raiz->iter = iter;
        raiz->Fx = Fx;
        return -1;
}

