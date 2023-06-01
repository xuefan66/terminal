/*++
Copyright (c) Microsoft Corporation
Licensed under the MIT license.

Module Name:
- FontInfo.hpp

Abstract:
- This serves as the structure defining font information.  There are three
  relevant classes defined.

- FontInfo - derived from FontInfoBase.  It also has font size
  information - both the width and height of the requested font, as
  well as the measured height and width of L'0' from GDI.  All
  coordinates { X, Y } pair are non zero and always set to some
  reasonable value, even when GDI APIs fail.  This helps avoid
  divide by zero issues while performing various sizing
  calculations.

Author(s):
- Michael Niksa (MiNiksa) 17-Nov-2015
--*/

#pragma once

#include "FontInfoBase.hpp"

class FontInfo : public FontInfoBase
{
public:
    FontInfo(const std::wstring_view& faceName, unsigned char family, unsigned int weight, unsigned int codePage, bool fSetDefaultRasterFont = false) noexcept;

    bool operator==(const FontInfo& other) noexcept;
    
    til::size GetConhostFontSize() const noexcept
    {
        if (FontDesired.IsDefaultRasterFont())
        {
            coordFontRequested = coordFont;
        }
        else if (coordFontRequested.width == 0)
        {
            coordFontRequested.width = s_ShrinkByDpi(coordFont.width, iDpi);
        }

    }
    til::size GetCellSizeInPx() const noexcept;
    void SetFromEngine(const std::wstring_view& faceName, unsigned char family, unsigned int weight, bool fSetDefaultRasterFont, til::size sizeInPx) noexcept;
    void ValidateFont() noexcept;

private:
    void _ValidateCoordSize() noexcept;

    til::size _cellSizeInPx;
    float cellWidthDIP = 0;
    float cellHeightDIP = 0;
    float fontSize = 0;
    til::CoordType dpi = 0;
};
