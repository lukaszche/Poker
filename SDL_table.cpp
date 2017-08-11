#include "SDL_table.h"
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

SDL_table::SDL_table(void)
{
	menuOpened=false;
	rPanelOpened=false;
	optionsOpened=false;

	menuOptions=NULL;
	optionsCards=NULL;
	menuOpen=NULL;
	table=NULL;
	rPannel=NULL;
	botPannel=NULL;
	pointer=NULL;
	for(int i=0;i<3;i++)
	{
		textBotPannel[i]=NULL;
	}

	menuPosY=-172;
	rightPanelX=850;

	optionsPanelLX=-450;
	optionsPanelRX=900;
	optionsAlfa=0;

	optionsCardSelected=0;
	optionsVolume=2;
}


SDL_table::~SDL_table(void)
{
	if(table!=NULL)
		SDL_FreeSurface(table);
	if(rPannel!=NULL)
		SDL_FreeSurface(rPannel);
	if(botPannel!=NULL)
		SDL_FreeSurface(botPannel);
	if(pointer!=NULL)
		SDL_FreeSurface(pointer);
	if(menuOpen!=NULL)
		SDL_FreeSurface(menuOpen);
	/*for(int i=0;i<5;i++)
	{
		if(textBotPannel!=NULL)
			SDL_FreeSurface(textBotPannel[i]);
	}*/
	SDL_FreeSurface(textBotPannel[0]);
	SDL_FreeSurface(textBotPannel[1]);
	SDL_FreeSurface(textBotPannel[2]);
	SDL_FreeSurface(textBotPannel[3]);
	SDL_FreeSurface(textBotPannel[4]);

	SDL_FreeSurface(textOptions[0]);
	SDL_FreeSurface(textOptions[1]);
	SDL_FreeSurface(textOptions[2]);

	TTF_CloseFont(czcionka1);
	TTF_CloseFont(czcionka2);
	TTF_CloseFont(czcionka3);
	TTF_CloseFont(czcionka4);
	TTF_CloseFont(czcionka5);
}
void SDL_table::loadTable()
{
	


	table=SDL_functions::wczytaj_obraz("Surf/stol2.bmp");
	rPannel=SDL_functions::wczytaj_obraz("Surf/graLPanel.bmp");
	SDL_SetAlpha(rPannel,SDL_SRCALPHA,225);
	botPannel=SDL_functions::wczytaj_obraz("Surf/botPanelNew.bmp");
	SDL_SetAlpha(botPannel,SDL_SRCALPHA,225);
	pointer=SDL_functions::wczytaj_obraz("Surf/items.bmp");
	menuOpen=SDL_functions::wczytaj_obraz("Surf/graMenuUpLOpened.bmp");
	SDL_SetAlpha(menuOpen,SDL_SRCALPHA,225);

	czcionka1=TTF_OpenFont("Czcionki/BlackAngel.ttf",30);
	czcionka2=TTF_OpenFont("Czcionki/BlackAngel.ttf",25);
	czcionka3=TTF_OpenFont("Czcionki/VTKSNoName.ttf",39);
	czcionka4=TTF_OpenFont("Czcionki/BURNSTOW.ttf",60);
	czcionka5=TTF_OpenFont("Czcionki/VTKSNoName.ttf",29);

	//SDL_Color t1color={164,68,21};
	SDL_Color t1color={160,68,21};
	SDL_Color t2color={209,209,209};
	SDL_Color t3color={210,196,115};
	textBotPannel[0]=TTF_RenderText_Blended(czcionka3,"Rise",t3color);
	SDL_SetAlpha(textBotPannel[0],SDL_SRCALPHA,225);
	textBotPannel[1]=TTF_RenderText_Blended(czcionka3,"Call",t3color);
	SDL_SetAlpha(textBotPannel[1],SDL_SRCALPHA,225);
	textBotPannel[2]=TTF_RenderText_Blended(czcionka3,"Fold",t3color);
	SDL_SetAlpha(textBotPannel[2],SDL_SRCALPHA,225);
	textBotPannel[3]=TTF_RenderText_Blended(czcionka1,"NAME",t2color);
	SDL_SetAlpha(textBotPannel[3],SDL_SRCALPHA,225);
	textBotPannel[4]=TTF_RenderText_Blended(czcionka1,"COINS",t2color);
	SDL_SetAlpha(textBotPannel[4],SDL_SRCALPHA,225);

	textOptions[0]=TTF_RenderText_Blended(czcionka1,"Choose card layout:",t2color);
	SDL_SetAlpha(textBotPannel[0],SDL_SRCALPHA,225);
	textOptions[1]=TTF_RenderText_Blended(czcionka1,"Audio Volume:",t2color);
	SDL_SetAlpha(textBotPannel[0],SDL_SRCALPHA,225);
	textOptions[2]=TTF_RenderText_Blended(czcionka1,"Back",t2color);
	SDL_SetAlpha(textBotPannel[0],SDL_SRCALPHA,225);
	

}
void SDL_table::drawTable(SDL_Surface *&ekran)
{
	SDL_functions::blit_obraz(table,ekran,0,0,0);	
	SDL_functions::blit_obraz(botPannel,ekran,0,480,0);
}
//----rysuje informacje o rozgrywce, liste imion graczy, ich zetony, pule zetonow, nazwe fazy gry itd.
void SDL_table::drawInfo(int ileGraczy,int *pCoins,int pot,int *pBets,std::string *pNames,SDL_Surface *&ekran, int gamephase)
{
	SDL_Color t1color={15,15,15};
	SDL_Color t2color={209,209,209};
	//---Nazwa Fazy Gry----
	SDL_Surface *textGamePhase=NULL;
	std::string tmp="";
	switch(gamephase)
	{
		case 0:
			tmp="pre flop";
			break;
		case 1:
			tmp="flop";
			break;
		case 2:
			tmp="turn";
			break;
		case 3:
			tmp="river";
			break;
		case 4:
			tmp="showdown";
			break;

	}
	textGamePhase=TTF_RenderText_Blended(czcionka1,tmp.c_str(),t2color);
	SDL_SetAlpha(textGamePhase,SDL_SRCALPHA,225);
	SDL_functions::blit_obraz(textBotPannel[3],ekran,rightPanelX+100,20,0);
	SDL_functions::blit_obraz(textBotPannel[4],ekran,rightPanelX+270,20,0);
	SDL_FreeSurface(textGamePhase);
	//-----Imiona graczy + liczba zetonow + liczba zetonow obstawionych
	for(int i=0;i<ileGraczy;i++)
	{
		//--imiona graczy+wszystkie zetony
		SDL_Surface *textRPannel=NULL;
		std::string tmp=pNames[i]+" :";//+SDL_functions::IntToStr(pCoins[i]);
		textRPannel=TTF_RenderText_Blended(czcionka1,tmp.c_str(),t2color);
		SDL_SetAlpha(textRPannel,SDL_SRCALPHA,225);
		SDL_functions::blit_obraz(textRPannel,ekran,rightPanelX+100,80+40*i,0);
		SDL_FreeSurface(textRPannel);

		//--wszystkie zetony gracza
		tmp="$"+SDL_functions::IntToStr(pCoins[i]);
		textRPannel=TTF_RenderText_Blended(czcionka1,tmp.c_str(),t2color);
		SDL_SetAlpha(textRPannel,SDL_SRCALPHA,225);
		SDL_functions::blit_obraz(textRPannel,ekran,rightPanelX+270,80+40*i,0);
		SDL_FreeSurface(textRPannel);
	
	}
	//---- Pula graczy ---
	SDL_Color t3color={210,196,115};
	SDL_Surface *textPot=NULL;
	tmp="Pot: "+SDL_functions::IntToStr(pot);
	textPot=TTF_RenderText_Blended(czcionka1,tmp.c_str(),t3color);
	SDL_functions::blit_obraz(textPot,ekran,730,490,0);
	SDL_FreeSurface(textPot);

	delete[]pBets;
	delete[]pCoins;
	delete[]pNames;
}

void SDL_table::drawTableInfo(int ileGraczy,int *pBets,SDL_Surface *&ekran)
{
	SDL_Color t1color={6,8,54};
	for(int i=0;i<ileGraczy;i++)
	{
		//-zetony graczy obstawione
		SDL_Surface *textBids=NULL;
		
		std::string tmp=SDL_functions::IntToStr(pBets[i]);
		textBids=TTF_RenderText_Blended(czcionka2,tmp.c_str(),t1color);
		if(i<3)
		{
			SDL_functions::blit_obraz(textBids,ekran,GRACZ0X+210*(i)+50,GRACZ0Y+70,0);
		}
		else
			if(i<4)
			{
				SDL_functions::blit_obraz(textBids,ekran,GRACZ3X-40,GRACZ3Y,0);
			}
			else
				if(i<7)
				{
					SDL_functions::blit_obraz(textBids,ekran,GRACZ4X-195*((i-4))+30,GRACZ4Y-40,0);
				}
				else
					if(i<8)
					{
						SDL_functions::blit_obraz(textBids,ekran,GRACZ7X+100,GRACZ7Y,0);
					}
				
		SDL_FreeSurface(textBids);	
	}
	delete[]pBets;
}


//---przyciski na dolnym panelu "raise","call","fold"
void SDL_table::drawButtons(int mode,int minBet,int maxBet,SDL_Surface *&ekran)
{
	if(mode==1)//mode okresla czy przyciski maja byc wyswietlone, tzn czy jest aktualnie ruch u¿ytkownika, je¿eli jest ruch gracza komputerowego, lub uzytkownik spasowal przyciski sie nie wyswietlaja
	{

		SDL_functions::blit_obraz(textBotPannel[0],ekran,60,495,0);//przycisk raise
		SDL_functions::blit_obraz(textBotPannel[1],ekran,260,495,0);//przycisk call
		SDL_functions::blit_obraz(textBotPannel[2],ekran,460,495,0);//przycisk fold
	}
}

// wyswietla napis "Winner is:"+ winer gdzie w parametrze winer przechowuje imie zyciezcy
//oraz wyswietla przycisk next round
void SDL_table::drawWinner(std::string winer,SDL_Surface *&ekran) 
{
	//---napis zwyciezcy
	SDL_Color t1color={210,196,115};
	SDL_Surface *textWinner=NULL;
	std::string tmp="Winner is: "+winer;
	textWinner=TTF_RenderText_Blended(czcionka3,tmp.c_str(),t1color);
	SDL_SetAlpha(textWinner,SDL_SRCALPHA,225);
	SDL_functions::blit_obraz(textWinner,ekran,130,500,0);
	//---przycisk "next round"
	SDL_Surface *textNextRound=NULL;
	textNextRound=TTF_RenderText_Blended(czcionka1,"Next Round",t1color);
	SDL_SetAlpha(textNextRound,SDL_SRCALPHA,225);
	SDL_functions::blit_obraz(textNextRound,ekran,180,545,0);
	SDL_FreeSurface(textWinner);
	SDL_FreeSurface(textNextRound);
}

void SDL_table::drawPointer(int i,SDL_Surface *&ekran)
{
	
		if(i<3)
		{
			SDL_functions::blit_obraz(pointer,ekran,GRACZ0X+220*(i),140,0);
		}
		else
			if(i<4)
			{
				SDL_functions::blit_obraz(pointer,ekran,565,215,0);
			}
			else
				if(i<7)
				{
					SDL_functions::blit_obraz(pointer,ekran,GRACZ4X-220*((i-4)),315,0);
				}
				else
					if(i<8)
					{
						SDL_functions::blit_obraz(pointer,ekran,145,215,0);
					}
}

void SDL_table::drawRPanel(SDL_Surface *&ekran)
{
	if(!rPanelOpened)
	{
		if(rightPanelX<850)
		{
			rightPanelX+=25;
		}
		else
			rightPanelX=850;
		SDL_functions::blit_obraz(rPannel,ekran,rightPanelX,0,0);
	}
	else
	{
		if(rightPanelX>450)
			rightPanelX-=25;
		else
			rightPanelX=450;
		SDL_functions::blit_obraz(rPannel,ekran,rightPanelX,0,0);
	}
	
}

void SDL_table::drawGameMenu(SDL_Surface *&ekran)
{
	SDL_Rect tmpMenu;
	//----menu-----
	if(!menuOpened)
	{
		if(menuPosY>-217)
		{
			menuPosY-=45;
			tmpMenu.x=0;
			tmpMenu.y=0;
			tmpMenu.h=217;
			tmpMenu.w=159;
			SDL_functions::blit_obraz(menuOpen,ekran,0,menuPosY,&tmpMenu);
		}
		else
			menuPosY=-217;
		tmpMenu.x=0;
		tmpMenu.y=217;
		tmpMenu.h=63;
		tmpMenu.w=120;
		//tmpMenu.w=108;
		//tmpMenu.h=45;
		SDL_functions::blit_obraz(menuOpen,ekran,0,0,&tmpMenu);
	}
	else
	{
		if(menuPosY<0)
			menuPosY+=25;
		tmpMenu.x=0;
		tmpMenu.y=0;
		tmpMenu.h=217;
		tmpMenu.w=159;
		SDL_functions::blit_obraz(menuOpen,ekran,0,menuPosY,&tmpMenu);
	}
}

void SDL_table::drawOptionsMenu(SDL_Surface *&ekran)
{
	SDL_Rect rTmp1;
	rTmp1.y=0;
	rTmp1.h=550;
	rTmp1.w=357;

	if(optionsOpened)
	{
		
		rTmp1.y=0;
		rTmp1.h=550;
		rTmp1.w=714;
		//------WCZYTANIE OBRAZOW OPCJI i KART
		if(menuOptions==NULL)
			menuOptions=SDL_functions::wczytaj_obraz("Surf/Opcje.bmp");
		//------ZWIEKSZENIE KANALU ALFA
		if(optionsAlfa<215)
		{
			optionsAlfa+=20;
			SDL_SetAlpha(menuOptions,SDL_SRCALPHA,optionsAlfa);
		}
		else
			optionsAlfa=225;

		//-----PANEL OPCJI WYSWIETLANIE
		rTmp1.x=0;		
		SDL_functions::blit_obraz(menuOptions,ekran,100,0,&rTmp1);
		//---------WYSWIETLANIE TEKSTU
		if(optionsAlfa==225)
			drawOptionsText(ekran);
	}
	else
	{
		rTmp1.y=0;
		rTmp1.h=550;
		rTmp1.w=714;
		//------ZMNIEJSZENIE KANALU ALFA I WYSWIETLANIE
		if(optionsAlfa>20)
		{
			optionsAlfa-=20;
			rTmp1.x=0;
			SDL_SetAlpha(menuOptions,SDL_SRCALPHA,optionsAlfa);
			SDL_functions::blit_obraz(menuOptions,ekran,100,0,&rTmp1);
		}
		else
			optionsAlfa=0;
		
		//-----ZWALNIANIE PAMIECI PO POWIERZCHNIACH
		if(optionsAlfa==0 && menuOptions!=NULL)
		{
			SDL_FreeSurface(menuOptions);
			SDL_FreeSurface(optionsCards);
			menuOptions=NULL;
			optionsCards=NULL;
		}
	}
}

void SDL_table::drawOptionsText(SDL_Surface *&ekran)
{
	//NAPISY
	SDL_functions::blit_obraz(textOptions[0],ekran,120,130,0);
	SDL_functions::blit_obraz(textOptions[1],ekran,120,230,0);
	SDL_functions::blit_obraz(textOptions[2],ekran,430,420,0);

	//KARTY
	if(optionsCards==NULL)
			optionsCards=SDL_functions::wczytaj_obraz("Surf/cards2.bmp");

	SDL_SetAlpha(optionsCards,SDL_SRCALPHA,225);
	SDL_Rect tmp2;
	tmp2.x=585;
	tmp2.y=0;
	tmp2.w=45;
	tmp2.h=60;
	SDL_functions::blit_obraz(optionsCards,ekran,500,110,&tmp2);
	tmp2.y=60;
	SDL_functions::blit_obraz(optionsCards,ekran,560,110,&tmp2);
	tmp2.x=630;	
	tmp2.y=0;
	SDL_functions::blit_obraz(optionsCards,ekran,620,110,&tmp2);

	//Podswietlenie wybranej karty
	SDL_Rect tmp3;
	tmp3.x=855;
	tmp3.y=0;
	tmp3.w=45;
	tmp3.h=60;
	SDL_SetAlpha(menuOptions,SDL_SRCALPHA,100);
	SDL_functions::blit_obraz(menuOptions,ekran,500+(optionsCardSelected*60),110,&tmp3);

	//----PUNKTY GLOSNOSC
	tmp3.y=60;
	tmp3.h=45;
	SDL_SetAlpha(menuOptions,SDL_SRCALPHA,225);
	for(int i=0;i<4;i++)
	{
		SDL_functions::blit_obraz(menuOptions,ekran,500+(i*50),220,&tmp3);
	}

	tmp3.y=105;
	SDL_functions::blit_obraz(menuOptions,ekran,502+(optionsVolume*50),234,&tmp3);
}

void SDL_table::eventOptionsCard(int mx,int my,int &cardID)
{
	optionsCardSelected=cardID;
	for(int i=0;i<3;i++)
	{
		if(mx>500+(i*60) && mx<545+(i*60) && my>110 && my<170)
		{
			optionsCardSelected=i;
			cardID=i;
		}
	}


}

bool SDL_table::eventOptionsVolume(int mx,int my,int &vol)
{
	optionsVolume=vol/40;
	for(int i=0;i<4;i++)
	{
		if(mx>510+(i*50) && mx<540+(i*50) && my>230 && my<260)
		{
			optionsVolume=i;
			vol=i*40;
			return true;
		}
	}

	return false;
}

void SDL_table::eventOptionsBack(int mx,int my)
{
	if((mx>430) && (mx<500) && (my>420)&&(my<445))
		{
			setoptionsOpened(false);
		}
}

void SDL_table::eventRightPanel(int mx,int my)
{
	if(!rPanelOpened)
		{
			//-------OTWORZENIE PANELU
			if((mx>850) && (mx<901) && (my>2)&&(my<480))
			setRPanelOpened(true);
		}
	else
		{
			//-------ZAMKNIECIE PANELU
			setRPanelOpened(false);
		}
}

void SDL_table::eventDrawWinner(int mx,int my,int &phase,int &gamePhase)
{
	if(phase==4)
		{
			//PRZYCISK NASTEPNA RUNDA
			if((mx>180) && (mx<450) &&(my>530)&&(my<585))
			{
				phase=8;
				gamePhase=0;
			}
		}
}

void SDL_table::eventMenu(int mx,int my)
{
	if(!menuOpened)
		{
			//-----OTWORZENIE MENU LEWA-GORA
			if((mx>4) && (mx<114) && (my>4)&&(my<58))
				menuOpened=true;
		}
		else
		{
			//------ZAMKNIECIE MENU LEWA-GORA
			if(((mx>155)  && (my>0)) || ((mx>0)  && (my>212)) )
				menuOpened=false;
		}
}

bool SDL_table::eventExit(int mx,int my)
{
	if((mx>18) && (mx<85) && (my>164)&&(my<188))
		return true;
	else
		return false;
}

void SDL_table::eventOptions(int mx,int my)
{
	if(!optionsOpened)
	{
		if((mx>18) && (mx<140) && (my>20)&&(my<48))
		{
			setoptionsOpened(true);
			setMenuOpened(false);
		}
				
	}
}

int SDL_table::eventPokerButtons(int mx,int my)
{
	for(int i=0;i<3;i++)
	{
		if((mx>60+200*i) && (mx<220+200*i) &&(my>460)&&(my<545))
		{
			return i;
		}
	}
	return -1;
}
