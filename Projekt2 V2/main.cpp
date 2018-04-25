#include <iostream>
#include <string>
#include <fstream>

#include "Baza.h"
#include "Word.h"
#include "Wystapienie.h"
#include "Plik.h"
using namespace std;

int main() {
	Baza baza;
	unsigned opcja = 1;
	while (opcja != 0) {
		cout << "OPCJE:" << endl;
		cout << "1 Wprowadz plik" << endl;
		cout << "2 Szukaj slowa w bazie" << endl;
		cout << "3 Wypisz baze" << endl;
		cout << "4 Wypisz tresc pliku" << endl;
		cout << "5 Zapisz baze w pliku" << endl;
		cout << "6 Odczytaj baze z pliku" << endl;
		cout << "0 Wyjdz z programu" << endl;
		while (!(cin >> opcja)) {
			cout << endl << "Blad! Podaj odpowiedni numer ";
			cin.clear();
			cin.ignore(1024, '\n');
		}
		if (opcja == 0)
			break;
		if (opcja == 1) { //wprowadz plik
			cout << "Podaj nazwe pliku: ";
			string nazwa;
			cin >> nazwa;
			/*while (!(cin >> opcja)) {
				cout << endl << "Blad! Podaj odpowiedni numer ";
				cin.clear();
				cin.ignore(1024, '\n');
			}*/
			if (baza.dolaczPlik(nazwa) == 0) {
				cout << "Blad!" << endl;
				continue;
			}
			if (baza.wczytajPlikDoBazy(nazwa) == 0) {
				cout << "Blad!" << endl;
				continue;
			}
			cout << "Plik " << nazwa << " zostal wprowadzony do bazy danych." << endl;
		}
		else if (opcja == 2) {//szukaj slowa w bazie
			cout << "Podaj slowo: ";
			string w;
			cin >> w;
			Word* slowo = baza.szukajSlowa(w);
			if (slowo == nullptr) {
				cout << w << " nie ma w bazie!"<<endl;
				continue;
			}
			cout << "Slowo: " << slowo->tresc << " wystapilo w calej bazie " << slowo->ilosc << " razy w " << slowo->listaPlikow.size() << " plikach" << endl;
			for (unsigned i = 0; i < slowo->listaPlikow.size(); ++i) {
				cout << slowo->listaPlikow[i].getNazwaPliku() << " " << slowo->listaPlikow[i].getIlosc() << endl;
			}
		}
		else if (opcja == 3) {//wypisz baze
			baza.wypiszBaze();
		}
		else if (opcja == 4) {//wypisz tresc pliku
			cout << "Podaj nazwe pliku: ";
			string nazwa;
			cin >> nazwa;
			if (baza.wypiszPlik(nazwa) == 0) 
				cout << "Blad! Nie ma pliku o takiej nazwie!" << endl;
		}
		else if (opcja == 5) {//zapisz baze do pliku
			if (baza.saveToFile() == 0) {
				cout << "Blad! Nie udalo sie zapisac bazy do pliku!";
			}
		}
		else if (opcja == 6) {//odczytaj baze z pliku
			baza.wyczyscBaze();
			if (baza.loadFromFile() == 0) {
				cout << "Blad! Nie udalo sie odczytac bazy z pliku!";
				baza.wyczyscBaze();
			}
		}
	}
	return 0;
}