#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
class Plik
{
	std::string nazwa;
	std::string trescPliku;
public:
	Plik(std::string nazwa_) {
		std::fstream uchwytDoPliku;
		nazwa = "";
		trescPliku = "";
		uchwytDoPliku.open(nazwa_);
		if (uchwytDoPliku.good()) {
			nazwa = nazwa_;
			std::string linia;
			while (!uchwytDoPliku.eof()) {
				//uchwytDoPliku >> linia;
				getline(uchwytDoPliku, linia);
				trescPliku += linia+"\n";
			}
		}
		uchwytDoPliku.close();
	}
	
	std::string getNazwa() const {
		return nazwa;
	}
	std::string getTrescPliku() const {
		return trescPliku;
	}
	/*std::fstream* getPtrUchwyt() const {
		return &uchwytDoPliku;
	}*/
};

