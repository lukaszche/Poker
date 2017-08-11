#pragma once
#include <time.h>
#include <stdio.h>
#include <iostream>
#include "Deck.h"
#include "SDL_functions.h"

class Game//:Deck
{
private:
	int ileGraczy;
	int playersLeft;
	int playersLeftInRound;
	int pot;
	int bigBlind;
	int biggestBet;
	Player *players;
	Deck *t;
public:
	
	
	Game(int iGraczy);
	~Game(void);

	int getIleGraczy();
	void setIleGraczy(int ilegraczy);
	int getLeftInGame();
	std::string* getPlayersNames();
	int *getPlayersCoins();
	int *getPlayersBets();
	int getPot();
	int* getCards();
	std::string getPlayersName(int playerIndex);
	bool getPlayerFold(int playerIndex);
	int getPlayerCoins(int playerIndex);
	int getAllPlayerCoins(int playerIndex);
	bool getPlayerInGame(int playerIndex);
	int getMaxBet(){return biggestBet;};
	//int menu();
	//void Options();
	void Create_players();//
	void setLoosers();//
	//void ShowPlayerCards(Deck ta);
	void userAction(int flag,int bet);
	void Preflop(int &phase,int &player,bool &mode,int &gamePhase);
	void Flop(int &phase,int &player,bool &mode,int &gamePhase);
	void Turn(int &phase,int &player,bool &mode,int &gamePhase);
	void River(int &phase,int &player,bool &mode,int &gamePhase);
	void startGame();
	void startRound();
	bool isEndGame();
	//void gameplay();
	//void showCoins();
	int showResults(int &gamePhase);
};
