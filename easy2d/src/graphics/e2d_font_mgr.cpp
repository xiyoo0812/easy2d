#include "e2d_font_mgr.h"
#include "resource\e2d_asset_mgr.h"

using namespace Easy2D;

FontManager::FontManager() : Singleton<FontManager>()
{

}

FontManager::~FontManager()
{

}

void FontManager::clear()
{
    mFontList.clear();
    FT_Done_FreeType(mLibrary);
}

void FontManager::initialize(const String& path)
{
    auto error = FT_Init_FreeType(&mLibrary);
    if (error)
    {
        LOG_ERROR << _T("FontManager::setPath FT_Init_FreeType failed! code: ") << error;
    }
    Path fontPath = Path(path);
    for (Path filePath : AssetManager::instance()->enumerateDirectory(fontPath, false))
    {
        Path fullPath = fontPath / filePath;
        mFontFiles.insert(std::make_pair(filePath.string(), fullPath));
    }
}

const SPtr<Font> FontManager::loadFont(const String& name, const String& fontName, uint32 size /* = 12 */)
{
    auto it = mFontList.find(name);
    if (it != mFontList.end())
    {
        return it->second;
    }
    auto pit = mFontFiles.find(fontName);
    if (pit == mFontFiles.end())
    {
        LOG_ERROR << _T("FontManager::loadFont font file not exist! name: ") << fontName;
        return nullptr;
    }
    Path& path = pit->second;
    SPtr<Stream> fontData = nullptr;
    auto dit = mFontDatas.find(path.string());
    if (dit == mFontDatas.end())
    {
        fontData = AssetManager::instance()->loadAsset(path);
        if (fontData == nullptr || fontData->size() <= 0)
        {
            LOG_ERROR << _T("FontManager::loadFont loadAsset failed!");
            return false;
        }
        mFontDatas.insert(std::make_pair(path.string(), fontData));
    }
    auto font = std::make_shared<Font>(path, size);
    if (!font->load())
    {
        LOG_ERROR << _T("FontManager::loadFont font load failed! name: ") << fontName;
        return nullptr;
    }
    mFontList.insert(std::make_pair(name, font));
    return font;
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


FT_Library FontManager::getLibrary()
{
    return mLibrary;
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

const SPtr<Stream> FontManager::getStream(const Path& path)
{
    auto it = mFontDatas.find(path.string());
    if (it != mFontDatas.end())
    {
        return it->second;
    }
    return nullptr;
}
