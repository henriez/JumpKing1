#pragma once
#include "../Personagem.h"

class Jogador : public Personagem {
public:

	Jogador();
	Jogador(float x, float y, int points, int hp, int id);
	~Jogador();

	void setGround(const bool inGround);
	bool inGround() const;
	void atualizar();
	void atacar();
	void render();
	void shoot();
	void damage(int dmg = 1) override;
	void setID(int id) { this->id = id; }

	const int getSpeed() const { return speed; }
	bool facingLeft() { return flip; }
	bool isAttacking() const { return attacking; }
	void setPontuacao(int pontuacao) { points = pontuacao; }
	int getPontuacao() const { return points; }
	void hit(int increase) { points += increase; }

	void salvar(int faseID) {
		ofstream file;
		if (faseID == 1) file.open("Saves/Fase1/jogadores.dat", ios::app);
		else if (faseID == 2) file.open("Saves/Fase2/jogadores.dat", ios::app);

		ComponenteTransform* transform = getComponente<ComponenteTransform>();
		int saude = getComponente<ComponenteSaude>()->getHealth();
		std::string str = std::to_string(transform->posicao.x) + " " + std::to_string(transform->posicao.y) + " "
			+ std::to_string(points) + " " + std::to_string(saude) + " " + std::to_string(id) + "\n";

		file << str;

		file.close();
	}

private:
	void inicializar();
	friend class GerenciadorDeCamera;

	int points;
	int id;

	const int speed;
	const int maxSpeed;
	bool onGround;
	bool flip;
	bool attacking;
	Uint32 timer;
};
