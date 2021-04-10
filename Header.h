#ifndef Header_h // identifier
#define Header_h

class pendule{
private:
    //définition du temps
    double t;
    //numero
    int num ;
    //définition de la position
    double x,dx,ddx;
    double y,dy,ddy;
    //définition des angles
    double theta,omega,domega ;
    //définition des parametres du système (masse et longueur)
    double longueur;
    double masse ;
    //définition des energies
    double energie ;
    double Ec;
    double Ep;
    public :
    //Constructeur et Destructeur
    pendule(){};
    pendule(int,double,double,double,double,double,double);
    ~pendule(){};
    //Initialisation
    void init(int,double,double,double,double,double,double);
    //Coordon√©e
    void coordonnee();
    
    //Energie
    void Energie(); 
    void ec();
    void ep();
    // Accesseur — GET
    double GetEnergie() const {return energie;}
    double GetEc() const {return Ec;}
    double GetEp() const {return Ep;}
    int GetNum() const {return num;}
    double GetT() const{return t;}
    double GetX() const{return x;}
    double GetY()const {return y;}
    double GetDx()const {return dx;}
    double GetDdx()const{return ddx;}
    double GetDy()const{return dy;}
    double GetDdy() const{return ddy ;}
    double GetTheta()const{return theta ;}
    double GetOmega()const{return omega ;}
    double GetDomega()const{return domega ;}
    double GetLongueur() const {return longueur;}
    double GetMasse() const {return masse ;}
    //Mutateur — SET
    void SetEnergie(double a){energie=a;}
    void SetEc(double a){Ec=a;}
    void SetEp(double a){Ep=a;}
    void SetNum(double a){num=a;}
    void SetT(double a){t=a;}
    void SetX(double a){x=a;}
    void SetY(double a){y=a;}
    void SetDx(double a){dx=a;}
    void SetDy(double a){dy=a;}
    void SetDdx(double a){ddx=a;}
    void SetDdy(double a){ddy=a;}
    void SetTheta(double a){theta=a;}
    void SetOmega(double a){omega=a;}
    void SetDomega(double a){domega=a;}
    void SetLongueur(double a){longueur=a;}
    void SetMasse(double a){masse=a;}
    
    //incrément +=
    void AdX(double a){x+=a;}
    void AdY(double a){y+=a;}
    void AdDx(double a){dx+=a;}
    void AdDy(double a){dy+=a;}
    void AdDdx(double a){ddx+=a;}
    void AdDdy(double a){ddy+=a;}
};

#endif 
