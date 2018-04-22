#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Wystapienie.h"
class Word
{
public:
	std::string tresc;
	int ilosc;
	std::vector<Wystapienie> listaPlikow;

	Word(std::string tresc_) : tresc(tresc_), ilosc(1) {};
	~Word();
};

