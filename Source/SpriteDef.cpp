#include "SpriteDef.h"
#include "Config.h"

SpriteDef::SpriteDef()
{
	modulos[0].id = MODULO_MINAVE_NAVE;
	modulos[0].x = 0;
	modulos[0].y = 0;
	modulos[0].w = 64;
	modulos[0].h = 64;

	modulos[1].id = MODULO_MENU_FONDO;
	modulos[1].x = 0;
	modulos[1].y = 0;
	modulos[1].w = WIDTH_SCREEN;
	modulos[1].h = HEIGHT_SCREEN;

	modulos[2].id = MODULO_ENEMIGO_NAVE;
	modulos[2].x = 0;
	modulos[2].y = 0;
	modulos[2].w = 54;
	modulos[2].h = 61;

	modulos[3].id = MODULO_TEXTO_TITULO;
	modulos[3].x = 12;
	modulos[3].y = 14;
	modulos[3].w = 141;
	modulos[3].h = 25;

	modulos[4].id = MODULO_TEXTO_NOMBRE;
	modulos[4].x = 10;
	modulos[4].y = 104;
	modulos[4].w = 139;
	modulos[4].h = 50;

	modulos[5].id = MODULO_TEXTO_MENUOPCION1;
	modulos[5].x = 182;
	modulos[5].y = 60;
	modulos[5].w = 52;
	modulos[5].h = 23;

	modulos[6].id = MODULO_TEXTO_MENUOPCION2;
	modulos[6].x = 182;
	modulos[6].y = 104;
	modulos[6].w = 71;
	modulos[6].h = 22;

	modulos[7].id = MODULO_TEXTO_MENUOPCION1_SELECCIONADO;
	modulos[7].x = 180;
	modulos[7].y = 136;
	modulos[7].w = 52;
	modulos[7].h = 23;

	modulos[7].id = MODULO_TEXTO_MENUOPCION2_SELECCIONADO;
	modulos[7].x = 180;
	modulos[7].y = 136;
	modulos[7].w = 52;
	modulos[7].h = 23;
}