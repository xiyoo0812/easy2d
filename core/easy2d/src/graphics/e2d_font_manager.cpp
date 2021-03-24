#include "e2d_font_manager.h"

using namespace Easy2D;

FontManager::FontManager(): mLibrary(0)
{
	auto error = FT_Init_FreeType(&mLibrary);
	if(error)
	{
		// log
	}
}

FontManager::~FontManager()
{

}

void FontManager::clear()
{
	for(const auto& font : mFontList)
	{
        delete font.second;
	}
	mFontList.clear();
	FT_Done_FreeType(mLibrary);
}

bool FontManager::loadFont(const String& path, const String& name, uint32 size)
{
	if(mFontList.find(name) != mFontList.end())
	{
		return true;
	}
	Font* tempFont = new Font();
	if(tempFont->load(path, size, mLibrary))
	{
		mFontList[name] = tempFont;
	}
	else
	{
		delete tempFont;
		return false;
	}
	return true;
}

bool FontManager::removeFont(const String& name)
{
	auto it = mFontList.find(name);
	if(it != mFontList.end())
	{
		mFontList.erase(it);
		return true;
	}
	return false;
}

const Font* FontManager::getFont(const String& name)
{
	return mFontList[name];
}
