#pragma once
#include "Asema.h"
#include "Siirto.h"
#include <string>

using namespace std;

class Kayttoliittyma
{

public:
	Kayttoliittyma(Asema* asema);
	Asema* _asema;
	void piirraLauta();
	Siirto* annaVastustajanSiirto();
	Siirto* Siirtaminen(string komento, int i);
};
