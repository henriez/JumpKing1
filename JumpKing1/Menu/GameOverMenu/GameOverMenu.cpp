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


	background = GerenciadorGrafico::LoadTexture("Assets/Buttons/gameover.png");
}

void GameOverMenu::reset() {
	quit.reset();
}

int GameOverMenu::update() {
	quit.handleEvents();
	if (quit.click()) return BUTTON_QUIT;

	return NO_BUTTON_CLICKED; //nenhum botao foi clicado
}

void GameOverMenu::render() {
	SDL_Rect fonte = { 0,0,300,168 }; //dimensao da textura
	SDL_Rect destino = { 0,0,GerenciadorGrafico::getDimensoesJanela().x,GerenciadorGrafico::getDimensoesJanela().y };
	GerenciadorGrafico::render(background, fonte, destino);
	quit.render();
}