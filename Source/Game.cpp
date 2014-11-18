#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "Config.h"
#include <SDL.h>
#include <SDL_image.h>

CGame::CGame()
{
	tiempoFrameInicial = 0;
	estado = ESTADO_JUGANDO;
	atexit(SDL_Quit);
}

// Con esta función eliminaremos todos los elementos en pantalla
void CGame::Finalize()
{
	delete nave;
//	delete []keys;
	delete *enemigoArreglo;
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


	nave = new Nave(screen, "../Data/minave.bmp", (WIDTH_SCREEN / 2) , (HEIGHT_SCREEN - 80), 0);
	menu = new Nave(screen, "../Data/notspacewar.bmp",0,0,1);

	for (int i = 0; i < 10; i++)
	{
		enemigoArreglo[i] = new Nave(screen, "../Data/enemigo.bmp", i*60, 0, 2);
		enemigoArreglo[i]->SetAutoMovimiento(false);
		enemigoArreglo[i]->SetPasoLimite(4);
	}
	tick = 0;
	//delete nave;
}

bool CGame::Start()
{
	// Esta variable nos ayudara a controlar la salida del juego...
	int salirJuego = false;
	int i = 0;
	while (salirJuego == false){

		//Maquina de estados
		switch (estado)
		{
		case Estado::ESTADO_INICIANDO: //INICIALIZAR
			Iniciando();
			estado = ESTADO_MENU;
			break;
		case Estado::ESTADO_MENU: //MENU
			menu->Pintar();
			break;
		case Estado::ESTADO_JUGANDO:	//JUGAR	
			for (int i = 0; i < 10; i++)
			{
				enemigoArreglo[i]->Actualizar();
			}
			MoverEnemigo();
			SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
			keys = SDL_GetKeyState(NULL);
			if (keys[SDLK_LEFT])
			{
				if (!EsLimitePantalla(nave, BORDE_IZQUIERDO))
					nave->MoverX(-15);

			}

			if (keys[SDLK_RIGHT])
			{
				if (!EsLimitePantalla(nave, BORDE_DERECHO))
					nave->MoverX(15);

			}//Los 3 casos siguientes son el primero aplicado a las demás direcciones


			//Mover en Y, arriba y abajo (opcional)
			if (keys[SDLK_UP])
			{
			if (!EsLimitePantalla(nave, BORDE_SUPERIOR))
			nave->MoverY(-15);
			}

			if (keys[SDLK_DOWN])
			{
			if (!EsLimitePantalla(nave, BORDE_INFERIOR))
			nave->MoverY(15);
			}
			//Aqui termina Y

			nave->Pintar();
			for (int i = 0; i < 10; i++)
			{
				enemigoArreglo[i]->Pintar();
			}
			break;

		case Estado::ESTADO_TERMINANDO: //SALIR

			break;

		case Estado::ESTADO_FINALIZANDO: //FINALIZAR
			salirJuego = true;
			break;
		}

		while (SDL_PollEvent(&event)) //SDL creará una lista de eventos ocurridos
		{
			if (event.type == SDL_QUIT) { salirJuego = true; }     //Si se detecta una salida de SDL o...
			if (event.type == SDL_KEYDOWN) {} //... una dirección (abajo) del teclado.
		}

		SDL_Flip(screen);
		//Calculando FPS
		tiempoFrameFinal = SDL_GetTicks();
		while (tiempoFrameFinal < (tiempoFrameInicial + FPS_DELAY))
		{
			tiempoFrameFinal = SDL_GetTicks();
			SDL_Delay(1);
		}
		printf("Frames: %d Tiempo: %d Tiempo promedio: %f Tiempo por frame: %d FPS: %f\n", tick, SDL_GetTicks(), (float)SDL_GetTicks() / (float)tick, tiempoFrameFinal - tiempoFrameInicial, 1000.f / (float) (tiempoFrameFinal-tiempoFrameInicial));
		tiempoFrameInicial = tiempoFrameFinal;//Marcamos el inicio nuevamente
		tick++;
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
	for (int i = 0; i < 10; i++)
	{
		if (enemigoArreglo[i]->ObtenerPasoActual() == 0)
			if (!EsLimitePantalla(enemigoArreglo[i], BORDE_DERECHO))
				enemigoArreglo[i]->MoverX(15);
			else
			{
				enemigoArreglo[i]->IncrementarPasoActual();
				//enemigoArreglo[i]->IncrementarPasoActual();
			}
		if (enemigoArreglo[i]->ObtenerPasoActual() == 1)
			if (!EsLimitePantalla(enemigoArreglo[i], BORDE_INFERIOR))
				enemigoArreglo[i]->MoverY(15);//ABAJO
			else
			{
				enemigoArreglo[i]->IncrementarPasoActual();
				//enemigoArreglo[i]->IncrementarPasoActual();
			}
		if (enemigoArreglo[i]->ObtenerPasoActual() == 2)
			if (!EsLimitePantalla(enemigoArreglo[i], BORDE_IZQUIERDO))
				enemigoArreglo[i]->MoverX(-15);//IZQUIERDA
			else
			{
				enemigoArreglo[i]->IncrementarPasoActual();
				//enemigoArreglo[i]->IncrementarPasoActual();
			}
		if (enemigoArreglo[i]->ObtenerPasoActual() == 3)
			if (!EsLimitePantalla(enemigoArreglo[i], BORDE_SUPERIOR))
				enemigoArreglo[i]->MoverY(-15);//ABAJO
			else
			{
				enemigoArreglo[i]->IncrementarPasoActual();
				//enemigoArreglo[i]->IncrementarPasoActual();
			}
	}

}

bool Nave::EstaColisionando(Nave * b)
{
	return false;
}