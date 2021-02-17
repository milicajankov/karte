#include <iostream>
#include <vector>
using namespace std;

class Datum {
    int mesec;
    int godina;
public:
    Datum(int m, int g): mesec(m), godina(g) {}
    friend bool operator == (const Datum &d1, const Datum &d2){
        return (d1.mesec == d2.mesec) == (d1.godina == d2.godina);
    }
    friend bool operator != (const Datum &d1, const Datum &d2){
        return !(d1==d2);
    }
    friend ostream& operator << (ostream& out, const Datum &d){
        out << "(" << d.mesec << "/" << d.godina << ")";
        return out;

    }
    string ispis(){
        return "(" + to_string(mesec) + "/" + to_string(godina) + ")";

    }
};

class Karta {
    int id;
public:
   Karta(int i): id(i) { }
   virtual bool valjanost(double cena, Datum datum) = 0;
   virtual string stampa() {
        return to_string(id);

   }
};

class Mesecna: public Karta{
    string ime;
    Datum d;
public:
    Mesecna(int id, string i, Datum dan): Karta(id), ime (i), d(dan) { }
    string stampa(){
        return ime + " (" + Karta::stampa() + ") -" + d.ispis();
    }
    bool valjanost(double x, Datum dd){
        return (dd == d);
    }
    bool produzi(double x, Datum dd){
        d==dd;
    }
};

class Pojedinacna: public Karta{
    double iznos=50.;
public:
    Pojedinacna(double iz, int id): iznos(iz), Karta(id){ }
    string stampa(){
        return Karta::stampa() + " : " + to_string(iznos);

    }
    bool valjanost(double x, Datum dd){
            if(iznos >= x){
                iznos-=x;
                return true;
            }
        return false;
    }
    void produzi(double x, Datum dd){
        iznos+=x;
    }
};

class Aparat{
    vector<Karta*> niz;
public:
    Aparat() = default;
    void dodaj(Karta *k){
        niz.push_back(k);
    }
    void provera(double x, Datum d){
        for(unsigned i=0; i < niz.size(); ++i){
            bool ok= niz[i]->valjanost(x,d);
            cout << niz[i]->stampa();
            if(ok)
                cout <<", valjana" << endl;
            else
                cout <<", nije valjanja" <<endl;
        }
    }
};

int main()
{
    Aparat a;

    a.dodaj(new Mesecna(1, "Petar Petrovic", Datum(9,2019)));
    a.dodaj(new Mesecna(2, "Marija Petrovic", Datum(10,2019)));
    a.dodaj(new Mesecna(3, "Marko Markovic", Datum(10,2019)));
    a.dodaj(new Pojedinacna(50.5, 4));
    a.dodaj(new Pojedinacna(20, 5));

    a.provera(30, Datum(10,19));

    return 0;
}
