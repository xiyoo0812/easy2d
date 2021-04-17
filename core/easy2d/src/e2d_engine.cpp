#include "e2d_engine.h"
#include "base/e2d_timer_mgr.h"
#include "object/e2d_scene_mgr.h"
#include "graphics/e2d_font_mgr.h"
#include "graphics/e2d_texture_mgr.h"
#include "graphics/e2d_scale_system.h"
#include "graphics/e2d_graphics_mgr.h"
#include "graphics/e2d_render_batch.h"
#include "resource/e2d_asset_mgr.h"

#include "gui/e2d_text_field.h"
#include "gui/e2d_image.h"

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
    mStopWatch = std::make_shared<Stopwatch>();
    //初始化asset资源路径
    AssetManager::getInstance()->initialize("res");
    //初始化font资源路径，基于asset的路径
    FontManager::getInstance()->initialize("font");
    GraphicsManager::getInstance()->initialize(window_width, window_height);
#endif
#ifdef ANDROID
void E2dEngine::initialize(SPtr<android_app> app)
{
    GraphicsManager::getInstance()->initialize(app);
#endif
    //AudioManager::getInstance()->start();
    ScaleSystem::getInstance()->setWorkingResolution(window_width, window_height);
    GraphicsManager::getInstance()->calculateViewPort();
    RenderBatch::getInstance()->initialize();
    //DebugDraw::getInstance()->initialize();

    auto scene = std::make_shared<Scene>("test");
    SceneManager::getInstance()->addScene(scene);

    auto tex = TextureManager::getInstance()->loadTexture("image/bg.png", "bg");
    auto image = std::make_shared<UIImage>("image");
    scene->addEntity(image);
    image->setTexture(tex);
    image->setHorizontalAlignment(HorizontalAlignment::Center);
    image->setVerticalAlignment(VerticalAlignment::Center);
    image->translate(400, 300);
    image->translateL(1);

    auto font = FontManager::getInstance()->loadFont("felt-12", "fzltxh_gbk.ttf", 48);

    //auto txt = std::make_shared<UITextField>("text");
    //scene->addEntity(txt);
    //txt->setFont(font);
    //txt->setColor(Color::White);
    //txt->setText(L"我是国人daAFKsbB123");
    ////txt->setShadowColor(Color::Black, 2);
    //txt->setBold(true);
    //txt->setRootWidget();
    //txt->translateL(2);
    //txt->setHorizontalAlignment(HorizontalAlignment::Center);
    //txt->setVerticalAlignment(VerticalAlignment::Center);

    auto txt2 = std::make_shared<UITextField>("text2");
    scene->addEntity(txt2);
    txt2->setFont(font);
    txt2->setColor(Color::Black);
    txt2->setItalic(true);
    txt2->setShadowColor(Color::White, 1);
    txt2->setOutlineColor(Color::Red, 1);
    txt2->setRootWidget();
    txt2->setText(L"我是国人daAFKsbB123");
    txt2->setHorizontalAlignment(HorizontalAlignment::Center);
    txt2->setVerticalAlignment(VerticalAlignment::Center);
    txt2->translate(0, 60, 2);
}

void E2dEngine::update()
{
    uint32 escapeMs = mStopWatch->elapsedMillSecondsNow();
    TimerManager::getInstance()->update(escapeMs);
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
    RenderBatch::earseInstance();
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
