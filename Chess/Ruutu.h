#pragma once

class Ruutu
{
private:
	int _sarake;
	int _rivi;
public:
	Ruutu(int rivi, int sarake);
	Ruutu() {}
	int getRivi();
	int getSarake();
};
