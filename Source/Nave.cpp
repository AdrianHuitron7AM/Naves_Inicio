#include "Nave.h"

Nave::Nave(SDL_Surface * screen, char * rutaImagen, int x, int y, int module)
{
	nave = new Objeto(screen, rutaImagen, x, y, module);
}

void Nave::Pintar()
{
	nave->Pintar();
}

void Nave::MoveLeft()
{
	nave->MoverX(-20);
}

void Nave::MoveRight()
{
	nave->MoverX(20);
}

void Nave::MoveUp()
{
	nave->MoverY(-20);
}

void Nave::MoveDown()
{
	nave->MoverY(20);
}

Objeto* Nave::GetNaveObjeto()
{
	return nave;
}