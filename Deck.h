#pragma once
#include <time.h>
#include <stdio.h>
#include <iostream>
#include "Player.h"

class Deck
{
private:
	int cards[52];
	int **hands;
	int table[5];
	int ileG;
public:
	Deck();
	Deck(int ilegraczy);
	~Deck(void);
	void Shuffle();
	int* getTalia();
	//void Deal(int n);
	void Deal(int ilegraczy);
	void ShowHands(int player);
	int* GetTable();
	void setPlayerCards(Player *&player,int ilegraczy); 
	void Card(int x);	
	int* CheckHands(int *playercards);
	void Sort( int *&t);
	int HighCard(int *t);
	int Pair(int *t);
	int TwoPairs(int *t);
	int ThreeKind(int *t);
	int FourKind(int *t);
	int FullHouse(int *t);
	int Flush(int *t);
	int Straight(int *t);
	int Poker(int *t);
	int RoyalPoker(int *t);
	//void ShowResult(int ilegraczy,Player *players,int pot);
};

