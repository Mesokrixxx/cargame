#pragma once

#include "math/vec2.h"

class Window {
public:
	Window() = default;
	Window(const Window& other) = delete;
	Window(Window&& other);
	Window& operator=(const Window& other) = delete;
	Window& operator=(Window&& other);
	~Window();

	bool create(const char *title);
	void clear();
	void flush();

private:
	void *_handle = nullptr;
	void *_glctx = nullptr;
	Vec2<int> _size = {};
};
