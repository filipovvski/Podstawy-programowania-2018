//POP 2018-12-13 projekt 1 Filipowicz Piotr EIT 3 172158     Microsoft Visual Studio 2017

#include <iostream>
#include <time.h>
#include <iomanip>
#include <cstdlib>

using namespace std;

struct karta {
	int kolor;
	int figura;
};

void przygotowanie(karta T[]);
void generuj_talie(karta T[]);
void tasuj_talie(karta T[]);
void gra(karta talia[], int stawka, int &zetony);
int obstawianie(int &zetony);
void dodaj_karte_gracza(karta talia[], int &pkt_gracza, karta &karta_1);
void dodaj_karte_krupiera(karta talia[], int &pkt_krupiera, karta &karta_1);
void losuj_karte(karta &karta_1, karta talia[]);
void rysuj_karte(karta karta_1);
void wyswietl_figure(karta karta_1);
void rysuj_kolor(karta karta_1);
void rysuj_interface(karta grajace[], int stawka, int zetony, int pkt_gracza, int pkt_gracza_2, int pkt_krupiera, int czyja_kolej, int split, karta grajace_split[]);
void pisz_menu(int tura, int stawka, int zetony, karta grajace[]);
void decyzja_1(karta grajace[], int &pkt_gracza, int &pkt_gracza_2, int &wybor, karta talia[], int &czyja_kolej, int &czyja_kolej_1, int &czyja_kolej_2, int &tura, int &i, int &zetony, int &stawka, int &split, karta grajace_split[]);
int sprawdzenie(int pkt_gracza, int pkt_gracza_2, int split);
void krupier(karta grajace[], int stawka, int zetony, int pkt_gracza, int pkt_gracza_2, int &pkt_krupiera, karta talia[], int czyja_kolej, int split, karta grajace_split[]);
void podsumowanie(int &pkt_gracza, int &pkt_gracza_2, int &pkt_krupiera, int &zetony, int stawka, int &czyja_kolej, int &tura, karta grajace[], int &split, karta grajace_split[]);
void rysuj_statystyki(int stawka, int zetony);
int czy_nast_rozd(int &nast_rozd);
void wartosci_kart(karta grajace[], int &pkt_krupiera, int &pkt_gracza, karta talia[]);
void podsumowanie_1(int &pkt_gracza, int &pkt_krupiera, int &zetony, int stawka);
void czekaj(int czas);

int main()
{
	srand(time(NULL));

	int zetony = 100;
	int stawka = 0;
	int nast_rozd = 2;
	karta talia[156];

	while (zetony > 0)
	{
		przygotowanie(talia);
		gra(talia, stawka, zetony);
		if (czy_nast_rozd(nast_rozd) == 2)
			break;
	}

	system("pause");
	return 0;
}

int czy_nast_rozd(int &nast_rozd)
{
	cout << "Czy chcesz grac dalej?" << endl;
	cout << "1. Tak" << endl << "2. Nie" << endl;
	cin >> nast_rozd;
	return nast_rozd;
}

void przygotowanie(karta talia[])
{
	generuj_talie(talia);
	tasuj_talie(talia);
}

void generuj_talie(karta T[])
{
	int i = 1;

	for (int talie = 0; talie < 3; talie++)
		for (int kolor = 1; kolor <= 4; kolor++)
			for (int figura = 2; figura <= 14; figura++)
			{
				T[i - 1].kolor = kolor;
				T[i - 1].figura = figura;
				i++;
			}
}

void tasuj_talie(karta T[])
{
	karta buf;
	for (int i = 0; i < 52; i++)
	{
		int m = rand() % 156;
		buf = T[i];
		T[i] = T[m];
		T[m] = buf;
	}
}

void wartosci_kart(karta grajace[], int &pkt_krupiera, int &pkt_gracza, karta talia[])
{
	for (int i = 0; i < 20; i++)
	{
		grajace[i].kolor = 0;
		grajace[i].figura = 0;
	}

	for (int j = 0; j < 2; j++)
		dodaj_karte_gracza(talia, pkt_gracza, grajace[j]);

	dodaj_karte_krupiera(talia, pkt_krupiera, grajace[11]);
}

void gra(karta talia[], int stawka, int &zetony)
{
	int pkt_gracza = 0;
	int pkt_gracza_2 = 0;
	int pkt_krupiera = 0;
	int wybor = 0;
	int czyja_kolej = 0;
	int czyja_kolej_1 = 0;
	int czyja_kolej_2 = 0;
	int split = 0;
	int nast = 0;

	karta grajace[19];
	karta grajace_split[11];

	wartosci_kart(grajace, pkt_krupiera, pkt_gracza, talia);

	int tura = 1;
	int i = 2;

	system("cls");
	rysuj_statystyki(stawka, zetony);
	cout << "Ile zetonow chcesz obstawic ?" << endl;    //Tu zaczyna sie runda gracza

	stawka = obstawianie(zetony);

	while (czyja_kolej != 1 && i < 11)
	{
		rysuj_interface(grajace, stawka, zetony, pkt_gracza, pkt_gracza_2, pkt_krupiera, czyja_kolej, split, grajace_split);
		switch (sprawdzenie(pkt_gracza, pkt_gracza_2, split))
		{
		case 1:			
			czyja_kolej = 1;		
			krupier(grajace, stawka, zetony, pkt_gracza, pkt_gracza_2, pkt_krupiera, talia, czyja_kolej, split, grajace_split);
			break;
		case 0:
			pisz_menu(tura, stawka, zetony, grajace);
			decyzja_1(grajace, pkt_gracza, pkt_gracza_2, wybor, talia, czyja_kolej, czyja_kolej_1, czyja_kolej_2, tura, i, zetony, stawka, split, grajace_split);
			if (czyja_kolej == 1)	krupier(grajace, stawka, zetony, pkt_gracza, pkt_gracza_2, pkt_krupiera, talia, czyja_kolej, split, grajace_split);
			break;
		case -1:
			czyja_kolej = 1;
			break;
		}	
		i++;
	}		
	podsumowanie(pkt_gracza, pkt_gracza_2, pkt_krupiera, zetony, stawka, czyja_kolej, tura, grajace, split, grajace_split);
}

void decyzja_1(karta grajace[], int &pkt_gracza, int &pkt_gracza_2, int &wybor, karta talia[], int &czyja_kolej, int &czyja_kolej_1, int &czyja_kolej_2, int &tura, int &i, int &zetony, int &stawka, int &split, karta grajace_split[])
{
	cin >> wybor;

	switch (wybor)
	{
	case 1:
		if (split == 1)             //Wykonuje sie po zrobieniu splitu
		{
			int ktora;
			cout << "Do ktorej reki chcialbys dodac karte?";
			cin >> ktora;
			if (ktora == 1)
				dodaj_karte_gracza(talia, pkt_gracza, grajace[i]);
			else 
				dodaj_karte_gracza(talia, pkt_gracza_2, grajace_split[i]);
		}
		else
		{
			dodaj_karte_gracza(talia, pkt_gracza, grajace[i]);
			cout << endl;
			tura = 2;
		}
		break;
	case 2:
		if (split == 1)
		{
			int ktora;
			cout << "Dla ktorej reki chcesz spasowac ?";
			cin >> ktora;
			if (ktora == 1)
				czyja_kolej_1 = 1;
			else 
				czyja_kolej_2 = 1;

			if (czyja_kolej_1 == 1 && czyja_kolej_2 == 1)
				czyja_kolej = 1;
		}		
		else
		    czyja_kolej = 1;
		break;
	case 3:
		if (tura != 1)               //Po pierwszym wyborze nie bedzie mozliwosci uzywania tego
		{
			cout << "Nie ma takiej opcji" << endl;
			czekaj(3);
			i--;
			break;
		}
		zetony -= stawka;
		stawka = stawka * 2;
		tura++;
		i--;
		break;
	case 4:
		if (tura != 1 || grajace[0].figura != grajace[1].figura)               //Po pierwszym wyborze nie bedzie mozliwosci uzywania tego
		{
			cout << "Nie ma takiej opcji" << endl;
			czekaj(3);
			i--;
			break;
		}
		zetony -= stawka;
		stawka = stawka * 2;
		split = 1;
		tura++;
		grajace_split[0] = grajace[1];		
		grajace[1].figura = 0;  grajace[1].kolor = 0;
		pkt_gracza = pkt_gracza / 2;
		pkt_gracza_2 = pkt_gracza;
		
		for (int i = 1; i < 11; i++)
		{
			grajace_split[i].kolor = 0;
			grajace_split[i].figura = 0;
		}
		i = i - 2;

		break;
	default:
		cout << "Nie ma takiej opcji" << endl;
		czekaj(3);
		i--;
		break;
	}
}

int obstawianie(int &zetony)
{
	int x;

	cin >> x;

	if (x > zetony || x < 1)
	{
		while (x > zetony || x < 1)
		{
			cout << "Nie posiadasz tylu zetonow, podaj inna stawke" << endl;
			cin >> x;
		}
		zetony = zetony - x;
		return x;
	}

	else
	{
		zetony = zetony - x;                                                      //Aktualizacja posiadanych przez gracza zetonow
		return x;
	}
}

void dodaj_karte_gracza(karta talia[], int &pkt_gracza, karta &karta_1)
{
	losuj_karte(karta_1, talia);
	if (karta_1.figura <= 9)
		pkt_gracza += karta_1.figura;
	else if (karta_1.figura <= 13)
		pkt_gracza += 10;
	else if (pkt_gracza > 10)
		pkt_gracza += 1;
	else pkt_gracza += 11;
}

void dodaj_karte_krupiera(karta talia[], int &pkt_krupiera, karta &karta_1)
{
	losuj_karte(karta_1, talia);
	if (karta_1.figura <= 9)
		pkt_krupiera += karta_1.figura;
	else if (karta_1.figura <= 13)
		pkt_krupiera += 10;
	else if (pkt_krupiera > 10)
		pkt_krupiera += 1;
	else pkt_krupiera += 11;
}

void losuj_karte(karta &karta_1, karta talia[])
{
	int x = rand() % 156;
	karta_1 = talia[x];
}

void rysuj_karte(karta karta_1)
{ 
	for (int i = 0; i < 17; i++) cout << "-";                                   cout << endl;        //Gorna krawedz karty
	cout << "|"; wyswietl_figure(karta_1); cout << setw(14) << "|";             cout << endl;        //Linia pod gorna krawedzia
	cout << "|" << setw(16) << "|";                                             cout << endl;
	rysuj_kolor(karta_1);                                                       cout << endl;
	cout << "|" << setw(16) << "|";                                             cout << endl;
	cout << "|" << setw(13) << " "; wyswietl_figure(karta_1); cout << "|";      cout << endl;
	for (int i = 0; i < 17; i++) cout << "-";                                   cout << endl;
}

void wyswietl_figure(karta karta_1)
{
	if (karta_1.figura >= 2 && karta_1.figura <= 10)
	{		
		cout << setw(2) << karta_1.figura;
	}		

	else 
	{
		switch (karta_1.figura)
		{
		case 11:
			cout << setw(2) << 'W';
			break;
		case 12:
			cout << setw(2) << 'D';
			break;
		case 13:
			cout << setw(2) << 'K';
			break;
		case 14:
			cout << setw(2) << 'A';
			break;
		}	
	}
}

void rysuj_pusta()
{
	for (int i = 0; i < 17; i++) cout << "-"; cout << endl;
	for (int i = 0; i < 9; i++)
	{		
		cout << "|";
		for (int j = 0; j < 15; j++)
			cout << " ";
		cout << "|";		
		cout << endl;
	}	
	for (int i = 0; i < 17; i++) cout << "-"; cout << endl;
}

void rysuj_kolor(karta karta_1)
{	
	switch (karta_1.kolor)
	{
	case 1: //Karo
		cout << "|" << setw(8) << "*" << setw(8) << "|" << endl;
		cout << "|" << setw(9) << "***" << setw(7) << "|" << endl;
		cout << "|" << setw(10) << "*****" << setw(6) << "|" << endl;
		cout << "|" << setw(9) << "***" << setw(7) << "|" << endl;
		cout << "|" << setw(8) << "*" << setw(8) << "|";
		break;
	case 2: //Wino
		cout << "|" << setw(8) << "*" << setw(8) << "|" << endl;
		cout << "|" << setw(9) << "***" << setw(7) << "|" << endl;
		cout << "|" << setw(10) << "*****" << setw(6) << "|" << endl;
		cout << "|" << setw(11) << "*  *  *" << setw(5) << "|" << endl;
		cout << "|" << setw(9) << "***" << setw(7) << "|";
	
		break;
	case 3: //Kier
		cout << "|" << setw(10) << "*   *" << setw(6) << "|" << endl;
		cout << "|" << setw(11) << "*** ***" << setw(5) << "|" << endl;
		cout << "|" << setw(10) << "*****" << setw(6) << "|" << endl;
		cout << "|" << setw(9) << "***" << setw(7) << "|" << endl;
		cout << "|" << setw(8) << "*" << setw(8) << "|";
		break;
	case 4: //Trefl
		cout << "|" << setw(9) << "***" << setw(7) << "|" << endl;
		cout << "|" << setw(9) << "***" << setw(7) << "|" << endl;
		cout << "|" << setw(11) << "*******" << setw(5) << "|" << endl;
		cout << "|" << setw(11) << "*******" << setw(5) << "|" << endl;
		cout << "|" << setw(8) << "*" << setw(8) << "|";
		break;
	}
}

void rysuj_interface(karta grajace[], int stawka, int zetony, int pkt_gracza, int pkt_gracza_2, int pkt_krupiera, int czyja_kolej, int split, karta grajace_split[])
{
	system("cls");

	rysuj_statystyki(stawka, zetony);

	cout << setw(30) << "Twoje karty:" << endl << endl;
		
	for (int i = 0; i < 11; i++)
	{
		if (grajace[i].figura != 0)
			rysuj_karte(grajace[i]);
		else
			break;
	}
	cout << "Twoje punkty: " << pkt_gracza << endl << endl;
	cout << "-------------------------------------------" << endl << endl;
	
	if (split == 1)
	{
		for (int i = 0; i < 11; i++)
		{
			if (grajace_split[i].figura != 0)
				rysuj_karte(grajace_split[i]);
			else
				break;			
		}
		cout << "Twoje punkty: " << pkt_gracza_2 << endl << endl;
		cout << "-------------------------------------------" << endl << endl;
	}

	cout << endl << setw(30) << "Karty krupiera: " << endl;

	for (int i = 11; i < 19; i++)
	{
		if (grajace[i].figura != 0)
			rysuj_karte(grajace[i]);
		else
			break;
	}

	if (czyja_kolej == 0)
		rysuj_pusta();

	cout << "Punkty krupiera: " << pkt_krupiera << endl << endl;
	cout << "-------------------------------------------" << endl << endl;
}

void rysuj_statystyki(int stawka, int zetony)
{
	cout << "Aktualna stawka: " << stawka;
	cout << setw(50) << "Pozostale zetony: " << zetony << endl << endl;
}

void pisz_menu(int tura, int stawka, int zetony, karta grajace[])
{
	cout << "Co chcesz zrobic? " << endl << endl;
	cout << "1. Dobrac karte (hit)" << endl;
	cout << "2. Nie dobierac karty (stand)" << endl;
	if (tura == 1)
	{
		if (stawka * 2 < zetony) cout << "3. Podwoic stawke (double down)" << endl;
		if (grajace[0].figura == grajace[1].figura) cout << "4. Rozdwoic karty (split)" << endl;
	}
}

int sprawdzenie(int pkt_gracza, int pkt_gracza_2, int split)
{
	if (split != 1)
	{
		if (pkt_gracza == 21) return 1;
		else if (pkt_gracza < 21) return 0;
		else if (pkt_gracza > 21) return -1;
	}
	else
	{
		if(pkt_gracza == 21 && pkt_gracza_2 == 21) return 1;
		if (pkt_gracza > 21 && pkt_gracza_2 > 21) return -1;
		else return 0;
	}
	
}

void krupier(karta grajace[], int stawka, int zetony, int pkt_gracza, int pkt_gracza_2, int &pkt_krupiera, karta talia[], int czyja_kolej, int split, karta grajace_split[])
{
	int k = 13;

	dodaj_karte_krupiera(talia, pkt_krupiera, grajace[12]);
	rysuj_interface(grajace, stawka, zetony, pkt_gracza, pkt_gracza_2, pkt_krupiera, czyja_kolej, split, grajace_split);

	
	while (pkt_krupiera < 17 && k < 19)
	{
		dodaj_karte_krupiera(talia, pkt_krupiera, grajace[k]);
		rysuj_interface(grajace, stawka, zetony, pkt_gracza, pkt_gracza_2, pkt_krupiera, czyja_kolej, split, grajace_split);
		k++;
	}
	
}

void podsumowanie(int &pkt_gracza, int &pkt_gracza_2, int &pkt_krupiera, int &zetony, int stawka, int &czyja_kolej, int &tura, karta grajace[], int &split, karta grajace_split[])
{
	if (split == 1) cout << "Dla pierwszej rozgrywki: " << endl;	
	podsumowanie_1(pkt_gracza, pkt_krupiera, zetony, stawka);

	if (split == 1)
	{
		cout << "Dla drugiej rozgrywki: " << endl;
		podsumowanie_1(pkt_gracza_2, pkt_krupiera, zetony, stawka);
	}
	
	czyja_kolej = 0;
	tura = 1;
	pkt_gracza = 0;
	pkt_krupiera = 0;	
	split = 0;

	for (int i = 0; i < 19; i++)
	{
		grajace[i].figura = 0;
		grajace[i].kolor = 0;
	}

	for (int i = 0; i < 11; i++)
	{
		grajace_split[i].figura = 0;
		grajace_split[i].kolor = 0;
	}
}

void podsumowanie_1(int &pkt_gracza, int &pkt_krupiera, int &zetony, int stawka)
{
	if (pkt_gracza > 21)
	{
		cout << "Przegrales - tracisz postawione pieniadze" << endl << endl;
	}

	else
	{
		if (pkt_krupiera > 21)
		{
			zetony = zetony + stawka * 2;
			cout << "Gratulacje wygrales " << stawka << " zetonow!" << endl << endl;
		}
		else
		{
			if (pkt_gracza > pkt_krupiera)
			{
				zetony = zetony + stawka * 2;
				cout << "Gratulacje wygrales " << stawka << " zetonow!" << endl << endl;
			}
			else if (pkt_gracza == pkt_krupiera)
			{
				zetony += stawka;
				cout << "Remis - otrzymujesz zwrot wartosci zakladu!" << endl << endl;
			}
			else if (pkt_gracza < pkt_krupiera)
			{
				cout << "Przegrales - tracisz postawione pieniadze!" << endl << endl;
			}
		}
	}
}

void czekaj(int czas)
{
	time_t ile = time(0);
	while ((time(0) - ile) < czas);
}
