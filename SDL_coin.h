#pragma once
#include "SDL.h"
#include "SDL_functions.h"

class SDL_coin
{
private:
	int coin_amount;
	int cX,cY;
	bool visible;
public:
	SDL_coin(void);
	~SDL_coin(void);
	void setCoins(int amount,int X,int Y);
	void coinsDraw(SDL_Surface* cardSpr,SDL_Surface* &scr);
	void setVisible(bool vis);
	void setCoinsAmount(int amount);
};

