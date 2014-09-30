
#include "Sprite.h"
#include <SDL.h>
void Sprite :: CargarImagen(char * nombre)
{
	imagen = SDL_LoadBMP(nombre);
}
