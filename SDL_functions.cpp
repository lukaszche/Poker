#include "SDL_functions.h"


SDL_functions::SDL_functions(void)
{

}


SDL_functions::~SDL_functions(void)
{
}

SDL_Surface * SDL_functions::wczytaj_obraz(std::string plik)
{
	SDL_Surface *obraztmp=NULL;
	SDL_Surface *wyjobraz=NULL;
	obraztmp=IMG_Load(plik.c_str());
	if( obraztmp != NULL )
	{
		wyjobraz=SDL_DisplayFormat(obraztmp);
		SDL_FreeSurface(obraztmp);	
		Uint32 kolorkey= SDL_MapRGB(wyjobraz->format,0,0xFF,0xFF);
		SDL_SetColorKey(wyjobraz,SDL_SRCCOLORKEY,kolorkey);
	}
	
	return wyjobraz;
}

void SDL_functions::blit_obraz(SDL_Surface* zrodlo,SDL_Surface* cel,int x,int y,SDL_Rect *rec)
{
	SDL_Rect polozenie;
	polozenie.x=x;
	polozenie.y=y;
	SDL_BlitSurface(zrodlo,rec,cel,&polozenie);
}

std::string SDL_functions::IntToStr(int n)
{
    std::ostringstream out;
    out << n;
    return out.str();
}

