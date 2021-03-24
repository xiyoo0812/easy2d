#ifndef COLOR_H
#define COLOR_H

#include "math/e2d_math.h"

namespace Easy2D
{
    struct Color final
    {
        float32 r, g, b, a;

        static const Color
            AliceBlue,
            AntiqueWhite,
            Aqua,
            Aquamarine,
            Azure,
            Beige,
            Bisque,
            Black,
            BlanchedAlmond,
            Blue,
            BlueViolet,
            Brown,
            BurlyWood,
            CadetBlue,
            Chartreuse,
            Chocolate,
            Colar,
            CornflowerBlue,
            Cornsilk,
            Crimson,
            Cyan,
            DarkBlue,
            DarkCyan,
            DarkGoldenrod,
            DarkGray,
            DarkGreen,
            DarkKhaki,
            DarkMagenta,
            DarkOliveGreen,
            DarkOrange,
            DarkOrchild,
            DarkRed,
            DarkSalmon,
            DarkSeaGreen,
            DarkSlateBlue,
            DarkSlateGray,
            DarkTurquoise,
            DarkViolet,
            DeepPink,
            DeepSkyBlue,
            DimGray,
            DodgetBlue,
            Firebrick,
            FloralWhite,
            ForestGreen,
            Fuchsia,
            Gainsboro,
            GhostWhite,
            Gold,
            Goldenrod,
            Gray,
            Green,
            GreenYellow,
            Honeydew,
            HotPink,
            IndianRed,
            Indigo,
            Ivory,
            Khaki,
            Lavender,
            LavenderBlush,
            LawnGreen,
            LemonChiffon,
            LightBlue,
            LightCoral,
            LightCyan,
            LightGoldenrodYellow,
            LightGray,
            LightGreen,
            LightPink,
            LightSalmon,
            LightSeaGreen,
            LightSkyBlue,
            LightSlateGray,
            LightSteelBlue,
            LightYellow,
            Lime,
            LimeGreen,
            Linen,
            Magenta,
            Maroon,
            MediumAquamarine,
            MediumBlue,
            MediumOrchid,
            MediumPurple,
            MediumSeaGreen,
            MediumSlateBlue,
            MediumSpringGreen,
            MediumTurquoise,
            MediumVioletRed,
            MidnightBlue,
            MintCream,
            MistyRose,
            Moccasin,
            NavajoWhite,
            Navy,
            OldLace,
            Olive,
            OliveDrab,
            Orange,
            OrangeRed,
            Orchid,
            PaleGoldenrod,
            PaleGreen,
            PaleTurquoise,
            PaleVioletRed,
            PapayaWhip,
            PeachPuff,
            Peru,
            Pink,
            Plum,
            PowderBlue,
            Purple,
            Red,
            RosyBrown,
            RoyalBlue,
            SaddleBrown,
            Salmon,
            SandyBrown,
            SeaGreen,
            SeaShell,
            Sienna,
            Silver,
            SkyBlue,
            SlateBlue,
            SlateGray,
            Snow,
            SpringGreen,
            SteelBlue,
            Tan,
            Teal,
            Thistle,
            Tomato,
            Transparant,
            Turqouise,
            Violet,
            Wheat,
            White,
            WhiteSmoke,
            Yellow,
            YellowGreen;

        Color();
        Color(float32 R, float32 G, float32 B, float32 A = 1.0f);
        Color(const Color& yRef);
        Color(Color&& yRef);
        Color(const Vec3& yRef);
        Color(const Vec4& yRef);

        Color& operator=(const Color& yRef);
        Color& operator=(Color&& yRef);
        Color& operator=(const Vec3& yRef);
        Color& operator=(const Vec4& yRef);

        Color& operator+=(const Color& yRef);
        Color& operator+=(const Vec3& yRef);
        Color& operator+=(const Vec4& yRef);

        Color& operator-=(const Color& yRef);
        Color& operator-=(const Vec3& yRef);
        Color& operator-=(const Vec4& yRef);

        Color operator+(const Color& yRef) const;
        Color operator+(const Vec3& yRef) const;
        Color operator+(const Vec4& yRef) const;

        Color operator-(const Color& yRef) const;
        Color operator-(const Vec3& yRef) const;
        Color operator-(const Vec4& yRef) const;

        bool operator==(const Color& yRef) const;
        bool operator==(const Vec3& yRef) const;
        bool operator==(const Vec4& yRef) const;

        bool operator!=(const Color& yRef) const;
        bool operator!=(const Vec3& yRef) const;
        bool operator!=(const Vec4& yRef) const;
    };
};

#endif