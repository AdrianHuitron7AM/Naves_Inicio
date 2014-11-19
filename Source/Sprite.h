
#ifndef __SPRITE_H__
#define __SPRITE_H__
#include <SDL.h>
#include "SpriteDef.h"

class Sprite
{
	SDL_Surface * imagen;//la imagen a manipular
	SDL_Surface * screen;//la pantalla
	SpriteDef spriteDef;//definicion de sprite

public:
	Sprite(SDL_Surface * screen);//Constructor, recibe la pantalla
	~Sprite();//Destructor, se llama con delete
	void CargarImagen(char* path); 
	void PintarModulo( int nombre, int x, int y);
	int WidthModule(int module);
	int HeightModule(int module);
};

#endif