#ifndef __NAVE_H__
#define __NAVE_H__
#include "Sprite.h"

class Nave
{
	Sprite * sprite;
	int x;
	int y;
	int w;
	int h;
	bool autoMovimiento;
	int pasoActual;
	int pasoLimite;
	int module;

public:
	void MoverX(int posicion);

	void MoverY(int posicion);
	Nave(SDL_Surface * screen,char * rutaImagen,int x,int y, int module);//constructor
	void SetAutoMovimiento(bool autoMovimiento);
	void SetPasoLimite(int pasos);
	int ObtenerPasoActual();
	void IncrementarPasoActual();
	bool EstaColicionando(Nave * b);
	void Pintar();
	void Pintar(int module, int x, int y);
	void Actualizar();
	int ObtenerX();
	int ObtenerY();
	int ObtenerW();
	int ObtenerH();
}


#endif
;