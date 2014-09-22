#include <stdio.h>
#include <stdlib.h>
#include "Game.h"

CGame::CGame(){
	
}

// Con esta función eliminaremos todos los elementos en pantalla
void CGame::Finalize(){
}

bool CGame::Start()
{
	// Esta variable nos ayudara a controlar la salida del juego...
	int salirJuego = false;
          
	while (salirJuego == false){
            
		//Maquina de estados
		switch(Estado){
		case Estado::ESTADO_INICIANDO: //INICIALIZAR
			break;
		case Estado::ESTADO_MENU: //MENÚ
			break;
		case Estado::ESTADO_JUGANDO:	//JUGAR	
			break;
		case Estado::ESTADO_FINALIZANDO: //FINALIZAR
			break;
		case Estado::ESTADO_TERMINANDO: //SALIR
				salirJuego = true;
			break;
		};
    }
	return true;
}
