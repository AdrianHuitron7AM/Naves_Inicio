#include "Nave.h"
#include "Config.h"

Nave::Nave(SDL_Surface * screen, char * rutaImagen, int x, int y, int module)
{
	nave = new Objeto(screen, rutaImagen, x, y, module);
	bala = new Objeto(screen, "../Data/balas.bmp", 0, 0, MODULO_BALAS_BALA);
	bala->SetVisible(false);
}

void Nave::Pintar()
{
	nave->Pintar();
	bala->Pintar();
	bala->MoverY(-30);
}

void Nave::Disparar()
{
	bala->SetVisible(true);
	bala->PonerEn(nave->ObtenerX()+nave->ObtenerW()/2, nave->ObtenerY());
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