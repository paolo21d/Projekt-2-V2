#pragma once
#include <vector>
#include <iostream>
#include "Plik.h"
#include "Word.h"
#include "Wystapienie.h"
class Baza
{
	std::vector<Word> slowa;
	std::vector<Plik> pliki;
public:
	Baza();
	int dolaczPlik(std::string nazwa_);
	int wczytajPlikDoBazy(std::string nazwa_);
	int saveToFile();
	int loadFromFile();
	Plik* getFile(std::string nazwa_);
	void wyczyscBaze();

	Word* szukajSlowa(std::string nazwa_);
	void wypiszBaze()const;
	int wypiszPlik(std::string nazwa_)const;
};

