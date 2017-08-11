#pragma once
#include<iostream>
//#include "Talia.h"
using namespace std;

class Player
{
private:
	string name;
	int coins;
	int coinsInPot;
	bool inGame;
	bool folded;
	int strenghtOfCards;
	int cards[7];
public:	
	
	//cards, actions, betting, fold etc.
	Player(void);
	~Player(void);
	void setName(string name);
	string getName();
	void setCoins(int coins);
	int getCoins();
	void setInPot(int bet);
	int getInPot();
	void setCards(int *cards);
	int *getCards();
	bool isInGame();
	bool isFold();
	void leftGame();
	void setStrenghtOfCards();
	void bet(int coins);//
	void fold();
	void call(int &maxBet,int &pot);//
	//void userAction(int &maxBet,int &pot);
	void cpuActionPF(int &maxBet,int &pot);
	void cpuActionFL(int &maxBet,int &pot);
	void cpuActionTN(int &maxBet,int &pot);
	void cpuActionRV(int &maxBet,int &pot);
	void resetPlayer();

};

