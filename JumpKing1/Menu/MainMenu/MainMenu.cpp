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
	start.set(100, 100, 324, 156);
	start.setTex("Assets/Buttons/start.png");

	settings.set(100, 300, 324, 156);
	settings.setTex("Assets/Buttons/settingstest.png");

	quit.set(100, 500, 324, 156);
	quit.setTex("Assets/Buttons/quit.png");

	leaderboard.set(500, 300, 324, 156);
	leaderboard.setTex("Assets/Buttons/leaderboard.png");

	background = GerenciadorGrafico::CarregaTextura("Assets/Buttons/menu.png");
}

void MainMenu::reset() {
	start.reset();
	leaderboard.reset();
	settings.reset();
	quit.reset();
}

int MainMenu::update() {
	start.handleEvents();
	if (start.click()) return BUTTON_START;

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
	GerenciadorGrafico::Desenhe(background, fonte, destino);

	start.render();
	settings.render();
	quit.render();
	leaderboard.render();
}