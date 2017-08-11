#include "Player.h"
#include "Deck.h"
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

Deck metods;

Player::Player(void)
{
	inGame=true;
	folded=false;
	coins=0;
	coinsInPot=0;
	strenghtOfCards=0;
}


Player::~Player(void)
{
}

void Player::setName(string name)
{
	this->name=name;
}
string Player::getName()
{
	return name;
}

void Player::setCoins(int coins)
{
	this->coins+=coins;
}
int	 Player::getCoins()
{
	return coins;
}
void Player::setInPot(int bet)
{
	coinsInPot=bet;
}


int Player::getInPot()
{
	return coinsInPot;
}

void Player::setCards(int *cards)
{
	for(int i=0;i<7;i++)
		this->cards[i]=cards[i];
}
int *Player::getCards()
{
	return cards;
}

bool Player::isInGame()
{
	return inGame;
}
bool Player::isFold()
{
	return folded;
}
void Player::leftGame()
{
	inGame=false;
}

void Player::fold()
{
	folded=true;
}
void Player::setStrenghtOfCards()
{
	strenghtOfCards=metods.CheckHands(cards)[0];
}
void Player::bet(int coins)
{

}

/*void Player::userAction(int &maxBet,int &pot)
{
	int flag=0;
	int tmpBet=0;
	cout<<"\nmax bet= "<<maxBet<<"\nTwoje coinsy= "<<coins+coinsInPot<<endl;
	cout<<"1.Bet\n2.Call\n3.Fold\n"<<endl;
	while(flag<1 || flag>3)
		cin>>flag;
	switch(flag)
		{
			case 1:
				cout<<"\nIle?\n";
				while(tmpBet<maxBet || tmpBet>coins)
					cin>>tmpBet;
				pot+=tmpBet-coinsInPot;
				coins-=tmpBet-coinsInPot;
				maxBet=tmpBet;
				coinsInPot=tmpBet;
				break;
			case 2:
				call(maxBet,pot);
				break;
			case 3:
				folded=true;
				break;
		};
}
*/

void Player::cpuActionPF(int &maxBet,int &pot)
{
	int flag=0;
	int tmpBet=0;
	int tmpRand=rand()%20;
	//-------------Okreslanie akcji gracza komputerowego
	if(strenghtOfCards>=5)
	{
		if(tmpRand>16)
		{
			flag=1;
			tmpBet=rand()%15+maxBet;
		}
		else if(tmpRand>4)
		{
			flag=2;
		}
		else
			if(coinsInPot==maxBet)
				flag=2;
			else
				flag=3;
			
	}
	else 
	{
		if(tmpRand>17)
		{
			flag=1;
			tmpBet=rand()%15+maxBet;
		}
		else if(tmpRand>5)
		{
			flag=2;
		}
		else
			if(coinsInPot==maxBet)
				flag=2;
			else
				flag=3;
			
	}
	//---------------wykonanie akcji
	switch(flag)
		{
			case 1:
				if(tmpBet>coins+coinsInPot)
					tmpBet=coins;
				pot+=tmpBet-coinsInPot;
				coins-=tmpBet-coinsInPot;
				maxBet=tmpBet;
				coinsInPot=tmpBet;
				break;
			case 2:
				call(maxBet,pot);
				break;
			case 3:
				folded=true;
				break;
		};
}
void Player::cpuActionFL(int &maxBet,int &pot)
{
	int flag=0;
	int tmpBet=0;
	int tmpRand=rand()%20;
	//-------------Okreslanie akcji gracza komputerowego
	if(strenghtOfCards>=7)
	{
		if(tmpRand>11)
		{
			flag=1;
			tmpBet=rand()%15+maxBet;
		}
		else if(tmpRand>3)
		{
			flag=2;
		}
		else
			if(coinsInPot==maxBet)
				flag=2;
			else
				flag=3;
			
			
	}
	else if(strenghtOfCards>=2)
	{
		if(tmpRand>16)
		{
			flag=1;
			tmpBet=rand()%15+maxBet;
		}
		else if(tmpRand>4)
		{
			flag=2;
		}
		else
			if(coinsInPot==maxBet)
				flag=2;
			else
				flag=3;
			
	}
	else
	{
		if(tmpRand>16)
		{
			flag=1;
			tmpBet=rand()%15+maxBet;
		}
		else if(tmpRand>10)
		{
			flag=2;
		}
		else
			if(coinsInPot==maxBet)
				flag=2;
			else
				flag=3;
			
	}
	//---------------wykonanie akcji
	switch(flag)
		{
			case 1:
				if(tmpBet>coins+coinsInPot)
					tmpBet=coins;
				pot+=tmpBet-coinsInPot;
				coins-=tmpBet-coinsInPot;
				maxBet=tmpBet;
				coinsInPot=tmpBet;
				break;
			case 2:
				call(maxBet,pot);
				break;
			case 3:
				folded=true;
				break;
		};
}
void Player::cpuActionTN(int &maxBet,int &pot)
{
	int flag=0;
	int tmpBet=0;
	int tmpRand=rand()%20;
	//-------------Okreslanie akcji gracza komputerowego
	if(strenghtOfCards>=7)
	{
		if(tmpRand>11)
		{
			flag=1;
			tmpBet=rand()%30+maxBet;
		}
		else if(tmpRand>1)
		{
			flag=2;
		}
		else
			if(coinsInPot==maxBet)
				flag=2;
			else
				flag=3;
			
			
	}
	else if(strenghtOfCards>=5)
	{
		if(tmpRand>15)
		{
			flag=1;
			tmpBet=rand()%30+maxBet;
		}
		else if(tmpRand>2)
		{
			flag=2;
		}
		else
			if(coinsInPot==maxBet)
				flag=2;
			else
				flag=3;
			
	}
	else if(strenghtOfCards>=2)
	{
		if(tmpRand>15)
		{
			flag=1;
			tmpBet=rand()%10+maxBet;
		}
		else if(tmpRand>4)
		{
			flag=2;
		}
		else
			if(coinsInPot==maxBet)
				flag=2;
			else
				flag=3;
			
	}
	else
	{
		if(tmpRand>16)
		{
			flag=1;
			tmpBet=rand()%15+maxBet;
		}
		else if(tmpRand>8)
		{
			flag=2;
		}
		else
			if(coinsInPot==maxBet)
				flag=2;
			else
				flag=3;
			
	}
	//---------------wykonanie akcji
	switch(flag)
		{
			case 1:
				if(tmpBet>coins+coinsInPot)
					tmpBet=coins;
				pot+=tmpBet-coinsInPot;
				coins-=tmpBet-coinsInPot;
				maxBet=tmpBet;
				coinsInPot=tmpBet;
				break;
			case 2:
				call(maxBet,pot);
				break;
			case 3:
				folded=true;
				break;
		};
}
void Player::cpuActionRV(int &maxBet,int &pot)
{
	int flag=0;
	int tmpBet=0;
	int tmpRand=rand()%20;
	//-------------Okreslanie akcji gracza komputerowego
	if(strenghtOfCards>=7)
	{
		if(tmpRand>1)
		{
			flag=1;
			tmpBet=rand()%400+maxBet;
		}
		else if(tmpRand>0)
		{
			flag=2;
		}
		else
			if(coinsInPot==maxBet)
				flag=2;
			else
				flag=3;
			
			
	}
	else if(strenghtOfCards>=5)
	{
		if(tmpRand>10)
		{
			flag=1;
			tmpBet=rand()%100+maxBet;
		}
		else if(tmpRand>0)
		{
			flag=2;
		}
		else
			if(coinsInPot==maxBet)
				flag=2;
			else
				flag=3;
			
	}
	else if(strenghtOfCards>=2)
	{
		if(tmpRand>15)
		{
			flag=1;
			tmpBet=rand()%10+maxBet;
		}
		else if(tmpRand>2)
		{
			flag=2;
		}
		else
			if(coinsInPot==maxBet)
				flag=2;
			else
				flag=3;
			
	}
	else
	{
		if(tmpRand>12)
		{
			flag=1;
			tmpBet=rand()%15+maxBet;
		}
		else if(tmpRand>3)
		{
			flag=2;
		}
		else
			if(coinsInPot==maxBet)
				flag=2;
			else
				flag=3;
			
	}
	//---------------wykonanie akcji
	switch(flag)
		{
			case 1:
				if(tmpBet>coins+coinsInPot)
					tmpBet=coins;
				pot+=tmpBet-coinsInPot;
				coins-=tmpBet-coinsInPot;
				maxBet=tmpBet;
				coinsInPot=tmpBet;
				break;
			case 2:
				call(maxBet,pot);
				break;
			case 3:
				folded=true;
				break;
		};
}

void Player::call(int &maxBet,int &pot)
{
	if(maxBet>coins+coinsInPot)
				{
					coinsInPot+=coins;
					pot+=coins;
					coins=0;
				}
				else
				{
					pot+=maxBet-coinsInPot;
					coins-=maxBet-coinsInPot;
					coinsInPot=maxBet;					
				}
}

void Player::resetPlayer()
{
	coinsInPot=0;
	folded=false;

}