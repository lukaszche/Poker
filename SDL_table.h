#pragma once
#include "SDL_functions.h"
#include "SDL_Trackbar.h"
#include <string>
#include <sstream>
class SDL_table
{
private:
	SDL_Surface *table;
	SDL_Surface *rPannel;
	SDL_Surface *botPannel;
	SDL_Surface *pointer;
	SDL_Surface *menuOpen;
	SDL_Surface *menuOptions;
	SDL_Surface *optionsCards;
	


	SDL_Surface *textBotPannel[5];
	SDL_Surface *textOptions[5];

	TTF_Font *czcionka1;
	TTF_Font *czcionka2;
	TTF_Font *czcionka3;
	TTF_Font *czcionka4;
	TTF_Font *czcionka5;

	bool menuOpened;
	int menuPosY;

	bool rPanelOpened;
	int rightPanelX;

	bool optionsOpened;
	int optionsPanelLX;
	int optionsPanelRX;
	int optionsAlfa;
	int optionsCardSelected;
	int optionsVolume;

	bool helpOpened;

public:
	SDL_table(void);
	~SDL_table(void);

	bool getMenuOpened(){return menuOpened;};
	void setMenuOpened(bool x){menuOpened=x;};

	bool getRPanelOpened(){return rPanelOpened;};
	void setRPanelOpened(bool x){rPanelOpened=x;};

	bool getoptionsOpened(){return optionsOpened;};
	void setoptionsOpened(bool x){optionsOpened=x;};

	void loadTable();
	void drawTable(SDL_Surface * &ekran);
	void drawButtons(int mode,int minBet,int maxBet,SDL_Surface *&ekran);
	void drawPointer(int player,SDL_Surface *&ekran);
	void drawWinner(std::string  winer,SDL_Surface *&ekran);
	void drawInfo(int ileGraczy,int *pCoins,int pot,int *pBets,std::string *pNames,SDL_Surface *&ekran, int gamephase);
	void drawTableInfo(int ileGraczy,int *pBets,SDL_Surface *&ekran);
	void drawRPanel(SDL_Surface *&ekran);
	void drawOptionsMenu(SDL_Surface *&ekran);
	void drawOptionsText(SDL_Surface *&ekran);
	void drawGameMenu(SDL_Surface *&ekran);

	void eventRightPanel(int mx,int my);
	void eventOptionsCard(int mx,int my,int &cardID);
	bool eventOptionsVolume(int mx,int my,int &volume);
	void eventOptionsBack(int mx,int my);
	void eventDrawWinner(int mx,int my,int &phase,int &gamePhase);
	void eventMenu(int mx,int my);
	bool eventExit(int mx,int my);
	void eventOptions(int mx,int my);
	int  eventPokerButtons(int mx,int my);
};

