#include "Fase2.h"
#include "../../ECS/Gerenciador/GerenciadorDeColisao/GerenciadorDeColisao.h"
#include "../../ECS/Gerenciador/GerenciadorDeEventos/GerenciadorDeEventos.h"
#include "../../ECS/Gerenciador/GerenciadorDeCamera/GerenciadorDeCamera.h"
#include "../../ECS/Gerenciador/GerenciadorDeSave/GerenciadorDeSave.h"
#include "../../TextBox/Textbox.h"
#include "../Mapa/Mapa.h"
#include <string>
using namespace std;

Fase2::Fase2() {
	nMagos = 0;
	nGoblins = 0;
}

Fase2::~Fase2() {
	if (mapa != nullptr) {
		delete mapa;
		mapa = nullptr;
	}
}

void Fase2::inicializar() {
	GerenciadorDeColisao::getInstance()->setFase(this);

	mapa = new Mapa;
	mapa->inicializar(2, static_cast<Fase*>(this));

	Jogador* jogador = new Jogador;
	jogador->getComponente<ComponenteSprite>()->setCaminhoArquivo("Assets/HenriqueIsFallingx32.png");
	player_is_alive = true;
	event_manager->setJogador1(jogador);
	GerenciadorDeCamera::getInstance()->setJogador(jogador);
	GerenciadorDeColisao::getInstance()->setJogador(jogador);

	Jogador* jogador2 = new Jogador;
	jogador2->setID(2);
	jogador2->getComponente<ComponenteSprite>()->setCaminhoArquivo("Assets/player2.png");
	event_manager->setJogador2(jogador2);
	GerenciadorDeCamera::getInstance()->setJogador2(jogador2);
	GerenciadorDeColisao::getInstance()->setJogador2(jogador2);

	jogador->getComponente<ComponenteTransform>()->posicao.x = 400;
	jogador->getComponente<ComponenteTransform>()->posicao.y = 7648;
	jogador2->getComponente<ComponenteTransform>()->posicao.x = 500;
	jogador2->getComponente<ComponenteTransform>()->posicao.y = 7648;

	criaGoblins();

	listaEntidades.addEntidade(static_cast<Entidade*>(jogador));
	listaEntidades.addEntidade(static_cast<Entidade*>(jogador2));
}

void Fase2::criaGoblins() {
	Goblin* gbl = nullptr;
	std::vector<SDL_Point> posicoes;
	std::fstream file;
	SDL_Point pos = { 0,0 };
	char c;
	int a1, a2, a3, a4, i, nPosicoes;

	
	file.open("Assets/TileMap/Mapa2/mapa2_posicoes_goblins.csv");
	file.get(c);
	a1 = atoi(&c);
	file.get(c);
	a2 = atoi(&c);
	file.get(c);
	a3 = atoi(&c);
	file.ignore();
	//quantidade de posicoes

	nPosicoes = a1 * 100 + a2 * 10 + a3;

	for (int i = 0; i < nPosicoes; i++) {

		file.get(c);
		a1 = atoi(&c);
		file.get(c);
			a2 = atoi(&c);
		file.get(c);
		a3 = atoi(&c);
		file.get(c);
		a4 = atoi(&c);
		file.ignore();
		pos.x = a1 * 1000 + a2 * 100 + a3 * 10 + a4;

		file.get(c);
		a1 = atoi(&c);
		file.get(c);
		a2 = atoi(&c);
		file.get(c);
		a3 = atoi(&c);
		file.get(c);
		a4 = atoi(&c);
		file.ignore();
		pos.y = a1 * 1000 + a2 * 100 + a3 * 10 + a4;
		posicoes.push_back(pos);
	}

	file.close();
	

	std::vector<SDL_Point>::iterator it;

	nGoblins = rand() % (posicoes.size() - 3) + 3;

	for (i = 0; i < nGoblins; i++) {
		pos = posicoes[rand() % posicoes.size()];
		gbl = new Goblin(pos.x, pos.y);
		listaEntidades.addEntidade(static_cast<Entidade*>(gbl));
		GerenciadorDeColisao::getInstance()->addInimigo(static_cast<Inimigo*>(gbl));
	}
}

void Fase2::criaMagos() {
	GerenciadorDeColisao::getInstance()->clear();
	listaEntidades.clear();
	listaEntidades.addEntidade(static_cast<Entidade*>(GerenciadorDeColisao::getInstance()->getJogador1()));
	listaEntidades.addEntidade(static_cast<Entidade*>(GerenciadorDeColisao::getInstance()->getJogador2()));


	std::vector<SDL_Point> posicoes;
	posicoes.push_back({ 1000,200 });
	posicoes.push_back({ 150, 800 });
	posicoes.push_back({ 1050, 500 });
	posicoes.push_back({ 416, 224 });
	posicoes.push_back({ 1600, 400 });

	int nPosicoes = rand() % 3 + 3;

	Mago* mago = nullptr;
	for (int i = 0; i < nPosicoes; i++) {
		mago = new Mago(posicoes[i].x, posicoes[i].y);
		listaEntidades.addEntidade(static_cast<Entidade*>(mago));
		GerenciadorDeColisao::getInstance()->addInimigo(static_cast<Inimigo*>(mago));
	}

	posicoes.clear();
}

void Fase2::atualizar() {
	if (player_is_alive) {
		listaEntidades.atualizar();
		if (mapa != nullptr) {
			mapa->atualizar();
			if (mapa->isOnBossRoom())
				if (GerenciadorDeColisao::getInstance()->allEnemiesDead())
					win();
		}
		GerenciadorDeCamera::getInstance()->Atualiza();
		GerenciadorDeColisao::getInstance()->colidir();
	}
	else {
		clear();
		jogo->gameOverMenu();
	}
}

void Fase2::save() {
	ofstream out;

	// limpa arquivos
	out.open("Saves/Fase2/espinhos.dat", ofstream::out | ofstream::trunc); out.close();
	out.open("Saves/Fase2/goblins.dat", ofstream::out | ofstream::trunc); out.close();
	out.open("Saves/Fase2/jogadores.dat", ofstream::out | ofstream::trunc); out.close();
	out.open("Saves/Fase2/lavas.dat", ofstream::out | ofstream::trunc); out.close();
	out.open("Saves/Fase2/magos.dat", ofstream::out | ofstream::trunc); out.close();
	out.open("Saves/Fase2/projeteis.dat", ofstream::out | ofstream::trunc); out.close();
	out.open("Saves/Fase2/map.dat", ofstream::out | ofstream::trunc); out.close();

	out.open("Saves/Fase2/map.dat");
	if (mapa->isOnBossRoom()) out << 1 << std::endl;
	else out << 0 << std::endl;

	listaEntidades.salvar(2);
}

void Fase2::saveRank(){//salva nomes dos jogadores -> sera coletado ao final da fase
	TextBox name1;
	name1.setFontToHeight("Assets/fonts/acme.ttf");
	name1.run("Player 1", 300, 200);

	TextBox name2;
	name2.setFontToHeight("Assets/fonts/acme.ttf");
	name2.run("Player 2", 300, 200);

	std::ofstream out;

	Jogador* jog1 = GerenciadorDeColisao::getInstance()->getJogador1();
	Jogador* jog2 = GerenciadorDeColisao::getInstance()->getJogador2();
	out.open("Saves/Fase2/ranking.dat", std::ios::app);
	out << name1.getInput() << " " << name2.getInput() << " " << jog1->getPontuacao() + jog2->getPontuacao() << std::endl;
	out.close();

}

void Fase2::load() {

	ifstream in;

	event_manager = GerenciadorDeEventos::getInstance();

	GerenciadorDeColisao::getInstance()->setFase(this);
	mapa = new Mapa;
	player_is_alive = true;

	int boss;
	in.open("Saves/Fase2/map.dat", ios::in);
	while (in >> boss) {}
	in.close();
	if (boss) mapa->setBossRoom(true);
	mapa->reload(2, static_cast<Fase*>(this));

	int x, y, w, h, tam, temp, raiva, sab, hp, index, points;
	float px, py, vx, vy;
	

	in.open("Saves/Fase2/espinhos.dat", ios::in);
	while (in >> x >> y >> w >> h >> tam) {
		Espinhos* esp = new Espinhos(x, y, w, h, tam);
		GerenciadorDeColisao::getInstance()->addObstaculo(esp);
		listaEntidades.addEntidade(static_cast<Entidade*>(esp));
	}
	in.close();

	in.open("Saves/Fase2/goblins.dat", ios::in);
	while (in >> px >> py >> vx >> vy >> raiva) {
		Goblin* gob = new Goblin(px, py, raiva);
		gob->getComponente<ComponenteTransform>()->velocidade.x = vx;
		gob->getComponente<ComponenteTransform>()->velocidade.y = vy;
		GerenciadorDeColisao::getInstance()->addInimigo(gob);
		listaEntidades.addEntidade(static_cast<Entidade*>(gob));
	}
	in.close();

	in.open("Saves/Fase2/jogadores.dat", ios::in);
	while (in >> px >> py >> points >> hp >> index) {
		Jogador* jog = new Jogador(px, py, points, hp, index);
		listaEntidades.addEntidade(static_cast<Entidade*>(jog));

		if (index == 1) {
			event_manager->setJogador1(jog);
			GerenciadorDeCamera::getInstance()->setJogador(jog);
			GerenciadorDeColisao::getInstance()->setJogador(jog);
		}
		else if (index == 2) {
			event_manager->setJogador2(jog);
			GerenciadorDeCamera::getInstance()->setJogador2(jog);
			GerenciadorDeColisao::getInstance()->setJogador2(jog);
		}
	}
	in.close();

	in.open("Saves/Fase2/lavas.dat", ios::in);
	while (in >> x >> y >> w >> h >> temp) {
		Lava* lav = new Lava(x, y, w, h, temp);
		GerenciadorDeColisao::getInstance()->addObstaculo(lav);
		listaEntidades.addEntidade(static_cast<Entidade*>(lav));
	}
	in.close();

	in.open("Saves/Fase2/magos.dat", ios::in);
	while (in >> px >> py >> vx >> vy >> sab) {
		Mago* mag = new Mago(px, py, sab);
		mag->getComponente<ComponenteTransform>()->velocidade.x = vx;
		mag->getComponente<ComponenteTransform>()->velocidade.y = vy;
		GerenciadorDeColisao::getInstance()->addInimigo(mag);
		listaEntidades.addEntidade(static_cast<Entidade*>(mag));
	}
	in.close();

	in.open("Saves/Fase2/projeteis.dat", ios::in);
	while (in >> vx >> vy >> px >> py) {
		Projetil* pro = new Projetil(px, py, vx, vy);
		GerenciadorDeColisao::getInstance()->addProjetil(pro);
		listaEntidades.addEntidade(static_cast<Entidade*>(pro));
	}
	in.close();
}