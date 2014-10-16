#include "Nave.h"
#include "Config.h"

Nave::Nave(SDL_Surface * screen, char * rutaImagen, int x, int )
{
	sprite = new Sprite(screen);
	sprite->CargarImagen(rutaImagen);
	this->x = x;
	this->y = y;
	autoMovimiento = false;
}

void Nave::SetAutoMovimiento(bool autoMovimiento)
{
	this->autoMovimiento = autoMovimiento;
}

void Nave::Actualizar()
{
	if (autoMovimiento)
	{
		MoverX(1);
	}
}

void Nave::Pintar()
{
	sprite->PintarModulo(0, x, y);
}

void Nave :: MoverX(int posicion)
{
	x += posicion;
}

//Esto es opcional
//void Nave ::MoverY(int posicion)
//{
//	y += posicion;
//}