#include "Siirto.h"
#include "Kayttoliittyma.h"
#include "Asema.h"

Siirto::Siirto(Ruutu alku, Ruutu loppu, bool ohestalyonti)
{
	_alkuRuutu = alku;
	_loppuRuutu = loppu;
	_lyhytLinna = false;
	_pitkalinna = false;
	_ohestalyonti = ohestalyonti;
}

// Poikkeussiirto linnoitusta varten
Siirto::Siirto(bool lyhytLinna, bool pitkaLinna)
{
	_alkuRuutu = Ruutu(-1,-1);
	_loppuRuutu = Ruutu(-1,-1);
	_lyhytLinna = lyhytLinna;
	_pitkalinna = pitkaLinna;
	_ohestalyonti = false;
}

//Siirto palautusta varten
Siirto::Siirto(bool palautus)
{
	_alkuRuutu = Ruutu(-1, -1);
	_loppuRuutu = Ruutu(-1, -1);
	_palautus = true;
	_ohestalyonti = false;
}


bool Siirto::operator==(Siirto* siirto2)
{
	if (this->getAlkuruutu().getRivi() == siirto2->getAlkuruutu().getRivi() && this->getAlkuruutu().getSarake() == siirto2->getAlkuruutu().getSarake()
		&& this->getLoppuruutu().getRivi() == siirto2->getLoppuruutu().getRivi() && this->getLoppuruutu().getSarake() == siirto2->getLoppuruutu().getSarake() && this->onkoLyhytLinna() == siirto2->onkoLyhytLinna() && this->onkoPitkälinna() == siirto2->onkoPitkälinna())
	{
		if (_ohestalyonti)
		{
			siirto2->setOhestalyonti(true);
		}
		return true;
	}
	return false;
}

Ruutu Siirto::getAlkuruutu()
{
	return _alkuRuutu;
}

Ruutu Siirto::getLoppuruutu()
{
	return _loppuRuutu;
}

bool Siirto::onkoLyhytLinna()
{
	return _lyhytLinna;
}

bool Siirto::onkoPitkälinna()
{
	return _pitkalinna;
}

bool Siirto::getOhestalyonti()
{
	return _ohestalyonti;
}

void Siirto::setOhestalyonti(bool ohestalyonti)
{
	_ohestalyonti = ohestalyonti;
}