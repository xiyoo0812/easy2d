#include "e2d_scale_system.h"
#include "e2d_graphics_mgr.h"

using namespace Easy2D;

ScaleSystem::ScaleSystem()
{
}


ScaleSystem::~ScaleSystem()
{
}

void ScaleSystem::setWorkingResolution(int32 xPixels, int32 yPixels)
{
	Vec2i workingRes(xPixels, yPixels);
	setWorkingResolution(workingRes);
}

const Vec2i& ScaleSystem::getWorkingResolution() const
{
	return mWorkingRes;
}

const Vec2i& ScaleSystem::getActualResolution() const
{
	return GraphicsManager::getInstance()->getWindowResolution();
}

void ScaleSystem::setWorkingResolution(const Vec2i& pixels)
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
	mScale = graphicsManager::getInstance()->getViewportResolution().x / mWorkingRes.x;
}
