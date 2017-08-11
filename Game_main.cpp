
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


#include<iostream>
#include "Deck.h"
#include "Game.h"
#include "SDL_game.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_timer.h"

#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

using namespace std;

int main(int argc,char *args[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
	
	SDL_game *gra=new SDL_game();
	gra->wczytywanie_menu();
	SDL_timer fps;
	while(gra->zamkniecie)
	{
		fps.start();
		gra->zdarzenia();
		if(gra->menu_mode==0)
		{
			gra->wyswietlanie_menu1();
		//gra->wyswietlanie_ramka1(3);
		}
		if(gra->menu_mode==1)
		{
			gra->gamePlay();		
		}
		if(gra->menu_mode==2)
		{
			gra->wyswietlanie_menu2();
		//gra->wyswietlanie_ramka1(1);
		}
		
		if(gra->menu_mode==3)
		{
			gra->drawStartScreen();
		}
		gra->flip();
		gra->ustawienie_fps(fps);
		SDL_Delay(2);
	}
	gra->usunTable();
	if(gra->menu_mode==0)
		gra->usuwanie_menu();
	delete gra;
	SDL_VideoQuit();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
	return 0;
}