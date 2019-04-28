#pragma once
#include "Torni.h"
#include "Lahetti.h"

class Daami : public Torni, public Lahetti
{
public:
	Daami(std::wstring nimi, int vari, int koodi)
	{
		Torni::_unicode = nimi;
		Torni::_vari = vari;
		Torni::_koodi = koodi;
	}

	void annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
	{
		Torni::annaSiirrot(lista,ruutu,asema,vari);
		Lahetti::annaSiirrot(lista,ruutu,asema,vari);
	}
};