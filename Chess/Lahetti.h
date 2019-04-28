#pragma once
#include "Nappula.h"
#include "Ruutu.h"
#include "Asema.h"
#include "Siirto.h"

class Lahetti : public virtual Nappula
{
public:
	Lahetti() {}
	
	Lahetti(std::wstring nimi, int vari, int koodi)
	{
		_unicode = nimi;
		_vari = vari;
		_koodi = koodi;
	}

	void annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
	{
		int rivi = ruutu->getRivi();
		int sarake = ruutu->getSarake();
		//Käytännössä tässä on lista vektoreita origosta, jotka kuvaavat lähetin mahdollisia kulkusuuntia (lahetinSuunnat[rivi][sarake])
		int lahetinSuunnat[2][4] = {{1, -1, -1, 1},
									{1, 1, -1, -1}};

		// Käydään läpi kaikki neljä suuntaa vuorotellen
		for (int i = 0; i < 4; i++)
		{
			int kerroin = 1;
			while (1)
			{
				// Lisätään vektori nappulan sijaintiin ja tarkistetaan onko tämä loppusijainti laudalla
				if (rivi + (lahetinSuunnat[0][i] * kerroin) >= 0 && rivi + (lahetinSuunnat[0][i] * kerroin) <= 7 && sarake + (lahetinSuunnat[1][i] * kerroin) >= 0 && sarake + (lahetinSuunnat[1][i] * kerroin) <= 7)
				{
					// Mikäli loppuruutu on vapaa lisätään siirto laillisten siirtojen listaan
					if (asema->_lauta[rivi + (lahetinSuunnat[0][i] * kerroin)][sarake + (lahetinSuunnat[1][i] * kerroin)] == nullptr)
					{
						lista.push_back(Siirto(*ruutu, Ruutu(rivi + (lahetinSuunnat[0][i] * kerroin), sarake + (lahetinSuunnat[1][i] * kerroin)), false));
					}
					else
					{
						// Jos loppuruudussa on nappula, tarkistetaan onko se oma vai vastustajan nappula. Lisätään vastustajan nappulan syöminen listaan ja keskeytetään suunnan iteroiminen
						int koodi = asema->_lauta[rivi + (lahetinSuunnat[0][i] * kerroin)][sarake + (lahetinSuunnat[1][i] * kerroin)]->getKoodi();
						if (vari && (koodi == VS || koodi == VR || koodi == VT || koodi == VD || koodi == VL || koodi == VK))
						{
							lista.push_back(Siirto(*ruutu, Ruutu(rivi + (lahetinSuunnat[0][i] * kerroin), sarake + (lahetinSuunnat[1][i] * kerroin)), false));
							break;
						}
						else if (!vari && (koodi == MS || koodi == MR || koodi == MT || koodi == MD || koodi == ML || koodi == MK))
						{
							lista.push_back(Siirto(*ruutu, Ruutu(rivi + (lahetinSuunnat[0][i] * kerroin), sarake + (lahetinSuunnat[1][i] * kerroin)), false));
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