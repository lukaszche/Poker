#pragma once
class SDL_timer
{
    private:
    int startTicks;

    int pausedTicks;

    bool paused;
    bool started;

    public:
    SDL_timer();

    void start();
    void stop();

    int getTicks();

};

