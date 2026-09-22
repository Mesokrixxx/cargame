#include "time.h"
#include <SDL3/SDL_timer.h>

Time time::now() {
	static u64 start, freq;
	u64 now, diff;

	if (!freq)
		freq = SDL_GetPerformanceFrequency();
	now = SDL_GetPerformanceCounter();
	if (!start)
		start = now;
	diff = now - start;
	return diff / (f64)freq;
}
