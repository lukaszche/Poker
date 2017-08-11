#pragma once
#include "SDL.h"
#include "SDL_functions.h"
#include "math.h"

class SDL_card//:SDL_functions
{
private:
	int card_id;
	int cX,cY;
	bool visible;
	bool front;
public:
	SDL_card();
	~SDL_card(void);
	void setCard(int card_id,int cX,int cY,bool visible,bool front);
	bool cardMove(int cX,int cY);
	void cardDraw(SDL_Surface* cardSpr,SDL_Surface* &scr,int cardBack);
	void setVisible(bool vis);
	void setFront(bool frt);

};
