#ifndef __SPRITEDEF_H__
#define __SPRITEDEF_H__

class SpriteDef
{
public:
	struct Modulos
	{
		int id;
		int x;
		int y;
		int w;
		int h;
	};
public:
	Modulos modulos[1];
	SpriteDef();
};

#endif