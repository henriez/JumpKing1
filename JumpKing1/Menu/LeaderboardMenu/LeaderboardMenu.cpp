#include "LeaderboardMenu.h"
#include "../../ECS/Gerenciador/GerenciadorGrafico/GerenciadorGrafico.h"
#include "../../Jogo/Jogo.h"

LeaderboardMenu::LeaderboardMenu() {
	background = nullptr;
}

LeaderboardMenu::~LeaderboardMenu() {
	SDL_DestroyTexture(background);
}

void LeaderboardMenu::init() {
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);

	quit.set(0.1 * dm.w, 0.8 * dm.h, 0.13 * dm.w, 0.115 * dm.h);
	quit.setTex("Assets/Buttons/Back Button.png");

	level1.set(0.1 * dm.w, 0.25 * dm.h, 0.13 * dm.w, 0.115 * dm.h);
	level1.setTex("Assets/Buttons/Level 1.png");

	level2.set(0.1 * dm.w, 0.43 * dm.h, 0.13 * dm.w, 0.115 * dm.h);
	level2.setTex("Assets/Buttons/Level 2.png");

	background = graphics->LoadTexture("Assets/Buttons/menu.png");
}

void LeaderboardMenu::reset() {
	level1.reset();
	level2.reset();
	quit.reset();
}

int LeaderboardMenu::update() {
	graphics->clear();
	SDL_PollEvent(&Jogo::evento);
	render();
	graphics->present();

	level1.handleEvents();
	if (level1.click()) return BUTTON_START1;

	level2.handleEvents();
	if (level2.click()) return BUTTON_START2;

	quit.handleEvents();
	if (quit.click()) return BUTTON_QUIT;

	return NO_BUTTON_CLICKED; //nenhum botao foi clicado
}

int LeaderboardMenu::updateRanking(SDL_Texture* textTex, SDL_Rect ranking) {
	graphics->clear();
	SDL_PollEvent(&Jogo::evento);
	render();

	SDL_Color grey = { 192,192,192,255 };
	SDL_Color black = { 0,0,0,255 };
	graphics->renderRect(ranking, grey, black);

	SDL_Rect textRect = { 0,0,0,0 };
	SDL_QueryTexture(textTex, NULL, NULL, &textRect.w, &textRect.h);
	graphics->render(textTex, textRect, ranking);

	graphics->present();

	level1.handleEvents();
	if (level1.click()) return BUTTON_START1;

	level2.handleEvents();
	if (level2.click()) return BUTTON_START2;

	quit.handleEvents();
	if (quit.click()) return BUTTON_QUIT;

	return NO_BUTTON_CLICKED; //nenhum botao foi clicado
}

void LeaderboardMenu::render() {
	SDL_Rect fonte = { 0,0,1280,720 };
	SDL_Rect destino = { 0,0,graphics->getDimensoesJanela().x,graphics->getDimensoesJanela().y}; //receber dados da janela
	graphics->render(background, fonte, destino);
	quit.render();
	level1.render();
	level2.render();
}