#pragma once

#include "stdafx.h"

namespace Color
{
	static COLORREF FromHex(int hex)
	{
		auto r = (hex & 0xFF0000) >> 16;
		auto g = (hex & 0x00FF00) >> 8;
		auto b = (hex & 0x0000FF) >> 0;
		return RGB(r, g, b);
	}

	static const COLORREF Firebrick = FromHex(0xB22222);
	static const COLORREF Goldenrod1 = FromHex(0xFFC125);
	static const COLORREF SpringGreen3 = FromHex(0x00CD66);
	static const COLORREF Black = FromHex(0x000000);
	static const COLORREF White = FromHex(0xFFFFFF);
	static const COLORREF SteelBlue2 = FromHex(0x5CACEE);
	static const COLORREF SlateBlue = FromHex(0x6A5ACD);
	static const COLORREF Sienna1 = FromHex(0xFF8247);
	static const COLORREF Turquoise3 = FromHex(0x00C5CD);
	static const COLORREF OrangeRed = FromHex(0xFF4500);
	static const COLORREF DeepSkyBlue = FromHex(0x00BFFF);
	static const COLORREF Aquamarine = FromHex(0x7FFFD4);
	static const COLORREF Orchid = FromHex(0xDA70D6);
	static const COLORREF Lime = FromHex(0x00FF00);
	static const COLORREF Crimson = FromHex(0xDC143C);
	static const COLORREF LiteSeaGreen = FromHex(0x20B2AA);

}
