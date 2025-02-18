#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>

int main(int argc, char *argv[]) {

  SDL_Init(SDL_INIT_EVENTS);

  SDL_WarpMouseGlobal(200, 200);

  SDL_Quit();

  return 0;
}
