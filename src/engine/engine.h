#pragma once

#include "engine/renderer.h"
#include "engine/time.h"

class Engine {
public:
	typedef void (*EngineFunc)(Engine&);

	Engine() = delete;
	Engine(EngineFunc initF, EngineFunc updateF, EngineFunc tickF, EngineFunc renderF, EngineFunc quitF)
		: _initF(initF), _updateF(updateF), _tickF(tickF), _renderF(renderF), _quitF(quitF) {}
	~Engine();
	
	bool init(const char *title);
	void setFps(u64 fps);
	void launch();

	Renderer& renderer() { return _renderer; }
	
	u64 fps() const { return _time.fps; } 
	u64 tps() const { return _time.tps; } 
	Time dt() const { return _time.dt; }
	u64 aimedFps() const { return _time.aimedFps; } 
	u64 aimedTps() const { return _time.aimedTps; } 

private:	
	static bool _initialized;
	
	EngineFunc _initF, _updateF, _tickF, _renderF, _quitF;
	Renderer _renderer;

	bool _running = false;
	struct {
		Time now, dt;
		u64 frames = 0, fps = 0, aimedFps = 60;
		u64 ticks = 0, tps = 0, aimedTps = 20;
		Time fpsDt = 1 / 60.0, tpsDt = 1 / 20.0;
	} _time;
};
