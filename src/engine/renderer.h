#pragma once

#include "engine/window.h"
#include "util/types.h"

class Renderer {
public:
	Renderer() = default;
	Renderer(const Renderer& other) = delete;
	Renderer& operator=(const Renderer& other) = delete;

	bool init(const char *title);
	void process(const SDL_Event& ev);
	void setBackgroundColor(f32 r, f32 g, f32 b, f32 a);
	void frameBegin();
	void frameEnd();

	const Window& window() const { return _window; }

private:
	Window _window;
};
