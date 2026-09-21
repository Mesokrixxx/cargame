#include "engine/window.h"
#include "util/error.h"
#include "util/assert.h"
#include "util/log.h"
#include <SDL3/SDL.h>
#include <GL/glew.h>

int main() {
	Window window;
	
	ASSERT(SDL_Init(SDL_INIT_VIDEO), 
		"failed to init sdl: {}", SDL_GetError());
	
	ASSERT(window.create("Car Game"), 
		"failed to create window: {}", error::get());

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
		window.clear();
		window.flush();
	}

	SDL_Quit();
	return 0;
}
