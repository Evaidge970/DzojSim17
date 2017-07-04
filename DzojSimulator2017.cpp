#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <cstdlib>
#include <time.h>
#include <windows.h>
using namespace std;

int losuj_typ_reakcji()
{
	srand(time(NULL));
	return rand()%2; //albo 0 albo 1
}

int los_t()
{
	srand(time(NULL));
	return rand()%3499+501; //od 1001 do 5000
}

int main()
{
	ifstream reakcje;
	ifstream reakcje2;
	ifstream reakcje_watki;
	string odp;
	string odp_p;
	string odp_pp;
	string input; //wiadomosc pisana przez ciebie do dzoja - input
	int wkurzenie=0; //od 0 do 2, 0 - normalny, 1 - zly, 2 - koniec petli
	int typ_reakcji; //od 0 do 2, 0 - reakcje, 1 - reakcje_watki, 2 - reakcje2
	int j=0; //licznik watkow
	int los_l;
	cout<<"Witaj w symulatorze rozmowy z Dzojem! Wybacz brak polskich znakow!\n(wersja i baza reakcji: 2.07.2017)\n";
	do
	{
		cout<<"\n\nTy: ";
		getline(cin, input);
		if(input=="cze")
		{
			Sleep(los_t());
			cout<<endl<<"Dzoj: cze";
			continue;
		}
		else if(input=="wal sie")
		{
			Sleep(los_t());
			cout<<endl<<"Dzoj: ty sie wal bardziej";
			wkurzenie+=1;
			continue;
		}
		else if(input=="k?")
		{
			Sleep(los_t());
			srand(time(NULL));
			int los_k = rand()%8; //losuje liczbe od 0 do 8, czyli 9 liczb
			if(los_k<=1) //dwie dziewiate szans na odpowiedz k
			{
				cout<<endl<<"Dzoj: k";
				continue;
			}
		}
		if(wkurzenie==1)
		{
			typ_reakcji=2; //agresywny dzoj
		}
		else
		{
			if(j==0)
			{
				typ_reakcji=losuj_typ_reakcji(); //dzoj albo wielowatkowy albo zwykly
			}
			else
			{
				typ_reakcji=1;
			}
		}
		Sleep(los_t());
		if(typ_reakcji==0) //jesli dzoj odpowiada normalnie
		{
			reakcje.open("reakcje.txt", ios::in); //plik - wejscie
			if(reakcje.good())
			{
				cout<<"\nDzoj: ";
				int numLines = 0; //licznik linii
				ifstream in("reakcje.txt");
				string unused;
				while (getline(in, unused))
				{
					numLines+=1; 
				} //koniec licznika linii
				srand(time(NULL));
				los_l = rand()%numLines;
				for(int i=0; i<los_l; i++)
     			{
     				getline(reakcje, odp);
				}
				reakcje.close();
			}
			else cout<<"Blad wczytywania odpowiedzi z pliku"; //jesli plik nie dziala wyswietl blad
			cout<<odp;
		}
		else if(typ_reakcji==1) //jesli dzoj odpowiada wielowatkowo
		{
			reakcje_watki.open("reakcje_watki.txt", ios::in); //plik - wejscie
			if(reakcje_watki.good())
			{
				int numLines = 0; //licznik linii
				ifstream in("reakcje_watki.txt");
				string unused;
				while (getline(in, unused))
				{
					numLines+=1; 
				} //koniec licznika linii
				if(j==0) //pierwszy watek
				{
					cout<<"\nDzoj: ";
					numLines/=3;
					srand(time(NULL));
					los_l = 3*(rand()%numLines)+1;
					for(int i=0; i<los_l; i++)
	     			{
	     				getline(reakcje_watki, odp);
					}
					reakcje_watki.close();
					cout<<odp;
				}
				if(j==1 || j==2) //drugi lub trzeci watek
				{
					cout<<"\nDzoj: ";
					los_l++;
					for(int i=0; i<los_l; i++)
	     			{
	     				getline(reakcje_watki, odp);
					}
					reakcje_watki.close();
					cout<<odp;
				}
			}
			else cout<<"Blad wczytywania odpowiedzi z pliku"; //jesli plik nie dziala wyswietl blad
			j+=1;
			if(j==3)
			{
				j=0;
			}
		}
		else if(typ_reakcji==2) //jesli dzoj odpowiada agresywnie
		{
			reakcje2.open("reakcje2.txt", ios::in); //plik - wejscie
			if(reakcje2.good())
			{
				cout<<"\nDzoj: ";
				int numLines = 0; //licznik linii
				ifstream in("reakcje2.txt");
				string unused;
				while (getline(in, unused))
				{
					numLines+=1; 
				} //koniec licznika linii
				srand(time(NULL));
				int los_l = rand()%numLines;
				for(int i=0; i<los_l; i++)
     			{
     				getline(reakcje2, odp);
				}
				reakcje2.close();
			}
			else cout<<"Blad wczytywania odpowiedzi z pliku"; //jesli plik nie dziala wyswietl blad
			cout<<odp;
		}
	}
	while(wkurzenie<2);
	cout<<"\n\n[Uzytkownik sie obrazil]";
	getch();
	return 0;
}
