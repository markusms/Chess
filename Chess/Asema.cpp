#include <list>
#include <iostream>
#include <string>
#include "Asema.h"
#include "Kuningas.h"
#include "Daami.h"
#include "Torni.h"
#include "Lahetti.h"
#include "Ratsu.h"
#include "Sotilas.h"

using namespace std;

Asema::Asema()
{
	//Luodaan pelinappulat
	_vk = new Kuningas(L"\u2654", 0, VK);
	_vd = new Daami(L"\u2655", 0, VD);
	_vt = new Torni(L"\u2656", 0, VT);
	_vl = new Lahetti(L"\u2657", 0, VL);
	_vr = new Ratsu(L"\u2658", 0, VR);
	_vs = new Sotilas(L"\u2659", 0, VS);
	_mk = new Kuningas(L"\u265A", 1, MK);
	_md = new Daami(L"\u265B", 1, MD);
	_mt = new Torni(L"\u265C", 1, MT);
	_ml = new Lahetti(L"\u265D", 1, ML);
	_mr = new Ratsu(L"\u265E", 1, MR);
	_ms = new Sotilas(L"\u265F", 1, MS);

	alustaAsema();
}

void Asema::alustaAsema()
{
	_siirtovuoro = 0;
	_sotilaanKaksoissiirto = false;
	_onkoValkeaKuningasLiikkunut = false;
	_onkoMustaKuningasLiikkunut = false;
	_onkoValkeaDTLiikkunut = false;
	_onkoValkeaKTLiikkunut = false;
	_onkoMustaDTLiikkunut = false;
	_onkoMustaKTLiikkunut = false;
	_viimeinenSiirto = nullptr;

	//Alustetaan pelilauta tyhjill‰ ruuduilla
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			_lauta[y][x] = nullptr;
		}
	}

	//Lis‰t‰‰n sotilaat
	for (int x = 0; x < 8; x++)
	{
		_lauta[1][x] = _vs;
	}
	for (int x = 0; x < 8; x++)
	{
		_lauta[6][x] = _ms;
	}

	//Asetetaan muut nappulat
	_lauta[0][0] = _vt;
	_lauta[0][1] = _vr;
	_lauta[0][2] = _vl;
	_lauta[0][3] = _vd;
	_lauta[0][4] = _vk;
	_lauta[0][5] = _vl;
	_lauta[0][6] = _vr;
	_lauta[0][7] = _vt;

	_lauta[7][0] = _mt;
	_lauta[7][1] = _mr;
	_lauta[7][2] = _ml;
	_lauta[7][3] = _md;
	_lauta[7][4] = _mk;
	_lauta[7][5] = _ml;
	_lauta[7][6] = _mr;
	_lauta[7][7] = _mt;
}

//P‰ivitet‰‰n pelilauta annetulla siirrolla
void Asema::paivitaAsema(Siirto* siirto, bool tarkistus)
{
	if (siirto->onkoLyhytLinna())
	{
		//Suoritetaan lyhyt linnoitus, mik‰li sallittua
		if (_siirtovuoro)
		{
			if (_lauta[7][5] == nullptr && _lauta[7][6] == nullptr && !_onkoMustaKuningasLiikkunut && !_onkoMustaKTLiikkunut)
			{
				_lauta[7][6] = _lauta[7][4];
				_lauta[7][4] = nullptr;
				_lauta[7][5] = _lauta[7][7];
				_lauta[7][7] = nullptr;
				if (!tarkistus)
				{
					_onkoMustaKuningasLiikkunut = true;
					_onkoMustaKTLiikkunut = true;
				}
			}
		}
		else
		{
			if (_lauta[0][5] == nullptr && _lauta[0][6] == nullptr && !_onkoValkeaKuningasLiikkunut && !_onkoValkeaKTLiikkunut)
			{
				_lauta[0][6] = _lauta[0][4];
				_lauta[0][4] = nullptr;
				_lauta[0][5] = _lauta[0][7];
				_lauta[0][7] = nullptr;
				if (!tarkistus)
				{
					_onkoValkeaKuningasLiikkunut = true;
					_onkoValkeaKTLiikkunut = true;
				}
			}
		}
	}
	else if (siirto->onkoPitk‰linna())
	{
		//Suoritetaan pitk‰ linnoitus, mik‰li sallittua
		if (_siirtovuoro)
		{
			if (_lauta[7][1] == nullptr && _lauta[7][2] == nullptr && _lauta[7][3] == nullptr && !_onkoMustaKuningasLiikkunut && !_onkoMustaDTLiikkunut)
			{
				_lauta[7][2] = _lauta[7][4];
				_lauta[7][4] = nullptr;
				_lauta[7][3] = _lauta[7][0];
				_lauta[7][0] = nullptr;
				if (!tarkistus)
				{
					_onkoMustaKuningasLiikkunut = true;
					_onkoMustaDTLiikkunut = true;
				}
			}
		}
		else
		{
			if (_lauta[0][1] == nullptr && _lauta[0][2] == nullptr && _lauta[0][3] == nullptr && !_onkoValkeaKuningasLiikkunut && !_onkoValkeaDTLiikkunut)
			{
				_lauta[0][2] = _lauta[0][4];
				_lauta[0][4] = nullptr;
				_lauta[0][3] = _lauta[0][0];
				_lauta[0][0] = nullptr;
				if (!tarkistus)
				{
					_onkoValkeaKuningasLiikkunut = true;
					_onkoValkeaDTLiikkunut = true;
				}
			}
		}
	}
	else
	{
		//Normaalin siirron suoritus

		//Nappulan tiedot ylˆs
		Ruutu alkuRuutu = siirto->getAlkuruutu();
		int alkuRivi = alkuRuutu.getRivi();
		int alkuSarake = alkuRuutu.getSarake();
		Ruutu loppuRuutu = siirto->getLoppuruutu();
		int loppuRivi = loppuRuutu.getRivi();
		int loppuSarake = loppuRuutu.getSarake();

		//Suoritetaan ylent‰minen vain mik‰li kyseess‰ ei ole kuninkaan turvatarkistus
		if (!tarkistus)
		{
			if (_siirtovuoro == 1 && loppuRivi == 0 && _lauta[alkuRivi][alkuSarake]->getKoodi() == MS)
			{
				//T‰ss‰ ylennet‰‰n musta sotilas
				bool incorrectInput;
				do
				{
					incorrectInput = false;
					wcout << "Sotilaan korotus: syˆt‰ D/L/R/T" << endl;
					char korotus;
					cin >> korotus;
					cin.clear();

					switch (korotus)
					{
					case 'D':
					case 'd':
						_lauta[alkuRivi][alkuSarake] = _md;
						break;
					case 'L':
					case 'l':
						_lauta[alkuRivi][alkuSarake] = _ml;
						break;
					case 'R':
					case 'r':
						_lauta[alkuRivi][alkuSarake] = _mr;
						break;
					case 'T':
					case 't':
						_lauta[alkuRivi][alkuSarake] = _mt;
						break;
					default:
						incorrectInput = true;
						break;
					}
				} while (incorrectInput);
			}
			else if (_siirtovuoro == 0 && loppuRivi == 7 && _lauta[alkuRivi][alkuSarake]->getKoodi() == VS)
			{
				//T‰ss‰ ylennet‰‰n valkea sotilas
				bool incorrectInput;
				do
				{
					incorrectInput = false;
					wcout << "Sotilaan korotus: syˆt‰ D/L/R/T" << endl;

					char korotus;
					cin >> korotus;
					cin.clear();

					switch (korotus)
					{
					case 'D':
					case 'd':
						_lauta[alkuRivi][alkuSarake] = _vd;
						break;
					case 'L':
					case 'l':
						_lauta[alkuRivi][alkuSarake] = _vl;
						break;
					case 'R':
					case 'r':
						_lauta[alkuRivi][alkuSarake] = _vr;
						break;
					case 'T':
					case 't':
						_lauta[alkuRivi][alkuSarake] = _vt;
						break;
					default:
						incorrectInput = true;
						break;
					}
				} while (incorrectInput);
			}
		}
		//Siirto
		_lauta[loppuRivi][loppuSarake] = _lauta[alkuRivi][alkuSarake];
		_lauta[alkuRivi][alkuSarake] = nullptr;
		bool ohestalyonti = siirto->getOhestalyonti();
		if (ohestalyonti)
		{
			if (_siirtovuoro)
			{
				_lauta[loppuRivi + 1][loppuSarake] = nullptr;
			}
			else
			{
				_lauta[loppuRivi - 1][loppuSarake] = nullptr;
			}
		}
		// Linnoitukseen liittyvi‰ tarkistuksia
		// Katsotaan onko kuninkaat tai tornit siirtyneet
		if (!tarkistus)
		{
			if (!_onkoValkeaKuningasLiikkunut)
			{
				if (_lauta[0][4] == nullptr || _lauta[0][4]->getKoodi() != VK)
				{
					_onkoValkeaKuningasLiikkunut = true;
				}
			}
			if (!_onkoMustaKuningasLiikkunut)
			{
				if (_lauta[7][4] == nullptr || _lauta[7][4]->getKoodi() != MK)
				{
					_onkoMustaKuningasLiikkunut = true;
				}
			}
			if (!_onkoValkeaKTLiikkunut)
			{
				if (_lauta[0][7] == nullptr || _lauta[0][7]->getKoodi() != VT)
				{
					_onkoValkeaKTLiikkunut = true;
				}
			}
			if (!_onkoValkeaDTLiikkunut)
			{
				if (_lauta[0][0] == nullptr || _lauta[0][0]->getKoodi() != VT)
				{
					_onkoValkeaDTLiikkunut = true;
				}
			}
			if (!_onkoMustaKTLiikkunut)
			{
				if (_lauta[7][7] == nullptr || _lauta[7][7]->getKoodi() != MT)
				{
					_onkoMustaKTLiikkunut = true;
				}
			}
			if (!_onkoMustaDTLiikkunut)
			{
				if (_lauta[7][0] == nullptr || _lauta[7][0]->getKoodi() != MT)
				{
					_onkoMustaDTLiikkunut = true;
				}
			}
		}
	}
}

int Asema::getSiirtovuoro()
{
	return _siirtovuoro;
}

//Vaihtaa siitovuoron toiseen pelaajaan
void Asema::setSiirtovuoro()
{
	if (_siirtovuoro == 1)
	{
		_siirtovuoro = 0;
	}
	else
	{
		_siirtovuoro = 1;
	}
}

bool Asema::getOnkoValkeaKuningasLiikkunut()
{
	if (_lauta[0][4] != nullptr && _lauta[0][4]->getKoodi() == VK)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Asema::getOnkoMustaKuningasLiikkunut()
{
	if (_lauta[7][4] != nullptr && _lauta[7][4]->getKoodi() == MK)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Asema::getOnkoValkeaDTLiikkunut()
{
	if (_lauta[0][0] != nullptr && _lauta[0][0]->getKoodi() == VT)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Asema::getOnkoValkeaKTLiikkunut()
{
	if (_lauta[0][7] != nullptr && _lauta[0][7]->getKoodi() == VT)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Asema::getOnkoMustaDTLiikkunut()
{
	if (_lauta[7][0] != nullptr && _lauta[7][0]->getKoodi() == MT)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Asema::getOnkoMustaKTLiikkunut()
{
	if (_lauta[7][7] != nullptr && _lauta[7][7]->getKoodi() == MT)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Asema::getSotilaanKaksoissiirto()
{
	return _sotilaanKaksoissiirto;
}

void Asema::setSotilaanKaksoissiirto(bool check)
{
	_sotilaanKaksoissiirto = check;
}

//Lis‰‰ annettuun listaan siirtovuorossa olevan pelaajan lailliset siirrot
void Asema::annaLaillisetSiirrot(std::list<Siirto>& lista)
{
	//K‰y l‰pi kaikki pelilaudalla olevat nappulat ja "kysyy" jokaisen mahdolliset siirrot
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			if (_lauta[y][x] != nullptr)
			{
				if (_siirtovuoro == 0)
				{
					if (_lauta[y][x]->getVari() == 0)
					{
						_lauta[y][x]->annaSiirrot(lista, &Ruutu(y, x), this, _siirtovuoro);
					}
				}
				else
				{
					if (_lauta[y][x]->getVari() == 1)
					{
						_lauta[y][x]->annaSiirrot(lista, &Ruutu(y, x), this, _siirtovuoro);
					}
				}
			}
		}
	}

	//Tarkistaa mik‰li linnoitukset ovat mahdollisia siirtoja ja lis‰‰ ne listaan
	if (_siirtovuoro)
	{
		if (_lauta[7][5] == nullptr && _lauta[7][6] == nullptr && !getOnkoMustaKuningasLiikkunut() && !getOnkoMustaKTLiikkunut())
		{
			lista.push_back(Siirto(true, false));
		}
		if (_lauta[7][1] == nullptr && _lauta[7][2] == nullptr && _lauta[7][3] == nullptr && !getOnkoMustaKuningasLiikkunut() && !getOnkoMustaDTLiikkunut())
		{
			lista.push_back(Siirto(false, true));
		}
	}
	else
	{
		if (_lauta[0][5] == nullptr && _lauta[0][6] == nullptr && !getOnkoValkeaKuningasLiikkunut() && !getOnkoValkeaKTLiikkunut())
		{
			lista.push_back(Siirto(true, false));
		}
		if (_lauta[0][1] == nullptr && _lauta[0][2] == nullptr && _lauta[0][3] == nullptr && !getOnkoValkeaKuningasLiikkunut() && !getOnkoValkeaDTLiikkunut())
		{
			lista.push_back(Siirto(false, true));
		}
	}
}

//K‰y l‰pi annaLaillisetSiirrot funktiosta saadun listan jokaisen siirron ja poistaa siirron listasta, mik‰li se johtaisi shakkiin
void Asema::onkoShakki(std::list<Siirto>& lista)
{
	list<Siirto>::iterator siirto;
	list<Siirto> laillisetSiirrot;
	Siirto palautusSiirto;
	Siirto siirtoTorni;
	Siirto palautusSiirtoTorni;
	Siirto siirtoKuningas;
	Siirto palautusSiirtoKuningas;
	Nappula* loppuRuutu = nullptr;
	Nappula* ohestalyonti = nullptr;
	bool kuningas;
	bool lyhytLinna;
	bool pitkaLinna;

	//Iteroidaan l‰pi mahdollisten siirtojen lista
	for (siirto=lista.begin(); siirto!=lista.end();siirto++)
	{
		//Tarkistetaan mik‰li siirto on linnoitus
		lyhytLinna = siirto->onkoLyhytLinna();
		pitkaLinna = siirto->onkoPitk‰linna();

		//Suoritetaan linnoituksen tarkistus
		if (lyhytLinna || pitkaLinna)
		{
			if (lyhytLinna)
			{
				//Lyhyt linnoitus. Tehd‰‰n siirrot v‰liaikaiseen linnoitukseen ja sen palautukseen. Tarkistus on tehty aikaisemmin, niin ei tarvitse huolehtia katoavista nappuloista
				if (_siirtovuoro)
				{
					siirtoTorni = Siirto(Ruutu(7, 7), Ruutu(7, 5), false);
					palautusSiirtoTorni = Siirto(Ruutu(7, 5), Ruutu(7, 7), false);
					siirtoKuningas = Siirto(Ruutu(7, 4), Ruutu(7, 6), false);
					palautusSiirtoKuningas = Siirto(Ruutu(7, 6), Ruutu(7, 4), false);
				}
				else
				{
					siirtoTorni = Siirto(Ruutu(0, 7), Ruutu(0, 5), false);
					palautusSiirtoTorni = Siirto(Ruutu(0, 5), Ruutu(0, 7), false);
					siirtoKuningas = Siirto(Ruutu(0, 4), Ruutu(0, 6), false);
					palautusSiirtoKuningas = Siirto(Ruutu(0, 6), Ruutu(0, 4), false);
				}
			}
			else
			{
				//Pitk‰ linnoitus. Tehd‰‰n siirrot v‰liaikaiseen linnoitukseen ja sen palautukseen. Tarkistus on tehty aikaisemmin, niin ei tarvitse huolehtia katoavista nappuloista
				if (_siirtovuoro)
				{
					siirtoTorni = Siirto(Ruutu(7, 0), Ruutu(7, 3), false);
					palautusSiirtoTorni = Siirto(Ruutu(7, 3), Ruutu(7, 0), false);
					siirtoKuningas = Siirto(Ruutu(7, 4), Ruutu(7, 2), false);
					palautusSiirtoKuningas = Siirto(Ruutu(7, 2), Ruutu(7, 4), false);
				}
				else
				{
					siirtoTorni = Siirto(Ruutu(0, 0), Ruutu(0, 3), false);
					palautusSiirtoTorni = Siirto(Ruutu(0, 3), Ruutu(0, 0), false);
					siirtoKuningas = Siirto(Ruutu(0, 4), Ruutu(0, 2), false);
					palautusSiirtoKuningas = Siirto(Ruutu(0, 2), Ruutu(0, 4), false);
				}
			}

			//P‰ivitet‰‰n lauta linnoituksen siirroilla
			paivitaAsema(&siirtoTorni, true);
			paivitaAsema(&siirtoKuningas, true);

		}
		else
		{
			//Normaali siirto
			//Otetaan ylˆs loppuruudun sis‰ltˆ, tehd‰‰n palautussiirto ja p‰ivitet‰‰n lauta siirrolla.
			loppuRuutu = _lauta[siirto->getLoppuruutu().getRivi()][siirto->getLoppuruutu().getSarake()];
			palautusSiirto = Siirto(siirto->getLoppuruutu(), siirto->getAlkuruutu(), false);
			if (siirto->getOhestalyonti())
			{
				if (_siirtovuoro)
				{
					ohestalyonti = _lauta[siirto->getLoppuruutu().getRivi() + 1][siirto->getLoppuruutu().getSarake()];
				}
				else
				{
					ohestalyonti = _lauta[siirto->getLoppuruutu().getRivi() - 1][siirto->getLoppuruutu().getSarake()];
				}
			}
			paivitaAsema(&*siirto, true);

		}

		//T‰h‰n tallennetaan "seuraavan vuoron" siirrot
		list<Siirto> laittomatSiirrot;
		list<Siirto> laittomatSiirrot2;
		
		//Muutetaan siirtovuoro
		setSiirtovuoro();
		//Otetaan ylˆs aikaisemmin tehdyn siirron j‰lkeiset uudet mahdolliset siirrot vastustajalle.
		annaLaillisetSiirrot(laittomatSiirrot);
		//Poistetaan siirtolistasta linnoituksen siirrot, koska tuleva koodi ei osaa sellaisia k‰sitell‰
		list<Siirto>::iterator siirto2;
		for (siirto2 = laittomatSiirrot.begin(); siirto2 != laittomatSiirrot.end(); siirto2++)
		{
			if (!siirto2->onkoLyhytLinna() && !siirto2->onkoPitk‰linna())
			{
				laittomatSiirrot2.push_back(*siirto2);
			}
		}
		laittomatSiirrot = laittomatSiirrot2;
		//Palautetaan siirtovuoro takaisin pelaajalle
		setSiirtovuoro();

		//K‰yd‰‰n l‰pi aikaisemmin tehty vastustajan mahdollisten siirtojen lista ja tarkistetaan mik‰li mik‰‰n siirto pystyy aiheuttamaan vaaran kuninkaalle
		kuningas = false;
		for (Siirto siirto3 : laittomatSiirrot)
		{
			if (_lauta[siirto3.getLoppuruutu().getRivi()][siirto3.getLoppuruutu().getSarake()] != nullptr)
			{
				if (_siirtovuoro == 1 && _lauta[siirto3.getLoppuruutu().getRivi()][siirto3.getLoppuruutu().getSarake()]->getKoodi() == MK)
				{
					kuningas = true;
				}
				else if (_siirtovuoro == 0 && _lauta[siirto3.getLoppuruutu().getRivi()][siirto3.getLoppuruutu().getSarake()]->getKoodi() == VK)
				{
					kuningas = true;
				}
			}
		}

		//Jos mik‰‰n vastustajan nappula ei uhkaa kuningasta, on siirto laillinen ja palautetaan se listaan
		if (!kuningas)
		{
			laillisetSiirrot.push_back(*siirto);
		}

		//Palautetaan laudan alkuper‰inen tilanne
		if (lyhytLinna || pitkaLinna)
		{
			paivitaAsema(&palautusSiirtoTorni, true);
			paivitaAsema(&palautusSiirtoKuningas, true);
		}
		else
		{
			paivitaAsema(&palautusSiirto, true);
			_lauta[siirto->getLoppuruutu().getRivi()][siirto->getLoppuruutu().getSarake()] = loppuRuutu;
			if (siirto->getOhestalyonti())
			{
				if (_siirtovuoro)
				{
					_lauta[siirto->getLoppuruutu().getRivi() + 1][siirto->getLoppuruutu().getSarake()] = ohestalyonti;
				}
				else
				{
					_lauta[siirto->getLoppuruutu().getRivi() - 1][siirto->getLoppuruutu().getSarake()] = ohestalyonti;
				}
			}
		}
	}

	//Annetaan lista kutsujalle
	lista = laillisetSiirrot;
}

MinMaxPaluu Asema::minimax(int syvyys, bool valkeanVuoro, double alpha, double beta)
{
	MinMaxPaluu paluuarvo;

	// Generoidaan aseman lailliset siirrot.
	std::list<Siirto> siirrot;
	annaLaillisetSiirrot(siirrot);
	onkoShakki(siirrot);

	// Rekursion kantatapaus 1: peli on loppu koska laillisia siirtoja ei ole.
	if (siirrot.size() == 0)
	{
		paluuarvo._evaluointiArvo = lopputulos();
		return paluuarvo;
	}

	// Rekursion kantatapaus 2: katkaisusyvyydess‰
	if (syvyys == 0)
	{
		paluuarvo._evaluointiArvo = evaluoi();
		return paluuarvo;
	}

	// Rekursioaskel: kokeillaan jokaista laillista siirtoa s
	// (alustetaan paluuarvo huonoimmaksi mahdolliseksi).
	paluuarvo._evaluointiArvo = (_siirtovuoro == 0 ? -1000000 : 1000000);
	for (auto s : siirrot)
	{

		alphaBetaCounter++;
		// Seuraaja-asema (tehd‰‰n nykyisess‰ asemassa siirto s).

		Siirto palautusSiirto;
		Siirto siirtoTorni;
		Siirto palautusSiirtoTorni;
		Siirto siirtoKuningas;
		Siirto palautusSiirtoKuningas;
		Nappula* loppuRuutu = nullptr;
		Nappula* ohestalyonti = nullptr;
		bool lyhytLinna;
		bool pitkaLinna;

		//Tarkistetaan mik‰li siirto on linnoitus
		lyhytLinna = s.onkoLyhytLinna();
		pitkaLinna = s.onkoPitk‰linna();

		//Suoritetaan linnoituksen tarkistus
		if (lyhytLinna || pitkaLinna)
		{
			if (lyhytLinna)
			{
				//Lyhyt linnoitus. Tehd‰‰n siirrot v‰liaikaiseen linnoitukseen ja sen palautukseen. Tarkistus on tehty aikaisemmin, niin ei tarvitse huolehtia katoavista nappuloista
				if (_siirtovuoro)
				{
					siirtoTorni = Siirto(Ruutu(7, 7), Ruutu(7, 5), false);
					palautusSiirtoTorni = Siirto(Ruutu(7, 5), Ruutu(7, 7), false);
					siirtoKuningas = Siirto(Ruutu(7, 4), Ruutu(7, 6), false);
					palautusSiirtoKuningas = Siirto(Ruutu(7, 6), Ruutu(7, 4), false);
				}
				else
				{
					siirtoTorni = Siirto(Ruutu(0, 7), Ruutu(0, 5), false);
					palautusSiirtoTorni = Siirto(Ruutu(0, 5), Ruutu(0, 7), false);
					siirtoKuningas = Siirto(Ruutu(0, 4), Ruutu(0, 6), false);
					palautusSiirtoKuningas = Siirto(Ruutu(0, 6), Ruutu(0, 4), false);
				}
			}
			else
			{
				//Pitk‰ linnoitus. Tehd‰‰n siirrot v‰liaikaiseen linnoitukseen ja sen palautukseen. Tarkistus on tehty aikaisemmin, niin ei tarvitse huolehtia katoavista nappuloista
				if (_siirtovuoro)
				{
					siirtoTorni = Siirto(Ruutu(7, 0), Ruutu(7, 3), false);
					palautusSiirtoTorni = Siirto(Ruutu(7, 3), Ruutu(7, 0), false);
					siirtoKuningas = Siirto(Ruutu(7, 4), Ruutu(7, 2), false);
					palautusSiirtoKuningas = Siirto(Ruutu(7, 2), Ruutu(7, 4), false);
				}
				else
				{
					siirtoTorni = Siirto(Ruutu(0, 0), Ruutu(0, 3), false);
					palautusSiirtoTorni = Siirto(Ruutu(0, 3), Ruutu(0, 0), false);
					siirtoKuningas = Siirto(Ruutu(0, 4), Ruutu(0, 2), false);
					palautusSiirtoKuningas = Siirto(Ruutu(0, 2), Ruutu(0, 4), false);
				}
			}

			//P‰ivitet‰‰n lauta linnoituksen siirroilla
			paivitaAsema(&siirtoTorni, true);
			paivitaAsema(&siirtoKuningas, true);

		}
		else
		{
			//Normaali siirto
			//Otetaan ylˆs loppuruudun sis‰ltˆ, tehd‰‰n palautussiirto ja p‰ivitet‰‰n lauta siirrolla.
			loppuRuutu = _lauta[s.getLoppuruutu().getRivi()][s.getLoppuruutu().getSarake()];
			palautusSiirto = Siirto(s.getLoppuruutu(), s.getAlkuruutu(), false);
			if (s.getOhestalyonti())
			{
				if (_siirtovuoro)
				{
					ohestalyonti = _lauta[s.getLoppuruutu().getRivi() + 1][s.getLoppuruutu().getSarake()];
				}
				else
				{
					ohestalyonti = _lauta[s.getLoppuruutu().getRivi() - 1][s.getLoppuruutu().getSarake()];
				}
			}
			paivitaAsema(&s, true);

		}

		// Rekursiivinen kutsu.
		MinMaxPaluu arvo = minimax(syvyys - 1, !valkeanVuoro, alpha, beta);

		// Tutkitaan ollaanko lˆydetty uusi paras siirto.
		if
		(
			(_siirtovuoro == 0 && arvo._evaluointiArvo > paluuarvo._evaluointiArvo) ||
			(_siirtovuoro == 1 && arvo._evaluointiArvo < paluuarvo._evaluointiArvo)
		)
		{
			// Lˆydettiin uusi paras siirto.
			paluuarvo._evaluointiArvo = arvo._evaluointiArvo;
			paluuarvo._parasSiirto = s;
		}

		if (valkeanVuoro)
		{
			if (arvo._evaluointiArvo > alpha)
			{
				alpha = arvo._evaluointiArvo;
			}
		}
		else
		{
			if (arvo._evaluointiArvo < beta)
			{
				beta = arvo._evaluointiArvo;
			}
		}

		//Palautetaan laudan alkuper‰inen tilanne
		if (lyhytLinna || pitkaLinna)
		{
			paivitaAsema(&palautusSiirtoTorni, true);
			paivitaAsema(&palautusSiirtoKuningas, true);
		}
		else
		{
			paivitaAsema(&palautusSiirto, true);
			_lauta[s.getLoppuruutu().getRivi()][s.getLoppuruutu().getSarake()] = loppuRuutu;
			if (s.getOhestalyonti())
			{
				if (_siirtovuoro)
				{
					_lauta[s.getLoppuruutu().getRivi() + 1][s.getLoppuruutu().getSarake()] = ohestalyonti;
				}
				else
				{
					_lauta[s.getLoppuruutu().getRivi() - 1][s.getLoppuruutu().getSarake()] = ohestalyonti;
				}
			}
		}
		//alfa beta katkaisu
		if (beta <= alpha)
		{
			break;
		}
	}

	return paluuarvo;
}


double Asema::lopputulos()
{
	// Asemassa ei ole en‰‰ laillisia siirtoja. Etsit‰‰n siirtovuoroisen pelaajan
	// kuningas; jos kuningas on uhattu, on pelaaja h‰vinnyt (muuten tasapeli, "patti").

	// Kuninkaan sijainti (x,y).
	Nappula* kunkku = _siirtovuoro == 0 ? _vk : _mk;
	int kx, ky;
	bool loydetty = false;
	for (int x = 0; x < 8; ++x)
	{
		for (int y = 0; y < 8; ++y)
		{
			if (_lauta[x][y] == kunkku)
			{
				kx = x;
				ky = y;
				loydetty = true;
				break;
			}
		}
		if (loydetty)
		{
			break;
		}
	}

	setSiirtovuoro();
	list<Siirto> vastustajanSiirrotLista;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (this->_lauta[i][j] == NULL)
			{
				continue;
			}
			if (this->_lauta[i][j]->getVari() == _siirtovuoro)
				this->_lauta[i][j]->annaSiirrot(vastustajanSiirrotLista, &Ruutu(i, j), this, _siirtovuoro);
		}
	}
	setSiirtovuoro();

	for (auto siirto : vastustajanSiirrotLista)
	{
		if (siirto.getLoppuruutu().getRivi() == kx && siirto.getLoppuruutu().getSarake() == ky)
		{
			return _siirtovuoro == 0 ? -1000000 : 1000000;
		}
	}

	return 0;
}

double Asema::evaluoi()
{
	double arvo = 0;
	double valkeaArvo;
	double mustaArvo;
	int valkeat;
	int mustat;
	laskeNappuloidenArvo(valkeaArvo, mustaArvo, valkeat, mustat);

	if (valkeat + mustat > 16)
	{
		Nappula* kunkku = _siirtovuoro == 0 ? _vk : _mk;
		int kx, ky;
		bool loydetty = false;
		for (int x = 0; x < 8; ++x)
		{
			for (int y = 0; y < 8; ++y)
			{
				if (_lauta[x][y] == kunkku)
				{
					kx = x;
					ky = y;
					loydetty = true;
					break;
				}
			}
			if (loydetty)
			{
				break;
			}
		}

		if ((kx == 0 && _siirtovuoro == 0) && (ky == 1 || ky == 2 || ky == 6))
		{
			arvo++;
		}
		if ((kx == 7 && _siirtovuoro == 1) && (ky == 1 || ky == 2 || ky == 6))
		{
			arvo--;
		}
	}

	arvo += valkeaArvo - mustaArvo;


	return arvo;
}

void Asema::laskeNappuloidenArvo(double &valkeaArvo, double &mustaArvo, int &valkeat, int &mustat)
{
	valkeaArvo = 0;
	mustaArvo = 0;
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			if (this->_lauta[x][y] != NULL)
			{
				int nappulanNimi = this->_lauta[x][y]->getKoodi();
				//Lasketaan aseman arvo laudalla olevien nappuloiden arvojen sek‰ niiden sijaintien perusteella
				
				//Valkoiset
				if (nappulanNimi == VD)
				{
					valkeaArvo += 9;
					valkeaArvo += _daaminArvot[x][y];
					valkeat++;
				}
				if (nappulanNimi == VT)
				{
					valkeaArvo += 5;
					valkeaArvo += _torninArvot[x][y];
					valkeat++;

				}
				if (nappulanNimi == VL)
				{
					valkeaArvo += 3.3;
					valkeaArvo += _lahetinArvot[x][y];
					valkeat++;
				}
				if (nappulanNimi == VR)
				{
					valkeaArvo += 3.2;
					valkeaArvo += _ratsunArvot[x][y];
					valkeat++;
				}
				if (nappulanNimi == VS)
				{
					valkeaArvo += 1;
					valkeaArvo += _sotilaanArvot[x][y];
					valkeat++;

				}

				//Mustat
				if (nappulanNimi == MD)
				{
					mustaArvo += 9;
					mustaArvo += _daaminArvot[7 - x][y];
					mustat++;
				}
				if (nappulanNimi == MT)
				{
					mustaArvo += 5;
					mustaArvo += _torninArvot[7 - x][y];
					mustat++;
				}
				if (nappulanNimi == ML)
				{
					mustaArvo += 3.3;
					mustaArvo += _lahetinArvot[7 - x][y];
					mustat++;
				}
				if (nappulanNimi == MR)
				{
					mustaArvo += 3.2;
					mustaArvo += _ratsunArvot[7 - x][y];
					mustat++;
				}
				if (nappulanNimi == MS)
				{
					mustaArvo += 1;
					mustaArvo += _sotilaanArvot[7 - x][y];
					mustat++;
				}
			}
		}
	}
}