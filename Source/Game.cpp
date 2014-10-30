#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "Config.h"
#include <SDL.h>
#include <SDL_image.h>

CGame::CGame()
{
	estado = ESTADO_INICIANDO;
	atexit(SDL_Quit);
}

// Con esta función eliminaremos todos los elementos en pantalla
void CGame::Finalize()
{
	delete(nave);
	SDL_FreeSurface(screen);
	SDL_Quit();
}


void CGame::Iniciando()
{
	if (SDL_Init(SDL_INIT_VIDEO)){

		printf("Error %s ", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	screen = SDL_SetVideoMode(WIDTH_SCREEN, HEIGHT_SCREEN, 24, SDL_HWSURFACE);
	/*if (screen == NULL)
	{
		screen = SDL_SetVideoMode(640, 480, 24, SDL_SWSURFACE);
	}
	if (screen == NULL)
	{
		screen = SDL_SetVideoMode(640, 480, 24, SDL_SWSURFACE);
	}*/
	if (screen == NULL)
	{
		printf("Error %s ", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_WM_SetCaption("Mi primer Juego", NULL);


	nave = new Nave(screen, "../Data/minave.bmp", (WIDTH_SCREEN / 2) /*- (sprite->WidthModule(0) / 2)*/, (HEIGHT_SCREEN - 80) /*- sprite->HeightModule(0)*/);
	enemigo = new Nave(screen, "../Data/enemigo.bmp", 0, 0);
	enemigo->SetAutoMovimiento(false);
	enemigo->SetPasoLimite(4);

	//delete nave;
}

bool CGame::Start()
{
	// Esta variable nos ayudara a controlar la salida del juego...
	int salirJuego = false;
	int i = 0;
	while (salirJuego == false){

		//Maquina de estados
		switch(estado)
		{
		case Estado::ESTADO_INICIANDO: //INICIALIZAR
			printf("1. ESTADO_INICIANDO");
			Iniciando();
			estado = ESTADO_MENU;
			break;
		case Estado::ESTADO_MENU: //MENÚ
			if (i == 0) //bandera que controla que el programa mande a ESTADO_MENU sin regresar a ESTADO_JUGANDO
			{
				printf("\n2. ESTADO_MENU");
				estado = ESTADO_JUGANDO;
				i = 1;
			}
			else
			{
				printf("\n2. ESTADO_MENU");
				estado = ESTADO_FINALIZANDO;
			}
			break;
		case Estado::ESTADO_JUGANDO:	//JUGAR	
			enemigo->Actualizar();
			MoverEnemigo();
			SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
			keys = SDL_GetKeyState(NULL);
			if (keys[SDLK_LEFT])
			{
				if (!EsLimitePantalla(nave, BORDE_IZQUIERDO))
				nave->MoverX(-2);
				
			}
			
			if (keys[SDLK_RIGHT])
			{
				if (!EsLimitePantalla(nave, BORDE_DERECHO))
				nave->MoverX(2);
				
			}//Los 3 casos siguientes son el primero aplicado a las demás direcciones
			

			//Mover en Y, arriba y abajo (opcional)
			/*if (keys[SDLK_UP])
			{
			if (!EsLimitePantalla(nave, BORDE_SUPERIOR))
			nave->MoverY(-2);
			}

			if (keys[SDLK_DOWN])
			{
			if (!EsLimitePantalla(nave, BORDE_INFERIOR))
			nave->MoverY(2);
			}*/
			//Aqui termina Y

			nave->Pintar();
			enemigo->Pintar();

			if (keys[SDLK_SPACE]) //Para evitar que se cicle en un estado, Pulsamos la tecla Abajo (en ese caso) y esa tecla nos dice que estamos en ESTADO_JUGANDO y nos manda a ESTADO_TERMINANDO;
			{
				printf("\n3. ESTADO_JUGANDO");
				estado = ESTADO_TERMINANDO;
			}
			break;
		
		case Estado::ESTADO_TERMINANDO: //SALIR
			printf("\n4. ESTADO_TERMINANDO");
			estado = ESTADO_MENU;
			break;

		case Estado::ESTADO_FINALIZANDO: //FINALIZAR
			printf("\n5. ESTADO_FINALIZANDO");
			getchar();
			salirJuego = true;
			break;
		}

		while (SDL_PollEvent(&event)) //SDL creará una lista de eventos ocurridos
		{
			if (event.type == SDL_QUIT) { salirJuego = true;}     //Si se detecta una salida de SDL o...
			if (event.type == SDL_KEYDOWN) {} //... una dirección (abajo) del teclado.
		}

		SDL_Flip(screen);
	}
	return true;
}

bool CGame::EsLimitePantalla(Nave * objeto, int bandera)
{
	if (bandera & BORDE_IZQUIERDO)
		if (objeto->ObtenerX() <= 0)
			return true;
	if (bandera & BORDE_SUPERIOR)
		if (objeto->ObtenerY() <= 0)
			return true;
	if (bandera & BORDE_DERECHO)
		if (objeto->ObtenerX() >= WIDTH_SCREEN-objeto->ObtenerW())
			return true;
	if (bandera & BORDE_INFERIOR)
		if (objeto->ObtenerY() >= HEIGHT_SCREEN-objeto->ObtenerH())
			return true;
	return false;
}

void CGame::MoverEnemigo()
{
	if (enemigo->ObtenerPasoActual() == 0)
		if (!EsLimitePantalla(enemigo, BORDE_DERECHO))
			enemigo->MoverX(2);
		else
		{
			enemigo->IncrementarPasoActual();
			enemigo->IncrementarPasoActual();
		}
	if (enemigo->ObtenerPasoActual() == 1)
		if (!EsLimitePantalla(enemigo, BORDE_INFERIOR))
			enemigo->MoverY(2);//ABAJO
	if (enemigo->ObtenerPasoActual() == 2)
		if (!EsLimitePantalla(enemigo, BORDE_IZQUIERDO))
			enemigo->MoverX(-2);//IZQUIERDA
		else
		{
			enemigo->IncrementarPasoActual();
			enemigo->IncrementarPasoActual();
		}
	if (enemigo->ObtenerPasoActual() == 3)
		if (!EsLimitePantalla(enemigo, BORDE_INFERIOR))
			enemigo->MoverX(2);//ABAJO

}