#include "engine/engine.h"
#include "util/error.h"
#include "util/log.h"

static void init(Engine& engine) {
	engine.renderer().setBackgroundColor(1, 1, 1, 1);
}

static void update(Engine&) {
}

static void tick(Engine&) {
}

static void render(Engine& engine) {
	Renderer& renderer = engine.renderer();

	renderer.frameBegin();
	renderer.frameEnd();
}

int main() {
	Engine engine(init, update, tick, render, nullptr);
	
	if (!engine.init("Car Game")) {
		ERROR("failed to init engine: {}", error::get());
		return 1;
	} 

	engine.launch();
	return 0;
}
