#include "Nappula.h"
using namespace std;

Nappula::Nappula(wstring nimi, int vari, int koodi)
{
	_unicode = nimi;
	_vari = vari;
	_koodi = koodi;
}

void Nappula::setKoodi(int koodi)
{
	_koodi = koodi;
}

int Nappula::getKoodi()
{
	return _koodi;
}

void Nappula::setUnicode(wstring unicode)
{
	_unicode = unicode;
}

wstring Nappula::getUnicode()
{
	return _unicode;
}

void Nappula::setVari(int vari)
{
	_vari = vari;
}

int Nappula::getVari()
{
	return _vari;
}