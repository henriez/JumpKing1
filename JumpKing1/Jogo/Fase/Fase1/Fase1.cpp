#include "Fase1.h"
#include "../../ECS/Gerenciador/GerenciadorDeColisao/GerenciadorDeColisao.h"
#include "../../ECS/Gerenciador/GerenciadorDeEventos/GerenciadorDeEventos.h"
#include "../../ECS/Gerenciador/GerenciadorDeCamera/GerenciadorDeCamera.h"
#include "../../ECS/Gerenciador/GerenciadorDeSave/GerenciadorDeSave.h"
#include "../../TextBox/Textbox.h"
#include "../Mapa/Mapa.h"
#include <string>
using namespace std;

Fase1::Fase1() {
	nMagos = 0;
	nEsqueletos = 0;
}

Fase1::~Fase1() {
	if (mapa != nullptr) {
		delete mapa;
		mapa = nullptr;
	}
}

void Fase1::inicializar() {
	GerenciadorDeColisao::getInstance()->setFase(this);

	mapa = new Mapa;
	mapa->inicializar(1, static_cast<Fase*>(this));

	Jogador* jogador = new Jogador;
	jogador->getComponente<ComponenteSprite>()->setCaminhoArquivo("Assets/HenriqueIsFallingx32.png");
	player_is_alive = true;
	event_manager->setJogador1(jogador);
	GerenciadorDeCamera::getInstance()->setJogador(jogador);
	GerenciadorDeColisao::getInstance()->setJogador(jogador);

	Jogador* jogador2 = new Jogador;
	jogador2->getComponente<ComponenteSprite>()->setCaminhoArquivo("Assets/player2.png");
	jogador2->setID(2);
	event_manager->setJogador2(jogador2);
	GerenciadorDeCamera::getInstance()->setJogador2(jogador2);
	GerenciadorDeColisao::getInstance()->setJogador2(jogador2);

	jogador->getComponente<ComponenteTransform>()->posicao.x = 100;
	jogador->getComponente<ComponenteTransform>()->posicao.y = 6240;
	jogador2->getComponente<ComponenteTransform>()->posicao.x = 200;
	jogador2->getComponente<ComponenteTransform>()->posicao.y = 6240;

	criaEsqueletos();
	
	listaEntidades.addEntidade(static_cast<Entidade*>(jogador));
	listaEntidades.addEntidade(static_cast<Entidade*>(jogador2));
}

void Fase1::criaEsqueletos() {
	Esqueleto* esq = nullptr;
	std::vector<SDL_Point> posicoes;
	std::fstream file;
	SDL_Point pos = { 0,0 };
	char c;
	int a1, a2, a3, a4, i, nPosicoes;

	
	file.open("Assets/TileMap/Mapa1/mapa1_posicoes_esqueletos.csv");
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

	nEsqueletos = rand() % (posicoes.size() - 3) + 3;

	for (i = 0; i < nEsqueletos; i++) {
		pos = posicoes[rand() % posicoes.size()];
		esq = new Esqueleto(pos.x, pos.y);
		listaEntidades.addEntidade(static_cast<Entidade*>(esq));
		GerenciadorDeColisao::getInstance()->addInimigo(static_cast<Inimigo*>(esq));
	}
}

void Fase1::criaMagos() {
	GerenciadorDeColisao::getInstance()->clear();
	listaEntidades.clear();
	listaEntidades.addEntidade(static_cast<Entidade*>(GerenciadorDeColisao::getInstance()->getJogador1()));
	listaEntidades.addEntidade(static_cast<Entidade*>(GerenciadorDeColisao::getInstance()->getJogador2()));


	std::vector<SDL_Point> posicoes;
	posicoes.push_back({ 960,256 });
	posicoes.push_back({ 1160, 456 });
	posicoes.push_back({ 500, 600 });
	posicoes.push_back({ 550, 300 });

	int nPosicoes = rand() % 2 + 3;

	Mago* mago = nullptr;
	for (int i = 0; i < nPosicoes; i++) {
		mago = new Mago(posicoes[i].x, posicoes[i].y);
		listaEntidades.addEntidade(static_cast<Entidade*>(mago));
		GerenciadorDeColisao::getInstance()->addInimigo(static_cast<Inimigo*>(mago));
	}

	posicoes.clear();
}

void Fase1::atualizar() {
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

void Fase1::save() {
	ofstream out;

	// limpa arquivos
	out.open("Saves/Fase1/espinhos.dat", ofstream::out | ofstream::trunc); out.close();
	out.open("Saves/Fase1/esqueletos.dat", ofstream::out | ofstream::trunc); out.close();
	out.open("Saves/Fase1/jogadores.dat", ofstream::out | ofstream::trunc); out.close();
	out.open("Saves/Fase1/lavas.dat", ofstream::out | ofstream::trunc); out.close();
	out.open("Saves/Fase1/magos.dat", ofstream::out | ofstream::trunc); out.close();
	out.open("Saves/Fase1/projeteis.dat", ofstream::out | ofstream::trunc); out.close();
	out.open("Saves/Fase1/map.dat", ofstream::out | ofstream::trunc); out.close();

	out.open("Saves/Fase1/map.dat");
	if (mapa->isOnBossRoom()) out << 1 << std::endl;
	else out << 0 << std::endl;

	listaEntidades.salvar(1);
}

void Fase1::saveRank(){//salva nomes dos jogadores -> sera coletado ao final da fase
	TextBox name1;
	name1.setFontToHeight("Assets/fonts/acme.ttf");
	name1.run("Player 1", 300, 200);

	TextBox name2;
	name2.setFontToHeight("Assets/fonts/acme.ttf");
	name2.run("Player 2", 300, 200);

	std::ofstream out;

	Jogador* jog1 = GerenciadorDeColisao::getInstance()->getJogador1();
	Jogador* jog2 = GerenciadorDeColisao::getInstance()->getJogador2();
	out.open("Saves/Fase1/ranking.dat", std::ios::app);
	out << name1.getInput() << " " << name2.getInput() << " " << jog1->getPontuacao() + jog2->getPontuacao() << std::endl;
	out.close();

}

void Fase1::load() {

	ifstream in;

	event_manager = GerenciadorDeEventos::getInstance();

	GerenciadorDeColisao::getInstance()->setFase(this);
	mapa = new Mapa;
	player_is_alive = true;

	int boss;
	in.open("Saves/Fase1/map.dat", ios::in);
	while (in >> boss) {}
	in.close();
	if (boss) mapa->setBossRoom(true);
	mapa->reload(1, static_cast<Fase*>(this));

	int x, y, w, h, tam, temp, raiva, sab, hp, index, points;
	float px, py, vx, vy;


	in.open("Saves/Fase1/espinhos.dat", ios::in);
	while (in >> x >> y >> w >> h >> tam) {
		Espinhos* esp = new Espinhos(x, y, w, h, tam);
		GerenciadorDeColisao::getInstance()->addObstaculo(esp);
		listaEntidades.addEntidade(static_cast<Entidade*>(esp));
	}
	in.close();

	in.open("Saves/Fase1/esqueletos.dat", ios::in);
	while (in >> px >> py >> vx >> vy >> raiva) {
		Esqueleto* esq = new Esqueleto(px, py, raiva);
		esq->getComponente<ComponenteTransform>()->velocidade.x = vx;
		esq->getComponente<ComponenteTransform>()->velocidade.y = vy;
		GerenciadorDeColisao::getInstance()->addInimigo(esq);
		listaEntidades.addEntidade(static_cast<Entidade*>(esq));
	}
	in.close();

	in.open("Saves/Fase1/jogadores.dat", ios::in);
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

	in.open("Saves/Fase1/lavas.dat", ios::in);
	while (in >> x >> y >> w >> h >> temp) {
		Lava* lav = new Lava(x, y, w, h, temp);
		GerenciadorDeColisao::getInstance()->addObstaculo(lav);
		listaEntidades.addEntidade(static_cast<Entidade*>(lav));
	}
	in.close();

	in.open("Saves/Fase1/magos.dat", ios::in);
	while (in >> px >> py >> vx >> vy >> sab) {
		Mago* mag = new Mago(px, py, sab);
		mag->getComponente<ComponenteTransform>()->velocidade.x = vx;
		mag->getComponente<ComponenteTransform>()->velocidade.y = vy;
		GerenciadorDeColisao::getInstance()->addInimigo(mag);
		listaEntidades.addEntidade(static_cast<Entidade*>(mag));
	}
	in.close();

	in.open("Saves/Fase1/projeteis.dat", ios::in);
	while (in >> vx >> vy >> px >> py) {
		Projetil* pro = new Projetil(px, py, vx, vy);
		GerenciadorDeColisao::getInstance()->addProjetil(pro);
		listaEntidades.addEntidade(static_cast<Entidade*>(pro));
	}
	in.close();
}