#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "Header.h" 
#include <SDL.h>
#include <SDL_image.h>


CGame::CGame()
{
	tiempoFrame = 0;
	estado = ESTADO_INICIANDO;
	Iniciando();
	//delete nave;
}
void CGame::Iniciando(){
	if (SDL_Init(SDL_INIT_VIDEO)<0)//si regresa 1 el init de video si se activo y regresa -1 si no se pudo iniciar. 
	{
		printf("No se pudo iniciar SDL: Error %s\n", SDL_GetError());//
		exit(EXIT_FAILURE);
	}
	screen= SDL_SetVideoMode(WIDTH_SCREEN, HEIGHT_SCREEN, 24, SDL_HWSURFACE);//(ancho,alto,bpp,bandera)
	if (screen==NULL)
	{
		printf("No se puede inicializar el modo grafico: \n",SDL_GetError());
		getchar();
		exit(1);
	}
	SDL_WM_SetCaption( "NotSpacewar", NULL );

	atexit(SDL_Quit);

	nave = new Nave(screen,"../Data/minave.bmp",(WIDTH_SCREEN/2),(HEIGHT_SCREEN-80),MODULO_MINAVE_NAVE);
	menu = new Objeto(screen, "../Data/notspacewar.bmp", 0, 0, MODULO_MENU_FONDO);
	textos = new Objeto(screen, "../Data/menubase.bmp", 50, 59, -1);
	fondo = new Objeto(screen, "../Data/nivel1.bmp", 0, 0, MODULO_MENU_FONDO);

	for (int i = 0; i < 10; i++)
	{
		enemigoArreglo[i] = new Nave(screen,"../Data/enemigo.bmp", i * 60, 0, MODULO_ENEMIGO_NAVE);
		enemigoArreglo[i]->GetNaveObjeto()->SetAutoMovimiento(false);
		enemigoArreglo[i]->GetNaveObjeto()->SetPasoLimite(4);
	}
	tick = 0;
	opcionSeleccionada = MODULO_TEXTO_MENUOPCION1;

//	enemigo->SetAutoMovimiento(false);
//	enemigo->SetPasoLimite(4);

}
// Con esta función eliminaremos todos los elementos en pantalla
void CGame::Finalize()
{
	delete(nave);
	//delete(keys);
	//delete(enemigo);
	delete *enemigoArreglo;
	SDL_FreeSurface(screen);
	SDL_Quit();
}

bool CGame::Start()
{

	// Esta variable nos ayudara a controlar la salida del juego...
	int salirJuego = false;  
	while (salirJuego == false)
	{

		//Maquina de estados
		switch(estado){
		case Estado::ESTADO_INICIANDO:
			
			Iniciando();
			InicializandoStage(); 
			estado = ESTADO_MENU;
			break;
		case Estado ::ESTADO_MENU:
			menu->Pintar();
			textos->Pintar(MODULO_TEXTO_TITULO, 100,50);
			textos->Pintar(MODULO_TEXTO_NOMBRE, 300, 390);

			
			Menu();
			//estado = ESTADO_JUGANDO;
			break;
		case Estado::ESTADO_PRE_JUGANDO:
			nivelActual = 0;
			vida = 1;
			enemigosEliminados = 0;
			estado = ESTADO_JUGANDO;
			break;
		case Estado ::ESTADO_JUGANDO:

			for (int i = 0; i < nivel[nivelActual].NumeroEnemigosVisibles; i++)
			{
				enemigoArreglo[i]->GetNaveObjeto()->Actualizar();
			}
			MoverEnemigo();
			fondo->Pintar();
			keys= SDL_GetKeyState(NULL);
			if(keys[SDLK_RIGHT])
			{ 
				if(!EsLimitePantalla(nave->GetNaveObjeto(), BORDE_DERECHO))
				nave->MoveRight(nivel[nivelActual].VelocidadNavePropia);
			}//Los 3 casos siguientes son el primero aplicando a las demas direcciones
			if(keys[SDLK_LEFT])
			{
				if (!EsLimitePantalla(nave->GetNaveObjeto(), BORDE_IZQUIERDO))
					nave->MoveLeft(nivel[nivelActual].VelocidadNavePropia);
			}

			//Mover en Y, arriba y abajo
			if (keys[SDLK_UP])
			{
				if (!EsLimitePantalla(nave->GetNaveObjeto(), BORDE_SUPERIOR))
					nave->MoveUp(nivel[nivelActual].VelocidadNavePropia);
			}

			if (keys[SDLK_DOWN])
			{
				if (!EsLimitePantalla(nave->GetNaveObjeto(), BORDE_INFERIOR))
					nave->MoveDown(nivel[nivelActual].VelocidadNavePropia);
			}
			//Aqui termina Y

			if (keys[SDLK_SPACE])
			{
				nave->Disparar(NAVE_PROPIA, nivel[nivelActual].balasMaximas);
			}

			//SIMULACION DE COLISIONES//
			if (keys[SDLK_x])//BALA ENEMIGO / NUESTRA NAVE
			{
				nave->simularColision(true);
			}
			if (keys[SDLK_c])//NUESTRA BALA / NAVE ENEMIGO
			{
				int enemigoAEliminar = rand() % nivel[nivelActual].NumeroEnemigosVisibles;
				enemigoArreglo[enemigoAEliminar]->simularColision(true);
			}
			if (keys[SDLK_v])//NUESTRA NAVE / NAVE ENEMIGO
			{

			}

			//CONTROL DE COLISIONES//
			for (int i = 0; i < nivel[nivelActual].NumeroEnemigosVisibles; i++)
			{
				if (enemigoArreglo[i]->estaColisionandoConBala(nave)){
					vida--;
					enemigoArreglo[i]->simularColision(false);
				}
				if (nave->estaColisionandoConBala(enemigoArreglo[i]))
				{
					enemigoArreglo[i]->setVisible(false);
					nave->simularColision(false);
					enemigosEliminados++;
					if (enemigosEliminados < nivel[nivelActual].NumeroEnemigosAEliminar)
					{
						enemigoArreglo[i]->CrearNuevo();
					}
				}
			}

			if (vida <= 0)
			{
				estado = ESTADO_MENU;
			}
			if (enemigosEliminados >= nivel[nivelActual].NumeroEnemigosAEliminar)
			{
				nivelActual++;
				//CARGAR OTRO FONDO
			}

			nave->Pintar(NAVE_PROPIA);
			for (int i = 0; i<nivel[nivelActual].NumeroEnemigosVisibles; i++)
			{
				enemigoArreglo[i]->Pintar(NAVE_ENEMIGO);
				enemigoArreglo[i]->AutoDisparar(nivel[nivelActual].balasMaximas);
			}
			break;
			
		case Estado ::ESTADO_TERMINANDO:
			printf("\n4. ESTADO_TERMINANDO");
			estado=ESTADO_MENU;
			
			break;
		case Estado ::ESTADO_FINALIZANDO:
			printf("\n5. ESTADO_FINALIZADO");
			getchar();
			salirJuego = true;
			break;
		};
		while(SDL_PollEvent(&event))//Aqui SDL creara una lista de eventos ocurridos
		{
			if(event.type==SDL_QUIT){salirJuego = true;}//Si se detecta una salida de SDL o...
			if(event.type==SDL_KEYDOWN){}
		}
		SDL_Flip(screen);//Este codigo esta provisionalmente aqui
		
		int tiempoFrameFinal = SDL_GetTicks();
		while (tiempoFrameFinal < (tiempoFrame + FPS_DELAY)){
			tiempoFrameFinal = SDL_GetTicks();
			SDL_Delay(1);
		}
		printf("Frames:%d Tiempo:%d Tiempo promedio:%f Tiempo por frame:%d FPS:%f\n", tick, SDL_GetTicks(), (float)SDL_GetTicks() / (float)tick, tiempoFrameFinal - tiempoFrame, 1000.0f / (float)(tiempoFrameFinal - tiempoFrame));
		tiempoFrame = tiempoFrameFinal;
		tick++;


	}
	return true;
}

bool CGame::EsLimitePantalla(Objeto * objeto, int bandera)
{
	if (bandera&BORDE_IZQUIERDO)
	if (objeto->ObtenerX()<=0)
		return true;
	if(bandera&BORDE_SUPERIOR)
	if (objeto->ObtenerY()<=0)
		return true;
	if(bandera&BORDE_DERECHO)
	if (objeto->ObtenerX()>=WIDTH_SCREEN-objeto->ObtenerW())
		return true;
	if(bandera&BORDE_INFERIOR)
	if (objeto->ObtenerY()>=HEIGHT_SCREEN-objeto->ObtenerH())
		return true;
	return false;
}
void CGame::MoverEnemigo()
{
	for (int i = 0; i < nivel[nivelActual].NumeroEnemigosVisibles; i++)
		{
			if(enemigoArreglo[i]->GetNaveObjeto()->ObtenerPasoActual()==0)
				if (!EsLimitePantalla(enemigoArreglo[i]->GetNaveObjeto(), BORDE_DERECHO))
				{
				enemigoArreglo[i]->GetNaveObjeto()->MoverX(nivel[nivelActual].VelocidadNaveEnemigo);//Derecha
				}
				else
				{
					enemigoArreglo[i]->GetNaveObjeto()->IncrementarPasoActual();
				}
			if (enemigoArreglo[i]->GetNaveObjeto()->ObtenerPasoActual() == 1)
				if (!EsLimitePantalla(enemigoArreglo[i]->GetNaveObjeto(), BORDE_INFERIOR))
				{
				enemigoArreglo[i]->GetNaveObjeto()->MoverY(nivel[nivelActual].VelocidadNaveEnemigo);
				}
				else
				{
					enemigoArreglo[i]->GetNaveObjeto()->IncrementarPasoActual();
				}
			if (enemigoArreglo[i]->GetNaveObjeto()->ObtenerPasoActual() == 2)
				if (!EsLimitePantalla(enemigoArreglo[i]->GetNaveObjeto(), BORDE_IZQUIERDO))
				{	
				enemigoArreglo[i]->GetNaveObjeto()->MoverX(-nivel[nivelActual].VelocidadNaveEnemigo);
				}
				else
				{
					enemigoArreglo[i]->GetNaveObjeto()->IncrementarPasoActual();
				}
			if (enemigoArreglo[i]->GetNaveObjeto()->ObtenerPasoActual() == 3)
				if (!EsLimitePantalla(enemigoArreglo[i]->GetNaveObjeto(), BORDE_SUPERIOR))
				{
				enemigoArreglo[i]->GetNaveObjeto()->MoverY(-nivel[nivelActual].VelocidadNaveEnemigo);
				}
				else
				{
					enemigoArreglo[i]->GetNaveObjeto()->IncrementarPasoActual();
				}
	   }
}

void CGame::Menu()
{
	for (int i = MODULO_TEXTO_MENUOPCION1, j = 0; i <= MODULO_TEXTO_MENUOPCION2; i++, j++)
	{
		keys = SDL_GetKeyState(NULL);
		if (keys[SDLK_UP])
		{
			opcionSeleccionada = MODULO_TEXTO_MENUOPCION1;
		}

		if (keys[SDLK_DOWN])
		{
			opcionSeleccionada = MODULO_TEXTO_MENUOPCION2;
		}

		if (i == opcionSeleccionada)
			textos->Pintar(i + 2, 312, 250 + (j * 30));
		else
			textos->Pintar(i, 310, 250 + (j * 30));


		if (keys[SDLK_RETURN])
		{
			if (opcionSeleccionada == MODULO_TEXTO_MENUOPCION1)
			{
				estado = Estado::ESTADO_PRE_JUGANDO;
			}

			if (opcionSeleccionada == MODULO_TEXTO_MENUOPCION2)
			{
				estado = Estado::ESTADO_FINALIZANDO;
			}
		}
	}	
}