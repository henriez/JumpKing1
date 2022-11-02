#include "MainMenu.h"
#include "../../ECS/Gerenciador/GerenciadorGrafico.h"
#include "../../Jogo/Jogo.h"

MainMenu::MainMenu() {
	background = nullptr;
}

MainMenu::~MainMenu() {
	SDL_DestroyTexture(background);
}

void MainMenu::init() {
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);

	start.set(0.75 * dm.w, 0.1 * dm.w, 0.13 * dm.w, 0.115*dm.h);
	start.setTex("Assets/Buttons/New Game Button.png");

	settings.set(0.75 * dm.w, 0.2 * dm.w, 0.13 * dm.w, 0.115 * dm.h);
	settings.setTex("Assets/Buttons/Options Button.png");

	leaderboard.set(0.75 * dm.w, 0.3 * dm.w, 0.13 * dm.w, 0.115 * dm.h);
	leaderboard.setTex("Assets/Buttons/Button Leaderboard.png");

	quit.set(0.1 * dm.w, 0.8 * dm.h, 0.13 * dm.w, 0.115 * dm.h);
	quit.setTex("Assets/Buttons/Exit Button.png");

	background = GerenciadorGrafico::LoadTexture("Assets/Buttons/menu.png");
}

void MainMenu::reset() {
	start.reset();
	leaderboard.reset();
	settings.reset();
	quit.reset();
}

int MainMenu::update() {
	start.handleEvents();
	if (start.click()) return BUTTON_START1;

	settings.handleEvents();
	if (settings.click()) return BUTTON_SETTINGS;

	quit.handleEvents();
	if (quit.click()) return BUTTON_QUIT;

	leaderboard.handleEvents();
	if (leaderboard.click()) return BUTTON_LEADERBOARD;
	

	return NO_BUTTON_CLICKED; //nenhum botao foi clicado
}

void MainMenu::render() {
	SDL_Rect fonte = { 0,0,1280,720 };
	SDL_Rect destino = { 0,0,GerenciadorGrafico::getDimensoesJanela().x,GerenciadorGrafico::getDimensoesJanela().y };
	GerenciadorGrafico::render(background, fonte, destino);

	start.render();
	settings.render();
	quit.render();
	leaderboard.render();
}