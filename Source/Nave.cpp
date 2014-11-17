#include "Nave.h"
#include "Config.h"

Nave::Nave(SDL_Surface * screen, char * rutaImagen, int x, int y, int module)
{
	this->module = module;
	sprite = new Sprite(screen);
	sprite->CargarImagen(rutaImagen);
	w = sprite->WidthModule(this->module);
	h = sprite->HeightModule(this->module);
	this->x = x;
	this->y = y;
	autoMovimiento = false;
	pasoActual = 0;
	pasoLimite = -1;
}

void Nave::SetAutoMovimiento(bool autoMovimiento)
{
	this->autoMovimiento = autoMovimiento;
}

void Nave::Actualizar()
{
	if (autoMovimiento)
	{
		MoverX(1);
	}
	if (pasoLimite > 0)
	{
		//pasoActual++;
		if (pasoActual >= pasoLimite)
			pasoActual = 0;
	}

}

void Nave::Pintar()
{
	sprite->PintarModulo(module, x, y);
}

void Nave :: MoverX(int posicion)
{
	x += posicion;
}

void Nave ::MoverY(int posicion)
{
	y += posicion;
}

int Nave :: ObtenerX()
{
	return x;
}

int Nave::ObtenerY()
{
	return y;
}

int Nave::ObtenerW()
{
	return w;
}

int Nave::ObtenerH()
{
	return h;
}

void Nave::SetPasoLimite(int pasos)
{
	this->pasoLimite = pasos;
}

int Nave::ObtenerPasoActual()
{
	return pasoActual;
}

void Nave::IncrementarPasoActual()
{
	pasoActual++;
}