#pragma once
#include "Ruutu.h"

class Siirto
{
private:
	Ruutu _alkuRuutu;
	Ruutu _loppuRuutu;
	int _miksiKorotetaan = 0;
	bool _lyhytLinna;
	bool _pitkalinna;
	bool _ohestalyonti;
public:
	Siirto(Ruutu, Ruutu, bool ohestalyonti);
	Siirto() {}
	Siirto(bool lyhytLinna, bool pitkaLinna); // Poikkeussiirto linnoitusta varten
	Siirto(bool palautus); // Poikkeussiirto palautusta varten
	bool operator==(Siirto* siirto2);
	Ruutu getAlkuruutu();
	Ruutu getLoppuruutu();
	bool onkoLyhytLinna();
	bool onkoPitkälinna();
	bool getOhestalyonti();
	void setOhestalyonti(bool ohestalyonti);
	bool _palautus = false;
};