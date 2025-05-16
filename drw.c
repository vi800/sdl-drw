#include <stdio.h>
#include <SDL2/SDL.h>

int main(int argc, char* argv[]) {
	int width = 600, height = 400;
	int x0=0, y0=0;
	int mx=0, my=0;
	int quit = 0;
	int draw = 0;
	SDL_Rect rec;
	
	//0: nothing, 1: pencil, 2: rect, 3: line
	int mode = 1;
	
	SDL_Event e;
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *w = SDL_CreateWindow("drw", 
									 SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
									 width, height, 0);
	SDL_Renderer *r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawColor(r, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(r);
	SDL_RenderPresent(r);
	SDL_SetRenderDrawColor(r, 0xff, 0, 0, 0xff);
	while(quit == 0) {
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_KEYDOWN) {
				if(e.key.keysym.sym == SDLK_p) {
					mode = 1;
					printf("pen mode\n");
				} else if(e.key.keysym.sym == SDLK_r) {
					mode = 2;
					printf("rect mode\n");
				} else if(e.key.keysym.sym == SDLK_l) {
					mode = 3;
					printf("line mode\n");
				}
			} else if(e.type == SDL_MOUSEBUTTONDOWN) {
				draw = 1;
				SDL_GetMouseState(&x0, &y0);
			} else if(e.type == SDL_MOUSEBUTTONUP) {
				draw = 0;
			} else if(e.type == SDL_QUIT) {
				quit = 1;
				break;
			}

			if(mode == 1 && draw == 1) {
				SDL_GetMouseState(&mx, &my);
				SDL_RenderDrawPoint(r, mx, my);
			} else if(mode == 2) {
				if(e.type == SDL_MOUSEBUTTONUP) {
					SDL_GetMouseState(&mx, &my);
					rec.x = x0, rec.y = y0, rec.w = mx-x0, rec.h = my-y0;
					SDL_RenderFillRect(r, &rec);
				}
			} else if(mode == 3) {
				if(e.type == SDL_MOUSEBUTTONUP) {
					SDL_GetMouseState(&mx, &my);
					SDL_RenderDrawLine(r, x0, y0, mx, my);
				}
			}
			SDL_RenderPresent(r);
		}
	}

	SDL_DestroyRenderer(r);
	SDL_DestroyWindow(w);
	SDL_Quit();
	return 0;
}
