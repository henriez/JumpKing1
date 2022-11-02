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
	start.set(1400, 190, 250, 125);
	start.setTex("Assets/Buttons/New Game Button.png");

	settings.set(1400, 370, 250, 125);
	settings.setTex("Assets/Buttons/Options Button.png");

	leaderboard.set(1400, 550, 250, 125);
	leaderboard.setTex("Assets/Buttons/Button Leaderboard.png");

	quit.set(100, 900, 250, 125);
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