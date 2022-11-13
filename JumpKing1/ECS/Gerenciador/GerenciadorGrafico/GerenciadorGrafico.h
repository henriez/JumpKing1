#pragma once 
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class LeaderboardMenu;
class LevelMenu;
class MainMenu;
class PauseMenu;
class GameOverMenu;
class SettingsMenu;
class SaveMenu;
class LoadMenu;
class Fase;
class ListaDeEntidades;

class GerenciadorGrafico
{
public:
	~GerenciadorGrafico();

	static GerenciadorGrafico* getInstance();
	static void deleteInstance();
	void init(const char* nomeJanela, int largJanela, int alturaJanela, bool telaCheia);

	SDL_Texture* LoadTexture(const char* fileName);
	//static void render(SDL_Texture* tex, SDL_Rect fonte, SDL_Rect destino);
	void render(SDL_Texture* tex, SDL_Rect fonte, SDL_Rect destino, bool flip = false);

	SDL_Point getDimensoesJanela();

	void renderFase(Fase* fase);

	void renderTile(SDL_Rect fonte, SDL_Rect destino);
	void renderHitbox(SDL_Rect fonte, SDL_Rect destino);
	void renderEspinho(SDL_Rect fonte, SDL_Rect destino);
	void renderLava(SDL_Rect fonte, SDL_Rect destino);

	void renderCoracao(SDL_Rect fonte, SDL_Rect destino);
	void renderPontuacao(int pontuacao);

	void renderMenu(LeaderboardMenu& leaderboard);
	void renderMenu(LevelMenu& level);
	void renderMenu(MainMenu& start);
	void renderMenu(PauseMenu& pause);
	void renderMenu(GameOverMenu& gameover);
	void renderMenu(SettingsMenu& settings);
	void renderMenu(SaveMenu& save);
	void renderMenu(LoadMenu& load);
private:
	GerenciadorGrafico();
	static GerenciadorGrafico* manager;

	SDL_Texture* tileset;
	SDL_Texture* tilesetHitbox;
	SDL_Texture* lava;
	SDL_Texture* espinhos;
	SDL_Texture* coracao;
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Point dimensoesJanela;
	TTF_Font* font;
};
