#pragma once
#include "Nappula.h"
#include "Ruutu.h"
#include "Asema.h"
#include "Siirto.h"

class Sotilas : public Nappula
{
public:
	Sotilas(std::wstring nimi, int vari, int koodi)
	{
		_unicode = nimi;
		_vari = vari;
		_koodi = koodi;
	}

	void annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
	{
		int rivi = ruutu->getRivi();
		int sarake = ruutu->getSarake();

		if (vari)
		{
			if (rivi > 0)
			{
				if (asema->_lauta[rivi-1][sarake] == nullptr)
				{
					if (asema->_lauta[rivi - 2][sarake] == nullptr && rivi == 6)
					{
						lista.push_back(Siirto(*ruutu, Ruutu(rivi - 2, sarake), false));
						asema->setSotilaanKaksoissiirto(true);
					}
					lista.push_back(Siirto(*ruutu, Ruutu(rivi - 1, sarake), false));
				}
				if (sarake == 0)
				{
					if (asema->_lauta[rivi - 1][sarake + 1] != nullptr)
					{
						if (asema->_lauta[rivi - 1][sarake + 1]->getKoodi() == VS)
						{
							lista.push_back(Siirto(*ruutu, Ruutu(rivi - 1, sarake + 1), false));
						}
					}
					
					if (asema->_lauta[rivi][sarake + 1] != nullptr)
					{
						if (asema->getSotilaanKaksoissiirto() && asema->_lauta[rivi][sarake + 1]->getKoodi() == VS)
						{
							lista.push_back(Siirto(*ruutu, Ruutu(rivi - 1, sarake + 1), true));
						}
					}
				}
				else if (sarake == 7)
				{
					if (asema->_lauta[rivi - 1][sarake - 1] != nullptr)
					{
						if (asema->_lauta[rivi - 1][sarake - 1]->getKoodi() == VS)
						{
							lista.push_back(Siirto(*ruutu, Ruutu(rivi - 1, sarake - 1), false));
						}
					}
					if (asema->_lauta[rivi][sarake - 1] != nullptr)
					{
						if (asema->getSotilaanKaksoissiirto() && asema->_lauta[rivi][sarake - 1]->getKoodi() == VS)
						{
							lista.push_back(Siirto(*ruutu, Ruutu(rivi - 1, sarake - 1), true));
						}
					}
				}
				else
				{
					if (asema->_lauta[rivi - 1][sarake + 1] != nullptr)
					{
						if (asema->_lauta[rivi - 1][sarake + 1]->getVari() == 0)
						{
							lista.push_back(Siirto(*ruutu, Ruutu(rivi - 1, sarake + 1), false));
						}
					}
					if (asema->_lauta[rivi - 1][sarake - 1] != nullptr)
					{
						if (asema->_lauta[rivi - 1][sarake - 1]->getVari() == 0)
						{
							lista.push_back(Siirto(*ruutu, Ruutu(rivi - 1, sarake - 1), false));
						}
					}
					if (asema->_lauta[rivi][sarake + 1] != nullptr)
					{
						if (asema->getSotilaanKaksoissiirto() && asema->_lauta[rivi][sarake + 1]->getKoodi() == VS)
						{
							lista.push_back(Siirto(*ruutu, Ruutu(rivi - 1, sarake + 1), true));
						}
					}
					if (asema->_lauta[rivi][sarake - 1] != nullptr)
					{
						if (asema->getSotilaanKaksoissiirto() && asema->_lauta[rivi][sarake - 1]->getKoodi() == VS)
						{
							lista.push_back(Siirto(*ruutu, Ruutu(rivi - 1, sarake - 1), true));
						}
					}
				}
			}
		}
		else
		{
			if (ruutu->getRivi() < 7)
			{
				if (asema->_lauta[rivi + 1][sarake] == nullptr)
				{
					if (asema->_lauta[rivi + 2][sarake] == nullptr && rivi == 1)
					{
						lista.push_back(Siirto(*ruutu, Ruutu(rivi + 2, sarake), false));
						asema->setSotilaanKaksoissiirto(true);
					}
					lista.push_back(Siirto(*ruutu, Ruutu(rivi + 1, sarake), false));
				}
				if (sarake == 0)
				{
					if (asema->_lauta[rivi + 1][sarake + 1] != nullptr)
					{
						if (asema->_lauta[rivi + 1][sarake + 1]->getKoodi() == MS)
						{
							lista.push_back(Siirto(*ruutu, Ruutu(rivi + 1, sarake + 1), false));
						}
					}
					if (asema->_lauta[rivi][sarake + 1] != nullptr)
					{
						if (asema->getSotilaanKaksoissiirto() && asema->_lauta[rivi][sarake + 1]->getKoodi() == MS)
						{
							lista.push_back(Siirto(*ruutu, Ruutu(rivi + 1, sarake + 1), true));
						}
					}
				}
				else if (sarake == 7)
				{
					if (asema->_lauta[rivi + 1][sarake - 1] != nullptr)
					{
						if (asema->_lauta[rivi + 1][sarake - 1]->getKoodi() == MS)
						{
							lista.push_back(Siirto(*ruutu, Ruutu(rivi + 1, sarake - 1), false));
						}
					}
					if (asema->_lauta[rivi][sarake - 1] != nullptr)
					{
						if (asema->getSotilaanKaksoissiirto() && asema->_lauta[rivi][sarake - 1]->getKoodi() == MS)
						{
							lista.push_back(Siirto(*ruutu, Ruutu(rivi + 1, sarake - 1), true));
						}
					}
				}
				else
				{
					if (asema->_lauta[rivi + 1][sarake + 1] != nullptr)
					{
						if (asema->_lauta[rivi + 1][sarake + 1]->getVari() == 1)
						{
							lista.push_back(Siirto(*ruutu, Ruutu(rivi + 1, sarake + 1), false));
						}
					}
					if (asema->_lauta[rivi + 1][sarake - 1] != nullptr)
					{
						if (asema->_lauta[rivi + 1][sarake - 1]->getVari() == 1)
						{
							lista.push_back(Siirto(*ruutu, Ruutu(rivi + 1, sarake - 1), false));
						}
					}
					if (asema->_lauta[rivi][sarake + 1] != nullptr)
					{
						if (asema->getSotilaanKaksoissiirto() && asema->_lauta[rivi][sarake + 1]->getKoodi() == MS)
						{
							lista.push_back(Siirto(*ruutu, Ruutu(rivi + 1, sarake + 1), true));
						}
					}
					if (asema->_lauta[rivi][sarake - 1] != nullptr)
					{
						if (asema->getSotilaanKaksoissiirto() && asema->_lauta[rivi][sarake - 1]->getKoodi() == MS)
						{
							lista.push_back(Siirto(*ruutu, Ruutu(rivi + 1, sarake - 1), true));
						}
					}
				}
			}
		}
	}
};