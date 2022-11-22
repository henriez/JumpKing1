#include "Jogo.h"
#include <iostream>
#include "Fase/Fase.h"
#include "Fase/Fase1/Fase1.h"
#include "Fase/Fase2/Fase2.h"
#include "../ECS/Gerenciador/GerenciadorGrafico/GerenciadorGrafico.h"
#include "../ECS/Gerenciador/GerenciadorDeColisao/GerenciadorDeColisao.h"
using namespace std;

#define FPS 60

SDL_Event Jogo::evento;

Jogo::Jogo(const char* nomeJanela, int largJanela, int alturaJanela, bool telaCheia) {
	rodando = true;
	fase = nullptr;
	graphics = GerenciadorGrafico::getInstance();
	inicializar(nomeJanela, largJanela, alturaJanela, telaCheia);
}

Jogo::~Jogo() {
	SDL_Quit();
	delete fase;
	GerenciadorGrafico::deleteInstance();
}

void Jogo::inicializar(const char* nomeJanela, int largJanela, int alturaJanela, bool telaCheia) {
	SDL_Init(SDL_INIT_EVERYTHING);

	graphics->init(nomeJanela, largJanela, alturaJanela, telaCheia);

	menu.init();
	mainMenu();
	srand(time(NULL));
}

void Jogo::mainMenu() {

	menu.start.reset();
	int click = menu.start.update();
	
	while (click == NO_BUTTON_CLICKED)
		click = menu.start.update();
	

	switch (click) { //apos algum clique
	case BUTTON_START1:
		levelMenu();
		break;
	case BUTTON_LEADERBOARD:
		leaderboardMenu();
		break;		
	case BUTTON_SETTINGS:
		settingsMenu();
		break;
	case BUTTON_QUIT:
		rodando = false;
		break;
	case BUTTON_LOAD:
		loadMenu();
		break;
	default:
		break;
	}

}

void Jogo::pauseMenu() {

	menu.pause.reset();
	int click = menu.pause.update();

	while (click == NO_BUTTON_CLICKED) 
		click = menu.pause.update();
	

	switch (click) { //apos algum clique
	case BUTTON_RESUME:
		atualizar();
		break;
	case BUTTON_SAVE:
		fase->save(); // get points
		pauseMenu();
		break;
	case BUTTON_QUIT:
		fase->clear();
		mainMenu();
		break;
	default:
		break;
	}
}

void Jogo::gameOverMenu() {
	
	if (fase->beaten()) {
		menu.gameOver.won();
	}
	menu.gameOver.reset();
	int click = menu.gameOver.update();

	while (click == NO_BUTTON_CLICKED)
		click = menu.gameOver.update();


	switch (click) { //apos algum clique
	case BUTTON_QUIT:
		mainMenu();
		break;
	case BUTTON_SAVE:
		fase->saveRank(); //salvar
		mainMenu();
		break;
	default:
		break;
	}
}

void Jogo::settingsMenu() {

	//fazer o menu de settings
	//por enquanto redireciona para mainMenu()
	menu.settings.reset();
	int click = menu.settings.update();

	while (click == NO_BUTTON_CLICKED) 
		click = menu.settings.update();
	
	
	switch (click) { //apos algum clique
	case BUTTON_QUIT:
		mainMenu();
		break;
	default:
		break;
	}

}

void Jogo::leaderboardMenu() {

	menu.leaderboard.reset();
	int click = menu.leaderboard.update();

	while (click == NO_BUTTON_CLICKED) {
		click = menu.leaderboard.update();
		//graphics->present();
	}
	

	switch (click) { //apos algum clique
	case BUTTON_QUIT:
		mainMenu();
		break;
	case BUTTON_START1:
		showRanking(1);
		break;
	case BUTTON_START2:
		showRanking(2);
		break;
	default:
		break;
	}

}

void Jogo::levelMenu() {

	Fase1* fase1 = nullptr;
	Fase2* fase2 = nullptr;

	menu.level.reset();
	int click = menu.level.update();

	while (click == NO_BUTTON_CLICKED)
		click = menu.level.update();
	

	switch (click) { //apos algum clique
	case BUTTON_START1:
		fase1 = new Fase1;
		fase1->setJogo(this);
		fase1->inicializar();
		fase = static_cast<Fase*>(fase1);
		// fase = Fase1Builder::build()
		atualizar();
		break;
	case BUTTON_START2:
		fase2 = new Fase2;
		fase2->setJogo(this);
		fase2->inicializar();
		fase = static_cast<Fase*>(fase2);
		atualizar();
		break;
	case BUTTON_QUIT:
		mainMenu();
		break;
	default:
		break;
	}

}

void Jogo::loadMenu() {
	Fase1* fase1 = nullptr;
	Fase2* fase2 = nullptr;

	menu.load.reset();
	int click = menu.load.update();

	while (click == NO_BUTTON_CLICKED)
		click = menu.load.update();
	

	switch (click) { //apos algum clique
	case BUTTON_START1:
		fase1 = new Fase1;
		fase1->setJogo(this);
		fase1->load(); //carregar de arquivo
		fase = static_cast<Fase*>(fase1);
		break;
	case BUTTON_START2:
		fase2 = new Fase2;
		fase2->setJogo(this);
		fase2->load(); //carregar de arquivo
		fase = static_cast<Fase*>(fase2);
		break;
	case BUTTON_QUIT:
		mainMenu();
		break;
	default:
		break;
	}
}

void Jogo::atualizar() {
	Uint32 ticks0 = SDL_GetTicks();
	Uint32 finalTicks;
	Uint32 framedelay = 1000 / FPS;
	analisaEventos();

	if (!rodando) return;
	fase->atualizar();

	render();

	finalTicks = SDL_GetTicks();
	if (finalTicks - ticks0 < framedelay)
		SDL_Delay(framedelay - (finalTicks - ticks0));
}

void Jogo::render() {
	graphics->renderFase(fase);
}

void Jogo::analisaEventos() {
	SDL_PollEvent(&evento);

	if (evento.type == SDL_QUIT)
		rodando = false;

	else if (evento.type == SDL_KEYDOWN)
		if (evento.key.keysym.sym == SDLK_ESCAPE) //pause
			pauseMenu();
												  //rodando = false;
}

bool Jogo::executando() {
	return rodando;
}

void Jogo::showRanking(int id) {

	// le o arquivo de ranking
	ifstream in;

	if (id == 1) in.open("Saves/Fase1/ranking.dat", ios::in);
	else if (id == 2) in.open("Saves/Fase2/ranking.dat", ios::in);

	string nome1, nome2, line;
	map<int, string> rankings;
	int pontuacao;

	while (in >> nome1 >> nome2 >> pontuacao) {
		line = to_string(pontuacao) + ": " + nome1 + " & " + nome2;
		rankings.insert(pair<int, string>(pontuacao, line));
	}
	in.close();


	//Renderiza o menu leaderboard normalmente
	graphics->clear();
	SDL_PollEvent(&Jogo::evento);
	menu.leaderboard.render();


	//Retangulo de fundo da tabela
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);

	SDL_Rect ranking = { 0.49 * dm.w, 0.15 * dm.h, 0.4 * dm.w, 0.5 * dm.h };
	SDL_Color grey = { 192,192,192,255 };
	SDL_Color black = { 0,0,0,255 };
	graphics->renderRect(ranking, grey, black);

	graphics->present();

	//Renderiza os textos na ordem

	int i = 0;
	SDL_Point position = { ranking.x + 10, ranking.y + 10 };

	//Percorre o map com as pontuacoes em ordem decrescente
	map<int, string>::reverse_iterator it;
	for (it = rankings.rbegin(); it != rankings.rend() && i < 8; it++, i++) {
		graphics->renderText(it->second, position);
		position.y += 50;
	}

	graphics->present();

	//Tratamento padrao do menu
	menu.leaderboard.reset();
	int click = menu.leaderboard.updateRanking();

	graphics->present();

	while (click == NO_BUTTON_CLICKED)
		click = menu.leaderboard.updateRanking();

	rankings.clear();

	switch (click) { //apos algum clique
	case BUTTON_QUIT:
		leaderboardMenu();
		break;
	case BUTTON_START1:
		showRanking(1);
		break;
	case BUTTON_START2:
		showRanking(2);
		break;
	default:
		break;
	}
}
