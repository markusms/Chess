#pragma once
#include <iostream>
#include <list>

class Siirto;
class Ruutu;
class Asema;

enum
{
	VT, VR, VL, VD, VK, VS,
	MT, MR, ML, MD, MK, MS
};

class Nappula
{

protected:
	std::wstring _unicode;
	int _vari; // valkea = 0, musta = 1
	int _koodi; // VT, VR, MT tms.
public:
	Nappula(std::wstring, int, int);
	Nappula() {};
	void setKoodi(int);
	int getKoodi();
	void setUnicode(std::wstring);
	std::wstring getUnicode();
	void setVari(int);
	int getVari();
	virtual void annaSiirrot(std::list<Siirto>&, Ruutu*, Asema*, int) = 0;
};
