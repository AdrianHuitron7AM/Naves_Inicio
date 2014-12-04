#include "Nave.h"
#include "Config.h"

Nave::Nave(SDL_Surface * screen, char * rutaImagen, int x, int y, int module)
{
	nave = new Objeto(screen, rutaImagen, x, y, module);
	for (int i = 0; i < MAXIMO_DE_BALAS; i++)
	{
		bala[i] = new Objeto(screen, "../Data/balas.bmp", 0, 0, MODULO_BALAS_BALA);
		bala[i]->SetVisible(false);
	}
	balasVisibles = 0;
}

void Nave::Pintar(int tipoNave)
{
	nave->Pintar();
	for (int i = 0; i < MAXIMO_DE_BALAS; i++)
	{
		bala[i]->Pintar();
		switch (tipoNave)
		{
		case NAVE_PROPIA:
			bala[i]->MoverY(-30);
			break;
		case NAVE_ENEMIGO:
			bala[i]->MoverY(30);
			break;
		}
		
	}
	
}

void Nave::Disparar(int tipoNave, int balas)
{
	bala[balasVisibles]->SetVisible(true);
	switch (tipoNave)
	{
	case NAVE_PROPIA:
		bala[balasVisibles]->PonerEn(nave->ObtenerX() + nave->ObtenerW() / 2, nave->ObtenerY());
		break;

	case NAVE_ENEMIGO:
		bala[balasVisibles]->PonerEn(nave->ObtenerX() + nave->ObtenerW() / 2, nave->ObtenerY() + nave->ObtenerH());
		break;
	}
	
	balasVisibles++;

	if (balasVisibles >= balas)
	{
		balasVisibles = 0;
	}
}

void Nave::MoveLeft(int velocidad)
{
	nave->MoverX(-velocidad);
}

void Nave::MoveRight(int velocidad)
{
	nave->MoverX(velocidad);
}

void Nave::MoveUp(int velocidad)
{
	nave->MoverY(-velocidad);
}

void Nave::MoveDown(int velocidad)
{
	nave->MoverY(velocidad);
}

Objeto* Nave::GetNaveObjeto()
{
	return nave;
}

void Nave::AutoDisparar(int balas)
{
	if ((rand() % 100)<1) //Probabilidad de disparo del enemigo (que tan seguido va a disparar)
	Disparar(NAVE_ENEMIGO, balas);
}

//void Nave::ColisionEnemigo()
//{
//	
//} 