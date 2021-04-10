#include <stdio.h>
#include"Header.h"
#include <iostream>
#include <cmath>
using namespace  std ;
double g=-9.81 ;

pendule::pendule(int NUM,double TIME,double THETA,double OMEGA,double DOMEGA,double LONG,double MASSE)
{
    num=NUM;
    t=TIME;
    theta=THETA;
    omega=OMEGA;
    domega=DOMEGA;
    longueur=LONG;
    masse=MASSE;
}

void pendule::init(int NUM,double TIME,double THETA,double OMEGA,double DOMEGA,double LONG,double MASSE)
{
    num=NUM;
    t=TIME;
    theta=THETA;
    omega=OMEGA;
    domega=DOMEGA;
    longueur=LONG;
    masse=MASSE;
}

void pendule::Energie() // energie totale du pendule
{
    double g =-9.81;
    double Ep = -masse*y*g;
    double v2 = pow(dx,2)+pow(dy,2);
    double Ec =0.5*masse*v2;
    energie=Ep+Ec ;
}

void pendule::ep()
{
    double g=-9.81;
    Ep=-masse*y*g;
}

void pendule::ec()
{
    double v2 = pow(dx,2)+pow(dy,2);
    Ec=0.5*masse*v2;
}

void pendule::coordonnee()
{
    y=longueur*cos(theta);
    x=longueur*sin(theta);
    dy=-omega*longueur*sin(theta);
    dx=omega*longueur*cos(theta);
    ddy=-longueur*(domega*sin(theta)+pow(omega,2)*cos(theta));
    ddx=longueur*(domega*cos(theta)-pow(omega,2)*sin(theta));
}
