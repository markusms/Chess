#pragma once
#include "Nappula.h"
#include "Ruutu.h"
#include "Asema.h"
#include "Siirto.h"

class Torni : public virtual Nappula
{
public:
	Torni() {}

	Torni(std::wstring nimi, int vari, int koodi)
	{
		_unicode = nimi;
		_vari = vari;
		_koodi = koodi;
	}

	void annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
	{
		int rivi = ruutu->getRivi();
		int sarake = ruutu->getSarake();
		//K�yt�nn�ss� t�ss� on lista vektoreita origosta, jotka kuvaavat tornin mahdollisia kulkusuuntia (torninSuunnat[rivi][sarake])
		int torninSuunnat[2][4] = { {1, 0, -1, 0},
									{0, 1, 0, -1} };

		//K�yd��n l�pi kaikki nelj� suuntaa vuorotellen
		for (int i = 0; i < 4; i++)
		{
			int kerroin = 1;
			while (1)
			{
				// Lis�t��n vektori nappulan sijaintiin ja tarkistetaan onko t�m� loppusijainti laudalla
				if (rivi + (torninSuunnat[0][i] * kerroin) >= 0 && rivi + (torninSuunnat[0][i] * kerroin) <= 7 && sarake + (torninSuunnat[1][i] * kerroin) >= 0 && sarake + (torninSuunnat[1][i] * kerroin) <= 7)
				{
					// Mik�li loppuruutu on vapaa lis�t��n siirto laillisten siirtojen listaan
					if (asema->_lauta[rivi + (torninSuunnat[0][i] * kerroin)][sarake + (torninSuunnat[1][i] * kerroin)] == nullptr)
					{
						lista.push_back(Siirto(*ruutu, Ruutu(rivi + (torninSuunnat[0][i] * kerroin), sarake + (torninSuunnat[1][i] * kerroin)), false));
					}
					else
					{
						// Jos loppuruudussa on nappula, tarkistetaan onko se oma vai vastustajan nappula. Lis�t��n vastustajan nappulan sy�minen listaan ja keskeytet��n suunnan iteroiminen
						int koodi = asema->_lauta[rivi + (torninSuunnat[0][i] * kerroin)][sarake + (torninSuunnat[1][i] * kerroin)]->getKoodi();
						if (vari && (koodi == VS || koodi == VR || koodi == VT || koodi == VD || koodi == VL || koodi == VK))
						{
							lista.push_back(Siirto(*ruutu, Ruutu(rivi + (torninSuunnat[0][i] * kerroin), sarake + (torninSuunnat[1][i] * kerroin)), false));
							break;
						}
						else if (!vari && (koodi == MS || koodi == MR || koodi == MT || koodi == MD || koodi == ML || koodi == MK))
						{
							lista.push_back(Siirto(*ruutu, Ruutu(rivi + (torninSuunnat[0][i] * kerroin), sarake + (torninSuunnat[1][i] * kerroin)), false));
							break;
						}
						break;
					}
				}
				else
				{
					break;
				}

				kerroin++;
			}
		}
	}
};