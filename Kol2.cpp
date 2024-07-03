#include "Wybor.h"
#include <iostream>
#include <cstring>	
#include <cmath>
#include <stdexcept>

using namespace std;

/*
* Uwaga: Zadania kod rozwiazania zaania umieszczaæ pomiêdzy #ifdef a #endif.
*/

#ifdef Kol_2


class Wlasciciel {
    
};

class Samochod {
protected:
    char numerRejestracyjny[10];
    int stanLicznika;
    bool czyDopuszczonyDoJazdy;
    Wlasciciel* wlasciciel;

    static Samochod* wzorcowySamochod;
    static constexpr double WAR_POCZ = 50000.0;
    static constexpr double O2 = 0.2;

public:
    
    Samochod(const char* nr, int licznik, bool dopuszczony, Wlasciciel* wlasc) {
        initSamochod(nr, licznik, dopuszczony, wlasc);
    }

    // k.domysln
    Samochod() {
        if (wzorcowySamochod == nullptr) {
            throw runtime_error("Brak instancji wzorcowej");
        }
        initSamochod(wzorcowySamochod->numerRejestracyjny, wzorcowySamochod->stanLicznika,
            wzorcowySamochod->czyDopuszczonyDoJazdy, wzorcowySamochod->wlasciciel);
    }

   
    virtual ~Samochod() {
        if (wzorcowySamochod == this) {
            wzorcowySamochod = nullptr;
        }
    }

  
    const char* getNumerRejestracyjny() const { return numerRejestracyjny; }
    int getStanLicznika() const { return stanLicznika; }
    bool getCzyDopuszczonyDoJazdy() const { return czyDopuszczonyDoJazdy; }
    Wlasciciel* getW³aœciciel() const { return wlasciciel; }

    static Samochod* getWzorcowySamochod() { return wzorcowySamochod; }
    static void setWzorcowySamochod(Samochod* wzorcowy) { wzorcowySamochod = wzorcowy; }

    void setNumerRejestracyjny(const char* nr) {
        for (int i = 0; i < strlen(nr); ++i) {
            if (!isdigit(nr[i])) {
                throw invalid_argument("Numer rejestracyjny sklada sie tylko z cyfr.");
            }
        }
        strncpy(numerRejestracyjny, nr, sizeof(numerRejestracyjny) - 1);
        numerRejestracyjny[sizeof(numerRejestracyjny) - 1] = '\0';
    }

   
    void setStanLicznika(int nowyLicznik) {
        if (nowyLicznik < 0) {
            throw invalid_argument("Stan licznika musi byc dodatni");
        }
        stanLicznika = nowyLicznik;
    }


    virtual float getZasieg() const {
        if (!czyDopuszczonyDoJazdy) {
            throw runtime_error("Samochod niedopuszczony do jazdy");
        }
        return 800.0f; 
    }

   
    virtual operator double() const {
        double WSP_SPARW = czyDopuszczonyDoJazdy ? 1.0 : 0.2;
        double value = (WAR_POCZ - O2 * stanLicznika) * WSP_SPARW;
        return (value < 400.0) ? 400.0 : value;
    }

    
    bool operator!=(const Samochod& other) const {
        return abs(stanLicznika - other.stanLicznika) > 20 || czyDopuszczonyDoJazdy != other.czyDopuszczonyDoJazdy;
    }

protected:
   
    void initSamochod(const char* nr, int licznik, bool dopuszczony, Wlasciciel* wlasc) {
        setNumerRejestracyjny(nr);
        setStanLicznika(licznik);
        czyDopuszczonyDoJazdy = dopuszczony;
        wlasciciel = wlasc;
    }
};

Samochod* Samochod::wzorcowySamochod = nullptr; 

class SamochodElektryczny : public Samochod {
private:
    int stanBaterii;

public:
  
    SamochodElektryczny(const Samochod& samochod, int bateria) : Samochod(samochod) {
        setStanBaterii(bateria);
    }

   
    void setStanBaterii(int bateria) {
        if (bateria < 0 || bateria > 100) {
            throw invalid_argument("Stan baterii musi byc w zakresie 0-100%");
        }
        stanBaterii = bateria;
    }

    int getStanBaterii() const { return stanBaterii; }

   
    float getZasieg() const override {
        if (!czyDopuszczonyDoJazdy) {
            throw runtime_error("Samochod niedopuszczony do jazdy");
        }
        return 2.5f * stanBaterii; 
    }

    
    operator double() const override {
        double WSP_SPARW = czyDopuszczonyDoJazdy ? 1.0 : 0.2;
        double value = ((WAR_POCZ - O2 * stanLicznika) * WSP_SPARW) * 0.7; 
        return (value < 400.0) ? 400.0 : value;
    }
};

int main()
{

}

#endif
