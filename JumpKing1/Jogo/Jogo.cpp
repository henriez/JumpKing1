#include "Jogo.h"
#include <iostream>
#include "Fase/Fase.h"
#include "../ECS/Gerenciador/GerenciadorGrafico/GerenciadorGrafico.h"
#include "../ECS/Gerenciador/GerenciadorDeColisao/GerenciadorDeColisao.h"

#define FPS 60

SDL_Event Jogo::evento;

Jogo::Jogo(const char* nomeJanela, int largJanela, int alturaJanela, bool telaCheia) {
	rodando = true;
	fase = new Fase;
	graphics = GerenciadorGrafico::getInstance();
	inicializar(nomeJanela, largJanela, alturaJanela, telaCheia);
}

Jogo::~Jogo() {
	//fase->clear();
	SDL_Quit();
	delete fase;
}

void Jogo::inicializar(const char* nomeJanela, int largJanela, int alturaJanela, bool telaCheia) {
	SDL_Init(SDL_INIT_EVERYTHING);

	graphics->init(nomeJanela, largJanela, alturaJanela, telaCheia);
	fase->setJogo(this);

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

	menu.gameOver.reset();
	int click = menu.gameOver.update();

	while (click == NO_BUTTON_CLICKED)
		click = menu.gameOver.update();


	switch (click) { //apos algum clique
	case BUTTON_QUIT:
		fase->clear();
		mainMenu();
		break;
	case BUTTON_SAVE:
		fase->saveRank(); //salvar
		gameOverMenu();
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
		SDL_Delay(100);
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

	menu.level.reset();
	int click = menu.level.update();

	while (click == NO_BUTTON_CLICKED)
		click = menu.level.update();
	

	switch (click) { //apos algum clique
	case BUTTON_START1:
		fase->inicializar(1);
		atualizar();
		break;
	case BUTTON_START2:
		fase->inicializar(2);
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
	menu.load.reset();
	int click = menu.load.update();

	while (click == NO_BUTTON_CLICKED)
		click = menu.load.update();
	

	switch (click) { //apos algum clique
	case BUTTON_START1:
		fase->load(1); //carregar de arquivo
		break;
	case BUTTON_START2:
		fase->load(2); //carregar de arquivo
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

	// carrega a textura com os textos
	std::ifstream in;

	if (id == 1) in.open("Saves/Fase1/ranking.dat");
	else if (id == 2) in.open("Saves/Fase2/ranking.dat");

	std::string nome1, nome2, line, finalString = "";
	int pontuacao;

	while (in >> nome1 >> nome2 >> pontuacao) {
		line = std::to_string(pontuacao) + ": " + nome1 + " & " + nome2;
		finalString.append(line);
	}
	in.close();

	//renderiza tabelas
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);

	SDL_Rect ranking = { 0.49 * dm.w, 0.15 * dm.h, 0.4 * dm.w, 0.5 * dm.h };
	SDL_Color grey = { 192,192,192,255 };
	SDL_Color black = { 0,0,0,255 };
	graphics->renderRect(ranking, grey, black);

	
	SDL_Texture* textTex = graphics->TextTexture(finalString);
	SDL_Rect textRect = { 0,0,0,0 };
	SDL_QueryTexture(textTex, NULL, NULL, &textRect.w, &textRect.h);
	graphics->render(textTex, textRect, ranking);


	menu.leaderboard.reset();
	int click = menu.leaderboard.updateRanking(textTex, ranking);

	graphics->present();

	while (click == NO_BUTTON_CLICKED)
		click = menu.leaderboard.updateRanking(textTex, ranking);

	switch (click) { //apos algum clique
	case BUTTON_QUIT:
		leaderboardMenu();
		break;
	case BUTTON_START1:
		if(id != 1)
			showRanking(1);
		break;
	case BUTTON_START2:
		if (id != 2)
			showRanking(2);
		break;
	default:
		break;
	}

	SDL_DestroyTexture(textTex);
}
