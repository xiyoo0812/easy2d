#include "e2d_engine.h"
#include "base/e2d_timer_mgr.h"
#include "object/e2d_scene_mgr.h"
#include "graphics/e2d_font_mgr.h"
#include "graphics/e2d_texture_mgr.h"
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
    GraphicsManager::getInstance()->initialize(window_width, window_height);
#endif
#ifdef ANDROID
void E2dEngine::initialize(SPtr<android_app> app)
{
    GraphicsManager::getInstance()->initialize(app);
#endif
    mStopWatch = std::make_shared<Stopwatch>();
    //��ʼ��asset��Դ·��
    AssetManager::getInstance()->initialize("res");
    //��ʼ��font��Դ·��������asset��·��
    FontManager::getInstance()->initialize("font");
    //��ʼ��RenderBatch
    RenderBatch::getInstance()->initialize();
    RenderBatch::getInstance()->initializeGLStates();
    //��ʼ��UIRoot
    mUIRoot = std::make_shared<UIRoot>();
    mUIRoot->initialize();

    //AudioManager::getInstance()->start();
    //DebugDraw::getInstance()->initialize();

    auto scene = std::make_shared<Scene>("test");
    SceneManager::getInstance()->addScene(scene);

    auto tex = TextureManager::getInstance()->loadTexture("image/btn.png", "btn");
    auto image = std::make_shared<UIImage>("image");
    mUIRoot->addChild(image);
    image->setTexture(tex);
    image->setPosition(0, 0);
    image->setSize(Vec2(95, 42));
    //image->setScale9Tile(20, 12, 75, 30);
    image->setAnchor(0, 0);
    image->setZorder(1);
    image->setDockerAlign(DockerAlign::LeftTop);

    auto font = FontManager::getInstance()->loadFont("felt-12", "fzltxh_gbk.ttf", 36);

    auto txt = std::make_shared<UITextField>("text");
    mUIRoot->addChild(txt);
    txt->setFont(font);
    txt->setText(L"����daAFKsbBgf123");
    txt->setShadowColor(Color::Black, 2);
    //txt->setBold(true);
    txt->setZorder(2);
    txt->setSpacing(5);
    txt->setColor(Color::Red);
    txt->setSize(Vec2(200, 60));
    txt->setPosition(0, 5);
    txt->setAnchor(0, 0);
    txt->setLineWidth(200);
    txt->setHorizontalAlign(HorizontalAlign::Left);
    txt->setDockerAlign(DockerAlign::LeftTop);

     auto txt2 = std::make_shared<UITextField>("text2");
     mUIRoot->addChild(txt2);
     txt2->setFont(font);
     txt2->setItalic(true);
     //txt2->setShadowColor(Color::White, 1);
     txt2->setOutlineColor(Color::Red, 1);
     txt2->setZorder(2);
     txt2->setText(L"���ǹ���daAFKsbB123");
     txt2->setPosition(300, 100);
}

void E2dEngine::update()
{
    uint32 escapeMs = mStopWatch->elapsedMillSecondsNow();
    //mFPS.update(escapeMs);
    mUIRoot->update(escapeMs);
    TimerManager::getInstance()->update(escapeMs);
    SceneManager::getInstance()->update(escapeMs);
    GraphicsManager::getInstance()->update();
    RenderBatch::getInstance()->flush();
}

void E2dEngine::stop()
{
#ifdef ANDROID
    GraphicsManager::getInstance() :destroy()
#endif
    //DebugDraw::earseInstance();
    TimerManager::earseInstance();
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
