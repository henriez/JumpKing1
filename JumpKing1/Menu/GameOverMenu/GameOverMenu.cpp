#include "GameOverMenu.h"
#include "../../ECS/Gerenciador/GerenciadorGrafico/GerenciadorGrafico.h"
#include "../../Jogo/Jogo.h"

GameOverMenu::GameOverMenu() {
	background = nullptr;
}

GameOverMenu::~GameOverMenu() {
	SDL_DestroyTexture(background);
}

void GameOverMenu::init() {
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);

	quit.set(0.1* dm.w, 0.45 * dm.h, 0.13 * dm.w, 0.115 * dm.h);
	quit.setTex("Assets/Buttons/Exit Button.png");

	save.set(0.77 * dm.w, 0.45 * dm.h, 0.13 * dm.w, 0.115 * dm.h);
	save.setTex("Assets/Buttons/Save.png");

	background = graphics->LoadTexture("Assets/Buttons/gameover.png");
}

void GameOverMenu::reset() {
	quit.reset();
	save.reset();
}

int GameOverMenu::update() {
	graphics->clear();
	SDL_PollEvent(&Jogo::evento);
	render();
	graphics->present();

	quit.handleEvents();
	if (quit.click()) return BUTTON_QUIT;
	
	save.handleEvents();
	if (save.click()) return BUTTON_SAVE;

	return NO_BUTTON_CLICKED; //nenhum botao foi clicado
}

void GameOverMenu::render() {
	SDL_Rect fonte = { 0,0,300,168 }; //dimensao da textura
	SDL_Rect destino = { 0,0,graphics->getDimensoesJanela().x,graphics->getDimensoesJanela().y };
	graphics->render(background, fonte, destino);
	quit.render();
	save.render();
}