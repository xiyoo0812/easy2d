#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include "e2d_font.h"

namespace Easy2D
{
	class FontManager final : public Singleton<FontManager> 
	{
    public:
        friend Singleton<FontManager>;

        void initialize(const String& path);
        const SPtr<Font> loadFont(const String& name, const String& fontName, uint32 size = 12);

		const SPtr<Font> getFont(const String& name);
		bool removeFont(const String& name);
		void clear();

	private:
        FT_Library mLibrary = nullptr;
        UnorderedMap<String, Path> mFontFiles;
		UnorderedMap<String, SPtr<Font>> mFontList;

		FontManager();
		~FontManager();
	};
}

#endif
