#ifndef GAME_H
#define GAME_H

#include "base/e2d_types.h"

namespace Easy2D
{
	class E2DGame
	{
	public:
		E2DGame() {}
		virtual ~E2DGame() {}

		virtual void load(int32 width, int32 height) = 0;

		virtual void draw() = 0;
		virtual void update() = 0;
		virtual void stop() = 0;
	};
}

#endif
