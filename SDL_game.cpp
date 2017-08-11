#include "SDL_game.h"
#include <crtdbg.h>
#include <assert.h>


#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

SDL_game::SDL_game(void)
{

	tmpIleGraczy=8;
	//inicjalizacja modu³ów SDLa
	SDL_Init(SDL_INIT_EVERYTHING);
	Mix_Init(MIX_INIT_MP3);
	TTF_Init();
	//ustawienie powierzchni ekran na g³ówna
	ekran=SDL_SetVideoMode(EKRAN_W,EKRAN_H,EKRAN_BITY,SDL_SWSURFACE|SDL_DOUBLEBUF);
	//nazwa okna
	SDL_WM_SetCaption("Poker",NULL);
	//ustawienie zmiennych
	przycisk_flag=0;
	menu_mode=3;
	alfaRamka=255;
	alfaMenu2=255;
	alfaSand = 0;
	posSand = 0;
	//glosnosc
	audioVolume=60;
	//tyl karty
	cardBack=0;
	alfaflag=false;
	alfasandf=false;
	zamkniecie=true;
	phase=0;

	background1=NULL;
	background2 = NULL;
	button1 = NULL;
	button2 = NULL;
	button3 = NULL;
	button4 = NULL;
	buttonOver = NULL;
	buttonOff = NULL;

	ButtonOverMove = 0;

	sand = NULL;

	for(int i=0;i<10;i++)
		tekstX[i]=NULL;
	ramka1=NULL;
	cardsSPR=NULL;
	czcionka1=NULL;
	gameSound=NULL;

	Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
	cards=NULL;
	coins=NULL;
	tab=NULL;
	track=NULL;
	gra=NULL;
}


SDL_game::~SDL_game(void)
{

}

void SDL_game::usunTable()
{
	if(menu_mode!=1)
		delete tab;
	if(menu_mode==1)
	{
		
		if(cardsSPR!=NULL)
			SDL_FreeSurface(cardsSPR);
		delete track;

		for(int i=0;i<(gra->getIleGraczy()*2+5);i++)
		{
			delete cards[i];
		}
		delete []cards;

		for(int i=0;i<(gra->getIleGraczy()+1);i++)
		{
			delete coins[i];
		}
		delete []coins;

		delete gra;
		
	}
}


void SDL_game::wczytywanie_menu()
{

	//wczytanie backgrounda
	//background=IMGLoad("background1.jpg");
	background1=wczytaj_obraz("Surf/background2.jpg");
	background2 = wczytaj_obraz("Surf/background3.jpg");
	button1 = wczytaj_obraz("Surf/Button3.bmp");
	button2 = wczytaj_obraz("Surf/Button3.bmp");
	button3 = wczytaj_obraz("Surf/Button4.bmp");
	button4 = wczytaj_obraz("Surf/Button5.bmp");
	buttonOver = wczytaj_obraz("Surf/ButtonOver.bmp");


	buttonOff = wczytaj_obraz("Surf/OFF.bmp");
	sand = wczytaj_obraz("Surf/sand.jpg");

	//wczytanie czcionki
	czcionka1=TTF_OpenFont("Czcionki/VTKSNoName.ttf",28);
	czcionka2=TTF_OpenFont("Czcionki/BlackAngel.ttf",20);
	//wczytanie ramki
	ramka1=wczytaj_obraz("Surf/ramka.bmp");
	startSurf=wczytaj_obraz("Surf/StartScreen.bmp");
	//stworzenie powierzchni z tekstem
	TTF_SetFontHinting(czcionka1,TTF_HINTING_LIGHT);
	//kolor tekstu
	SDL_Color t3color={255,255,255};
	SDL_Color t2color={200,222,120};
	tekstX[0]=TTF_RenderText_Blended(czcionka1,"Start",t3color);
	tekstX[1]=TTF_RenderText_Blended(czcionka1,"Info",t3color);
	tekstX[2]=TTF_RenderText_Blended(czcionka1,"Quit",t3color);
	tekstX[3]=TTF_RenderText_Blended(czcionka1,"Back",t3color);
	tekstX[4]=TTF_RenderText_Blended(czcionka2,"Autor:  Lukasz Jablonski",t3color);
	tekstX[5]=TTF_RenderText_Blended(czcionka2,"Program \"Gra Poker\" ",t3color);
	tekstX[6]=TTF_RenderText_Blended(czcionka2,"Temat pracy: \"Gra w pokera z zastosowaniem biblioteki graficznej SDL\" ",t3color);
	tekstX[7]=TTF_RenderText_Blended(czcionka2,"Temat seminarium: Algorytmy i zlozonosc obliczeniowa",t3color);
	tekstX[8]=TTF_RenderText_Blended(czcionka2,"Promotor: Pani Doktor Joanna Kapusta",t3color);
	tekstX[9]=TTF_RenderText_Blended(czcionka2,"Autor: Lukasz Jablonski",t3color);
	TTF_CloseFont(czcionka1);
}
void SDL_game::wczytywanie_gra()
{
	gamePhase=0;
	roundMode=true;
	delayer=0;
	playerTurn=0;
	cardsSPR=wczytaj_obraz("Surf/cards2.bmp");
	coinsSPR=wczytaj_obraz("Surf/coinsy.bmp");
	delete tab;
	tab=new SDL_table();
	tab->loadTable();
	track=new SDL_Trackbar(0,200,540,50,280,66,20,100);
	gameSound = Mix_LoadMUS("Audio/ambience_casino-stephan_schutze-1391090820.mp3");
}
void SDL_game::usuwanie_menu()
{
	SDL_FreeSurface(background1);
	SDL_FreeSurface(ramka1);
	SDL_FreeSurface(startSurf);
	for(int i=0;i<10;i++)
	{
		if(tekstX[i]!=NULL)
			SDL_FreeSurface(tekstX[i]);
	}

}


void SDL_game::zdarzenia()
{
	while(SDL_PollEvent(&zdarzenie))
	{


		switch(zdarzenie.type)
		{
			//zdarzenie zamkniecia programu
		case SDL_QUIT:
			zamkniecie=false;
			break;
			//zapisywanie polozenia myszki
		case SDL_MOUSEMOTION:
			mx=zdarzenie.motion.x;
			my=zdarzenie.motion.y;
			break;

		case SDL_MOUSEBUTTONDOWN:
			if(menu_mode==1)
			{
				track->change(mx,my);
				myszka_gra();
			}
				myszka_menu1(menu_mode);
			
			
			break;
		}
	}
}

void SDL_game::drawStartScreen()
{
	blit_obraz(startSurf,ekran,0,0,0);
	blit_obraz(tekstX[4],ekran,600,EKRAN_H-50,NULL);
	
}

void SDL_game::wyswietlanie_menu1()
{
	//tlo menu
	blit_obraz(background2,ekran,0,0,NULL);
	wyswietlanie_sand();
	blit_obraz(button1, ekran, 100, -2, NULL);
	blit_obraz(button1, ekran, 290, -2, NULL);
	blit_obraz(button1, ekran, 480, -2, NULL);
	blit_obraz(button3, ekran, 606, -2, NULL);

	blit_obraz(button4, ekran, -91, -2, NULL);
	blit_obraz(button1, ekran, 795, -2, NULL);
	wyswietlanieButtonBlue();
	blit_obraz(buttonOff, ekran, 724, 15, NULL);
	//tekst start
	blit_obraz(tekstX[0],ekran,50,EKRAN_H-295,NULL);
	//options
	blit_obraz(tekstX[1],ekran,50,EKRAN_H-245,NULL);
	//quit
	blit_obraz(tekstX[2],ekran,50,EKRAN_H-195,NULL);


	wyswietlanie_ramka1(3);
}
void SDL_game::wyswietlanie_menu2()
{
	//tlo menu
	blit_obraz(background1,ekran,-300,-50,NULL);
	

	SDL_Surface * tmp=NULL;

	tmp = SDL_CreateRGBSurface(SDL_SWSURFACE, 900,250, 32, 0, 0, 0, 0); 
	SDL_FillRect(tmp,NULL,SDL_MapRGB(tmp->format,0,0,0));
	if(alfaMenu2>12)
	{
		alfaMenu2-=12;		
	}
	else
		alfaMenu2=0;
	SDL_SetAlpha(tmp,SDL_SRCALPHA,alfaMenu2);	
	blit_obraz(tekstX[5],ekran,100,EKRAN_H-487,NULL);
	blit_obraz(tekstX[6],ekran,100,EKRAN_H-437,NULL);
	blit_obraz(tekstX[7],ekran,100,EKRAN_H-387,NULL);
	blit_obraz(tekstX[8],ekran,200,EKRAN_H-337,NULL);
	blit_obraz(tekstX[9],ekran,200,EKRAN_H-287,NULL);
	blit_obraz(tmp,ekran,100,EKRAN_H-487,NULL);
	//back
	blit_obraz(tekstX[3],ekran,50,EKRAN_H-295,NULL);
	SDL_FreeSurface(tmp);

	wyswietlanie_ramka1(1);
}
void SDL_game::wyswietlanieGraGui(int mode)
{	
	tab->drawTable(ekran);
	for(int i=0;i<(gra->getIleGraczy()*2+5);i++)
		cards[i]->cardDraw(cardsSPR,ekran,cardBack);
	for(int i=0;i<gra->getIleGraczy()+1;i++)
		coins[i]->coinsDraw(coinsSPR,ekran);
	if(mode==1)
	{
		track->drawTrackbar(ekran);
		tab->drawButtons(1,0,0,ekran);
		if(!gra->getPlayerFold(playerTurn-1))
			tab->drawPointer(playerTurn-1,ekran);
	}
	else
		if(!gra->getPlayerFold(playerTurn))
			tab->drawPointer(playerTurn,ekran);	
	tab->drawTableInfo(gra->getIleGraczy(),gra->getPlayersBets(),ekran);
	tab->drawRPanel(ekran);
	tab->drawInfo(gra->getIleGraczy(),gra->getPlayersCoins(),gra->getPot(),gra->getPlayersBets(),gra->getPlayersNames(),ekran,gamePhase);
	tab->drawGameMenu(ekran);
	tab->drawOptionsMenu(ekran);

}

void SDL_game::tworzenieCards()
{
	cards=new SDL_card*[gra->getIleGraczy()*2+5];
	for(int i=0;i<(gra->getIleGraczy()*2+5);i++)
	{
		cards[i]=new SDL_card();
	}
}

void SDL_game::setCards()
{
	int nplayers=gra->getIleGraczy();
	for(int i=0;i<(nplayers*2+5);i++)
	{
		if(i<nplayers*2)
		{
			if(!gra->getPlayerInGame(i/2))
				cards[i]->setCard((gra->getCards())[i],400,270,false,false);
			else
				cards[i]->setCard((gra->getCards())[i],400,270,true,false);


		}
		else
			cards[i]->setCard((gra->getCards())[i],225+50*(i%5),245,false,true);
	}
}
void SDL_game::tworzenieCoins()
{
	coins=new SDL_coin*[gra->getIleGraczy()+1];
	for(int i=0;i<gra->getIleGraczy()+1;i++)
		coins[i]=new SDL_coin();
	int *plCoinsTmp=gra->getPlayersCoins();
	for(int i=0;i<gra->getIleGraczy()+1;i++)
	{	
		if(i<3)
		{
			coins[i]->setCoins(plCoinsTmp[i],GRACZ0X+220*i,GRACZ0Y-35);
		}
		else
			if(i<4)
			{
				coins[i]->setCoins(plCoinsTmp[i],GRACZ3X+100,GRACZ3Y+15);
			}
			else
				if(i<7)
				{
					coins[i]->setCoins(plCoinsTmp[i],GRACZ4X-220*(i-4),GRACZ4Y+60);
				}
				else
					if(i<8)
					{
						coins[i]->setCoins(plCoinsTmp[i],GRACZ7X-45,GRACZ7Y+15);
					}
					else
						coins[i]->setCoins(gra->getPot(),345,195);
	}
	delete plCoinsTmp;
}

void SDL_game::wyswietlanie_ramka1(int k)
{
	for(int i=0;i<k;i++)
	{
		if((mx>44) && (mx<154) &&(my>EKRAN_H-303+50*i)&&(my<EKRAN_H-259+50*i))
			przycisk_flag=i;
	}		
	if(alfaflag)
	{
		alfaRamka+=20;
		if(alfaRamka>=255)
		{
			alfaRamka=255;
			alfaflag=false;
		}
	}
	else
	{
		alfaRamka-=10;
		if(alfaRamka<=0)
		{
			alfaRamka=0;
			alfaflag=true;
		}
	}
	SDL_SetAlpha(ramka1,SDL_SRCALPHA,alfaRamka);
	//ramka
	blit_obraz(ramka1,ekran,44,EKRAN_H-303+50*przycisk_flag,NULL);

}

void SDL_game::wyswietlanie_sand()
{
	
	if (alfasandf)
	{
		alfaSand += 0.1;
		if (alfaSand >= 20)
		{
			alfaSand = 20;
			alfasandf = false;
		}
	}
	else
	{
		alfaSand -= 0.1;
		if (alfaSand <= 0)
		{
			alfaSand = 0;
			alfasandf = true;
		}
	}

	
		posSand += 1;
		if (posSand >= 900)
		{
			posSand = 0;
		}
	




	SDL_SetAlpha(sand, SDL_SRCALPHA, alfaSand);
	//ramka
	blit_obraz(sand, ekran, 0, 0, NULL);

}

void SDL_game::wyswietlanieButtonBlue(){
	int butt_flag = -1;
	for (int i = 0; i<3; i++)
	{
		if ((mx>100+190*i) && (mx<280+190*i) && (my>0) && (my < 70))
			butt_flag = i;
	}

	if (ButtonOverMove >= 4){
		ButtonOverMove = 4;
	}

	if (ButtonOverMove <= 0){
		ButtonOverMove = 0;
	}

	if (butt_flag != -1){
		ButtonOverMove++;
		switch (butt_flag)
		{
		case 0:
			blit_obraz(buttonOver, ekran, 100 + 190 * butt_flag, -2 + ButtonOverMove, NULL);

			break;
		case 1:
			blit_obraz(buttonOver, ekran, 100 + 190 * butt_flag, -2 + ButtonOverMove, NULL);

			break;
		case 2:
			blit_obraz(buttonOver, ekran, 100 + 190 * butt_flag, -2 + ButtonOverMove, NULL);

			break;
		default:
			break;
		}
		butt_flag = -1;
	}
	else{
		ButtonOverMove=0;
	}
	
}
void SDL_game::myszka_menu1(int mode)
{
	for(int i=0;i<4;i++)
	{
		if((mx>44) && (mx<154) &&(my>EKRAN_H-303+50*i)&&(my<EKRAN_H-259+50*i))
		{
			switch(mode)
			{
			case 0:
				switch(i)
				{
				case 0:
					menu_mode=1;
					break;
				case 1:
					menu_mode=2;
					przycisk_flag=0;
					break;
				case 2:
					zamkniecie=false;
					break;
				}
				break;
			case 2:
				switch(i)
				{
				case 0:
					menu_mode=0;
					alfaMenu2=255;
					break;
				}
				break;

			}
		}
	}
	if(menu_mode==3)
		menu_mode=0;
}

void SDL_game::flip()
{
	SDL_Flip( ekran );
}

void SDL_game::ustawienie_fps(SDL_timer fps)
{
	if( fps.getTicks() < 1000 / PROGRAM_FPS )
	{
		SDL_Delay( ( 1000 / PROGRAM_FPS ) - fps.getTicks() );
	}


}

void SDL_game::preFlop()
{
	//if(playerTurn<8)
	{
		gra->Preflop(phase,playerTurn,roundMode,gamePhase);
	}
	if(playerTurn>-1)
	{
		coins[playerTurn]->setCoinsAmount(gra->getPlayerCoins(playerTurn));
	}
	coins[8]->setCoinsAmount(gra->getPot());

	if(playerTurn>-1 && playerTurn<8 && gra->getPlayerFold(playerTurn))
	{
		cards[playerTurn*2]->setVisible(false);
		cards[playerTurn*2+1]->setVisible(false);
	}
	if(playerTurn<gra->getIleGraczy()-1)
		playerTurn++;
	else
	{
		playerTurn=0;
		//roundMode=false;
	}
}

void SDL_game::flop()
{
	cards[gra->getIleGraczy()*2]->setVisible(true);
	cards[gra->getIleGraczy()*2+1]->setVisible(true);
	cards[gra->getIleGraczy()*2+2]->setVisible(true);

	if(gra->getLeftInGame()>1)
	{
		//if(playerTurn<8)
		{
			gra->Flop(phase,playerTurn,roundMode,gamePhase);
		}
		if(playerTurn>-1)
		{
			coins[playerTurn]->setCoinsAmount(gra->getPlayerCoins(playerTurn));
		}
		coins[8]->setCoinsAmount(gra->getPot());

		if(playerTurn>-1 && playerTurn<8 && gra->getPlayerFold(playerTurn))
		{
			cards[playerTurn*2]->setVisible(false);
			cards[playerTurn*2+1]->setVisible(false);
		}
		if(playerTurn<gra->getIleGraczy())
			playerTurn++;
		else
		{
			playerTurn=0;
			//roundMode=false;
		}
	}

	else
		gamePhase++;
}
void SDL_game::turn()
{
	cards[gra->getIleGraczy()*2+3]->setVisible(true);
	if(gra->getLeftInGame()>1)
	{
		//if(playerTurn<8)
		{
			gra->Turn(phase,playerTurn,roundMode,gamePhase);
		}
		if(playerTurn>-1)
		{
			coins[playerTurn]->setCoinsAmount(gra->getPlayerCoins(playerTurn));
		}
		coins[8]->setCoinsAmount(gra->getPot());

		if(playerTurn>-1 && playerTurn<8 && gra->getPlayerFold(playerTurn))
		{
			cards[playerTurn*2]->setVisible(false);
			cards[playerTurn*2+1]->setVisible(false);
		}
		if(playerTurn<gra->getIleGraczy())
			playerTurn++;
		else
		{
			playerTurn=0;
			//roundMode=false;
		}
	}
	else
		gamePhase++;
}
void SDL_game::river()
{
	cards[gra->getIleGraczy()*2+4]->setVisible(true);
	if(gra->getLeftInGame()>1)
	{
		//if(playerTurn<8)
		{
			gra->River(phase,playerTurn,roundMode,gamePhase);
		}
		if(playerTurn>-1)
		{
			coins[playerTurn]->setCoinsAmount(gra->getPlayerCoins(playerTurn));
		}
		coins[8]->setCoinsAmount(gra->getPot());

		if(playerTurn>-1 && playerTurn<8 && gra->getPlayerFold(playerTurn))
		{
			cards[playerTurn*2]->setVisible(false);
			cards[playerTurn*2+1]->setVisible(false);
		}
		if(playerTurn<gra->getIleGraczy())
			playerTurn++;
		else
		{
			playerTurn=0;
			//roundMode=false;
		}
	}
	else
		gamePhase++;
}
void SDL_game::showdown()
{
	for(int i=2;i<gra->getIleGraczy()*2;i++)
		cards[i]->setFront(true);
	winner=gra->showResults(gamePhase);
	coins[winner]->setCoinsAmount(gra->getPlayerCoins(winner));
	coins[gra->getIleGraczy()]->setCoinsAmount(0);
	tab->setRPanelOpened(true);
	phase=4;
}

void SDL_game::gamePlay()
{
	switch(phase)
	{
	case 0: //start gry
		{
			//zwalnia pamiec po obiektach z menu gry
			usuwanie_menu();
			//wczytuje elementy gry
			wczytywanie_gra();
			//ustawienie glosnosci odglosow w tle i rozpoczecie odtwarzania
			Mix_VolumeMusic(audioVolume);
			Mix_PlayMusic(gameSound,-1);
			//stworzenie obiektu nowej gry
			gra=new Game(tmpIleGraczy);
			//ustawia parametry nowej gry
			gra->startGame();
			//tworzy obiekty zetonow
			tworzenieCoins();
			tworzenieCards();
			//konczy faze 0(start gry) i rozpoczyna faze 1(start partii)
			phase=1;
			break;
		}

	case 1: //start partii
		{
			//ustawia parametry nowej partii(rundy)
			gra->startRound();
			//tworzy obiekty kart
			setCards();
			//ustawia ktory gracz bedzie zaczynal runde
			playerTurn=0;
			//ustawia opozniacz na 0
			delayer=0;
			//konczy faze 1(start partii) i zmienia na faze 5(rozdanie kart)
			phase=5;
			break;
		}
	case 5: //rozdanie kart
		{
			//wyswietla gui+elementy gry
			wyswietlanieGraGui(0);
			//rozdaje karty, gdy skonczy zmienia faze gry na 2(akcje graczy komputerowych
			dealCards();
			break;
		}

	case 2: //akcje graczy komputerowych
		{
			//wyswietla gui+elementy gry
			wyswietlanieGraGui(0);
			//ustawia trackbar na odpowienie wartosci, min= obecna stawka, max=wszystkie zetony gracza
			track->setMinMax(gra->getMaxBet(),gra->getAllPlayerCoins(0));
			//ustawia trackbar na minimalna wartosc
			track->setPosition(gra->getMaxBet());
			//sprawdza czy aktualny gracz pozostaje w grze
			if(playerTurn>7 || !gra->getPlayerFold(playerTurn))
			{
				//sprawdza czy opozniacz pozwala juz na wykonanie akcji przez gracza komputerowego, opoznienie wynosi 12 fps
				if(delayer>12)
				{
					//zaleznie od fazy gry(flop,preflop,turn,river,showdown) wykonuje odpowiednie akcje 
					switch(gamePhase)
					{
					case 0:
						preFlop();
						break;
					case 1:

						flop();
						break;
					case 2:
						turn();
						break;
					case 3:
						river();
						break;
					case 4:
						showdown();
						break;
					}
					delayer=0;
				}
				delayer++;
			}
			else
			{
				playerTurn++;
			}
			break;
		}
	case 3: //ruch gracza
		{
			wyswietlanieGraGui(1);
			break;
		}
	case 4: //wyswietlanie wynikow
		{
			wyswietlanieGraGui(0);
			tab->drawWinner(gra->getPlayersName(winner),ekran);
			break;
		}

	case 8: // usuwanie rundy
		{
			gra->setLoosers();
			phase=1;
		}
	}

}

void SDL_game::myszka_gra()
{
	//---------------------AKCJE GRACZA
	if(phase==3)
	{
		switch(tab->eventPokerButtons(mx,my))
		{
		case 0:
			gra->userAction(1,track->getPosition());
			phase=2;
			coins[0]->setCoinsAmount(gra->getPlayerCoins(0));
			break;
		case 1:
			gra->userAction(2,0);
			phase=2;
			coins[0]->setCoinsAmount(gra->getPlayerCoins(0));
			break;
		case 2:
			gra->userAction(3,0);
			phase=2;
			cards[0]->setVisible(false);
			cards[1]->setVisible(false);

			break;
		}							


	}
	//-----------EKRAN WYNIKOW--PRZYCISK NEXT ROUND
	tab->eventDrawWinner(mx,my,phase,gamePhase);

	//-----------------------------------------------------------------
	//-----------------------------------------------------------------

	//-------LEFT-UP-MENU-GRA
	if(tab->getMenuOpened())
	{
		//-----PRZYCISK EXIT
		if(tab->eventExit(mx,my))
		{
			Mix_HaltMusic();
			Mix_FreeMusic(gameSound);		
			usunTable();
			wczytywanie_menu();
			menu_mode=0;
			phase=0;

		}
		//-----PRZYCISK OPTIONS
		tab->eventOptions(mx,my);
	}
	//---PRZYCISK MENU
	tab->eventMenu(mx,my);

	//-----------------------------------------------------------------

	//-------ZAMKNIECIE OPCJI(PRZYCISK BACK), WYBOR KARTY
	if(tab->getoptionsOpened())
	{
		tab->eventOptionsBack(mx,my);
		tab->eventOptionsCard(mx,my,cardBack);
		if(tab->eventOptionsVolume(mx,my,audioVolume))
			Mix_VolumeMusic(audioVolume);

	}
	//---------------------------PRAWY_PANEL_GRA
	tab->eventRightPanel(mx,my);
}

void SDL_game::dealCards()
{
	if(delayer<gra->getIleGraczy()*2)
	{
		if(delayer<2)
		{
			if(cards[delayer]->cardMove(GRACZ0X+50*(delayer%2),GRACZ0Y+10)==true || !gra->getPlayerInGame(delayer/2))
			{
				cards[delayer]->setFront(true);
				delayer++;

			}
		}
		else
			if(delayer>=2 && delayer<6)
			{
				if(cards[delayer]->cardMove(GRACZ0X+220*(delayer/2)+50*(delayer%2),GRACZ0Y+10)==true  || !gra->getPlayerInGame(delayer/2))
				{
					delayer++;
				}
			}
			else
				if(delayer>=6 && delayer<8)
				{
					if(cards[delayer]->cardMove(GRACZ3X+50*(delayer%2),GRACZ3Y)==true || !gra->getPlayerInGame(delayer/2))
					{
						delayer++;
					}
				}
				else
					if(delayer>=8 && delayer<14)
					{
						if(cards[delayer]->cardMove(GRACZ4X-220*((delayer-8)/2)+50*(delayer%2),GRACZ4Y-15)==true || !gra->getPlayerInGame(delayer/2))
						{
							delayer++;
						}

					}
					else
						if(delayer>=14 && delayer<16)
						{
							if(cards[delayer]->cardMove(GRACZ7X+50*(delayer%2),GRACZ7Y)==true  ||  !gra->getPlayerInGame(delayer/2))
							{
								delayer++;
							}
						}
	}
	else
	{
		phase=2;
		delayer=0;
	}
}