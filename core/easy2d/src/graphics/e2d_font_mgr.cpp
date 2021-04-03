#include "e2d_font_mgr.h"

using namespace Easy2D;

FontManager::FontManager() : mLibrary(0)
{
    auto error = FT_Init_FreeType(&mLibrary);
    if (error)
    {
        // log
    }
}

FontManager::~FontManager()
{

}

void FontManager::clear()
{
    mFontList.clear();
    FT_Done_FreeType(mLibrary);
}

bool FontManager::loadFont(const String& path, const String& name, uint32 size)
{
    if (mFontList.find(name) != mFontList.end())
    {
        return true;
    }
    auto font = std::make_shared<Font>();
    if (font->load(path, size, mLibrary))
    {
        mFontList.insert(std::make_pair(name, font));
        return true;
    }
    return false;
}

bool FontManager::removeFont(const String& name)
{
    auto it = mFontList.find(name);
    if (it != mFontList.end())
    {
        mFontList.erase(it);
        return true;
    }
    return false;
}

const SPtr<Font> FontManager::getFont(const String& name)
{
    auto it = mFontList.find(name);
    if (it != mFontList.end())
    {
        return it->second;
    }
    return nullptr;
}
