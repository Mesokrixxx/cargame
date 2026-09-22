#pragma once

#include "math/vec2.h"
#include <SDL3/SDL_events.h>

class Window {
public:
	Window() = default;
	Window(const Window& other) = delete;
	Window(Window&& other);
	Window& operator=(const Window& other) = delete;
	Window& operator=(Window&& other);
	~Window();

	bool init(const char *title);
	void process(const SDL_Event& ev);
	void present();

	const Vec2<int>& size() const { return _size; }

private:
	void *_handle = nullptr;
	void *_glctx = nullptr;
	Vec2<int> _size = {};

	void _destroyInternal();
};
