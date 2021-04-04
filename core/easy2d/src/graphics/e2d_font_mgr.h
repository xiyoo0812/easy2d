#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include "e2d_font.h"

namespace Easy2D
{
	class FontManager final : public Singleton<FontManager> 
	{
    public:
        friend Singleton<FontManager>;
		bool loadFont(const String& path, const String& name, uint32 size);

		const SPtr<Font> getFont(const String& name);
		bool removeFont(const String& name);
		void clear();

	private:
		FT_Library mLibrary;
		UnorderedMap<String, SPtr<Font>> mFontList;

		FontManager();
		~FontManager();
	};
}

#endif
