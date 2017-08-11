#pragma once
#include "SDL_functions.h"
class SDL_Trackbar
{
private:
	int tx,ty,th,tw;
	int bx;
	int tmin,tmax;
	int position;
	SDL_Surface *tbar;
	TTF_Font *czcionka;
	int skin;
public:
	SDL_Trackbar(int skin,int x,int y,int h,int w,int pos,int min,int max);
	~SDL_Trackbar(void);
	void drawTrackbar(SDL_Surface * ekran);
	void change(int mx,int my);
	void setMinMax(int min,int max);
	void setPosition(int pos);
	int getPosition();
};

