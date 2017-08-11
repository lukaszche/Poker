#include "SDL_Trackbar.h"


SDL_Trackbar::SDL_Trackbar(int skin,int x,int y,int h,int w,int pos,int min,int max)
{
	tx=x;
	ty=y;
	th=h;
	tw=w;
	bx=x+10+260/(max-min+1)*(pos-min);
	this->skin=skin;
	tbar=SDL_functions::wczytaj_obraz("Surf/trackbar2.bmp");
	czcionka=TTF_OpenFont("Czcionki/BlackAngel.ttf",40);
	position=pos;
	tmax=max;
	tmin=min;
}


SDL_Trackbar::~SDL_Trackbar(void)
{
	TTF_CloseFont(czcionka);
	SDL_FreeSurface(tbar);
}
void SDL_Trackbar::drawTrackbar(SDL_Surface * ekran)
{
	SDL_Rect tmpRec;
	tmpRec.x=0;
	tmpRec.y=0;
	tmpRec.h=50;
	tmpRec.w=280;
	SDL_functions::blit_obraz(tbar,ekran,tx,ty,&tmpRec);
	tmpRec.x=280;
	tmpRec.w=45;
	SDL_functions::blit_obraz(tbar,ekran,bx-20,ty,&tmpRec);
	std::string temp=SDL_functions::IntToStr(position);
	SDL_Color color1={210,196,115};
	SDL_Surface *text;
	text=TTF_RenderText_Blended(czcionka,temp.c_str(),color1);
	SDL_SetAlpha(text,SDL_SRCALPHA,225);
	SDL_functions::blit_obraz(text,ekran,tx+280,ty,0);
	SDL_FreeSurface(text);

}

void SDL_Trackbar::change(int mx,int my)

{
	if((mx>tx+10) && (mx<tx+tw-10) &&(my>ty+4)&&(my<ty+th-4))
	{
		float pomTMAX=tmax, pomTMIN=tmin;
		position=((mx-(tx+10))/(260.0/(pomTMAX-pomTMIN+1)))+pomTMIN;
		bx=tx+10+260/(pomTMAX-pomTMIN+1)*(position-tmin);
	}

}
void SDL_Trackbar::setPosition(int pos)
{
	if(pos>tmax || pos<tmin)
		pos=tmax;
	float pomTMAX=tmax, pomTMIN=tmin;
	position=pos;
	bx=tx+10+260/(pomTMAX-pomTMIN+1)*(position-tmin);
}
int SDL_Trackbar::getPosition()
{
	return position;
}

void SDL_Trackbar::setMinMax(int min,int max)
{
	tmin=min;
	tmax=max;
}