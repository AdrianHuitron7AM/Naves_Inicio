#ifndef __NAVE_H__
#define __NAVE_H__
#include "objeto.h"
#include "Config.h"

class Nave
{
	Objeto * nave;
	Objeto * bala[MAXIMO_DE_BALAS];
	int balasVisibles;
	bool visible;
	bool colision;
public:
	Nave(SDL_Surface * screen, char * rutaImagen, int x, int y, int module);
	void Pintar(int tipoNave);
	void Disparar(int tipoNave, int balas);
	void AutoDisparar(int balas);

	void MoveLeft(int velocidad);
	void MoveRight(int velocidad);
	void MoveUp(int velocidad);
	void MoveDown(int velocidad);

	void setVisible(bool visible);
	bool estaColisionandoConBala(Nave * nave);
	void simularColision(bool colision);
	void CrearNuevo();
	Objeto * GetNaveObjeto();

};

#endif
