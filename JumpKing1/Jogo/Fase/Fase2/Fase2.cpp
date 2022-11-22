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
	posicoes.push_back({ 416, 192 });
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
	std::ofstream out;

		
	out.open("Saves/Fase2/jogadores.dat", std::ios::out);
	if (out) {
		Jogador* jog1 = GerenciadorDeColisao::getInstance()->getJogador1();
		Jogador* jog2 = GerenciadorDeColisao::getInstance()->getJogador2();
		if (mapa->isOnBossRoom()) out << 1 << std::endl;
		else out << 0 << std::endl;
		out << "1 " << jog1->getComponente<ComponenteTransform>()->posicao.x << " "
			<< jog1->getComponente<ComponenteTransform>()->posicao.y << " "
			<< jog1->getComponente<ComponenteTransform>()->velocidade.x << " "
			<< jog1->getComponente<ComponenteTransform>()->velocidade.y << " "
			<< jog1->getComponente<ComponenteSaude>()->getHealth() << " "
			<< jog1->getPontuacao() << std::endl
			<< "2 " << jog2->getComponente<ComponenteTransform>()->posicao.x << " "
			<< jog2->getComponente<ComponenteTransform>()->posicao.y << " "
			<< jog2->getComponente<ComponenteTransform>()->velocidade.x << " "
			<< jog2->getComponente<ComponenteTransform>()->velocidade.y << " "
			<< jog2->getComponente<ComponenteSaude>()->getHealth() << " "
			<< jog2->getPontuacao() << std::endl;
	}//aqui salva os dados
	else {
		std::cout << "Failed saving!\n";
		return;
	}
	out.close();

	GerenciadorDeSave::getInstance()->save(2);
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
	string esqueleto = "Esqueleto";
	string goblin = "Goblin";
	string chefe = "Mago";
	string jogador = "Jogador";
	string lava = "Lava";
	string espinhos = "Espinhos";
	string projetil = "Projetil";
	ifstream in;
	event_manager = GerenciadorDeEventos::getInstance();

	GerenciadorDeColisao::getInstance()->setFase(this);
	mapa = new Mapa;
	player_is_alive = true;

	this->id = id;

	in.open("Saves/Fase2/jogadores.dat", ios::in);
	if (in) {
		int saude, id, pontuacao;
		float x, y, vx, vy;
			in >> id; //se esta na boss room
		if (id) mapa->setBossRoom(true);
		mapa->reload(2, static_cast<Fase*>(this));
		while (in >> id >> x >> y >> vx >> vy >> saude >> pontuacao) {
			Jogador* jog = new Jogador;
			jog->getComponente<ComponenteTransform>()->posicao.x = x;
			jog->getComponente<ComponenteTransform>()->posicao.y = y;
			jog->getComponente<ComponenteTransform>()->velocidade.x = vx;
			jog->getComponente<ComponenteTransform>()->velocidade.y = vy;
			jog->getComponente<ComponenteSaude>()->init(saude);
			jog->setPontuacao(pontuacao);
			listaEntidades.addEntidade(static_cast<Entidade*>(jog));
			if (id == 1) {
				GerenciadorDeCamera::getInstance()->setJogador(jog);
				GerenciadorDeColisao::getInstance()->setJogador(jog);
				jog->getComponente<ComponenteSprite>()->setCaminhoArquivo("Assets/HenriqueIsFallingx32.png");
				event_manager->setJogador1(jog);
			}
			else if (id == 2) {
				GerenciadorDeCamera::getInstance()->setJogador2(jog);
				GerenciadorDeColisao::getInstance()->setJogador2(jog);
				jog->getComponente<ComponenteSprite>()->setCaminhoArquivo("Assets/player2.png");
				event_manager->setJogador2(jog);
			}
		}
	}
	else {
		jogo->mainMenu();
		std::cerr << " Arquivo nao pode ser aberto " << endl;
		return;
	}
	in.close();


	in.open("Saves/Fase2/obstaculos.dat", std::ios::in);
	if (in) {
		string classe, nomeClasse;
		int x, y, w, h;
			while (in >> classe >> nomeClasse >> x >> y >> w >> h) {
				if (nomeClasse == espinhos) {
					Espinhos* esp = new Espinhos;
					esp->getComponente<ComponenteColisao>()->set(x, y, w, h);
					GerenciadorDeColisao::getInstance()->addObstaculo(esp);
					}
				else if (nomeClasse == lava) {
					Lava* lav = new Lava;
					lav->getComponente<ComponenteColisao>()->set(x, y, w, h);
					GerenciadorDeColisao::getInstance()->addObstaculo(lav);
				}
			}
	}
	else {
		jogo->mainMenu();
		std::cerr << " Arquivo nao pode ser aberto " << endl;
		return;
	}
	in.close();

	in.open("Saves/Fase2/projeteis.dat", std::ios::in);
	if (in) {
		string classe, nomeClasse;
		float x, y, vx, vy;
		while (in >> classe >> nomeClasse >> x >> y >> vx >> vy) {
		Projetil* pro = new Projetil;
		pro->getComponente<ComponenteTransform>()->posicao.x = x;
		pro->getComponente<ComponenteTransform>()->posicao.y = y;
		pro->getComponente<ComponenteTransform>()->velocidade.x = vx;
		pro->getComponente<ComponenteTransform>()->velocidade.y = vy;
		GerenciadorDeColisao::getInstance()->addProjetil(pro);
		}
	}
	else {
		jogo->mainMenu();
		std::cerr << " Arquivo nao pode ser aberto " << endl;
		return;
	}
	in.close();

	in.open("Saves/Fase2/inimigos.dat", std::ios::in);
	if (in) {
		string classe, nomeClasse;
		float x, y, vx, vy;

		while (in >> classe >> nomeClasse >> x >> y >> vx >> vy) {
			if (nomeClasse == esqueleto) {
				Esqueleto* inimigo = new Esqueleto(x, y);
				inimigo->getComponente<ComponenteTransform>()->velocidade.x = vx;
				inimigo->getComponente<ComponenteTransform>()->velocidade.y = vy;
				GerenciadorDeColisao::getInstance()->addInimigo(inimigo);
				listaEntidades.addEntidade(static_cast<Entidade*>(inimigo));
			}
			else if (nomeClasse == goblin) {
				Goblin* inimigo = new Goblin(x, y);
				inimigo->getComponente<ComponenteTransform>()->velocidade.x = vx;
				inimigo->getComponente<ComponenteTransform>()->velocidade.y = vy;
				GerenciadorDeColisao::getInstance()->addInimigo(inimigo);
				listaEntidades.addEntidade(static_cast<Entidade*>(inimigo));
			}
			else if (nomeClasse == chefe) {
				Mago* inimigo = new Mago;
				inimigo->getComponente<ComponenteTransform>()->posicao.x = x;
				inimigo->getComponente<ComponenteTransform>()->posicao.y = y;
				inimigo->getComponente<ComponenteTransform>()->velocidade.x = vx;
				inimigo->getComponente<ComponenteTransform>()->velocidade.y = vy;
				GerenciadorDeColisao::getInstance()->addInimigo(inimigo);
				listaEntidades.addEntidade(static_cast<Entidade*>(inimigo));
			}
		}

		in.close();
	}
	else {
		jogo->mainMenu();
		std::cerr << " Arquivo nao pode ser aberto " << endl;
		return;
	}
}