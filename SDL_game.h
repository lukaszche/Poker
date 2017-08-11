#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_timer.h"
#include "SDL_table.h"
#include "SDL_card.h"
#include "SDL_coin.h"
#include "SDL_Trackbar.h"
#include "Game.h"
#include <string>
#include "SDL_functions.h"
#include "SDL_mixer.h"

class SDL_game: SDL_functions
{
private:
	//obiekty
	SDL_table *tab;
	SDL_card **cards;
	SDL_coin **coins;
	Game *gra;
	SDL_Trackbar *track;

	//ekran
	SDL_Surface * ekran;
	//powierzchnie menu
	SDL_Surface * background1;
	SDL_Surface * background2;
	SDL_Surface * button1;
	SDL_Surface * button2;
	SDL_Surface * button3;
	SDL_Surface * button4;
	SDL_Surface * buttonOver;

	SDL_Surface * sand;


	SDL_Surface * buttonOff;

	SDL_Surface * tekstX[10];
	SDL_Surface * ramka1;
	SDL_Surface * startSurf;

	//sprites gra
	SDL_Surface *cardsSPR;
	SDL_Surface *coinsSPR;
	//czcionki
	TTF_Font *czcionka1;
	TTF_Font *czcionka2;
	//zdarzenia
	SDL_Event zdarzenie;
	//dzwiek
	Mix_Music *gameSound;

	//polozenie myszki
	int mx,my;
	//glosnosc
	int audioVolume;
	//faza gry
	int phase;
	//faza gameplayu
	int gamePhase;
	bool roundMode;

	int winner;
	int delayer;
	//kto wykonuje ruch
	int playerTurn;
	
	//prostokaty
	//kanal alfa dla ramki
	int alfaRamka;
	bool alfaflag;
	double alfaSand;
	int posSand;
	bool alfasandf;
	
	int ButtonOverMove;
	
	int alfaMenu2;
	//wyglad karty
	int cardBack;
	//inne
	int przycisk_flag;
	int tmpIleGraczy;
	//music

	
public:

	
	bool zamkniecie;

	
	int menu_mode;
	SDL_game(void);
	~SDL_game(void);

	void drawStartScreen();
	void wczytywanie_menu();//wczytanie elementow menu(obrazy,czcionki,dzwieki
	void wczytywanie_gra();//wczytanie elementow menu(obrazy,czcionki,dzwieki)
	
	void dealCards();
	void zdarzenia(); //obsluga zdarzen
	void wyswietlanie_menu1(); //wyswietlanie menu glownego
	void wyswietlanie_menu2(); //wyswietlanie menu opcji
	void wyswietlanieGraGui(int mode);
	//void wyswietlanieCpuMoves(int time);

	void setCards();
	void tworzenieCoins();
	void tworzenieCards();

	void wyswietlanie_ramka1(int k);//wyswietlanie ramki
	void wyswietlanieButtonBlue();
	void wyswietlanie_sand();//wyswietlanie ramki
	void myszka_menu1(int mode);//obsluga myszki w menu
	void myszka_gra();
	
	void flip();

	void preFlop();
	void flop();
	void turn();
	void river();
	void showdown();

	void gamePlay();

	void usuwanie_menu();
	void usunTable();

	void ustawienie_fps(SDL_timer t);

};

