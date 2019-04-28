#include "Kayttoliittyma.h"
#include <algorithm>
#include <list>
#include <iterator>
#include <iostream>
#include <vector>
using namespace std;

void printList(vector<Siirto> lista)
{
	int i = 1;

	for (Siirto siirto : lista)
	{
		wcout << i << ". ";
		if (siirto.onkoLyhytLinna())
		{
			wcout << " 0-0";
		}
		else if (siirto.onkoPitkälinna())
		{
			wcout << " 0-0-0";
		}
		else
		{
			wcout << " ";
			wcout << (char)(siirto.getAlkuruutu().getSarake() + 97) << siirto.getAlkuruutu().getRivi() + 1 << "-" << (char)(siirto.getLoppuruutu().getSarake() + 97) << siirto.getLoppuruutu().getRivi() + 1;
		}
		wcout << endl;
		i++;
	}
}

 int main()
{
	
	bool tietokonePelaaja = false;
	string vastaus;
	string aloitusSiirtoVuoro = "0";

	//Kysytään pelaajan mielipidettä aloittajasta
	wcout << "Annetaanko tietokoneen suorittaa siirtonsa automaattisesti? (k/e) ";
	getline(cin, vastaus);
	if (vastaus == "K" || vastaus == "k")
	{
		tietokonePelaaja = true;
		wcout << "Pelataanko valkeilla(0) vai mustilla(1)?\n";
		getline(cin, aloitusSiirtoVuoro);
	}
	wcout << "Kirjoittamalla 'palautus' voidaan palata aikaisempaan asemaan.\n";

	//Tähän talletetaan tehdyt siirrot, voidaan palata mihin tahansa pelitilanteeseen takaisin.
	vector<Siirto> tehdytSiirrot;

	Asema asema = Asema();
	Kayttoliittyma kayttoliittyma = Kayttoliittyma(&asema);
	kayttoliittyma.piirraLauta();


	while (1)
	{
		list<Siirto> laillisetSiirrot;
		kayttoliittyma._asema->annaLaillisetSiirrot(laillisetSiirrot);
		kayttoliittyma._asema->onkoShakki(laillisetSiirrot);
		wcout << endl;

		wcout << "Laillisten siirtojen määrä: " << laillisetSiirrot.size() << endl;

		MinMaxPaluu parasValinta;
		if (asema.getSiirtovuoro() == 0)
		{
			parasValinta = asema.minimax(3, true);
		}
		else
		{
			parasValinta = asema.minimax(3, false);
		}

		//wcout << "\nMinimax-arvo: " << parasValinta._evaluointiArvo << "\n";
		//wcout << "\nEvaluointien määrä: " << asema.alphaBetaCounter << endl;
		asema.alphaBetaCounter = 0;
		Siirto parasSiirto = parasValinta._parasSiirto;
		//wcout << "Paras siirto: " << (char)(parasSiirto.getAlkuruutu().getSarake() + 97) << parasSiirto.getAlkuruutu().getRivi() + 1 <<
		//	"-" << (char)(parasSiirto.getLoppuruutu().getSarake() + 97) << parasSiirto.getLoppuruutu().getRivi() + 1 << endl << endl;

		if (laillisetSiirrot.size() == 0)
		{
			if (parasValinta._evaluointiArvo == 1000000)
			{
				wcout << "\nValkoinen voitti!\n";
			}
			else if (parasValinta._evaluointiArvo == -1000000)
			{
				wcout << "\nMusta voitti!\n";
			}
			else
			{
				wcout << "\nTasapeli.\n";
			}
			break;
		}


		Siirto* siirto;
		if (!tietokonePelaaja || ((asema.getSiirtovuoro() == 1 && aloitusSiirtoVuoro == "1") || (asema.getSiirtovuoro() == 0 && aloitusSiirtoVuoro == "0")))
		{
			do
			{
				siirto = kayttoliittyma.annaVastustajanSiirto();

				if (siirto != nullptr)
				{
					if (siirto->_palautus)
					{
						break;
					}

					bool found = (find(laillisetSiirrot.begin(), laillisetSiirrot.end(), siirto) != laillisetSiirrot.end());
					if (!found)
					{
						wcout << "\nLaiton siirto\n";
						siirto = nullptr;
					}
				}
			} while (siirto == nullptr);
		}
		else
		{
			siirto = &parasSiirto;
		}

		if	(siirto->_palautus)
		{
			printList(tehdytSiirrot);
			wcout << "Valitse siirto johon palataan: ";
			int palautusAsema;
			int poistettavatSiirrot;
			int tehdtyjenSiirtojenMaara = tehdytSiirrot.size();
			wcin >> palautusAsema;
			poistettavatSiirrot = tehdtyjenSiirtojenMaara - palautusAsema;
			if ((unsigned)palautusAsema > tehdtyjenSiirtojenMaara)
			{
				poistettavatSiirrot = 0;
				palautusAsema = tehdtyjenSiirtojenMaara;
			}
			asema.alustaAsema();
			for (int i = 0;i<palautusAsema; i++)
			{
				asema.paivitaAsema(&tehdytSiirrot[i], true);
				asema.setSiirtovuoro();
			}
			for (int i = 0; i < poistettavatSiirrot; i++)
			{
				tehdytSiirrot.pop_back();
			}

		}
		else
		{
			tehdytSiirrot.push_back(*siirto);

			kayttoliittyma._asema->paivitaAsema(siirto, false);

			kayttoliittyma._asema->setSiirtovuoro();
		}

		kayttoliittyma.piirraLauta();
	}

	wcout << "Peli on päättynyt";
	cin.ignore();

	return 0;
}