#ifndef __GAME_H__
#define __GAME_H__
#include <SDL.h>
#include "Objeto.h"
#include "Config.h"
#include "Nave.h"
#include "Stage.h"

class CGame
{
public:
	enum Estado
	{
		ESTADO_INICIANDO,
		ESTADO_MENU,
		ESTADO_PRE_JUGANDO,
		ESTADO_JUGANDO,
		ESTADO_TERMINANDO,
		ESTADO_FINALIZANDO
	};

	bool Start();
	static CGame instanceGame;

	CGame();
	void Finalize();

private:
	int tick;
	int tiempoFrame;

	Objeto *textos;//textos del juego
	Objeto *menu;//fondo del menu
    Objeto *fondo;//fondo del juego

	void Iniciando();
	void Menu();
	void MoverEnemigo();
	bool EsLimitePantalla(Objeto * objeto,int bandera);

	int opcionSeleccionada;

	Uint8 * keys;//Esta variable nos servira para ver si determinadas teclas estan o no pulsadas
	SDL_Event event;// La variable event de tipo evento de SDL nos servira para monitorizar el teclado

	SDL_Surface *screen;
	Nave *nave;
	Nave *enemigoArreglo[10];
	Stage nivel[4];
	void InicializandoStage();
	int nivelActual;
	Estado estado;

	int vida;
	int enemigosEliminados;
};

#endif