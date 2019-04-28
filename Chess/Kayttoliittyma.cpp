#include "Kayttoliittyma.h"
#include <iostream>
#include <fcntl.h>
#include <Windows.h>
#include <io.h>
#include <string>

using namespace std;

Kayttoliittyma::Kayttoliittyma(Asema* asema)
{
	_asema = asema;
}

void Kayttoliittyma::piirraLauta()
{
	_setmode(_fileno(stdout), _O_U16TEXT);

	for (int y = 7; y > -1; y--)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED);
		wcout << y + 1;
		
		for (int x = 0; x < 8; x++)
		{

			if (y % 2 == 0)
			{
				if (x % 2 == 0)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
					if (_asema->_lauta[y][x] == nullptr)
					{
						wcout << "  ";
					}
					else
					{
						wcout << _asema->_lauta[y][x]->getUnicode() << " ";
					}
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED);
					if (_asema->_lauta[y][x] == nullptr)
					{
						wcout << "  ";
					}
					else
					{
						wcout << _asema->_lauta[y][x]->getUnicode() << " ";
					}
				}
			}
			else
			{
				if (x % 2 != 0)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
					if (_asema->_lauta[y][x] == nullptr)
					{
						wcout << "  ";
					}
					else
					{
						wcout << _asema->_lauta[y][x]->getUnicode() << " ";
					}
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED);
					if (_asema->_lauta[y][x] == nullptr)
					{
						wcout << "  ";
					}
					else
					{
						wcout << _asema->_lauta[y][x]->getUnicode() << " ";
					}
				}
			}
		}
		wcout << endl;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED);
	wcout << " a b c d e f g h";
}

Siirto* Kayttoliittyma::annaVastustajanSiirto()
{
	string komento;
	wcout << "Siirto: ";
	getline(cin, komento);

	int pituus = komento.length();
	Siirto* siirto = nullptr;

	if (pituus == 6)
	{
		if (komento[1] >= 'a' && komento[1] <= 'h' && komento[2] >= '1' && komento[2] <= '8' &&
			komento[4] >= 'a' && komento[4] <= 'h' && komento[5] >= '1' && komento[5] <= '8')
		{
			bool laillinenSiirto = false;

			switch (komento[0])
			{
			case 'T':
				laillinenSiirto = true;
				break;
			case 'R':
				laillinenSiirto = true;
				break;
			case 'L':
				laillinenSiirto = true;
				break;
			case 'D':
				laillinenSiirto = true;
				break;
			case 'K':
				laillinenSiirto = true;
				break;
			default:
				break;
			}

			if (laillinenSiirto)
			{
				return Siirtaminen(komento, 0);
			}
		}

		return siirto;
		
	}
	else if (pituus == 5)
	{
		if (komento == "0-0-0")
		{
			siirto = new Siirto(false, true);
			return siirto;
		}
		else
		{
			if (komento[0] >= 'a' && komento[0] <= 'h' && komento[1] >= '1' && komento[1] <= '8' &&
				komento[3] >= 'a' && komento[3] <= 'h' && komento[4] >= '1' && komento[4] <= '8')
			{
				return Siirtaminen(komento, 1);
			}
		}
	}
	else if (komento == "0-0")
	{
		siirto = new Siirto(true, false);
	}
	else if (komento == "palautus")
	{
		siirto = new Siirto(true);
	}

	return siirto;
}

Siirto* Kayttoliittyma::Siirtaminen(string komento, int i)
{
	int rivi1 = (int)komento[2-i] - 49;
	int sarake1 = (int)komento[1-i] - 97;
	int rivi2 = (int)komento[5-i] - 49;
	int sarake2 = (int)komento[4-i] - 97;

	Ruutu alkuRuutu = Ruutu(rivi1, sarake1);
	Ruutu loppuRuutu = Ruutu(rivi2, sarake2);

	return new Siirto(alkuRuutu, loppuRuutu, false);
}