#include "Deck.h"
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
Deck::Deck()
{
	for(int i=0;i<52;i++)
	{
		cards[i]=i;
	}
}

Deck::Deck(int ilegraczy)
{
	for(int i=0;i<52;i++)
	{
		cards[i]=i;
	}
	ileG=ilegraczy;
	hands=new int*[ilegraczy];
	for(int i=0;i<ilegraczy;i++)
		hands[i]=new int[2];
}
Deck::~Deck(void)
{
	for(int i=0;i<ileG;i++)
		delete []hands[i];
	delete []hands;
}
void Deck::Shuffle()
{
	srand(time(NULL));
	for(int i=0;i<52;i++)
	{
		int rnd=rand()%52;
		int temp=cards[i];
		cards[i]=cards[rnd];
		cards[rnd]=temp;
	}
	
	/*cards[20]=2;
	cards[16]=11;
	cards[17]=24;
	cards[18]=31;
	cards[19]=49;*/
	
}
int* Deck::getTalia()
{
	return cards;
}
void Deck::Deal(int ilegraczy)
{
	for(int j=0;j<ilegraczy;j++)
	{
			hands[j][0]=cards[j*2];
			hands[j][1]=cards[j*2+1];
	}
	for(int i=0;i<5;i++)
		table[i]=cards[ilegraczy*2+i];
}
void Deck::ShowHands(int player)
{
	
		std::cout<<"Gracz "<<player+1<<": ";
		Card(hands[player][0]);
		std::cout<<" | ";
		Card(hands[player][1]);
	
}
void Deck::Card(int x)
{
	switch(x/4){
	case 0: std::cout<<"Dwojka "; break;
	case 1: std::cout<<"Trojka ";break;
	case 2: std::cout<<"Czwórka ";break;
	case 3: std::cout<<"Piatka ";break;
	case 4: std::cout<<"Szostka ";break;
	case 5: std::cout<<"Siodemka ";break;
	case 6: std::cout<<"Osemka ";break;
	case 7: std::cout<<"Dziewiatka ";break;
	case 8: std::cout<<"Dziesiatka ";break;
	case 9: std::cout<<"Walet ";break;
	case 10: std::cout<<"Dama ";break;
	case 11: std::cout<<"Krol ";break;
	case 12: std::cout<<"As ";break;}
	switch(x%4){
	case 0: std::cout<<"Trefl";break;
	case 1: std::cout<<"Karo";break;
	case 2: std::cout<<"Pik";break;
	case 3: std::cout<<"Kier";break;}
}
int* Deck::GetTable()
{
	/*std::cout<<"Stol: ";
	Card(table[0]);
	std::cout<<" | ";
	Card(table[1]);
	std::cout<<" | ";
	Card(table[2]);
	std::cout<<" | ";
	if(x>0)
	{
		Card(table[3]);
		std::cout<<" | ";
	}
	if(x>1)
	{
		Card(table[4]);
		std::cout<<" | ";
	}*/
	return table;
}
/*int* Deck::CheckHands(int player,int mode)
{
	int *results=new int[2];
	int *playercards=new int[7];
	for(int i=0;i<7;i++)
	{
		if(i<2)
			playercards[i]=hands[player][i];
		else
			playercards[i]=table[i-2];
	}
	Sort(playercards);
	if(RoyalPoker(playercards))
	{
		results[0]=9;
		results[1]=RoyalPoker(playercards);
		return results;
	}
	if(Poker(playercards))
	{
		results[0]=8;
		results[1]=Poker(playercards);
		return results;
	}
	if(FourKind(playercards))
	{
		results[0]=7;
		results[1]=FourKind(playercards);
		return results;
	}
	if(FullHouse(playercards))
	{
		results[0]=6;
		results[1]=FullHouse(playercards);
		return results;
	}
	if(Flush(playercards))
	{
		results[0]=5;
		results[1]=Flush(playercards);
		return results;
	}
	if(Straight(playercards))
	{
		results[0]=4;
		results[1]=Straight(playercards);
		return results;
	}
	if(ThreeKind(playercards))
	{
		results[0]=3;
		results[1]=ThreeKind(playercards);
		return results;
	}
	if(TwoPairs(playercards))
	{
		results[0]=2;
		results[1]=TwoPairs(playercards);
		return results;
	}
	if(Pair(playercards)!=0)	
	{
		results[0]=1;
		results[1]=Pair(playercards);
		return results;
	}
	results[0]=0;
	results[1]=HighCard(playercards);
	return results;

}*/
int* Deck::CheckHands(int *playercards)
{
	int *results =new int[2];
	if(RoyalPoker(playercards))
	{
		results[0]=9;
		results[1]=RoyalPoker(playercards);
		return results;
	}
	if(Poker(playercards))
	{
		results[0]=8;
		results[1]=Poker(playercards);
		return results;
	}
	if(FourKind(playercards))
	{
		results[0]=7;
		results[1]=FourKind(playercards);
		return results;
	}
	if(FullHouse(playercards))
	{
		results[0]=6;
		results[1]=FullHouse(playercards);
		return results;
	}
	if(Flush(playercards))
	{
		results[0]=5;
		results[1]=Flush(playercards);
		return results;
	}
	if(Straight(playercards))
	{
		results[0]=4;
		results[1]=Straight(playercards);
		return results;
	}
	if(ThreeKind(playercards))
	{
		results[0]=3;
		results[1]=ThreeKind(playercards);
		return results;
	}
	if(TwoPairs(playercards))
	{
		results[0]=2;
		results[1]=TwoPairs(playercards);
		return results;
	}
	if(Pair(playercards)!=0)	
	{
		results[0]=1;
		results[1]=Pair(playercards);
		return results;
	}
	results[0]=0;
	results[1]=HighCard(playercards);
	return results;
}
void Deck::setPlayerCards(Player *&player,int ilegraczy)
{ 
	int *playercards=new int[7];
	for(int i=0;i<ilegraczy;i++)
	{
		for(int j=0;j<7;j++)
		{
		if(j<2)
			playercards[j]=hands[i][j];
		else
			playercards[j]=table[j-2];
		}
		Sort(playercards);
		player[i].setCards(playercards);
	}
	delete []playercards;

}
void Deck::Sort( int *&t)
{
	bool tmp=true;
	while(tmp==true)
	{
		tmp=false;
		for(int i=0;i<6;i++)
			if(t[i]>t[i+1])
			{	
				int temp=t[i];
				t[i]=t[i+1];
				t[i+1]=temp;	
				tmp=true;
			}

	}
	
}
int Deck::HighCard(int *t)
{
	int score=0;
	int multiplier=1;
	for(int i=2;i<7;i++)
			{
				score+=t[i]/4*multiplier;
				multiplier*=13;
			}
			return score;

}
int Deck::Pair(int *t)
{
	unsigned int score=0;
	for(int i=0;i<6;i++)
		if(t[i]/4==t[i+1]/4)
		{
			score=0;
			score+=t[i]/4*2197;
			switch(i){
			case 5:
				score+=t[4]/4*169+t[3]/4*13+t[2];
				break;
			case 4:
				score+=t[6]/4*169+t[3]/4*13+t[2];
				break;
			case 3:
				score+=t[6]/4*169+t[5]/4*13+t[2];
				break;
			default:
				score+=t[6]/4*169+t[5]/4*13+t[4];
				break;
			};
			
		}	
		return score;
}
int Deck::TwoPairs(int* t)
{
	int pair1=-1;
	int pair2=-1;
	int card5=-1;
	int counter=0;

	for(int i=0;i<6;i++)
	{
			if(t[i]/4==t[i+1]/4)
			{
				counter++;
				pair2=pair1;
				pair1=t[i]/4;
				i++;
			}
			else
				card5=t[i]/4;
	}
	if(counter>1)
		return pair1*169+pair2*13+card5;
	else
		return 0;

}
int Deck::ThreeKind(int *t)
{
	unsigned int score=0;
	for(int i=0;i<5;i++)
		if(t[i]/4==t[i+1]/4 && t[i+1]/4==t[i+2]/4)
		{
			score=0;
			score+=t[i]/4*169;
			switch(i){
			case 4:
				score+=t[3]/4*13+t[2];
				break;
			case 3:
				score+=t[6]/4*13+t[2];
				break;
			default:
				score+=t[5]/4*13+t[4];
				break;
			};
		}
	return score;
	
}
int Deck::FourKind(int *t)
{
	int card5=0;
	int four=-1;
	for(int i=0;i<4;i++)
		if(t[i]/4==t[i+1]/4 && t[i+1]/4==t[i+2]/4 && t[i+2]/4==t[i+3]/4) 
		{
			four=t[i]/4;
			i+=3;
		}
		else
			card5=t[i]/4;
	if(four>=0)
		return card5+four*13;
	else
		return 0;
}
int Deck::FullHouse(int *t) //blad
{	
	int three=-1;
	int pair=-1;


	int counter=0;
	if(ThreeKind(t))
	{		
		for(int i=0;i<5;i++)
		{
			if(t[i]/4==t[i+1]/4 &&t[i+1]/4==t[i+2]/4)
			{
				counter++;
				if(counter<2)
					pair=t[i]/4;
				i+=2;
			}
		}
		if(counter>1)
		{
			three=ThreeKind(t)/169;
			return three*13+pair;
		}
		else
		{
			pair=-1;
			for(int j=0;j<6;j++)
			{
				if(t[j]/4==t[j+1]/4 && t[j+1]/4!=t[j+2]/4)
				{
					three=ThreeKind(t)/169;
					pair=t[j]/4;
				}
				else
					if(t[j]/4==t[j+1]/4)
					{
						j+=2;
					}
				
			}
		}


	}
	if(pair>0)
		return three*13+pair;
	else
		return 0;
}
int Deck::Flush(int *t)
{
	int color_cards[7];
	int counter;
	int multiplier=1;
	int score=0;
	for(int k=0;k<4;k++)
	{
		for(int i=0;i<7;i++)
			color_cards[i]=0;
		counter=0;
		multiplier=1;
		for(int i=0;i<7;i++)
			if(t[i]%4==k)
			{
				counter++;
				color_cards[counter-1]=t[i]/4;
			}
		if(counter>4)
		{
			for(int i=counter-5;i<counter;i++)
			{
				score+=color_cards[i]*multiplier;
				multiplier*=13;
			}
			return score;
		}
	}
	return 0;

}
int Deck::Straight(int *t)
{
	int k=0;
	int str_high=0;
	for(int i=0;i<6;i++)
		{
			if(t[i]/4==t[i+1]/4)
				continue;
			else
				if(t[i]/4==t[i+1]/4-1)
				{
					k++;
					str_high=t[i+1]/4;
				}
				else
					if(k>=4)
						return str_high;
					else
						k=0;
			
		}
		if(k>=4)
			return str_high;
		else
			return 0;
	/*for(int i=0;i<3;i++)
		if(t[i]/4== t[i+1]/4-1 && t[i+1]/4== t[i+2]/4-1 && t[i+2]/4== t[i+3]/4-1 && t[i+3]/4== t[i+4]/4-1 )
			return true;
	return false;*/
}
int Deck::Poker(int *t)
{
	int k=0,kolor=0;
	int poker_high=0;
	for(int i=0;i<6;i++)
		{
			if(t[i]/4==t[i+1]/4)
				kolor++;
			else
			{
				if(kolor==0)
					{
						if(t[i]/4==t[i+1]/4-1 && t[i]%4==t[i+1]%4)
						{
							k++;
							poker_high=t[i+1]/4;
						}
						else
							if (k>=4)
								return poker_high;
							else
								k=0;
					}
				else
					{
						if(t[i]/4==t[i+1]/4-1)
							{
								for(int j=0;j<=kolor;j++)
									if(t[i-j]%4==t[i+1]%4)
									{
										k++;
										poker_high=t[i+1]/4;
									}
							}
						else
							if(k>=4)
								return poker_high;
							else
								k=0;						
					}
			kolor=0;			
			}
		}
	
		return 0;
	/*if(Straight(t))
	{
		for(int i=0;i<3;i++)
			if(t[i]/4==t[i+1]/4-1 && t[i+1]/4==t[i+2]/4-1)
				if(t[i]%4 == t[i+1]%4 && t[i+1]%4 == t[i+2]%4 && t[i+2]%4== t[i+3]%4 && t[i+3]%4== t[i+4]%4 )
					return true;
	}
	return false;*/
}
int Deck::RoyalPoker(int *t)
{
	int k=0,kolor=0;
	int poker_high=0;
	for(int i=0;i<6;i++)
		{
			if(t[i]/4==t[i+1]/4)
				kolor++;
			else
			{
				if(kolor==0)
					{
						if(t[i]/4==t[i+1]/4-1 && t[i]%4==t[i+1]%4)
						{
							k++;
							poker_high=t[i+1]/4;
						}
						else
							if (k>=4 && poker_high==12)
								return poker_high;
							else
								k=0;
					}
				else
					{
						if(t[i]/4==t[i+1]/4-1)
							{
								for(int j=0;j<=kolor;j++)
									if(t[i-j]%4==t[i+1]%4)
									{
										k++;
										poker_high=t[i+1]/4;
									}
							}
						else
							if(k>=4 && poker_high==12)
								return poker_high;
							else
								k=0;						
					}
			kolor=0;			
			}
		}
	
		return 0;
}
