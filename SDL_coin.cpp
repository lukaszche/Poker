#include "SDL_coin.h"


SDL_coin::SDL_coin(void)
{
}


SDL_coin::~SDL_coin(void)
{
}
void SDL_coin::setCoins(int amount,int X,int Y)
{
	coin_amount=amount;
	cX=X;
	cY=Y;
}
void SDL_coin::coinsDraw(SDL_Surface* cardSpr,SDL_Surface* &scr)
{
	int a20=(coin_amount-60)/20;
	if(a20<0)
		a20=0;
	int a5=(coin_amount-a20*20-(coin_amount%10+5))/5;
	if(a5<0)
		a5=0;
	int a1=(coin_amount-a20*20-a5*5);

	SDL_Rect tmp1;
	tmp1.x=0;
	tmp1.y=0;
	tmp1.h=20;
	tmp1.w=20;
	
	SDL_Rect tmpShadow;
	tmpShadow.x=60;
	tmpShadow.y=0;
	tmpShadow.h=20;
	tmpShadow.w=20;

	for(int i=0;i<a20;i++)
	{
	SDL_SetAlpha(cardSpr,SDL_SRCALPHA,75);
	SDL_functions::blit_obraz(cardSpr,scr,cX-i-7,cY-i-2,&tmpShadow);
	SDL_SetAlpha(cardSpr,SDL_SRCALPHA,255);
	SDL_functions::blit_obraz(cardSpr,scr,cX-i,cY-i,&tmp1);

	}

	tmp1.x=20;

	for(int i=0;i<a5;i++)
	{
	SDL_SetAlpha(cardSpr,SDL_SRCALPHA,75);
	SDL_functions::blit_obraz(cardSpr,scr,cX-i-7+20,cY-i-2,&tmpShadow);
	SDL_SetAlpha(cardSpr,SDL_SRCALPHA,255);
	SDL_functions::blit_obraz(cardSpr,scr,cX-i+20,cY-i,&tmp1);

	}

	tmp1.x=40;

	for(int i=0;i<a1;i++)
	{
	SDL_SetAlpha(cardSpr,SDL_SRCALPHA,75);
	SDL_functions::blit_obraz(cardSpr,scr,cX-i-7,cY-i-2+20,&tmpShadow);
	SDL_SetAlpha(cardSpr,SDL_SRCALPHA,255);
	SDL_functions::blit_obraz(cardSpr,scr,cX-i,cY-i+20,&tmp1);

	}

}
void SDL_coin::setCoinsAmount(int amount)
{
	coin_amount=amount;
}
