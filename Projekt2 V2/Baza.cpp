#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "Baza.h"

using namespace std;


Baza::Baza()
{
}

int Baza::dolaczPlik(string nazwa_) {
	//0- nie udalo sie wczytac; 1-uda³o siê wczytac plik
	for (unsigned i = 0; i < pliki.size(); ++i) {
		if (pliki[i].getNazwa() == nazwa_)
			return 0;
	}
	Plik p(nazwa_);
	if (p.getNazwa() != nazwa_)
		return 0;
	pliki.push_back(p);
	return 1;
}

int Baza::wczytajPlikDoBazy(string nazwa_) {
	//0-blad 1-ok
	Plik* plikptr=nullptr;
	for (unsigned i = 0; i < pliki.size(); ++i) {
		if (pliki[i].getNazwa() == nazwa_) {
			plikptr = &pliki[i];
			break;
		}
	}
	if (plikptr == nullptr) {//nie udalo sie znalezc pliku
		return 0;
	}
	string tresc, wyraz;
	tresc= plikptr->getTrescPliku();
	while (true) {
		wyraz = tresc.substr(0, min(tresc.find("\n"), tresc.find(" ")));
		if (wyraz.empty()) { //koniec tresci
			break;
		}
		tresc.erase(0, wyraz.size() + 1);
		//dodajemy wyraz do listy wyrazow
		unsigned i;
		for (i = 0; i < slowa.size(); ++i) {
			if (slowa[i].tresc == wyraz) { //juz jest ten wyraz w bazie
				
				unsigned k;
				for (k = 0; k < slowa[i].listaPlikow.size(); ++k) {//sprawdzamy czy ten wyraz wystapil juz w tym pliku
					if (slowa[i].listaPlikow[k].getNazwaPliku() == nazwa_) { //byl juz ten wyraz w tym pliku
						
						slowa[i].listaPlikow[k].zwiekszIlosc();
						k = slowa[i].listaPlikow.size() + 1;
						break;
					}
				}
				if (k <= slowa[i].listaPlikow.size()) { //nie bylo tego wyrazu w tym pliku
					Wystapienie wyst(plikptr->getNazwa(), plikptr);
					slowa[i].listaPlikow.push_back(wyst);
				}
				slowa[i].ilosc++;
				i = slowa.size() + 1;
				break;
			}
		}
		if (i <= slowa.size()) {//nie ma tego wyrazu w bazie, dodajemy go
			Word word(wyraz);
			Wystapienie wyst(plikptr->getNazwa(), plikptr);
			word.listaPlikow.push_back(wyst);
			slowa.push_back(word);
		}
	}
	return 1;
}

int Baza::saveToFile() {
	fstream file;
	file.open("BazaDane.txt", ios::trunc | ios::out);
	if (!file.good())
		return 0;

	for (unsigned i = 0; i < pliki.size(); ++i) {
		file << pliki[i].getNazwa() << endl;
	}
	file << "#WORDS" << endl;
	for (unsigned i = 0; i < slowa.size(); ++i) {
		Word &word = slowa[i];
		file << word.tresc << " " << word.ilosc << " " << word.listaPlikow.size() << " ";
		for (unsigned k = 0; k < word.listaPlikow.size(); ++k) {
			Wystapienie wyst = word.listaPlikow[k];
			file << wyst.getNazwaPliku() << " " << wyst.getIlosc() << " ";
		}
		file << endl;
	}
	file.close();
	return 1;
}

int Baza::loadFromFile()
{
	fstream file;
	file.open("BazaDane.txt", ios::in);
	if (!file.good())
		return 0;

	wyczyscBaze();
	string linia, tresc, nazwa;
	unsigned ilosc, iloscPlikow;
	while (!file.eof()) {
		//file >> linia;
		getline(file, linia);
		if (linia == "#WORDS") //koniec nazw plikow, poczatek slow
			break;
		if (dolaczPlik(linia) == 0) {
			wyczyscBaze();
			return 0;
		}
	}
	while (!file.eof()) {
		//file >> linia;
		getline(file, linia);
		if (linia.empty())
			break;
		stringstream ss;
		ss << linia;
		ss >> tresc >> ilosc >> iloscPlikow;
		Word w(tresc);
		w.ilosc = ilosc;
		for (unsigned i = 0; i < iloscPlikow; ++i) {
			ss >> nazwa >> ilosc;
			Plik* plikptr = this->getFile(nazwa);
			if (plikptr == nullptr) {//blad, nie ma takiego pliku!
				file.close();
				return 0;
			}
			Wystapienie wyst(nazwa, plikptr);
			wyst.setIlosc(ilosc);
			w.listaPlikow.push_back(wyst);
		}
		slowa.push_back(w);
	}
	file.close();
	return 1;
}

Plik * Baza::getFile(string nazwa_)
{
	for (unsigned i = 0; i < pliki.size(); ++i) {
		if (pliki[i].getNazwa() == nazwa_)
			return &pliki[i];
	}
	return nullptr;
}

void Baza::wyczyscBaze()
{
	pliki.clear();
	slowa.clear();
}

Word * Baza::szukajSlowa(string nazwa_)
{
	for (unsigned i = 0; i < slowa.size(); ++i) {
		if (slowa[i].tresc == nazwa_)
			return &slowa[i];
	}
	return nullptr;
}

void Baza::wypiszBaze() const
{
	for (unsigned i = 0; i < pliki.size(); ++i) {
		cout << pliki[i].getNazwa() << endl;
	}
	cout << "WORDS:" << endl;
	for (unsigned i = 0; i < slowa.size(); ++i) {
		Word const &word = slowa[i];
		cout << word.tresc << " " << word.ilosc << " " << word.listaPlikow.size() << " ";
		for (unsigned k = 0; k < word.listaPlikow.size(); ++k) {
			Wystapienie const &wyst = word.listaPlikow[k];
			cout << wyst.getNazwaPliku() << " " << wyst.getIlosc() << " ";
			//cout << word.listaPlikow[i].getNazwaPliku() << " " << word.listaPlikow[i].getIlosc() << " ";
		}
		cout << endl;
	}
}

int Baza::wypiszPlik(string nazwa_) const
{
	for (unsigned i = 0; i < pliki.size(); ++i) {
		if (pliki[i].getNazwa() == nazwa_) {
			cout << pliki[i].getTrescPliku();
			return 1;
		}
	}
	return 0;
}
