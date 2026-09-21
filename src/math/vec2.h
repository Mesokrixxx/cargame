#pragma once

template <typename T>
class Vec2 {
public:
	Vec2() = default;
	Vec2(T xy): Vec2(xy, xy) {}
	Vec2(T x, T y): x(x), y(y) {}

	T x = 0, y = 0;
};
