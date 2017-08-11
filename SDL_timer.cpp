#include "SDL_timer.h"
#include "SDL.h"

SDL_timer::SDL_timer()
{	
	paused = false;
    started = false;
    startTicks = 0;
    pausedTicks = 0;
    
}
void SDL_timer::start()
{
    started = true;
    paused = false;
    startTicks = SDL_GetTicks();
}
void SDL_timer::stop()
{
    started = false;
    paused = false;
}
int SDL_timer::getTicks()
{
    if( started == true )
    {
        if( paused == true )
        {
            return pausedTicks;
        }
        else
        {
            return SDL_GetTicks() - startTicks;
        }
    }
    return 0;
}