#pragma once

#include "../Fase.h"

class Fase2 : public Fase
{
private:
	int nGoblins;
	int nMagos;
public:
	Fase2();
	~Fase2();

	void inicializar();
	void atualizar();
	
	void criaGoblins();
	void criaMagos();

	void save();
	void saveRank();
	void load();

};