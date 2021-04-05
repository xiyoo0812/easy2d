#include "e2d_engine.h"
#include "base/e2d_timer_mgr.h"
#include "object/e2d_scene_mgr.h"
#include "graphics/e2d_font_mgr.h"
#include "graphics/e2d_texture_mgr.h"
#include "graphics/e2d_scale_system.h"
#include "graphics/e2d_graphics_mgr.h"
#include "graphics/e2d_sprite_batch.h"
#include "resource/e2d_asset_mgr.h"

/* Easy2D */
using namespace Easy2D;

E2dEngine::E2dEngine() : Singleton<E2dEngine>()
{

}

E2dEngine::~E2dEngine()
{
}

#ifdef WIN32
void E2dEngine::initialize(uint32 window_width, uint32 window_height)
{
    AssetManager::getInstance()->setPath(Path("res"));
    GraphicsManager::getInstance()->initialize(window_width, window_height);
#endif
#ifdef ANDROID
void E2dEngine::initialize(SPtr<android_app> app)
{
    GraphicsManager::getInstance()->initialize(app);
#endif
    //AudioManager::getInstance()->start();
    GraphicsManager::getInstance()->calculateViewPort();
    SpriteBatch::getInstance()->initialize();
    //DebugDraw::getInstance()->initialize();
}

void E2dEngine::update()
{
    uint32 escapeMs = TimerManager::getInstance()->update();
    SceneManager::getInstance()->update(escapeMs);
    GraphicsManager::getInstance()->update();
    //mFPS.update(escapeMs);
    //InputManager::getInstance()->Endupdate();
}

void E2dEngine::draw()
{
    GraphicsManager::getInstance()->startDraw();
    SceneManager::getInstance()->draw();
    GraphicsManager::getInstance()->stopDraw();
}

void E2dEngine::stop()
{
#ifdef ANDROID
    GraphicsManager::getInstance() :destroy()
#endif
    //DebugDraw::earseInstance();
    TimerManager::earseInstance();
    ScaleSystem::earseInstance();
    FontManager::earseInstance();
    SpriteBatch::earseInstance();
    SceneManager::earseInstance();
    TextureManager::earseInstance();
    GraphicsManager::earseInstance();
    //AudioManager::earseInstance();
    //PathFindManager::earseInstance();
    //SpriteAnimationManager::earseInstance();
}

void E2dEngine::setActive()
{
    //AudioManager::getInstance()->resumeAllSounds();
}

void E2dEngine::setInactive()
{
    //AudioManager::getInstance()->pauseAllSounds();
}

uint32 E2dEngine::getCurrentFPS() const
{
    return 0; //mFPS.CurrentFPS;
}

uint32 E2dEngine::getPreviousFPS() const
{
    return 0; //mFPS.PreviousFPS;
}

void E2dEngine::setTitle(const String& title)
{
    mTitle = title;
    mTitleHasUpdated = true;
}

void E2dEngine::setSubTitle(const String & title)
{
    mSubTitle = title;
    mTitleHasUpdated = true;
}

const String& E2dEngine::getTitle()
{
    return mTitle;
}

const String& E2dEngine::getSubTitle()
{
    return mSubTitle;
}

bool E2dEngine::hasTitleUpdated() const
{
    return mTitleHasUpdated;
}

void E2dEngine::resetTitleUpdateMark()
{
    mTitleHasUpdated = false;
}

void E2dEngine::quit()
{
#ifdef WIN32
    PostQuitMessage(0);
#endif
#ifdef ANDROID
    ANativeActivity_finish(mAndroidApp->activity);
#endif
}

#ifdef ANDROID
SPtr<android_app> E2dEngine::GetAndroidApp() const
{
    return mAndroidApp;
}
#endif
