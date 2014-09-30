#ifndef __SPRITE_H__
#define __SPRITE_H__
#include <SDL.h>

class Sprite
{
	SDL_Surface * imagen;
public:
	void CargarImagen(char * nombre);

	//nave = IMG_LoadJPG_RW(SDL_RWFromFile("../Data/cuadro.jpg", "rb"));
}
#endif