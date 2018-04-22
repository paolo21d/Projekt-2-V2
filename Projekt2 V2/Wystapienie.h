#pragma once
#include <iostream>
#include <string>
#include "Plik.h"
class Wystapienie
{
	int ilosc;
	std::string nazwaPliku;
	Plik* plikPtr;
public:
	Wystapienie(std::string nazwa, Plik* pptr) : ilosc(1), nazwaPliku(nazwa), plikPtr(pptr) {};
	void zwiekszIlosc() {
		ilosc++;
	}
	void setIlosc(int ilosc_) {
		ilosc = ilosc_;
	}
	int getIlosc()const {
		return ilosc;
	}
	std::string getNazwaPliku() const {
		return nazwaPliku;
	}
	Plik* getPlikPtr() const {
		return plikPtr;
	}
};

