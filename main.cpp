/*

 Programme réalisé par Pierre Guichard 12/04/2020
 
*/

#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>
#include<stdlib.h>
#include "Header.h" // élements de class

using namespace std ;

//angle entre -pi et pi
void angle(double & theta)
{
    while (theta <-M_PI|| theta>M_PI){
        if(theta<-M_PI){theta=2*M_PI+theta;} // Si theta est au dela de -pi (exemple : -3pi alors, on actualise sa valeur par 2pi+théta, donc ça ferais 2pi-3pi => -pi  -pi est bien dans l'intervalle que l'ont veux
        if(theta> M_PI){theta=theta-2*M_PI;} // idem que la ligne au dessus mais ici c'est pour l'autre sens, exemple : 3pi
                                     }
}


//domega1 qui est équivalent à théta1pointpoint
double f1(double omega1 , double omega2, double theta1, double theta2, double l1, double l2, double m1, double m2)
{
    double Del_theta=theta2-theta1;
    double g=-9.81;
    double domega1=(pow(omega1,2)*m2*l1*cos(Del_theta)*sin(Del_theta)+pow(omega2,2)*m2*l2*sin(Del_theta)-(m1+m2)*g*sin(theta1)+m2*cos(Del_theta)*g*sin(theta2))/((m1+m2)*l2-m2*l2*pow(cos(Del_theta),2));
    return domega1;
    
}

//domega2 qui est équivalent à théta2pointpoint
double f2(double omega1 , double omega2, double theta1, double theta2, double l1, double l2, double m1, double m2)
{
    double Del_theta=theta2-theta1;
    double g=-9.81;
    double domega2=(-pow(omega2,2)*m2*l2*cos(Del_theta)*sin(Del_theta)+(m1+m2)*(g*sin(theta1)*cos(Del_theta)-l1*pow(omega1,2)*sin(Del_theta)-g*sin(theta2)))/((m1+m2)*l2-m2*l2*pow(cos(Del_theta),2));
    return domega2;
}

//theta1
double g1(double omega)
{
    return omega;
}

//theta2
double g2(double omega)
{
    return omega ;
}

//mettre a jour les Èlements de la classe
void coordon(pendule & pend_1 , pendule & pend_2)
{
    //mis à jour des coordonnées
    pend_1.coordonnee();
    // les coordonnees du pendule 2 dependent de celle de pendule 1
    pend_2.coordonnee();
    pend_2.AdX(pend_1.GetX());
    pend_2.AdY(pend_1.GetY());
    pend_2.AdDx(pend_1.GetDx());
    pend_2.AdDy(pend_1.GetDy());
    pend_2.AdDdx(pend_1.GetDdx());
    pend_2.AdDdy(pend_1.GetDdy());
    
    // mis à jour des énergies
    //pend_1.Energie();
    pend_1.ec();
    pend_1.ep();
    //pend_2.Energie();
    pend_2.ec();
    pend_2.ep();
}

//deplacer
void de(pendule & pend_1, pendule & pend_2, double h)
{
    double t = pend_1.GetT();
    double const omega1=pend_1.GetOmega();
    double const omega2=pend_2.GetOmega();
    double const theta1=pend_1.GetTheta();
    double const theta2=pend_2.GetTheta();
    double const long1 =pend_1.GetLongueur();
    double const long2=pend_2.GetLongueur();
    double const masse1=pend_1.GetMasse();
    double const masse2=pend_2.GetMasse();
    
    //1er coefficient
    double k1=f1(omega1,omega2,theta1,theta2,long1,long2,masse1,masse2);
    double j1=f2(omega1,omega2,theta1,theta2,long1,long2,masse1,masse2);
    double b1=g1(omega1);
    double p1=g2(omega2);
    
    //2eme coefficient
    double k2=f1(omega1+h/2.*k1,omega2+h/2.*j1,theta1+h/2*b1,theta2+h/2.*p1,long1,long2,masse1,masse2);
    double j2=f2(omega1+h/2.*k1,omega2+h/2.*j1,theta1+h/2.*b1,theta2+h/2.*p1,long1,long2,masse1,masse2);
    double b2=g1(omega1+h/2.*b1);
    double p2=g2(omega2+h/2.*p1);
    
    //3eme coefficient
    double k3=f1(omega1+h/2.*k2,omega2+h/2.*j2,theta1+h/2.*b2,theta2+h/2.*p2,long1,long2,masse1,masse2);
    double j3=f2(omega1+h/2.*k2,omega2+h/2.*j2,theta1+h/2.*b2,theta2+h/2.*p2,long1,long2,masse1,masse2);
    double b3=g1(omega1+h/2.*b2);
    double p3=g2(omega2+h/2.*p2);
    
    //4eme coefficient
    double k4=f1(omega1+h*k3,omega2+h*j3,theta1+h*b3,theta2+h*p3,long1,long2,masse1,masse2);
    double j4=f2(omega1+h*k3,omega2+h*j3,theta1+h*b3,theta2+h*p3,long1,long2,masse1,masse2);
    double b4=g1(omega1+h*b3);
    double p4=g2(omega2+h*p3);
    
    //valeur
    double Omega1=omega1+h/6.*(k1+2*k2+2*k3+k4);
    double Omega2=omega2+h/6.*(j1+2*j2+2*j3+j4);
    double Theta1 = theta1+h/6.*(b1+2*b2+2*b3+b4);
    double Theta2 =theta2+h/6.*(p1+2*p2+2*p3+p4);
    
    double Domega1=f1(Omega1,Omega2,Theta1,Theta2,masse1,masse2,long1,long2);
    double Domega2=f2(Omega1,Omega2,Theta1,Theta2,masse1,masse2,long1,long2);
    angle(Theta1);
    angle(Theta2);
    
    pend_1.SetOmega(Omega1);
    pend_2.SetOmega(Omega2);
    pend_1.SetTheta(Theta1);
    pend_2.SetTheta(Theta2);
    pend_1.SetT(t+h);
    pend_2.SetT(t+h);
    pend_1.SetDomega(Domega1);
    pend_2.SetDomega(Domega2);
    coordon(pend_1,pend_2);
    
}

// solution analytique pour un pendule simple avec un petit angle
void de_PetitAngle(  pendule & pend_1,pendule & pend_2, double theta0, double t)
{
    double g=-9.81;
    double  l1=pend_1.GetLongueur();
    double theta=theta0*cos(sqrt(g/l1)*t);
    double dtheta=-theta0*sqrt(g/l1)*sin(sqrt(g/l1)*t);
    pend_1.SetTheta(theta);
    pend_1.SetOmega(dtheta);
    coordon(pend_1,pend_2);
}

int main()
{
    pendule pend_1;
    pendule pend_2;
    ifstream initialcondition("initialisation.txt");
    ofstream coordonnee("coordonnee"); // en blocs
    ofstream altcoord("coordonneecolon"); // en colonne
    ofstream valeur_theta("theta");
    ofstream energie("energie");
    ofstream phase("phase");
    int num1 ,num2 ;
    double long1, long2 , masse1 , masse2 , theta1 , theta2 , omega1,omega2, domega1 ,domega2 ;
    double tmin , tmax , h;
    
    initialcondition>>num1>>long1>>masse1>>theta1>>omega1>>domega1;
    initialcondition>>num2>>long2>>masse2>>theta2>>omega2>>domega2;
    initialcondition>>tmin>>tmax>>h;
    
    pend_1.init(num1,tmin,theta1,omega1 ,domega1,long1,masse1);
    pend_2.init(num2,tmin,theta2,omega2, domega2, long2,masse2);
    coordon(pend_1,pend_2);

    altcoord<<"#"<<"temps"<<" "<<"X1"<<" "<<"Y1"<<" "<<"X2"<<" "<<"Y2"<<endl;
    valeur_theta<<"#"<<"temps"<<" "<<"theta1"<<" "<<"theta2"<<endl;
    phase<<"#"<<"temps"<<" "<<"theta1"<<" "<<"omega1"<<" "<<"theta2"<<" "<<"omega2"<<endl;
    energie<<"#"<<"temps"<<" "<<"Etot"<<" "<<"Ec"<<" "<<"Ep"<<endl;
    
    int i=0;
    double t=tmin;
    while(t<tmax)
    {
        // le pas doit être petit donc pour éviter d'avoir trop de valeur on prend tous les 100 x
        if (i%100==0){
            
            altcoord<<pend_1.GetT()<<" "<<pend_1.GetX()<<" "<<pend_1.GetY()<<" "<<pend_2.GetX()<<" "<<pend_2.GetY()<<endl; // fichier en colonne pour une trace simplifiée
            
            // coordoonnées en bloc pour un tracé simplifié lors de l'animation
            coordonnee<<pend_1.GetT()<<" "<<"0"<<" "<<"0"<<endl; //point d'origine du pendule
            coordonnee<<pend_1.GetT()<<" "<<pend_1.GetX()<<" "<<pend_1.GetY()<<endl;
            coordonnee<<pend_2.GetT()<<" "<<pend_2.GetX()<<" "<<pend_2.GetY()<<endl;
            coordonnee<<" "<<endl;
            coordonnee<<" "<<endl;
            
            valeur_theta<<pend_1.GetT()<<" "<<pend_1.GetTheta()<<" "<<pend_2.GetTheta()<<endl ; // valeur de theta1 et theta2
            
            phase<<pend_1.GetT()<<" "<<pend_1.GetTheta()<<" "<<pend_1.GetOmega()<<" "<<pend_2.GetTheta()<<" "<<pend_2.GetOmega()<<endl; // valeur de theta1, theta1 point, theta2, theta 2 point
            
            // calcul énergie totale
            double Ec= pend_1.GetEc()+ pend_2.GetEc();
            double Ep= pend_1.GetEp()+pend_2.GetEp();
            double E=  pend_1.GetEnergie()+pend_2.GetEnergie();
            
            energie<<pend_1.GetT()<<" "<<E<<" "<<Ec<<" "<<Ep<<endl;
        }
        
        de(pend_1, pend_2,h);
        t+=h;
        i+=1;
    }
    
    ofstream trac_energie("traceenergie.gnu");
    trac_energie<<"set key font \"Verdana,12\""<<endl;
    trac_energie<<"set xtics font \"Verdana,15\""<<endl;
    trac_energie<<"set ytics font \"Verdana,15\""<<endl;
    trac_energie<<"set title \"Tracé de l'energie en fonction du temps\""<<endl;
    trac_energie<<"set xlabel \"temps t\""<<endl;
    trac_energie<<"set ylabel \"energie E\""<<endl;
    trac_energie<<"set style fill transparent solid 0.2 noborder"<<endl;
    trac_energie<<"plot \"energie\" using 1:2 title 'Etot' with lines,\"energie\" using 1:3 title 'Ec' with lines,\"energie\" using 1:4 title 'Ep' with lines"<<endl;
    trac_energie<< "pause -1" <<endl;
    trac_energie<<"set terminal postscript eps size 3.5,2.62 enhanced color"<<endl;
    trac_energie<<"set output \"energie.eps\""<<endl;
    trac_energie<<"replot"<<endl;
    
    system("gnuplot traceenergie.gnu"); // trace du graphique de l'energie totale — potentiel — cinétique
    
    ofstream multiplot("multiplot.gnu");
    multiplot<<"set multiplot layout 2,2 rowsfirst"<<endl;
    multiplot<<"set key font \"Verdana,12\""<<endl;
    multiplot<<"set xtics font \"Verdana,15\""<<endl;
    multiplot<<"set ytics font \"Verdana,15\""<<endl;
    multiplot<<"set title \"theta1point en fonction de theta1\" font \"Verdana,13\""<<endl;
    multiplot<<"set xlabel \"theta1\""<<endl;
    multiplot<<"set xrange [-3.5:3.5]"<<endl;
    multiplot<<"set ylabel \"theta1point\""<<endl;
    multiplot<<"set yrange [-14:14]"<<endl;
    multiplot<<"set style fill transparent solid 0.2 noborder"<<endl;
    multiplot<<"plot \"phase\" using 2:3 title 'theta1point=f(theta1)' with lines"<<endl; // phase
    
    multiplot<<"set key font \"Verdana,12\""<<endl;
    multiplot<<"set xtics font \"Verdana,15\""<<endl;
    multiplot<<"set ytics font \"Verdana,15\""<<endl;
    multiplot<<"set title \"theta2point en fonction de theta2\""<<endl;
    multiplot<<"set xlabel \"theta2\""<<endl;
    multiplot<<"set xrange [-3.5:3.5]"<<endl;
    multiplot<<"set ylabel \"theta2 point\""<<endl;
    multiplot<<"set yrange [-14:14]"<<endl;
    multiplot<<"set style fill transparent solid 0.2 noborder"<<endl;
    multiplot<<"plot \"phase\" using 4:5 title 'theta2point=f(theta2)' with lines"<<endl; //phase
    
    multiplot<<"set key font \"Verdana,12\""<<endl;
    multiplot<<"set xtics font \"Verdana,15\""<<endl;
    multiplot<<"set ytics font \"Verdana,15\""<<endl;
    multiplot<<"set title \"Tracé des coordonnées en fonction du temps\""<<endl;
    multiplot<<"set xlabel \"temps t\""<<endl;
    multiplot<<"set xrange [0:"<<tmax<<"]"<<endl;
    multiplot<<"set ylabel \"coordonnées\""<<endl;
    multiplot<<"set yrange [-1.1:1.1]"<<endl;
    multiplot<<"set style fill transparent solid 0.2 noborder"<<endl;
    multiplot<<"plot \"coordonneecolon\" using 1:2 title 'x1' with lines,\"coordonneecolon\" using 1:3 title 'y1' with lines"<<endl; //coordonnées
    
    multiplot<<"set key font \"Verdana,12\""<<endl;
    multiplot<<"set xtics font \"Verdana,15\""<<endl;
    multiplot<<"set ytics font \"Verdana,15\""<<endl;
    multiplot<<"set title \"Tracé des coordonnées en fonction du temps\""<<endl;
    multiplot<<"set xlabel \"temps t\""<<endl;
    multiplot<<"set xrange [0:"<<tmax<<"]"<<endl;
    multiplot<<"set ylabel \"coordonnées\""<<endl;
    multiplot<<"set yrange [-2.1:2.1]"<<endl;
    multiplot<<"set style fill transparent solid 0.2 noborder"<<endl;
    multiplot<<"plot \"coordonneecolon\" using 1:4 title 'x2' with lines,\"coordonneecolon\" using 1:5 title 'y2' with lines"<<endl; //coordonnées
    
    multiplot<<"pause -1"<<endl; // le graphique reste affiché tant que je ne le ferme pas
    
    system("gnuplot multiplot.gnu");
    
    ofstream animation("animationpendule.gnu"); // création du fichier qui permet d'animé le pendule
    animation<<"set key font \"Verdana,12\""<<endl;
    animation<<"set title \"Animation du pendule au cours du temps\""<<endl;
    animation<<"set terminal gif animate delay "<<h*10000<<endl;
    animation<<"set output \"penduleanime.gif\"" <<endl;
    animation<<"set xrange ["<<-(long1+long2)<<":"<<(long1+long2)<<"]"<<endl;
    animation<<"set xtics font \"Verdana,15\""<<endl;
    animation<<"set yrange ["<<-(long1+long2)<<":"<<(long1+long2)<<"]"<<endl;
    animation<<"set ytics font \"Verdana,15\""<<endl;
    animation<<"set style line 11 lc rgb '#808080' lt 1"<<endl;
    animation<<"set border 3 back ls 11"<<endl;
    animation<<"set tics nomirror"<<endl;
    animation<<"set pointintervalbox 3"<<endl;
    animation<<"do for [i=1:999] {plot \"coordonnee\" index i using 2:3 title 'pendule' w linespoints ls 1,\"coordonneecolon\" every ::i-25::i using 4:5 title 'trajectoire' with lines lt rgb \"violet\"}"<<endl;

    system("gnuplot animationpendule.gnu"); // representation du pendule
    
    return 0;
}
