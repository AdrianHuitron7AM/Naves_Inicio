#include "Nave.h"
#include "Config.h"

Nave::Nave(SDL_Surface * screen, char * rutaImagen)
{
	sprite = new Sprite(screen);
	sprite->CargarImagen(rutaImagen);
	x = (WIDTH_SCREEN / 2) - sprite->WidthModule(0) / 2; //Posicionamiento en el centro de x (Ancho)
	y = (HEIGHT_SCREEN - 80) - sprite->HeightModule(0); // Posicionamiento en 1/4 (la mitad de la mitad) de la pantalla en y, dejando un espacio de 80px (Alto)
}

void Nave::Pintar()
{
	sprite->PintarModulo(0, x, y);
}