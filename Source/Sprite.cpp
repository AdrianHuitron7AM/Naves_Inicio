
#include "Sprite.h"
#include <SDL.h>


Sprite::Sprite(SDL_Surface * screen)//constructor
{
	
	this->screen= screen;
}


Sprite::~Sprite()// Destructor
{
	SDL_FreeSurface(imagen);
}

void Sprite::CargarImagen(char * path)
{
	imagen = SDL_LoadBMP(path);
	SDL_SetColorKey(imagen, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(imagen->format, 255, 0, 255));

}

void Sprite::PintarModulo(int nombre, int x, int y )
{
	SDL_Rect src;
	src.x = spriteDef.modulos[nombre].x;
	src.y = spriteDef.modulos[nombre].y;
	src.w = spriteDef.modulos[nombre].w;
	src.h = spriteDef.modulos[nombre].h;
	SDL_Rect dest;
	dest.x=x;
	dest.y=y;
	SDL_BlitSurface(imagen,&src,screen,&dest);
}
int Sprite::WidthModule(int module){
	return spriteDef.modulos[module].w;
}

int Sprite::HeightModule(int module){
	return spriteDef.modulos[module].h;
}