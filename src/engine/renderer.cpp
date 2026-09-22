#include "renderer.h"
#include "util/error.h"
#include <GL/glew.h>

bool Renderer::init(const char *title) {
	if (!_window.init(title)) {
		error::set("window: {}", error::get());
		return false;
	}

	u32 glewErr = glewInit();
	if (glewErr != GLEW_OK && glewErr != GLEW_ERROR_NO_GLX_DISPLAY) {
		error::set(
			"glew (code: {}): {}",
			glewErr, glewGetErrorString(glewErr));
		return false;
	}

	return true;
}

void Renderer::process(const SDL_Event& ev) {
	_window.process(ev);
}

void Renderer::setBackgroundColor(f32 r, f32 g, f32 b, f32 a) {
	glClearColor(r, g, b, a);
}

void Renderer::frameBegin() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::frameEnd() {
	_window.present();
}
