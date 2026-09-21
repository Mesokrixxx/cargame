#include <SDL3/SDL.h>
#include <GL/glew.h>
#include "util/assert.h"

int main() {
	ASSERT(SDL_Init(SDL_INIT_VIDEO), 
		"failed to init sdl: {}", SDL_GetError());
	
	SDL_Window *window = 
		SDL_CreateWindow(
			"Car Game",
			1080, 720,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	ASSERT(window, 
		"failed to create window: {}", SDL_GetError());

	SDL_GLContext glctx = 
		SDL_GL_CreateContext(window);
	ASSERT(glctx, 
		"failed to create opengl context: {}", SDL_GetError());

	u32 glewErr = glewInit();
	ASSERT(glewErr == GLEW_OK || glewErr == GLEW_ERROR_NO_GLX_DISPLAY, 
		"failed to init glew: {} | error code: {}",
		glewGetErrorString(glewErr), glewErr);

	bool running = true;
	while (running) {
		SDL_Event ev;
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_EVENT_QUIT)
				running = false;
		}
		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DestroyContext(glctx);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
