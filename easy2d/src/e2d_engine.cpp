#include "e2d_engine.h"
#include "gui/e2d_factory.h"
#include "base/e2d_timer_mgr.h"
#include "object/e2d_scene_mgr.h"
#include "graphics/e2d_font_mgr.h"
#include "graphics/e2d_graphics_mgr.h"
#include "graphics/e2d_render_batch.h"
#include "resource/e2d_asset_mgr.h"

/* Easy2D */
using namespace Easy2D;

E2dEngine::E2dEngine() : Singleton<E2dEngine>()
{

}

E2dEngine::~E2dEngine()
{
}

void E2dEngine::initialize(uint32 window_width, uint32 window_height)
{
    mStopWatch = std::make_shared<Stopwatch>();
    GraphicsManager::instance()->initialize(window_width, window_height);
    //初始化asset资源路径
    AssetManager::instance()->initialize("res");
    //初始化font资源路径，基于asset的路径
    FontManager::instance()->initialize("font");
    FontManager::instance()->loadFont("fzltxh-36", "fzltxh_gbk.ttf", 36);

    //初始化RenderBatch
    RenderBatch::instance()->initialize();
    RenderBatch::instance()->initializeGLStates();
    //初始化UIRoot
    UIFactory::instance()->setFont("fzltxh-36");
    mUIRoot = UIFactory::instance()->createRoot();

    //AudioManager::getInstance()->start();
    //DebugDraw::getInstance()->initialize();

    auto scene = SceneManager::instance()->createScene("test");

    //auto image = UIFactory::instance()->createImage("image", "image/bg.png", Vec2(0, 0), mUIRoot);
    ////image->setScale9Tile(20, 12, 75, 30);
    //image->setDockerAlign(DockerAlign::Center);
    //image->setAnchor(0.5, 0.5);
    //image->setZorder(1);

    auto button = UIFactory::instance()->createButton("button", "image/btn.png", Vec2(0, 0), mUIRoot);
    //image->setScale9Tile(20, 12, 75, 30);
    button->setDockerAlign(DockerAlign::Center);
    button->setAnchor(0.5, 0.5);
    button->setZorder(2);

    //auto txt = UIFactory::instance()->createLabel("text", L"国人daAFKsbBgf123", Vec2(0, 5), Vec2(200, 60), mUIRoot);
    //txt->setShadowColor(Color::Black, 2);
    ////txt->setBold(true);
    //txt->setZorder(2);
    //txt->setSpacing(5);
    //txt->setColor(Color::Red);
    //txt->setAnchor(0, 0);
    //txt->setLineWidth(200);
    //txt->setHorizontalAlign(HorizontalAlign::Left);
    //txt->setDockerAlign(DockerAlign::LeftTop);

    //auto txt2 = UIFactory::instance()->createLabel("text2", L"国人daAFKsbBgf123", Vec2(300, 100), Vec2(200, 60), mUIRoot);
    //txt2->setItalic(true);
    ////txt2->setShadowColor(Color::White, 1);
    //txt2->setOutlineColor(Color::Red, 1);
    //txt2->setZorder(2);
    //txt2->setText(L"我是国人daAFKsbB123");
}

void E2dEngine::update()
{
    uint32 escapeMs = mStopWatch->elapsedMillSecondsNow();
    //mFPS.update(escapeMs);
    mUIRoot->update(escapeMs);
    TimerManager::instance()->update(escapeMs);
    SceneManager::instance()->update(escapeMs);
    GraphicsManager::instance()->update();
    RenderBatch::instance()->flush();
}

void E2dEngine::stop()
{

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
