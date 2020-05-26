#include <SDL.h>
#include <windows.h>

int WIDTH  = 200;
int HEIGHT = 200 ;
int MAX_ITERATIONS = 100;

long double min = -2.84;;
long double max = 1.0;
long double factor = 1;

long double map(long double value, long double in_min, long double in_max, long double out_min, long double out_max) {
	return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main(int argc, char* []) {
	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;

	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0 ,&window, &renderer);
	SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);
	
	int count = 0;

	while (1) {

		max -= 0.1 * factor;
		min += 0.15 * factor;
		factor *= 0.9349;
		MAX_ITERATIONS += 1;

		SDL_RenderPresent(renderer);

		for (int x = 0; x < WIDTH; x++) { //x = a

			//exit the program
			if (SDL_PollEvent(&event) && event.type == SDL_QUIT) return 0;
			if (GetKeyState('Q') & 0x8000) return 0;

			//Populate Screen
			for (int y = 0; y < HEIGHT; y++) { // y = b
				long double a = map(x, 0, WIDTH,  min, max);  
				long double b = map(y, 0, HEIGHT, min, max);  

				long double a_init = a;
				long double b_init = b;

				int n = 0;
				for (int i = 0; i < MAX_ITERATIONS; i++){
					
					long double a1 = a * a - b * b;
					long double b1 = 2 * a * b;
					
					a = a1 + a_init;
					b = b1 + b_init;

					if ((a + b) > 2) break;

					n++;
				}
			    int bright = map(n, 0, MAX_ITERATIONS, 0, 255);
				
				//In mandel               // Clipping brightness
				if ((n == MAX_ITERATIONS) || ( n < 20) ) bright = 0;
				
				int red   = map(bright * bright, 0, 6502, 0, 255);
				int green = bright;
				int blue  = map(sqrt(bright), 0, sqrt(255), 0, 255);
				
				SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
				SDL_RenderDrawPoint(renderer, x, y);
			}//for y
		}//for x
		count++;
	}
	return 0;
}