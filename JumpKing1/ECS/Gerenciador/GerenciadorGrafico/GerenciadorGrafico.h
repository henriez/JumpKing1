#pragma once 
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

class Fase;

class GerenciadorGrafico
{
public:
	~GerenciadorGrafico();

	static GerenciadorGrafico* getInstance();
	static void deleteInstance();

	void init(const char* nomeJanela, int largJanela, int alturaJanela, bool telaCheia);
	void clear() { SDL_RenderClear(renderer); }
	void present() { SDL_RenderPresent(renderer); }

	SDL_Texture* LoadTexture(const char* fileName);
	SDL_Texture* TextTexture(std::string str);
	SDL_Point getDimensoesJanela();

	void render(SDL_Texture* tex, SDL_Rect fonte, SDL_Rect destino, bool flip = false);

	void renderFase(Fase* fase);

	void renderTile(SDL_Rect fonte, SDL_Rect destino);
	void renderHitbox(SDL_Rect fonte, SDL_Rect destino);
	void renderEspinho(SDL_Rect fonte, SDL_Rect destino);
	void renderLava(SDL_Rect fonte, SDL_Rect destino);
	void renderRect(SDL_Rect rect, SDL_Color fill, SDL_Color outline);

	void renderCoracao(SDL_Rect fonte, SDL_Rect destino);
	void renderPontuacao(int pontuacao);
	void renderText(std::string text, SDL_Point position);

	void renderInimigoHitbox(SDL_Rect destino);
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
