/* ============================================================================ */
//
// Author: Henrique A. p. Mendes 
// github: https://github.com/HenriqueAPMendes
// linkedin: https://www.linkedin.com/in/henrique-mendes-508156215/
//
// A simple SDL2 textBox for dealing with user text input 
//
/* ============================================================================ */


// TextBox implementation

#include "Textbox.h"

TextBox::TextBox() {
	position = { 100,100,440,50 };
	backgroundColor = { 255,255,255,255 };
	outlineColor = { 0,0,0,255 };
	textColor = { 0,0,0,255 };
	font = nullptr;
	background = nullptr;
	renderer = nullptr;
	window = nullptr;
}

TextBox::~TextBox() {
	closeFont();

	if (renderer) SDL_DestroyRenderer(renderer);
	if (window) SDL_DestroyWindow(window);
}

void TextBox::closeFont() {
	if (font != nullptr) {
		TTF_CloseFont(font);
		font = nullptr;
	}
}

void TextBox::appendText(std::string tmp_Text) {
	text.append(tmp_Text);
}//add text to the end of Text

void TextBox::eraseOneChar() {//if the string is not empty it erases the last character
	if (!text.empty())
		text.pop_back();
}

void TextBox::setBackground(const char* path) {
	background = path;
}

void TextBox::setBoxBackgroundColor(SDL_Color background) {
	backgroundColor = background;
}//change background color

void TextBox::setBoxOutlineColor(SDL_Color outline) {
	outlineColor = outline;
}//change outline color

void TextBox::setTextColor(SDL_Color text) {
	textColor = text;
}//set the text color

void TextBox::setPosition(int x, int y, int w, int h) {
	position = { x,y,w,h };
}

bool TextBox::setFontToHeight(std::string fontPath) {
	int fontSize = 1;
	bool done = false;
	int fails = 0;
	while (!done) {
		/* raises font size until its greater than the position rect height */
		font = TTF_OpenFont(fontPath.c_str(), fontSize);
		if (fails == 10) {
			std::cout << "Failed 10 times in a row" << std::endl;
			return false;
		}
		if (font == NULL) {
			fails++;
			std::cout << "FontOpeningInSetFont:" << TTF_GetError() << std::endl;
			continue;
		}
		if (TTF_FontHeight(font) < position.h)
			fontSize++;	
		else {
			fontSize--;
			done = true;
		}
	}
	font = TTF_OpenFont(fontPath.c_str(), fontSize);
	return true;
}

bool TextBox::setFont(std::string fontPath, int fontSize) {//given a font file and a size it opens it,if it fails it prints error and returns false
	const char* tmp_FontPath = fontPath.c_str();
	font = TTF_OpenFont(tmp_FontPath, fontSize);
	if (font == NULL) {
		std::cout << "SetFontFailed:" << TTF_GetError() << std::endl;
		return false;
	}
	return true;
}

void TextBox::clearBox() {//prints a clear box to the renderer

	if (background == nullptr) { //raw text box
		//set 4 Uint8 to hold the original drawing color the renderer had to restore it at the end of the function
		Uint8 OriginalRed;
		Uint8 OriginalGreen;
		Uint8 OriginalBlue;
		Uint8 OriginalAlpha;

		SDL_GetRenderDrawColor(renderer, &OriginalRed, &OriginalGreen, &OriginalBlue, &OriginalAlpha);

		//create a position fill it with box background color then create an outline for it
		SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(renderer, &position);

		SDL_SetRenderDrawColor(renderer, outlineColor.r, outlineColor.g, outlineColor.b, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(renderer, &position);

		//Set the render draw color to the original, update the renderer and exit the function
		SDL_SetRenderDrawColor(renderer, OriginalRed, OriginalGreen, OriginalBlue, OriginalAlpha);

		SDL_Surface* tmpSurface;
		SDL_Texture* tmpTexture;
		tmpSurface = TTF_RenderText_Solid(font, message.c_str(), textColor);//load a surface with the text
		tmpTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);//create a texture from the surface

		SDL_Rect messageRect = { 0,0,0,0 };
		SDL_QueryTexture(tmpTexture, NULL, NULL, &messageRect.w, &messageRect.h);//prepare the texture
		messageRect = { (position.x + position.w / 2) - messageRect.w/2, position.y - messageRect.h, messageRect.w, messageRect.h };

		SDL_RenderCopy(renderer, tmpTexture, NULL, &messageRect);//copy to the renderer
		SDL_RenderPresent(renderer);
	}
	else { //in case there is a predefined background
		//window dimmensions
		SDL_Texture* temp = IMG_LoadTexture(renderer, background);
		int w = 0, h = 0;
		SDL_QueryTexture(temp, NULL, NULL, &w, &h);
		SDL_Rect dest = { 0,0,w,h };
		SDL_RenderCopy(renderer, temp, NULL, &dest);
		SDL_RenderPresent(renderer);
		SDL_DestroyTexture(temp);
	}
}

void TextBox::update() {
	SDL_Rect tmp_Rect = position;
	std::string renderedText = text;
	bool done = false;
	int textW;

	if (text.empty()) {//if text is empty make a clear box
		this->clearBox();
		return;
	}

	//check that the lenght of the string fits in the box and truncate(taking the first part out) if not
	while (!done) {
		TTF_SizeText(font, renderedText.c_str(), &textW, NULL);

		if (textW > tmp_Rect.w) renderedText = renderedText.substr(1, -1); //final part of the string
		else done = true;
	}

	SDL_Surface* TextSurface = TTF_RenderText_Solid(font, renderedText.c_str(), textColor);//load a surface with the text
	SDL_Texture* TextTexture = SDL_CreateTextureFromSurface(renderer, TextSurface);//create a texture from the surface

	this->clearBox();//clear the box

	SDL_QueryTexture(TextTexture, NULL, NULL, &tmp_Rect.w, &tmp_Rect.h);//prepare the texture
	SDL_RenderCopy(renderer, TextTexture, NULL, &tmp_Rect);//copy to the renderer

	

	SDL_RenderPresent(renderer);//update renderer

	SDL_DestroyTexture(TextTexture);
	SDL_FreeSurface(TextSurface);
}

void TextBox::run(std::string message, int windowW, int windowH) {
	setPosition(0.1 * windowW, 0.4 * windowH, 0.8 * windowW, position.h);
	this->message = message;
	window = SDL_CreateWindow("TextBox", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowW, windowH, SDL_WINDOW_POPUP_MENU);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawColor(renderer, 192, 192, 192, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	SDL_RenderClear(renderer);
	update();

	SDL_Event Event;
	bool done = false;

	while (!done) {
		while (SDL_PollEvent(&Event)) {
			if ((Event.type == SDL_WINDOWEVENT && Event.window.event == SDL_WINDOWEVENT_CLOSE)|| 
				(Event.type == SDL_KEYDOWN && Event.key.keysym.scancode == SDL_SCANCODE_RETURN))
				done = true;

			else if (Event.type == SDL_KEYDOWN && Event.key.keysym.sym == SDLK_BACKSPACE) {
				eraseOneChar();
				update();
			}
			else if (Event.type == SDL_TEXTINPUT) {
				appendText(Event.text.text);
				update();
			}
		}

	}
	closeFont();
	if (renderer) SDL_DestroyRenderer(renderer);
	if (window) SDL_DestroyWindow(window);
}

std::string TextBox::getInput() {
	return text;
}
