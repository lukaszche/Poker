#include "SDL_card.h"
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW


SDL_card::SDL_card()
{
}

SDL_card::~SDL_card(void)
{
}

void SDL_card::setCard(int c_id,int x,int y,bool vis,bool frt)
{
	card_id=c_id;
	cX=x;
	cY=y;
	visible=vis;
	front=frt;
}
void SDL_card::setVisible(bool vis)
{visible=vis;}
void SDL_card::setFront(bool frt)
{front=frt;}
void SDL_card::cardDraw(SDL_Surface* cardSpr,SDL_Surface* &scr,int cardBack)
{
	if(visible)
	{
		if(front)
		{
			SDL_Rect tmpRec;
			tmpRec.x=45*(card_id/4);
			tmpRec.y=0;
			tmpRec.h=60;
			tmpRec.w=45;
			SDL_functions::blit_obraz(cardSpr,scr,cX,cY,&tmpRec);
			tmpRec.x=45*(card_id%4);
			tmpRec.y=60;
			SDL_functions::blit_obraz(cardSpr,scr,cX,cY,&tmpRec);
		}
		else
		{
			SDL_Rect tmpRec;
			tmpRec.x=585+(cardBack/2*45);
			tmpRec.y=0+(cardBack%2*60);
			tmpRec.h=60;
			tmpRec.w=45;
			SDL_functions::blit_obraz(cardSpr,scr,cX,cY,&tmpRec);
		}
	}

}
bool SDL_card::cardMove(int X,int Y)
{
	float tmp=(abs(cX-X)+abs(cY-Y));
	float xModifier=abs(cX-X)/tmp;
	float yModifier=abs(cY-Y)/tmp;
	if(cX<(X-20) || cX>(X+20))
	{
		if(cX<(X))
			cX+=50*xModifier;
		else
			cX-=50*xModifier;
	}
	if( cY<(Y-20) || cY>(Y+20))
	{
		if(cY<(Y))
			cY+=50*yModifier;
		else
			cY-=50*yModifier;
	}
	if(cX<(X-20) || cX>(X+20) || cY<(Y-20) || cY>(Y+20))
		return false;
	else
	{
		cX=X;
		cY=Y;
		return true;
	}
}
