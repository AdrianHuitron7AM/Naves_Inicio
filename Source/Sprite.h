#ifndef __SPRITE_H__
#define __SPRITE_H__
#include <SDL.h>

class Sprite
{
	SDL_Surface * imagen;
	SDL_Surface * screen;
public:
	Sprite(SDL_Surface *Screen);
	void CargarImagen(char * nombre);
	void PintarModulo(int nombre, int x, int y, int w, int h);

	//nave = IMG_LoadJPG_RW(SDL_RWFromFile("../Data/cuadro.jpg", "rb"));
};
#endif