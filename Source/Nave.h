#ifndef __NAVE_H__
#define __NAVE_H__
#include "Sprite.h"
#include <SDL.h>
class Nave
{
	Sprite *sprite;
	int x;
	int y;
	bool autoMovimiento;
public:
	void MoverX(int posicion);
	//void MoverY(int posicion);
	Nave(SDL_Surface * screen, char * rutaImagen, int x, int y); //Constructor
	void SetAutoMovimiento(bool autoMovimiento);
	void Pintar();
	void Actualizar();
};


#endif