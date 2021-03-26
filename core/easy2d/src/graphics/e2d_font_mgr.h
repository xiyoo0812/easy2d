#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include "e2d_font.h"

namespace Easy2D
{
	class FontManager final : public Singleton<FontManager> 
	{
	public:
		bool loadFont(const String& path, const String& name, uint32 size);

		const Font* getFont(const String& name);
		bool removeFont(const String& name);
		void clear();

	private:
		FT_Library mLibrary;
		UnorderedMap<String, Font*> mFontList;

		FontManager();
		~FontManager();
	};
}

#endif
