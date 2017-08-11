#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>
#include <sstream>

		const int PROGRAM_FPS=30; //klatki na sek
		const int EKRAN_BITY=32; //bity kolorow
		const int EKRAN_H=600; //wysokosc ekranu
		const int EKRAN_W=900; //szerokosc ekranu

		enum pozycje_graczyX {GRACZ0X=130, GRACZ1X=350, GRACZ2X=570, GRACZ3X=615, GRACZ4X=570, GRACZ5X=350, GRACZ6X=130, GRACZ7X=95};
		enum pozycje_graczyY {GRACZ0Y=70, GRACZ1Y=80, GRACZ2Y=80, GRACZ3Y=205, GRACZ4Y=355, GRACZ5Y=355, GRACZ6Y=355, GRACZ7Y=205};

class SDL_functions
{
	
public:
	
	//powierzchnia ekran
	//SDL_Surface * ekran;
	//polozenie myszki

	//stale programu
	
	
	

	//metody(funkcje pomocnicze SDL)
	SDL_functions(void);
	~SDL_functions(void);
	static SDL_Surface *wczytaj_obraz(std::string plik); //funkcja wczytujaca obraz, wraz ze zmiana formatu
	static void blit_obraz(SDL_Surface *zrodlo,SDL_Surface *cel,int z,int y,SDL_Rect *wycinek); // funkcja nakladajac obrazy na ekran/powierzchnie
	static std::string IntToStr(int n);
};	

