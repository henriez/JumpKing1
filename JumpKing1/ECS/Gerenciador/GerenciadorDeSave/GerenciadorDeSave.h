#pragma once
#include <vector>

class Obstaculo;
class Projetil;
class Inimigo;

class GerenciadorDeSave
{
public:
	~GerenciadorDeSave();
	static GerenciadorDeSave* getInstance();
	static void deleteInstance();

	void save(int id);
	void addObstaculo(Obstaculo* obst);
	void addProjetil(Projetil* proj);
	void addInimigo(Inimigo* in);
	void clear();
private:
	GerenciadorDeSave();

	static GerenciadorDeSave* manager;
	std::vector<Inimigo*> inimigos;
	std::vector<Obstaculo*> obstaculos;
	std::vector<Projetil*> projeteis;

};

