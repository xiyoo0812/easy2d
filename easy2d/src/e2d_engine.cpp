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
    mWatchUpdate = std::make_shared<Stopwatch>();
    GraphicsManager::instance()->initialize(window_width, window_height);
    //初始化asset资源路径
    AssetManager::instance()->initialize("res");
    //初始化font资源路径，基于asset的路径
    FontManager::instance()->initialize("font");
    FontManager::instance()->loadFont("fzltxh-36", "fzltxh_gbk.ttf", 36);
    FontManager::instance()->loadFont("fzltxh-12", "fzltxh_gbk.ttf", 12);

    //初始化RenderBatch
    RenderBatch::instance()->initialize();
    RenderBatch::instance()->initializeGLStates();
    //初始化UIRoot
    auto mUIRoot = UIFactory::instance()->initialize("fzltxh-36");
   
    //AudioManager::getInstance()->start();
    //DebugDraw::getInstance()->initialize();
    auto scene = SceneManager::instance()->createScene("test");

    auto image = UIFactory::instance()->createImage("image", "image/bg.png", Vec2(0, 0), mUIRoot);
    //image->setScale9Tile(20, 12, 75, 30);
    image->setDockerAlign(DockerAlign::Center);
    image->setAnchor(0.5, 0.5);
    image->setZorder(1);
    image->setScale(0.8);

    auto button = UIFactory::instance()->createButton("button", "image/btn.png", Vec2(0, 0), image);
    //image->setScale9Tile(20, 12, 75, 30);
    button->setDockerAlign(DockerAlign::Center);
    button->setHoverScale(1.05f);
    button->setPushedScale(0.95f);
    button->setAnchor(0.5, 0.5);
    button->setScale(2);
    button->setZorder(2);

    auto buttonb = UIFactory::instance()->createButton("buttonb", "skin/btn_b_n.png", "skin/btn_b_p.png", Vec2(0, 0), image);
    //image->setScale9Tile(20, 12, 75, 30);
    buttonb->setDockerAlign(DockerAlign::LeftTop);
    buttonb->setAnchor(0, 0);
    buttonb->setScale(1.2);
    buttonb->setZorder(2);
    buttonb->setRotate(-PI / 2);

    auto buttony = UIFactory::instance()->createButton("buttony", "skin/btn_y_n.png","skin/btn_y_p.png", Vec2(0, 0), image);
    //image->setScale9Tile(20, 12, 75, 30);
    buttony->setDockerAlign(DockerAlign::RightTop);
    buttony->setAnchor(1, 0);
    buttony->setZorder(2);
    buttony->setScale(0.8);

    auto progress = UIFactory::instance()->createProgress("progress", "skin/progress_bg.png","skin/progress_bar.png", Vec2(0, 0), image);
    //image->setScale9Tile(20, 12, 75, 30);
    progress->setDockerAlign(DockerAlign::Bottom);
    progress->setAnchor(0.5, 1);
    progress->setZorder(2);

    auto slider = UIFactory::instance()->createSlider("slider", "skin/progress_bg.png", "skin/slider.png", Vec2(0, 40), image);
    //image->setScale9Tile(20, 12, 75, 30);
    slider->setDockerAlign(DockerAlign::Bottom);
    slider->setAnchor(0.5, 1);
    slider->setZorder(2);
   // slider->setRotate(PI / 2);

    auto editbox = UIFactory::instance()->createEditbox("editbox", "skin/editbox.png", Vec2(0, 80), Vec2(200, 30), image);
    editbox->setDockerAlign(DockerAlign::Bottom);
    editbox->setFont("fzltxh-12");
    editbox->setAnchor(0.5, 1);
    editbox->setZorder(3);

    auto checkbox = UIFactory::instance()->createCheckBox("checkbox", "skin/chbox_b_off.png","skin/chbox_b_on.png", Vec2(0, 0), mUIRoot);
    //image->setScale9Tile(20, 12, 75, 30);
    checkbox->setDockerAlign(DockerAlign::LeftTop);
    checkbox->setAnchor(0, 0);
    checkbox->setZorder(2);

    auto radioGroup = UIFactory::instance()->createRadioGroup("radioGroup", "skin/frame.png", Vec2(0, 0), mUIRoot);
    //image->setScale9Tile(20, 12, 75, 30);
    radioGroup->setDockerAlign(DockerAlign::Top);
    radioGroup->setAnchor(0.5, 0.5);
    radioGroup->setZorder(2);

    auto radio1 = UIFactory::instance()->createRadio("radio1", "skin/radio_b_off.png", "skin/radio_b_on.png", Vec2(5, 0), radioGroup);
    //image->setScale9Tile(20, 12, 75, 30);
    radio1->setDockerAlign(DockerAlign::Left);
    radio1->setAnchor(0, 0);
    radio1->setZorder(2);

    auto radio2 = UIFactory::instance()->createRadio("radio2", "skin/radio_b_off.png", "skin/radio_b_on.png", Vec2(5, 0), radioGroup);
    //image->setScale9Tile(20, 12, 75, 30);
    radio2->setDockerAlign(DockerAlign::Right);
    radio2->setAnchor(1, 0);
    radio2->setZorder(2);

    auto switchb = UIFactory::instance()->createSwitch("switchb", "skin/switch_b_off.png", "skin/switch_b_on.png", Vec2(0, 0), mUIRoot);
    //image->setScale9Tile(20, 12, 75, 30);
    switchb->setDockerAlign(DockerAlign::RightTop);
    switchb->setAnchor(1, 0);
    switchb->setZorder(2);

    auto txt = UIFactory::instance()->createLabel("text", L"国人daAFKsbBgf123", Vec2(0, 5), Vec2(200, 60), mUIRoot);
    txt->setShadowColor(Color::Black, 2);
    //txt->setBold(true);
    txt->setZorder(2);
    txt->setSpacing(5);
    txt->setColor(Color::Red);
    txt->setAnchor(0, 0);
    txt->setLineWidth(200);
    txt->setHorizontalAlign(HorizontalAlign::Left);
    txt->setDockerAlign(DockerAlign::LeftTop);

    auto txt2 = UIFactory::instance()->createLabel("text2", L"国人daAFKsbBgf123", Vec2(300, 100), Vec2(100, 60), mUIRoot);
    txt2->setItalic(true);
    //txt2->setShadowColor(Color::White, 1);
    txt2->setOutlineColor(Color::Red, 1);
    txt2->setZorder(3);
}

void E2dEngine::update()
{
    uint32 escapeMs = mWatchUpdate->elapsedMillSecondsNow();
    bool escapeSec = mWatchUpdate->elapsedMillSeconds(Stopwatch::MILLSECOND);
    //mFPS.update(escapeMs);
    TimerManager::instance()->update(escapeMs);
    UIRoot::instance()->update(escapeMs, escapeSec);
    SceneManager::instance()->update(escapeMs, escapeSec);
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
