#include "engine.h"
#include "util/error.h"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_timer.h>

bool Engine::_initialized = false;

bool Engine::init(const char *title) {
	if (_initialized)
		return true;

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		error::set("sdl: {}", SDL_GetError());
		return false;
	}

	if (!_renderer.init(title)) {
		error::set("renderer: {}", error::get());
		SDL_Quit();
		return false;
	}

	_initialized = true;
	return true;
}

void Engine::setFps(u64 fps) {
	_time.aimedFps = fps;
	_time.fpsDt = fps ? 1 / (Time)fps : 0;
}

void Engine::launch() {
	if (_initF)
		_initF(*this);

	Time last = time::now();
	Time tickAccumulator = 0;
	Time secondAccumulator = 0;

	_running = true;
	while (_running) {
		_time.now = time::now();
		_time.dt = _time.now - last;
		last = _time.now;

		secondAccumulator += _time.dt;
		if (secondAccumulator >= 1) {
			_time.fps = _time.frames;
			_time.tps = _time.ticks;
			_time.frames = 0;
			_time.ticks = 0;
			secondAccumulator = 0;
		}

		SDL_Event ev;
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_EVENT_QUIT) {
				_running = false;
				break ;
			}
			_renderer.process(ev);
		}
		_updateF(*this);

		tickAccumulator += _time.dt;
		while (tickAccumulator >= _time.tpsDt) {
			_tickF(*this);
			tickAccumulator -= _time.tpsDt;
			_time.ticks++;
		}
		_renderF(*this);

		Time toWaste = _time.fpsDt - (time::now() - _time.now);
		if (toWaste >= 0)
			SDL_Delay(toWaste * 1000);
		_time.frames++;
	}

	if (_quitF)
		_quitF(*this);
}

Engine::~Engine() {
	if (_initialized) {
		SDL_Quit();
		_initialized = true;
	}
}
