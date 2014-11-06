#ifndef __NAVE_H__
#define __NAVE_H__
#include "Sprite.h"
#include <SDL.h>
class Nave
{
	Sprite *sprite;
	int x;
	int y;
	int w;
	int h;
	bool autoMovimiento;
	int pasoActual;
	int pasoLimite;
public:
	void MoverX(int posicion);
	void MoverY(int posicion);
	Nave(SDL_Surface * screen, char * rutaImagen, int x, int y); //Constructor
	void SetAutoMovimiento(bool autoMovimiento);
	void SetPasoLimite(int pasos);
	int ObtenerPasoActual();
	void IncrementarPasoActual();
	bool EstaColisionando(Nave * b);
	void Pintar();
	void Actualizar();
	int ObtenerX();
	int ObtenerY();
	int ObtenerW();
	int ObtenerH();
};


#endif