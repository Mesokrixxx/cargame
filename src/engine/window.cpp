#include "window.h"
#include "util/error.h"
#include <SDL3/SDL_video.h>
#include <GL/glew.h>

Window::Window(Window&& other): _handle(other._handle), _glctx(other._glctx) {
	other._handle = nullptr;
	other._glctx = nullptr;
}

Window& Window::operator=(Window&& other) {
	if (this != &other) {
		_handle = other._handle;
		_glctx = other._glctx;

		other._handle = nullptr;
		other._glctx = nullptr;
	}
	return *this;
}

Window::~Window() {
	if (_glctx)
		SDL_GL_DestroyContext((SDL_GLContext)_glctx);
	if (_handle)
		SDL_DestroyWindow((SDL_Window *)_handle);
}

bool Window::create(const char *title) {
	_handle = 
		SDL_CreateWindow(
			title, 1080, 720,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (!_handle) {
		error::set(SDL_GetError());
		return false;
	}

	_glctx = 
		SDL_GL_CreateContext((SDL_Window *)_handle);
	if (!_glctx) {
		error::set(SDL_GetError());
		SDL_DestroyWindow((SDL_Window *)_handle);
		_handle = nullptr;
		return false;
	}

	_size = { 1080, 720 };
	return true;
}

void Window::clear() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::flush() {
	SDL_GL_SwapWindow((SDL_Window *)_handle);
}
