#ifndef SCALE_SYSTEM_H
#define SCALE_SYSTEM_H

#include "e2d_config.h"

namespace Easy2D
{
	class ScaleSystem final : public Singleton<ScaleSystem>
	{
	public:
		friend Singleton<ScaleSystem>;

		void setWorkingResolution(int32 xPixels, int32 yPixels);

		void setWorkingResolution(const Vec2i& pixels);

		const Vec2i& getWorkingResolution() const;

		const Vec2i& getActualResolution() const;

		float32 getScale() const;

		void calculateScale();

	private:
		ScaleSystem();
		~ScaleSystem();

		float32 mScale = 0;
		Vec2i mWorkingRes = {};
	};
}

#endif
