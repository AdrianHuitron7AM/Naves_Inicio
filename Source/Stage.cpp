#include "Game.h"
#include "Stage.h"

void CGame::InicializandoStage()
{
	nivel[0].fondoNivel = 0;
	nivel[0].balasMaximas = 3;
	nivel[0].NumeroEnemigosAEliminar = 10;
	nivel[0].NumeroEnemigosVisibles = 2;
	nivel[0].velocidadBalasEnemigo = 5;
	nivel[0].velocidadBalasPropias = 10;
	nivel[0].VelocidadNaveEnemigo = 10;
	nivel[0].VelocidadNavePropia = 5;
	nivel[0].vidaEnemigo = 1;

	nivel[1].fondoNivel = 1;
	nivel[1].balasMaximas = 6;
	nivel[1].NumeroEnemigosAEliminar = 20;
	nivel[1].NumeroEnemigosVisibles = 4;
	nivel[1].velocidadBalasEnemigo = 10;
	nivel[1].velocidadBalasPropias = 15;
	nivel[1].VelocidadNaveEnemigo = 17;
	nivel[1].VelocidadNavePropia = 8;
	nivel[1].vidaEnemigo = 2;
}