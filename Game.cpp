#include<iostream>

#include "Game.h"

#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

using namespace std;
Game::Game(int iGraczy)
{
	ileGraczy=iGraczy;
	playersLeft=ileGraczy;
	playersLeftInRound=ileGraczy;
	players=new Player[ileGraczy];
	t=new Deck(ileGraczy);
}
Game::~Game(void)
{
	
	delete t;
	delete []players;
};
int Game::getIleGraczy()
{
	return ileGraczy;
}
void Game::setIleGraczy(int ig)
{
	ileGraczy=ig;
}


void Game::Create_players()
{
	
	std::string names[8]={"Player1","Jhon","Bill","Kevin","Dean","Frank","Jack","Joe"};
	for(int i=0;i<ileGraczy;i++)
	{
		players[i].setCoins(200);
		players[i].setName(names[i]);
	}
}
void Game::setLoosers()
{
	for(int i=0;i<ileGraczy;i++)
	{
		if(players[i].getCoins()==0 && players[i].isInGame())
		{
			playersLeft--;
			players[i].leftGame();
		}
		players[i].resetPlayer();
	}
	playersLeftInRound=playersLeft;
}
/*void Game::ShowPlayerCards(Deck ta)
{
	for(int i=1;i<ileGraczy;i++)
	{
		if(players[i].isInGame() && !players[i].isFold())
		{
			ta.ShowHands(i);
			cout<<"  bet: "<<players[i].getInPot()<<endl;
		}
		else if(!players[i].isInGame())
			cout<<"Gracz "<<i+1<<" :-------LEFT TABLE-----\n";
		else
			cout<<"Gracz "<<i+1<<" :-------FOLD-----\n";
	}
	cout<<"\n===================================================\n"<<endl;
	cout<<"Twoje karty:"<<endl;
	ta.ShowHands(0);
}*/

int* Game::getCards()
{
	return t->getTalia();
}

std::string* Game::getPlayersNames()
{
	std::string *tmp=new std::string[ileGraczy];
	for(int i=0;i<ileGraczy;i++)
		tmp[i]=players[i].getName();
	return tmp;
}
std::string Game::getPlayersName(int i)
{
	return players[i].getName();
}
int* Game::getPlayersCoins()
{
	int *tmp=new int[ileGraczy];
	for(int i=0;i<ileGraczy;i++)
		tmp[i]=players[i].getCoins();
	return tmp;
}

int* Game::getPlayersBets()
{
	int *tmp=new int[ileGraczy];
	for(int i=0;i<ileGraczy;i++)
		tmp[i]=players[i].getInPot();
	return tmp;
}

int Game::getPot()
{
	return pot;
}

int Game::getLeftInGame()
{
	return playersLeftInRound;
}

int Game::getPlayerCoins(int i)
{
	return players[i].getCoins();
}

int Game::getAllPlayerCoins(int i)
{
	return players[i].getCoins()+players[i].getInPot();
}


void Game::Preflop(int &phase,int &i,bool &mode,int &gamePhase)
{
	//cout<<"\n=================================PREFLOP=====================================\n"<<endl;
	
	//for(int i=0;i<ileGraczy;i++)
	//
	if(mode)
	{
		if(playersLeftInRound>1)
		{
			if(players[i].isInGame() && !players[i].isFold())
			{
				if(i==0)
					phase=3;
					//players[i].userAction(biggestBet,pot);
				else
					players[i].cpuActionPF(biggestBet,pot);
				if(players[i].isFold() && i!=0)
					playersLeftInRound--;
			}
		}
	//}
		if(i>=ileGraczy-1)
			mode=false;
	}
	else
	{
		if(players[i].getInPot()<biggestBet && playersLeftInRound>1)
		{
			if(players[i].isInGame() && !players[i].isFold())
			{
				if(i==0)
					phase=3;
				else
					players[i].cpuActionPF(biggestBet,pot);
				if(players[i].isFold() && i!=0)
					playersLeftInRound--;
			}
			/*if(i<ileGraczy)
				i++;
			else
			{
				i=0;
			}*/
		}
		else
		{
			i=-1;
			mode=true;
			gamePhase++;
		}
	}
	//ShowPlayerCards(ta);
	//cout<<"POT: "<<pot<<".\n";
	//cout<<"ACTUAL HIGHEST BET: "<<biggestBet<<".\n";

	//cout<<endl;
} 
void Game::Flop(int &phase,int &i,bool &mode,int &gamePhase)
{
	if(mode)
	{
		if(playersLeftInRound>1)
		{
			if(players[i].isInGame() && !players[i].isFold())
			{
				if(i==0)
					phase=3;
					//players[i].userAction(biggestBet,pot);
				else
					players[i].cpuActionFL(biggestBet,pot);
				if(players[i].isFold() && i!=0)
					playersLeftInRound--;
			}
		}
	//}
		if(i>=ileGraczy)
			mode=false;
		
	}
	else
	{
		if(players[i].getInPot()<biggestBet && playersLeftInRound>1)
		{
			if(players[i].isInGame() && !players[i].isFold())
			{
				if(i==0)
					phase=3;
				else
					players[i].cpuActionFL(biggestBet,pot);
				if(players[i].isFold() && i!=0)
					playersLeftInRound--;
			}
			if(i>=ileGraczy)
				mode=false;
		}
		else
		{
			i=-1;
			mode=true;
			gamePhase++;
		}
	}
	
}
void Game::Turn(int &phase,int &i,bool &mode,int &gamePhase)
{
	if(mode)
	{
		if(playersLeftInRound>1)
		{
			if(players[i].isInGame() && !players[i].isFold())
			{
				if(i==0)
					phase=3;
					//players[i].userAction(biggestBet,pot);
				else
					players[i].cpuActionTN(biggestBet,pot);
				if(players[i].isFold() && i!=0)
					playersLeftInRound--;
			}
		}
	//}
		if(i>=ileGraczy)
			mode=false;
	}
	else
	{
		if(players[i].getInPot()<biggestBet && playersLeftInRound>1)
		{
			if(players[i].isInGame() && !players[i].isFold())
			{
				if(i==0)
					phase=3;
				else
					players[i].cpuActionTN(biggestBet,pot);
				if(players[i].isFold() && i!=0)
					playersLeftInRound--;
			}
			/*if(i<ileGraczy)
				i++;
			else
			{
				i=0;
			}*/
		}
		else
		{
			i=-1;
			mode=true;
			gamePhase++;
		}
	}
}
void Game::River(int &phase,int &i,bool &mode,int &gamePhase)
{
	if(mode)
	{
		
		if(players[i].isInGame() && !players[i].isFold())
		{
			if(i==0)
				phase=3;
					//players[i].userAction(biggestBet,pot);
			else
				players[i].cpuActionRV(biggestBet,pot);
			if(players[i].isFold() && i!=0)
				playersLeftInRound--;
		}
		
	//}
		if(i>=ileGraczy)
			mode=false;
	}
	else
	{
		if(players[i].getInPot()<biggestBet)
		{
			if(players[i].isInGame() && !players[i].isFold())
			{
				if(i==0)
					phase=3;
				else
					players[i].cpuActionRV(biggestBet,pot);
				if(players[i].isFold() && i!=0)
					playersLeftInRound--;
			}
			/*if(i<ileGraczy)
				i++;
			else
			{
				i=0;
			}*/
		}
		else
		{
			i=-1;
			mode=true;
			gamePhase++;
		}
	}
	
}
void Game::startGame()
{
	playersLeft=ileGraczy;
	playersLeftInRound=ileGraczy;
	Create_players();
}
void Game::startRound()
{
	pot=0;
	bigBlind=0;
	biggestBet=15;
	t->Shuffle();
	t->Deal(ileGraczy);	
	t->setPlayerCards(players,ileGraczy);
}

bool Game::isEndGame()
{
	if(playersLeft>1)
		return false;
	else
		return true;
}
/*void Game::gameplay()
{
	pot=0;
	bigBlind=0;
	biggestBet=15;
	t.Shuffle();
	//t.ShowTalia();
	//t.Deal(nplayers);
	t.Deal(ileGraczy);	
	t.setPlayerCards(players,ileGraczy);
	/*t.table[0]=35;
	t.table[1]=39;
	t.table[2]=43;
	t.table[3]=47;
	t.table[4]=0;
	cout<<endl;
	//Preflop(t);
	//Flop(t);
	//Turn(t);
	//River(t);
	cout<<"\n=================================RESULTS=====================================\n"<<endl;
	t.ShowResult(ileGraczy,players,pot);
	setLoosers();
	showCoins();
	t.~Deck();
}*/

/*void Game::showCoins()
{
	cout<<"\n=============================================================================\n";
	for(int i=0;i<ileGraczy;i++)
		cout<<"Gracz "<<i+1<<": "<<players[i].getCoins()<<".\n";
}*/



void Game::userAction(int flag,int bet)
{
	//cout<<"\nmax bet= "<<maxBet<<"\nTwoje coinsy= "<<coins+coinsInPot<<endl;
	//cout<<"1.Bet\n2.Call\n3.Fold\n"<<endl;
	//while(flag<1 || flag>3)
		//cin>>flag;
	switch(flag)
		{
			case 1:
				//while(tmpBet<maxBet || tmpBet>coins)
					//cin>>tmpBet;
				pot+=bet-players[0].getInPot();
				players[0].setCoins((bet-players[0].getInPot())*-1);
				biggestBet=bet;
				players[0].setInPot(bet);
				break;
			case 2:
				players[0].call(biggestBet,pot);
				break;
			case 3:
				players[0].fold();
				playersLeftInRound--;
				break;
		};
}

int Game::showResults(int &gamePhasel)
{
	int winner=0;
	int best_result_1=-1;
	int best_result_2=-1;

	for(int i=0;i<ileGraczy;i++)
	{
		int *tmp=t->CheckHands(players[i].getCards());
		if(players[i].isInGame() && !players[i].isFold())
		{
			if(tmp[0]>best_result_1)
			{
				best_result_1=tmp[0];
				best_result_2=tmp[1];
				winner=i;
			}
			else
			if(tmp[0]==best_result_1 && tmp[1]>best_result_2)
			{
				best_result_2=tmp[1];
				winner=i;
			}
		}
		delete []tmp;
	}
	players[winner].setCoins(pot);
	return winner;
}

bool Game::getPlayerFold(int playerIndex)
{
	return players[playerIndex].isFold();
}

bool Game::getPlayerInGame(int playerIndex)
{
	return players[playerIndex].isInGame();
}