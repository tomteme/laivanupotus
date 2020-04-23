#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <windows.h>
#include <algorithm>
using namespace std;

const int LAIVOJEN_LKM = 4; //Laivojen lukumäärä
const int LAIVA_KOKO = 5;
const int RIVIT = 7; //Rivit
const int SARAKKEET = 7; //Sarakkeet
const char AAKKOSET[RIVIT] = {'A','B','C','D','E','F','G'};
	
void pelaa(int peliLauta[][SARAKKEET]);
void syotalaivat(int peliLauta[][SARAKKEET]);
void paljastasijainnit(int peliLauta[][SARAKKEET]);
void ammunta(int peliLauta[][SARAKKEET]);
void laivarikki(int peliLauta[][SARAKKEET]);
void satunnaislaivat(int peliLauta[][SARAKKEET]);
void tallennus(int peliLauta[][SARAKKEET]);
void lataapeli(int peliLauta[][SARAKKEET]);
void upotuslaskuri(int peliLauta[][SARAKKEET]);
void upotuslaskuriosumasta(int peliLauta[][SARAKKEET]);
void ohjelmapelaa(int peliLauta[][SARAKKEET]);
void ohjelmaammunta(int peliLauta[][SARAKKEET]);
void tietojenresetointi(int peliLauta[][SARAKKEET]);
void tilastot();
void osumisJakso();
struct koordinaatit
{
	int x;
	int y;
} alku,loppu;

struct ampumiskoordinaatit
{
	char x;
	char y;
} pum;

struct laivaelamat
{
	int laivatelossa;
	int viisi;
	int nelja;
	int kolme;
	int kaksi;
} laiva;
struct autotallennus
{
	int kytkin;
} tallentamis,simulaatio;

struct laskuri
{
	string jarjestys; 
	int laivat, alku, loppu, laskuri;
	int viisi, nelja, kolme, kaksi, tehokkain;
	float suhdeviisi, suhdenelja, suhdekolme, suhdekaksi;
}laukaus,osuma,upotus,ohi, suurempiohi, osumisjakso;

void paavalikko()
{
	int peliLauta[RIVIT][SARAKKEET] = { };
	char valinta;

do {
		
system("cls");
cout << laiva.laivatelossa << " " << laiva.viisi << laiva.nelja << laiva.kolme << laiva.kaksi << endl;
cout << alku.x << " " << alku.y << endl;
cout << tallentamis.kytkin << endl;
cout << upotus.jarjestys << endl;

cout <<
"Laivanupotuspeli\n\
================\n\
\n\
Valinnat:\n                                  Huom. automaattitallennus on ";
if (tallentamis.kytkin == 0)
{
	cout << "PAALLA ";
}
else
{
	cout << "POISSA PAALTA ";
}
cout <<
"\n\
1) Syota laivat\n\
2) Pelaa\n\
3) Arvo laivojen sijainnit\n\
4) Ampumisen simulaatio\n\
4) Tallenna peli\n\
5) Lataa peli\n\
T) Automaatti tallennus paalle/pois\n\
L) Lopeta\n\
\n\
Valintasi : ";

		cin >> valinta;
		switch (valinta)
		{
		case '1': syotalaivat(peliLauta);
			      break;
		case '2': pelaa(peliLauta);
			      break;
		case '3': satunnaislaivat(peliLauta);
			      break;
		case '4': ohjelmapelaa(peliLauta);
				  break;
		case '5': lataapeli(peliLauta);
				  break;
		case 't':
		case 'T': if (tallentamis.kytkin == 1)
				{
					tallentamis.kytkin = 0;
				}
				else
				{
					tallentamis.kytkin = 1;
				}
				break;
		case 'l':
		case 'L': cout << "\nPoistutaan ohjelmasta." << endl << endl;
				  system("pause");
				  exit(0);
			      break;
		default:  cerr << "\nLaiton valinta, syota uudelleen!\n\n";
				  system("pause");
				  break;
		}		
	} while ('L' != toupper(valinta));
}

void pelaa(int peliLauta[][SARAKKEET])
{
	char koordinaatit[2] = { };
	if (alku.x == 0 && loppu.x == 0)
	{
		cout << "Et ole viela sijoittanut laivoja." << endl;
		system("pause");
	}
	else if(laiva.laivatelossa == -1)
	{
		cout << "Olet jo upottanut nama laivat, sijoita uudet ja yrita uudelleen!" << endl;
		system("pause");
	}
	else
	{
	for (laiva.laivatelossa; laiva.laivatelossa >= 0;)
	{
		if(laiva.viisi == 0 || laiva.nelja == 0 || laiva.kolme == 0 || laiva.kaksi == 0)
		{
			laivarikki(peliLauta);
		}
		else if (laiva.laivatelossa == 0)
		{
				cout << "   1 2 3 4 5 6 7" << endl;
	cout << " -----------------" << endl;
		for (int i = 0; i < RIVIT; i++) 
	{
		cout << AAKKOSET[i] << "|" << ' ';
		for (int j = 0; j < SARAKKEET; j++) 
		{
			if (peliLauta[i][j] == 6)
			{
				cout << "X" << " "; 
			}
			else if (peliLauta[i][j] == 7 || peliLauta[i][j] == 8 ||peliLauta[i][j] == 9 ||peliLauta[i][j] == 10)
			{
				cout << "*" << " ";
			}
			else if (peliLauta[i][j] == 11 ||peliLauta[i][j] == 12 ||peliLauta[i][j] == 13 ||peliLauta[i][j] == 14)
			{
				cout << "#" << " ";
			}
			else
			{
			cout << "0" << " ";
			}
		}
		cout << '|' << AAKKOSET[i] << endl;
	}
	cout << " -----------------" << endl;
	cout << "   1 2 3 4 5 6 7" << endl;
	cout << endl;
	cout << "Onnittelut voitit pelin!" << endl;
		system("pause");
		laiva.laivatelossa = laiva.laivatelossa -1;
		if (tallentamis.kytkin == 0)
		{
		tallennus(peliLauta);
		}
			tilastot();
		}
		else
	{
	cout << "Pelitilanne on seuraava:" << endl;
	cout << laiva.kaksi << endl;
	cout << endl;
	cout << "   1 2 3 4 5 6 7" << endl;
	cout << " -----------------" << endl;
		for (int i = 0; i < RIVIT; i++) 
	{
		cout << AAKKOSET[i] << "|" << ' ';
		for (int j = 0; j < SARAKKEET; j++) 
		{
			if (peliLauta[i][j] == 6)
			{
				cout << "X" << " "; 
			}
			else if (peliLauta[i][j] == 7 || peliLauta[i][j] == 8 ||peliLauta[i][j] == 9 ||peliLauta[i][j] == 10)
			{
				cout << "*" << " ";
			}
			else if (peliLauta[i][j] == 11 ||peliLauta[i][j] == 12 ||peliLauta[i][j] == 13 ||peliLauta[i][j] == 14)
			{
				cout << "#" << " ";
			}
			else
			{
			cout << "0" << " ";
			}
		}
		cout << '|' << AAKKOSET[i] << endl;
	}
	cout << " -----------------" << endl;
	cout << "   1 2 3 4 5 6 7" << endl;
	cout << endl;
	cout << "Syota ampumiskoordinaatit: ";
	cin >> koordinaatit;
	pum.y = toupper(koordinaatit[0]);
	pum.x = koordinaatit[1];
	alku.y = koordinaatit[0];
	alku.x = koordinaatit[1] - '0' - 1;
	if (koordinaatit[0] == 'p' || koordinaatit[0] == 'P')
	{
		break;
	}
	else 
	{
	if (alku.y == 92 && alku.x == 15)
	{
		paljastasijainnit(peliLauta);
	}
				
	else if (alku.y >= 97 && alku.y <= 103)
		{
			alku.y = alku.y - 97;
		}
		else if (alku.y >= 65 && alku.y <= 71)
		{
			alku.y = alku.y - 65;
		}

		if (alku.y < 0 || alku.y > 6)
		{
			cout << "Virheelliset koordinaatit." << endl;
		}
		else if (alku.x < 0 || alku.x > 6)
		{
			cout << "Virheelliset koordinaatit." << endl;
		}
		else
		{
			ammunta(peliLauta);
		}

	}
	if (tallentamis.kytkin == 0)
	{
		tallennus(peliLauta);
	}
}
	}
}
}

void ohjelmapelaa(int peliLauta[][SARAKKEET])
{
	if (alku.x == 0 && loppu.x == 0)
	{
		cout << "Et ole viela sijoittanut laivoja." << endl;
		system("pause");
	}
	else if(laiva.laivatelossa == -1)
	{
		cout << "Kaikki laivat ovat jo uponneet, syotathan uudet." << endl;
		system("pause");
	}
	else
	{
	cout << "Kuinka suuren aikavalin haluat ammuntojen valille? (1-5sek, 0 mikali tahdot itse paattaa)" << endl;
	cin >> simulaatio.kytkin;
	if (simulaatio.kytkin > 5 || simulaatio.kytkin < 0)
	{
		cout << "Virheellinen aikavali." << endl;
		system("pause");
	}
	else
		{
	for (laiva.laivatelossa; laiva.laivatelossa >= 0;)
	{
		if(laiva.viisi == 0 || laiva.nelja == 0 || laiva.kolme == 0 || laiva.kaksi == 0)
		{
			laivarikki(peliLauta);
		}
		else if (laiva.laivatelossa == 0)
		{
			cout << "Simulaatio ohi!" << endl;
				cout << "   1 2 3 4 5 6 7" << endl;
	cout << " -----------------" << endl;
		for (int i = 0; i < RIVIT; i++) 
	{
		cout << AAKKOSET[i] << "|" << ' ';
		for (int j = 0; j < SARAKKEET; j++) 
		{
			if (peliLauta[i][j] == 6)
			{
				cout << "X" << " "; 
			}
			else if (peliLauta[i][j] == 7 || peliLauta[i][j] == 8 ||peliLauta[i][j] == 9 ||peliLauta[i][j] == 10)
			{
				cout << "*" << " ";
			}
			else if (peliLauta[i][j] == 11 ||peliLauta[i][j] == 12 ||peliLauta[i][j] == 13 ||peliLauta[i][j] == 14)
			{
				cout << "#" << " ";
			}
			else
			{
			cout << "0" << " ";
			}
		}
		cout << '|' << AAKKOSET[i] << endl;
	}
	cout << " -----------------" << endl;
	cout << "   1 2 3 4 5 6 7" << endl;
	cout << endl;
			system("pause");
			laiva.laivatelossa = laiva.laivatelossa -1;
			if (tallentamis.kytkin == 0)
			{
				tallennus(peliLauta);
			}
			tilastot();
		}
		else
	{
		cout << laukaus.viisi << endl;
	cout << "Pelitilanne on seuraava:" << endl;
	cout << laiva.kaksi << endl;
	cout << endl;
	cout << "   1 2 3 4 5 6 7" << endl;
	cout << " -----------------" << endl;
		for (int i = 0; i < RIVIT; i++) 
	{
		cout << AAKKOSET[i] << "|" << ' ';
		for (int j = 0; j < SARAKKEET; j++) 
		{
			if (peliLauta[i][j] == 6)
			{
				cout << "X" << " "; 
			}
			else if (peliLauta[i][j] == 7 || peliLauta[i][j] == 8 ||peliLauta[i][j] == 9 ||peliLauta[i][j] == 10)
			{
				cout << "*" << " ";
			}
			else if (peliLauta[i][j] == 11 ||peliLauta[i][j] == 12 ||peliLauta[i][j] == 13 ||peliLauta[i][j] == 14)
			{
				cout << "#" << " ";
			}
			else
			{
			cout << "0" << " ";
			}
		}
		cout << '|' << AAKKOSET[i] << endl;
	}
	cout << " -----------------" << endl;
	cout << "   1 2 3 4 5 6 7" << endl;
	cout << endl;
	if (simulaatio.kytkin == 0)
	{
	system("pause");
	}
	ohjelmaammunta(peliLauta);
	if (tallentamis.kytkin == 0)
	{
		tallennus(peliLauta);
	}
}
	}
}
}
}	
void syotalaivat(int peliLauta[][SARAKKEET])
{	
	tietojenresetointi(peliLauta);	
	char koordinaatit[2] = { };
	char valinta;
	for (int i = 0; i < LAIVOJEN_LKM; i++)
	{
		cout << "Syota " << LAIVA_KOKO - i << " pituisen laivan alkukoordinaatti: ";
		cin >> koordinaatit;
		alku.y = koordinaatit[0];
		alku.x = koordinaatit[1] - '0' - 1;
		
		
		if (alku.y >= 97 && alku.y <= 103)
		{
			alku.y = alku.y - 97;
		}
		else if (alku.y >= 65 && alku.y <= 71)
		{
			alku.y = alku.y - 65;
		}

		if (alku.y < 0 || alku.y > 6)
		{
			cout << "Virheelliset koordinaatit." << endl;
			i--;
		}
		else if (alku.x < 0 || alku.x > 6)
		{
			cout << "Virheelliset koordinaatit." << endl;
			i--;
		}
		else
		{
		
			cout << "Anna suunta (p(ohjoinen)/i(ta)/l(ansi)/e(tela): ";
			cin >> valinta;
			valinta = (toupper(valinta));
			if (valinta == 'P')
			{
				loppu.y = alku.y - LAIVA_KOKO + i+1;
				while(alku.y >= loppu.y)
				{
					if (loppu.y < 0 || loppu.y > 6)
					{
						cout << "Laiva menee kentan yli." << endl;
						alku.y = loppu.y;
						i--;
					}
				else if (peliLauta[alku.y][alku.x] != 0)
						{
							cout << "Laiva menee paallekkain toisen laivan kanssa." << endl;
							
							
										for (int k = 0; k < RIVIT; k++) 
											{
												for (int l = 0; l < SARAKKEET; l++) 
													{
														if (peliLauta[k][l] == LAIVA_KOKO - i)
														{
															peliLauta[k][l] = 0;
														}
													}
											}	
							
							alku.y = loppu.y;
							i--;
						}
					else
							{
								peliLauta[alku.y][alku.x] = LAIVA_KOKO - i;
							}
							alku.y--;
				}
				
			}
			else if (valinta == 'I')
			{
				loppu.x = alku.x + LAIVA_KOKO - i -1;
				while(alku.x <= loppu.x)
				{
					if (loppu.x < 0 || loppu.x > 6)
					{
						cout << "Laiva menee kentan yli." << endl;
						alku.x = loppu.x;
						i--;
					}
					else if (peliLauta[alku.y][alku.x] != 0)
						{
							cout << "Laiva menee paallekkain toisen laivan kanssa." << endl;

										for (int k = 0; k < RIVIT; k++) 
											{
												for (int l = 0; l < SARAKKEET; l++) 
													{
														if (peliLauta[k][l] == LAIVA_KOKO - i)
														{
															cout << LAIVA_KOKO - i << endl;
															peliLauta[k][l] = 0;
														}
													}
											}
	
							alku.x = loppu.x;
							i--;
						}
					else
							{
								peliLauta[alku.y][alku.x] = LAIVA_KOKO - i;
							}
							alku.x++;	
				}
			}
			
			else if (valinta == 'L')
			{
				loppu.x = alku.x - LAIVA_KOKO + i + 1;
				while(alku.x >= loppu.x)
				{
					if (loppu.x < 0 || loppu.x > 6)
					{
						cout << "Laiva menee kentan yli." << endl;
						alku.x = loppu.x;
						i--;
					}
				else if (peliLauta[alku.y][alku.x] != 0)
						{
							cout << "Laiva menee paallekkain toisen laivan kanssa." << endl;

							
										for (int k = 0; k < RIVIT; k++) 
											{
												for (int l = 0; l < SARAKKEET; l++) 
													{
														if (peliLauta[k][l] == LAIVA_KOKO - i)
														{
															peliLauta[k][l] = 0;
														}
													}
											}
							
							alku.x = loppu.x;
		
							
							i--;
						}
					else
							{
								peliLauta[alku.y][alku.x] = LAIVA_KOKO - i;
							}
							alku.x--;
				}
				
			}
			
			
			else if (valinta == 'E')
			{
				loppu.y = alku.y + LAIVA_KOKO - i -1;
				while(alku.y <= loppu.y)
				{
					if (loppu.y < 0 || loppu.y > 6)
					{
						cout << "Laiva menee kentan yli." << endl;
						alku.y = loppu.y;
						i--;
					}
					else if (peliLauta[alku.y][alku.x] != 0)
						{
							cout << "Laiva menee paallekkain toisen laivan kanssa." << endl;
							
							
										for (int k = 0; k < RIVIT; k++) 
											{
												for (int l = 0; l < SARAKKEET; l++) 
													{
														if (peliLauta[k][l] == LAIVA_KOKO - i)
														{
															cout << LAIVA_KOKO - i << endl;
															peliLauta[k][l] = 0;
														}
													}
											}
							
							alku.y = loppu.y;
							i--;
							
						}
					else
							{
								peliLauta[alku.y][alku.x] = LAIVA_KOKO - i;
							}
							alku.y++;
				}
				
			}

			else
			{
				cout << "Virheellinen ilmansuunta." << endl;
				i--;
			}
	cout << "   1 2 3 4 5 6 7" << endl;
	cout << " -----------------" << endl;
	for (int i = 0; i < RIVIT; i++) 
	{
		cout << AAKKOSET[i] << "|" << ' ';
		for (int j = 0; j < SARAKKEET; j++) 
		{
			cout << peliLauta[i][j] << " ";
		}
		cout << '|' << AAKKOSET[i] << endl;
	}
	cout << " -----------------" << endl;
	cout << "   1 2 3 4 5 6 7" << endl;
		}		
	}
	system("pause");
}
void paljastasijainnit(int peliLauta[][SARAKKEET])
{
	cout << "   1 2 3 4 5 6 7" << endl;
	cout << " -----------------" << endl;
		for (int i = 0; i < RIVIT; i++) 
	{
		cout << AAKKOSET[i] << "|" << ' ';
		for (int j = 0; j < SARAKKEET; j++) 
		{
			if (peliLauta[i][j] == 2 ||peliLauta[i][j] == 7 ||peliLauta[i][j] == 11)
			{
			cout << "2" << " ";
			}
			else if (peliLauta[i][j] == 3 ||peliLauta[i][j] == 8 ||peliLauta[i][j] == 12)
			{
			cout << "3" << " ";
			}
			else if (peliLauta[i][j] == 4 ||peliLauta[i][j] == 9 ||peliLauta[i][j] == 13)
			{
			cout << "4" << " ";
			}
			else if (peliLauta[i][j] == 5 ||peliLauta[i][j] == 10 ||peliLauta[i][j] == 14)
			{
			cout << "5" << " ";
			}
			else
			{
			cout << "0" << " ";
			}
		}
		cout << '|' << AAKKOSET[i] << endl;
	}
	cout << " -----------------" << endl;
	cout << "   1 2 3 4 5 6 7" << endl;
	system("pause");
}

void ammunta(int peliLauta[][SARAKKEET])
{
	if (peliLauta[alku.y][alku.x] == 0)
	{
		cout << "Laukaus kohtaan " << pum.y << pum.x << " ei osunut" << endl;
		peliLauta[alku.y][alku.x] = 6;
		laukaus.laivat = laukaus.laivat + 1;
		ohi.laivat = ohi.laivat + 1;
		if (ohi.laskuri == 1)
		{
			ohi.loppu = laukaus.laivat;
			if (ohi.loppu - ohi.alku > suurempiohi.loppu - suurempiohi.alku)
			{
				suurempiohi.alku = ohi.alku;
				suurempiohi.loppu = ohi.loppu;
			}
		}
		else
		{
			ohi.alku = laukaus.laivat;
			ohi.loppu = laukaus.laivat;
			ohi.laskuri = 1;
		}
		upotuslaskuri(peliLauta);
		upotuslaskuriosumasta(peliLauta);
		
	}	
	else if (peliLauta[alku.y][alku.x] == 6 || peliLauta[alku.y][alku.x] == 7 ||peliLauta[alku.y][alku.x] == 8||peliLauta[alku.y][alku.x] == 9||
	peliLauta[alku.y][alku.x] == 10||peliLauta[alku.y][alku.x] == 11||peliLauta[alku.y][alku.x] == 12||peliLauta[alku.y][alku.x] == 13||peliLauta[alku.y][alku.x] == 14)
	{
		cout << "Olet ampunut jo tahan, koitas uudestaan." << endl;
	}
	else if (peliLauta[alku.y][alku.x] == 2)
	{
		laiva.kaksi = laiva.kaksi - 1;
		if (laiva.kaksi == 0)
		{
			cout << "Laukaus kohtaan " << pum.y << pum.x << " upotti laivan." << endl;
			peliLauta[alku.y][alku.x] = 7;
			laukaus.laivat = laukaus.laivat + 1;
			upotuslaskuriosumasta(peliLauta);
			upotuslaskuri(peliLauta);
			ohi.laskuri = 0;
			osuma.kaksi = 0;
		}
		else
		{
			cout << "Laukaus kohtaan " << pum.y << pum.x << " osui laivaan." << endl;
			peliLauta[alku.y][alku.x] = 7;
			osuma.kaksi = 1;
			laukaus.laivat = laukaus.laivat + 1;
			upotuslaskuriosumasta(peliLauta);
			upotuslaskuri(peliLauta);
			ohi.laskuri = 0;
		}
	}
		else if (peliLauta[alku.y][alku.x] == 3)
	{
		laiva.kolme = laiva.kolme - 1;
		if (laiva.kolme == 0)
		{
			cout << "Laukaus kohtaan " << pum.y << pum.x << " upotti laivan." << endl;
			peliLauta[alku.y][alku.x] = 8;
			laukaus.laivat = laukaus.laivat + 1;
			upotuslaskuriosumasta(peliLauta);
			upotuslaskuri(peliLauta);
			ohi.laskuri = 0;
			osuma.kolme = 0;
		}
		else
		{
			cout << "Laukaus kohtaan " << pum.y << pum.x << " osui laivaan." << endl;
			peliLauta[alku.y][alku.x] = 8;
			osuma.kolme = 1;
			laukaus.laivat = laukaus.laivat + 1;
			upotuslaskuriosumasta(peliLauta);
			upotuslaskuri(peliLauta);
			ohi.laskuri = 0;
		}
	}
		else if (peliLauta[alku.y][alku.x] == 4)
	{
		laiva.nelja = laiva.nelja - 1;
		if (laiva.nelja == 0)
		{
			cout << "Laukaus kohtaan " << pum.y << pum.x << " upotti laivan." << endl;
			peliLauta[alku.y][alku.x] = 9;
			laukaus.laivat = laukaus.laivat + 1;
			upotuslaskuriosumasta(peliLauta);;
			upotuslaskuri(peliLauta);
			osuma.nelja = 0;
			ohi.laskuri = 0;
		}
		else
		{
			cout << "Laukaus kohtaan " << pum.y << pum.x << " osui laivaan." << endl;
			peliLauta[alku.y][alku.x] = 9;
			osuma.nelja = 1;
			laukaus.laivat = laukaus.laivat + 1;
			upotuslaskuriosumasta(peliLauta);
			upotuslaskuri(peliLauta);
			ohi.laskuri = 0;
		}
	}
		else if (peliLauta[alku.y][alku.x] == 5)
	{
		laiva.viisi = laiva.viisi - 1;
		if (laiva.viisi == 0)
		{
			cout << "Laukaus kohtaan " << pum.y << pum.x << " upotti laivan." << endl;
			peliLauta[alku.y][alku.x] = 10;
			laukaus.laivat = laukaus.laivat + 1;
			upotuslaskuriosumasta(peliLauta);
			upotuslaskuri(peliLauta);
			osuma.viisi = 0;
			ohi.laskuri = 0;
		}
		else
		{
			cout << "Laukaus kohtaan " << pum.y << pum.x << " osui laivaan." << endl;
			peliLauta[alku.y][alku.x] = 10;
			osuma.viisi = 1;
			laukaus.laivat = laukaus.laivat + 1;
			upotuslaskuriosumasta(peliLauta);
			upotuslaskuri(peliLauta);
			ohi.laskuri = 0;
		}
	}
}

void ohjelmaammunta(int peliLauta[][SARAKKEET])
{
	srand((unsigned int)time(0));
	if (simulaatio.kytkin != 0)
	{
		Sleep(simulaatio.kytkin * 1000);
	}
	for (int laskuri = 0; laskuri < 1; laskuri++)
	{
		alku.y = rand() % 7;
		alku.x = rand() % 7;
		if (peliLauta[alku.y][alku.x] == 0)
	{
		peliLauta[alku.y][alku.x] = 6;
		laukaus.laivat = laukaus.laivat + 1;
		ohi.laivat = ohi.laivat + 1;
		if (ohi.laskuri == 1)
		{
			ohi.loppu = laukaus.laivat;
			if (ohi.loppu - ohi.alku > suurempiohi.loppu - suurempiohi.alku)
			{
				suurempiohi.alku = ohi.alku;
				suurempiohi.loppu = ohi.loppu;
			}
		}
		else
		{
			ohi.alku = laukaus.laivat;
			ohi.loppu = laukaus.laivat;
			ohi.laskuri = 1;
		}
		upotuslaskuri(peliLauta);
		upotuslaskuriosumasta(peliLauta);
		
	}	
	else if (peliLauta[alku.y][alku.x] == 6 || peliLauta[alku.y][alku.x] == 7 ||peliLauta[alku.y][alku.x] == 8||peliLauta[alku.y][alku.x] == 9||
	peliLauta[alku.y][alku.x] == 10||peliLauta[alku.y][alku.x] == 11||peliLauta[alku.y][alku.x] == 12||peliLauta[alku.y][alku.x] == 13||peliLauta[alku.y][alku.x] == 14)
	{
		laskuri--;
	}
	else if (peliLauta[alku.y][alku.x] == 2)
	{
		laiva.kaksi = laiva.kaksi - 1;
		if (laiva.kaksi == 0)
		{
			peliLauta[alku.y][alku.x] = 7;
			laukaus.laivat = laukaus.laivat + 1;
			upotuslaskuriosumasta(peliLauta);
			upotuslaskuri(peliLauta);
			ohi.laskuri = 0;
			osuma.kaksi = 0;
		}
		else
		{
			peliLauta[alku.y][alku.x] = 7;
			osuma.kaksi = 1;
			laukaus.laivat = laukaus.laivat + 1;
			upotuslaskuriosumasta(peliLauta);
			upotuslaskuri(peliLauta);
			ohi.laskuri = 0;
		}
	}
		else if (peliLauta[alku.y][alku.x] == 3)
	{
		laiva.kolme = laiva.kolme - 1;
		if (laiva.kolme == 0)
		{
			peliLauta[alku.y][alku.x] = 8;
			laukaus.laivat = laukaus.laivat + 1;
			upotuslaskuriosumasta(peliLauta);
			upotuslaskuri(peliLauta);
			ohi.laskuri = 0;
			osuma.kolme = 0;
		}
		else
		{
			peliLauta[alku.y][alku.x] = 8;
			osuma.kolme = 1;
			laukaus.laivat = laukaus.laivat + 1;
			upotuslaskuriosumasta(peliLauta);
			upotuslaskuri(peliLauta);
			ohi.laskuri = 0;
		}
	}
		else if (peliLauta[alku.y][alku.x] == 4)
	{
		laiva.nelja = laiva.nelja - 1;
		if (laiva.nelja == 0)
		{
			peliLauta[alku.y][alku.x] = 9;
			laukaus.laivat = laukaus.laivat + 1;
			upotuslaskuriosumasta(peliLauta);;
			upotuslaskuri(peliLauta);
			osuma.nelja = 0;
			ohi.laskuri = 0;
		}
		else
		{
			peliLauta[alku.y][alku.x] = 9;
			osuma.nelja = 1;
			laukaus.laivat = laukaus.laivat + 1;
			upotuslaskuriosumasta(peliLauta);
			upotuslaskuri(peliLauta);
			ohi.laskuri = 0;
		}
	}
		else if (peliLauta[alku.y][alku.x] == 5)
	{
		laiva.viisi = laiva.viisi - 1;
		if (laiva.viisi == 0)
		{
			peliLauta[alku.y][alku.x] = 10;
			laukaus.laivat = laukaus.laivat + 1;
			upotuslaskuriosumasta(peliLauta);
			upotuslaskuri(peliLauta);
			osuma.viisi = 0;
			ohi.laskuri = 0;
		}
		else
		{
			peliLauta[alku.y][alku.x] = 10;
			osuma.viisi = 1;
			laukaus.laivat = laukaus.laivat + 1;
			upotuslaskuriosumasta(peliLauta);
			upotuslaskuri(peliLauta);
			ohi.laskuri = 0;
		}
	}
  }
}
void laivarikki(int peliLauta[][SARAKKEET])
{
	if (laiva.viisi == 0)
	{
		for (int i = 0; i < RIVIT; i++) 
	{
		for (int j = 0; j < SARAKKEET; j++) 
		{
			if (peliLauta[i][j] == 10)
			{
				peliLauta[i][j] = 14;
			}
		}

	}
	laiva.viisi = 6;
	laiva.laivatelossa = laiva.laivatelossa - 1;
	upotus.jarjestys += '5';
	}
	
		else if (laiva.nelja == 0)
	{
		for (int i = 0; i < RIVIT; i++) 
	{
		for (int j = 0; j < SARAKKEET; j++) 
		{
			if (peliLauta[i][j] == 9)
			{
				peliLauta[i][j] = 13;
			}
		}

	}
	laiva.nelja = 6;
	laiva.laivatelossa = laiva.laivatelossa - 1;
	upotus.jarjestys += '4';
	}
	
	
		else if (laiva.kolme == 0)
	{
		for (int i = 0; i < RIVIT; i++) 
	{
		for (int j = 0; j < SARAKKEET; j++) 
		{
			if (peliLauta[i][j] == 8)
			{
				peliLauta[i][j] = 12;
			}
		}

	}
	laiva.kolme = 6;
	laiva.laivatelossa = laiva.laivatelossa - 1;
	upotus.jarjestys += '3';
	}
	
	
		else if (laiva.kaksi == 0)
	{
		for (int i = 0; i < RIVIT; i++) 
	{
		for (int j = 0; j < SARAKKEET; j++) 
		{
			if (peliLauta[i][j] == 7)
			{
				peliLauta[i][j] = 11;
			}
		}

	}	
	laiva.kaksi = 6;
	laiva.laivatelossa = laiva.laivatelossa - 1;
	upotus.jarjestys += '2';
	}
}

void satunnaislaivat(int peliLauta[][SARAKKEET])
{
	tietojenresetointi(peliLauta);
	int suunta = 0;
		for (int i = 0; i < LAIVOJEN_LKM; i++)
	{
		srand((unsigned int)time(0));
		alku.y = rand() % 7;
		alku.x = rand() % 7;
		suunta = rand() % 3;
		if (suunta == 0)
			{
				loppu.y = alku.y - LAIVA_KOKO + i+1;
				while(alku.y >= loppu.y)
				{
					if (loppu.y < 0 || loppu.y > 6)
					{
						alku.y = loppu.y;
						i--;
					}
				else if (peliLauta[alku.y][alku.x] != 0)
						{
							
							
										for (int k = 0; k < RIVIT; k++) 
											{
												for (int l = 0; l < SARAKKEET; l++) 
													{
														if (peliLauta[k][l] == LAIVA_KOKO - i)
														{
															peliLauta[k][l] = 0;
														}
													}
											}	
							
							alku.y = loppu.y;
							i--;
						}
					else
							{
								peliLauta[alku.y][alku.x] = LAIVA_KOKO - i;
							}
							alku.y--;
				}
				
			}
					
					else if (suunta == 1)
			{
				loppu.x = alku.x + LAIVA_KOKO - i -1;
				while(alku.x <= loppu.x)
				{
					if (loppu.x < 0 || loppu.x > 6)
					{
						alku.x = loppu.x;
						i--;
					}
					else if (peliLauta[alku.y][alku.x] != 0)
						{

										for (int k = 0; k < RIVIT; k++) 
											{
												for (int l = 0; l < SARAKKEET; l++) 
													{
														if (peliLauta[k][l] == LAIVA_KOKO - i)
														{
															peliLauta[k][l] = 0;
														}
													}
											}
	
							alku.x = loppu.x;
							i--;
						}
					else
							{
								peliLauta[alku.y][alku.x] = LAIVA_KOKO - i;
							}
							alku.x++;	
				}
			}
			
			
			
			
			
			
			else if (suunta == 2)
			{
				loppu.x = alku.x - LAIVA_KOKO + i + 1;
				while(alku.x >= loppu.x)
				{
					if (loppu.x < 0 || loppu.x > 6)
					{
						alku.x = loppu.x;
						i--;
					}
				else if (peliLauta[alku.y][alku.x] != 0)
						{

							
										for (int k = 0; k < RIVIT; k++) 
											{
												for (int l = 0; l < SARAKKEET; l++) 
													{
														if (peliLauta[k][l] == LAIVA_KOKO - i)
														{
															peliLauta[k][l] = 0;
														}
													}
											}
							
							alku.x = loppu.x;
		
							
							i--;
						}
					else
							{
								peliLauta[alku.y][alku.x] = LAIVA_KOKO - i;
							}
							alku.x--;
				}
				
			}
			
			
			
			
			
			
			else if (suunta == 3)
			{
				loppu.y = alku.y + LAIVA_KOKO - i -1;
				while(alku.y <= loppu.y)
				{
					if (loppu.y < 0 || loppu.y > 6)
					{
						alku.y = loppu.y;
						i--;
					}
					else if (peliLauta[alku.y][alku.x] != 0)
						{
							
							
										for (int k = 0; k < RIVIT; k++) 
											{
												for (int l = 0; l < SARAKKEET; l++) 
													{
														if (peliLauta[k][l] == LAIVA_KOKO - i)
														{
															peliLauta[k][l] = 0;
														}
													}
											}
							
							alku.y = loppu.y;
							i--;
							
						}
					else
							{
								peliLauta[alku.y][alku.x] = LAIVA_KOKO - i;
							}
							alku.y++;
				}
				
			}

	}
}

void tallennus(int peliLauta[][SARAKKEET])
{
	if (laiva.laivatelossa == -1)
	{
		if (tallentamis.kytkin == 0)
		{
			tietojenresetointi(peliLauta);
			laiva.laivatelossa = -1;
		}
		else
		{
		cout << "Et voi tallentaa loppuun pelattua pelia." << endl;
		system("pause");
		}
	}
	else
	{
	ofstream tallennus;
	tallennus.open("pelitilanne.txt");
	for (int k = 0; k < RIVIT; k++) 
	{
		for (int l = 0; l < SARAKKEET; l++) 
		{
			tallennus << peliLauta[k][l] << " ";
		}
		tallennus << endl;
	}
	tallennus << laiva.laivatelossa << "\n" << laiva.viisi << "\n" << laiva.nelja << "\n" << laiva.kolme<< "\n" << laiva.kaksi << endl;
	tallennus << alku.x << "\n" << alku.y << endl;
	tallennus.close();	
	}
}
void lataapeli(int peliLauta[][SARAKKEET])
{
	ofstream tallennus;
	ifstream inFile;
	inFile.open("pelitilanne.txt");
	if (!inFile)
	{
		cout << "Tallenusta ei voitu ladata, joko sita ei ole tai se on avattuna muualla." << endl;
		system("pause");
	}
	else
	{

		for (int k = 0; k < RIVIT; k++) 
	{
		for (int l = 0; l < SARAKKEET; l++) 
		{
			inFile >> peliLauta[k][l];
		}
	}
	inFile >> laiva.laivatelossa >> laiva.viisi >> laiva.nelja >> laiva.kolme >> laiva.kaksi >> alku.x >> alku.y;
	inFile >> alku.x >> alku.y;
	tallennus.close();
	}
}

void upotuslaskuri(int peliLauta[][SARAKKEET])
{
		if (laiva.viisi < 6)
		{
		upotus.viisi = upotus.viisi + 1;
		}
		if (laiva.nelja < 6)
		{
		upotus.nelja = upotus.nelja + 1;
		}
		if (laiva.kolme < 6)
		{
		upotus.kolme = upotus.kolme + 1;
		}
		if (laiva.kaksi < 6)
		{
		upotus.kaksi = upotus.kaksi + 1;
		}
}
void upotuslaskuriosumasta(int peliLauta[][SARAKKEET])
{
		if (osuma.viisi == 1)
		{
			laukaus.viisi = laukaus.viisi + 1;
		}
		if (osuma.nelja == 1)
		{
			laukaus.nelja = laukaus.nelja + 1;
		}
		if (osuma.kolme == 1)
		{
			laukaus.kolme = laukaus.kolme + 1;
		}
		if (osuma.kaksi == 1)
		{
			laukaus.kaksi = laukaus.kaksi + 1;
		}
}
void tilastot()
{
	system("cls");
	cout << "PELIN TILASTOT" << endl;
	cout << endl;
	cout << "Pelissa ammuttiin yhteensa " << laukaus.laivat << " laukausta." << endl;
	cout << "Laukauksista meni " << ohi.laivat << " ohi." << endl;
	cout << "Laukauksien maara 5 pituisen laivan upottamiseen pelin alusta alkaen oli " << upotus.viisi << " laukausta!" << endl;
	cout << "Laukauksien maara 4 pituisen laivan upottamiseen pelin alusta alkaen oli " << upotus.nelja << " laukausta!" << endl;
	cout << "Laukauksien maara 3 pituisen laivan upottamiseen pelin alusta alkaen oli " << upotus.kolme << " laukausta!" << endl;
	cout << "Laukauksien maara 2 pituisen laivan upottamiseen pelin alusta alkaen oli " << upotus.kaksi << " laukausta!" << endl;
	cout << endl;
	cout << "Laukauksien maara 5 pituisen laivan upottamiseen ensimmaisesta osumasta alkaen oli " << laukaus.viisi << " laukausta!" << endl;
	cout << "Laukauksien maara 4 pituisen laivan upottamiseen ensimmaisesta osumasta alkaen oli " << laukaus.nelja << " laukausta!" << endl;
	cout << "Laukauksien maara 3 pituisen laivan upottamiseen ensimmaisesta osumasta alkaen oli " << laukaus.kolme << " laukausta!" << endl;
	cout << "Laukauksien maara 2 pituisen laivan upottamiseen ensimmaisesta osumasta alkaen oli " << laukaus.kaksi << " laukausta!" << endl;
	cout << endl;
	cout << "Ensimmainen uponnut laiva oli " << upotus.jarjestys[0] << " pituinen laiva." << endl;
	cout << "Toiseksi uponnut laiva oli " << upotus.jarjestys[1] << " pituinen laiva." << endl;
	cout << "Kolmanneksi uponnut laiva oli " << upotus.jarjestys[2] << " pituinen laiva." << endl;
	cout << "Viimeiseksi uponnut laiva oli " << upotus.jarjestys[3] << " pituinen laiva." << endl;
	cout << endl;
	osumisJakso();
	cout << "Tehokkain osumisjakso oli laukaukset " << osuma.tehokkain << ". - " << upotus.tehokkain << ". joilla upotettiin " << osumisjakso.tehokkain << " pituinen laiva." << endl;
	cout << "Pisin ohilaukaus jakso oli ammunnat " << suurempiohi.alku << ". - " << suurempiohi.loppu << "." << endl;
	system("pause");
}
void osumisJakso()
{
	osumisjakso.suhdeviisi = laukaus.viisi / 5.0f;
	osumisjakso.suhdenelja = laukaus.nelja / 4.0f;
	osumisjakso.suhdekolme = laukaus.kolme / 3.0f;
	osumisjakso.suhdekaksi = laukaus.kaksi / 2.0f;
	if (osumisjakso.suhdeviisi < osumisjakso.suhdenelja && osumisjakso.suhdeviisi < osumisjakso.suhdekolme && osumisjakso.suhdeviisi < osumisjakso.suhdekaksi)
	{
		osuma.tehokkain = upotus.viisi - laukaus.viisi + 1;
		upotus.tehokkain = upotus.viisi;
		osumisjakso.tehokkain = 5;
	}
	if (osumisjakso.suhdenelja < osumisjakso.suhdeviisi && osumisjakso.suhdenelja < osumisjakso.suhdekolme && osumisjakso.suhdenelja < osumisjakso.suhdekaksi)
	{
		osuma.tehokkain = upotus.nelja - laukaus.nelja + 1;
		upotus.tehokkain = upotus.nelja;
		osumisjakso.tehokkain = 4;
	}
	if (osumisjakso.suhdekolme < osumisjakso.suhdeviisi && osumisjakso.suhdekolme < osumisjakso.suhdenelja && osumisjakso.suhdekolme < osumisjakso.suhdekaksi)
	{
		osuma.tehokkain = upotus.kolme - laukaus.kolme + 1;
		upotus.tehokkain = upotus.kolme;
		osumisjakso.tehokkain = 3;
	}
	if (osumisjakso.suhdekaksi < osumisjakso.suhdeviisi && osumisjakso.suhdekaksi < osumisjakso.suhdenelja && osumisjakso.suhdekaksi < osumisjakso.suhdekolme)
	{
		osuma.tehokkain = upotus.kaksi - laukaus.kaksi + 1;
		upotus.tehokkain = upotus.kaksi;
		osumisjakso.tehokkain = 2;
	}
}
void tietojenresetointi(int peliLauta[][SARAKKEET])
{
		for (int i = 0; i < RIVIT; i++)
		{
			for (int j = 0; j < SARAKKEET; j++)
			{
			peliLauta[i][j] = 0;
			}
		}
		laiva.viisi = 5;
		laiva.nelja = 4;
		laiva.kolme = 3;
		laiva.kaksi = 2;
		laiva.laivatelossa = 4;
		laukaus.laivat = 0;
		ohi.laivat = 0;
		upotus.viisi = 0;
		upotus.nelja = 0;
		upotus.kolme = 0;
		upotus.kaksi = 0;
		laukaus.viisi = 0;
		laukaus.nelja = 0;
		laukaus.kolme = 0;
		laukaus.kaksi = 0;
		osuma.tehokkain = 0;
		upotus.tehokkain = 0;
		osumisjakso.tehokkain = 0;
		suurempiohi.alku = 0;
		suurempiohi.alku = 0;
		ohi.alku = 0;
		ohi.loppu = 0;
}
int main()
{
	paavalikko();
}
