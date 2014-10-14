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
	if (screen == NULL)
	{
		screen = SDL_SetVideoMode(640, 480, 24, SDL_SWSURFACE);
	}
	if (screen == NULL)
	{
		screen = SDL_SetVideoMode(640, 480, 24, SDL_SWSURFACE);
	}
	if (screen == NULL)
	{
		printf("Error %s ", SDL_GetError());
		exit(EXIT_FAILURE);
	


			printf("Error %s ", SDL_GetError());
			exit(EXIT_FAILURE);
	}

		SDL_WM_SetCaption("Mi primer Juego", NULL);
		nave = new Nave(screen, "../Data/minave.bmp");

		//delete nave;
}



bool CGame::Start()
{
	// Esta variable nos ayudara a controlar la salida del juego...
	int salirJuego = false;
          
	while (salirJuego == false){
		
		//Maquina de estados
		switch(estado)
		{
		case Estado::ESTADO_INICIANDO: //INICIALIZAR
			Iniciando();
			{
				estado = ESTADO_MENU;
			
			}
			break;
		case Estado::ESTADO_MENU: //MENÚ
			//nave->PintarModulo(0,0,0,64,64);
			//nave->PintarModulo(0, 100, 100);
			SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
			keys = SDL_GetKeyState(NULL);
			if (keys[SDLK_RIGHT])
			{
				nave->MoverX(1);
			}//Los 3 casos siguientes son el primero aplicado a las demás direcciones
			if (keys[SDLK_LEFT])
			{
				nave->MoverX(-1);
			}

			//Mover en Y, arriba y abajo (opcional)
			/*if (keys[SDLK_UP])
			{
				nave->MoverY(-1);
			}

			if (keys[SDLK_DOWN])
			{
				nave->MoverY(1);
			}*/
			//Aqui termina Y

			nave->Pintar();
			break;
		case Estado::ESTADO_JUGANDO:	//JUGAR	
			break;
		case Estado::ESTADO_FINALIZANDO: //FINALIZAR
			break;
		case Estado::ESTADO_TERMINANDO: //SALIR
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