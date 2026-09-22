#include "window.h"
#include "util/error.h"
#include <SDL3/SDL_video.h>
#include <GL/glew.h>

Window::Window(Window&& other): _handle(other._handle), _glctx(other._glctx), _size(other._size) {
	other._handle = nullptr;
	other._glctx = nullptr;
	other._size = {};
}

Window& Window::operator=(Window&& other) {
	if (this != &other) {
		_destroyInternal();
		_handle = other._handle;
		_glctx = other._glctx;
		_size = other._size;

		other._handle = nullptr;
		other._glctx = nullptr;
		other._size = {};
	}
	return *this;
}

Window::~Window() {
	_destroyInternal();
}

bool Window::init(const char *title) {
	_handle = 
		SDL_CreateWindow(
			title, 1080, 720,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (!_handle) {
		error::set("handle: {}", SDL_GetError());
		return false;
	}

	_glctx = 
		SDL_GL_CreateContext((SDL_Window *)_handle);
	if (!_glctx) {
		error::set("gl context: {}", SDL_GetError());
		SDL_DestroyWindow((SDL_Window *)_handle);
		_handle = nullptr;
		return false;
	}

	_size = { 1080, 720 };
	return true;
}

void Window::process(const SDL_Event& ev) {
	switch (ev.type) {
		case (SDL_EVENT_WINDOW_RESIZED):
			_size = { ev.window.data1, ev.window.data2 };
			break ;
	}
}

void Window::present() {
	SDL_GL_SwapWindow((SDL_Window *)_handle);
}

void Window::_destroyInternal() {
	if (_glctx) {
		SDL_GL_DestroyContext((SDL_GLContext)_glctx);
		_glctx = nullptr;
	}
	if (_handle) {
		SDL_DestroyWindow((SDL_Window *)_handle);
		_handle = nullptr;
	}
}
