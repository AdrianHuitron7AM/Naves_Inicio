#ifndef __SPRITE_H__
#define __SPRITE_H__
#include <SDL.h>
#include "SpriteDef.h"

class Sprite
{
	SDL_Surface * imagen; //Imagen a manipular
	SDL_Surface * screen; //Pantalla
	SpriteDef spriteDef; //Definicion de sprite
public:
	Sprite(SDL_Surface *Screen); //Constructor
	~Sprite(); //Destructor, se manda llamar con delete
	void CargarImagen(char * nombre);
	void PintarModulo(int nombre, int x, int y);
	int WidthModule(int module);
	int HeightModule(int module);
};
#endif