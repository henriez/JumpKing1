#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_events.h>
#include <string>

#include "../../ECS/Componentes/Vector2D/Vector2D.h"
#include "../../ECS/Gerenciador/GerenciadorGrafico/GerenciadorGrafico.h"

#define BUTTON_QUIT 1
#define BUTTON_START1 2
#define BUTTON_START2 3
#define BUTTON_SETTINGS 4
#define BUTTON_RESUME 5
#define BUTTON_LEADERBOARD 6

#define NO_BUTTON_CLICKED 7

class Button {
private:
	SDL_Rect pos;
	SDL_Texture* texture;

	bool isHovering;
	bool isClicked;

	Vector2D getMousePos();
public:

	Button();
	~Button();

	void set(int xpos, int ypos, int width, int height);
	void setTex(const char* path);

	void reset();

	virtual void handleEvents();
	void render();
	
	bool click();
};

