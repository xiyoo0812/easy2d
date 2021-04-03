#ifndef SCALE_SYSTEM_H
#define SCALE_SYSTEM_H

#include "e2d_config.h"

namespace Easy2D
{
	class ScaleSystem final : public Singleton<ScaleSystem>
	{
	public:
		friend Singleton<ScaleSystem>;

		void setWorkingResolution(float32 xPixels, float32 yPixels);

		void setWorkingResolution(const Vec2& pixels);

		const Vec2& getWorkingResolution() const;

		const Vec2& getActualResolution() const;

		float32 getScale() const;

		void calculateScale();

	private:
		ScaleSystem();
		~ScaleSystem();

		float32 mScale = 0;
		Vec2 mWorkingRes = {};
	};
}

#endif
