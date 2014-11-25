#ifndef __NAVE_H__
#define __NAVE_H__
#include "objeto.h"

class Nave
{
	Objeto * nave;
	Objeto * bala;
public:
	Nave(SDL_Surface * screen, char * rutaImagen, int x, int y, int module);
	void Pintar();
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	Objeto * GetNaveObjeto();

};

#endif
