#pragma once
#include "Nappula.h"
#include "Siirto.h"
#include "Ruutu.h"
#include "Asema.h"

class Kuningas : public Nappula
{
public:
	Kuningas(std::wstring nimi, int vari, int koodi)
	{
		_unicode = nimi;
		_vari = vari;
		_koodi = koodi;
	}

	void annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
	{
		int rivi = ruutu->getRivi();
		int sarake = ruutu->getSarake();
		// T‰ss‰ on lista vektoreita origosta, jotka kuvaavat kuninkaan mahdollisia siirtoja origosta (kuninkaanSiirrot[rivi][sarake])
		int kuninkaanSiirrot[2][8] = { { 1, 1, 0, -1, -1, -1, 0, 1 },
									{ 0, 1, 1, 1, 0, -1, -1, -1 } };

		// K‰yd‰‰n l‰pi kaikki siirrot
		for (int i = 0; i < 8; i++)
		{
			// Lis‰t‰‰n vektori nappulan sijaintiin ja tarkistetaan onko t‰m‰ loppusijainti laudalla
			if (rivi + kuninkaanSiirrot[0][i] >= 0 && rivi + kuninkaanSiirrot[0][i] <= 7 && sarake + kuninkaanSiirrot[1][i] >= 0 && sarake + kuninkaanSiirrot[1][i] <= 7)
			{
				// Mik‰li loppuruutu on vapaa lis‰t‰‰n siirto laillisten siirtojen listaan
				if (asema->_lauta[rivi + kuninkaanSiirrot[0][i]][sarake + kuninkaanSiirrot[1][i]] == nullptr)
				{
					lista.push_back(Siirto(*ruutu, Ruutu(rivi + kuninkaanSiirrot[0][i], sarake + kuninkaanSiirrot[1][i]), false));
				}
				else
				{
					// Jos loppuruudussa on nappula, tarkistetaan onko se oma vai vastustajan nappula. Lis‰t‰‰n vastustajan nappulan syˆminen listaan ja keskeytet‰‰n suunnan iteroiminen
					int koodi = asema->_lauta[rivi + kuninkaanSiirrot[0][i]][sarake + kuninkaanSiirrot[1][i]]->getKoodi();
					if (vari && (koodi == VS || koodi == VR || koodi == VT || koodi == VD || koodi == VL || koodi == VK))
					{
						lista.push_back(Siirto(*ruutu, Ruutu(rivi + kuninkaanSiirrot[0][i], sarake + kuninkaanSiirrot[1][i]), false));
					}
					else if (!vari && (koodi == MS || koodi == MR || koodi == MT || koodi == MD || koodi == ML || koodi == MK))
					{
						lista.push_back(Siirto(*ruutu, Ruutu(rivi + kuninkaanSiirrot[0][i], sarake + kuninkaanSiirrot[1][i]), false));
					}
				}
			}
		}
	}
};