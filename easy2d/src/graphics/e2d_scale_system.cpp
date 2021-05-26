#include "e2d_scale_system.h"
#include "e2d_graphics_mgr.h"

using namespace Easy2D;

ScaleSystem::ScaleSystem() : Singleton<ScaleSystem>()
{
}


ScaleSystem::~ScaleSystem()
{
}

void ScaleSystem::setWorkingResolution(float32 xPixels, float32 yPixels)
{
	Vec2 workingRes(xPixels, yPixels);
	setWorkingResolution(workingRes);
}

const Vec2& ScaleSystem::getWorkingResolution() const
{
	return mWorkingRes;
}

const Vec2& ScaleSystem::getActualResolution() const
{
	return GraphicsManager::getInstance()->getWindowResolution();
}

void ScaleSystem::setWorkingResolution(const Vec2& pixels)
{
	mWorkingRes = pixels;
	calculateScale();
}

float32 ScaleSystem::getScale() const
{
	return mScale;
}

void ScaleSystem::calculateScale()
{
	mScale = GraphicsManager::getInstance()->getViewportResolution().x / mWorkingRes.x;
}
