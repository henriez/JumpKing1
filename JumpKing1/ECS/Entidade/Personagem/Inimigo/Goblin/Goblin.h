#pragma once

#include "../Inimigo.h"

class Goblin : public Inimigo {
public:
	Goblin(float x, float y, int raiva = -1);
	~Goblin();

	const int getSpeed() const { return speed; }
	const bool facingLeft() const { return flip; }
	void setState(unsigned char val) { state = val; }

	void atualizar();
	void render();
	int attack();

	void salvar(int faseID) {
		ofstream file;
		if (faseID == 1) file.open("Saves/Fase1/goblins.dat", ios::app);
		else if (faseID == 2) file.open("Saves/Fase2/goblins.dat", ios::app);

		ComponenteTransform* transform = getComponente<ComponenteTransform>();
		int isRaivoso = (raivoso) ? 1 : 0;
		std::string str = std::to_string(transform->posicao.x) + " " + std::to_string(transform->posicao.y) + " "
			+ std::to_string(transform->velocidade.x) + " " + std::to_string(transform->velocidade.y) + " "
			+ std::to_string(isRaivoso) + "\n";

		file << str;

		file.close();
	}

private:
	bool raivoso;
};