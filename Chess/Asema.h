#pragma once
#include "Nappula.h"
#include "Siirto.h"
#include "MinMaxPaluu.h"

class Asema
{
private:
	int _siirtovuoro;
	bool _onkoValkeaKuningasLiikkunut;
	bool _onkoMustaKuningasLiikkunut;
	bool _onkoValkeaDTLiikkunut;
	bool _onkoValkeaKTLiikkunut;
	bool _onkoMustaDTLiikkunut;
	bool _onkoMustaKTLiikkunut;
	bool _sotilaanKaksoissiirto;

	double _kuninkaanArvot[8][8] = {
		{ 2.0, 3.0, 1.0, 0.0, 0.0, 1.0, 3.0, 2.0 },
		{ 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 2.0, 2.0 },
		{ -1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0 },
		{ -2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0 },
		{ -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0 },
		{ -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0 },
		{ -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0 },
		{ -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0 } };

	double _daaminArvot[8][8] = {
		{ -2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0 },
		{ -1.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, -1.0 },
		{ -1.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.0, -1.0 },
		{ 0.0, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -0.5 },
		{ -0.5, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -0.5 },
		{ -1.0, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -1.0 },
		{ -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0 },
		{ -2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0 } };

	double _torninArvot[8][8] = {
		{ 0.0, 0.0, 0.0, 0.5, 0.5, 0.0, 0.0, 0.0 },
		{ -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5 },
		{ -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5 },
		{ -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5 },
		{ -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5 },
		{ -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5 },
		{ 0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5 },
		{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } };

	double _lahetinArvot[8][8] = {
		{ -2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0 },
		{ -1.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, -1.0 },
		{ -1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0 },
		{ -1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, -1.0 },
		{ -1.0, 0.5, 0.5, 1.0, 1.0, 0.5, 0.5, -1.0 },
		{ -1.0, 0.0, 0.5, 1.0, 1.0, 0.5, 0.0, -1.0 },
		{ -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0 },
		{ -2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0 } };

	double _ratsunArvot[8][8] = {
		{ -5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0 },
		{ -4.0, -2.0, 0.0, 0.5, 0.5, 0.0, -2.0, -4.0 },
		{ -3.0, 0.5, 1.0, 1.5, 1.5, 1.0, 0.5, -3.0 },
		{ -3.0, 0.0, 1.5, 2.0, 2.0, 1.5, 0.0, -3.0 },
		{ -3.0, 0.5, 1.5, 2.0, 2.0, 1.5, 0.5, -3.0 },
		{ -3.0, 0.0, 1.0, 1.5, 1.5, 1.0, 0.0, -3.0 },
		{ -3.0, -2.0, 0.0, 0.0, 0.0, 0.0, -2.0, -4.0 },
		{ -5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0 } };

	double _sotilaanArvot[8][8] = {
		{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
		{ 0.5, 1.0, 1.0, -2.0, -2.0, 1.0, 1.0, 0.5 },
		{ 0.5, -0.5, -1.0, 0.0, 0.0, -1.0, -0.5, 0.5 },
		{ 0.0, 0.0, 0.0, 2.0, 2.0, 0.0, 0.0, 0.0 },
		{ 0.5, 0.5, 1.0, 2.5, 2.5, 1.0, 0.5, 0.5 },
		{ 1.0, 1.0, 2.0, 3.0, 3.0, 2.0, 1.0, 1.0 },
		{ 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0 },
		{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } };

public:

	Nappula* _vk;
	Nappula* _vd;
	Nappula* _vt;
	Nappula* _vl;
	Nappula* _vr;
	Nappula* _vs;
	Nappula* _mk;
	Nappula* _md;
	Nappula* _mt;
	Nappula* _ml;
	Nappula* _mr;
	Nappula* _ms;
	Siirto* _viimeinenSiirto;
	int alphaBetaCounter = 0;

	//Konstruktori luo alkuaseman laudalle
	Asema();
	Nappula* _lauta[8][8];
	void alustaAsema();
	void paivitaAsema(Siirto* siirto, bool tarkistus);
	int getSiirtovuoro();
	void setSiirtovuoro();
	bool getOnkoValkeaKuningasLiikkunut();
	bool getOnkoMustaKuningasLiikkunut();
	bool getOnkoValkeaDTLiikkunut();
	bool getOnkoValkeaKTLiikkunut();
	bool getOnkoMustaDTLiikkunut();
	bool getOnkoMustaKTLiikkunut();
	bool getSotilaanKaksoissiirto();
	void setSotilaanKaksoissiirto(bool);
	void annaLaillisetSiirrot(std::list<Siirto>& lista);
	void onkoShakki(std::list<Siirto>& lista);
	MinMaxPaluu minimax(int syvyys, bool valkeanVuoro, double alpha = -10000000, double beta = 10000000);
	double lopputulos();
	double evaluoi();
	void laskeNappuloidenArvo(double &valkeArvo, double &mustaArvo, int &valkeat, int &mustat);

};
