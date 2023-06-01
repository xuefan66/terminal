// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#include "precomp.h"

#include "../inc/FontInfo.hpp"

FontInfo::FontInfo(const std::wstring_view& faceName,
                   const unsigned char family,
                   const unsigned int weight,
                   const unsigned int codePage,
                   const bool fSetDefaultRasterFont /* = false */) noexcept :
    FontInfoBase(faceName, family, weight, fSetDefaultRasterFont, codePage)
{
    ValidateFont();
}

bool FontInfo::operator==(const FontInfo& other) noexcept
{
    return FontInfoBase::operator==(other) && _cellSizeInPx == other._cellSizeInPx;
}

til::size FontInfo::GetCellSizeInPx() const noexcept
{
    return _cellSizeInPx;
}

void FontInfo::SetFromEngine(const std::wstring_view& faceName, const unsigned char family, const unsigned int weight, const bool fSetDefaultRasterFont, const til::size cellSizeInPx) noexcept
{
    FontInfoBase::SetFromEngine(faceName, family, weight, fSetDefaultRasterFont);
    _cellSizeInPx = cellSizeInPx;
    _ValidateCoordSize();
}

void FontInfo::ValidateFont() noexcept
{
    _ValidateCoordSize();
}

void FontInfo::_ValidateCoordSize() noexcept
{
    // a (0,0) font is okay for the default raster font, as we will eventually set the dimensions based on the font GDI
    // passes back to us.
    if (!IsDefaultRasterFontNoSize())
    {
        // Initialize X to 1 so we don't divide by 0
        if (_cellSizeInPx.width == 0)
        {
            _cellSizeInPx.width = 1;
        }

        // If we have no font size, we want to use 8x12 by default
        if (_cellSizeInPx.height == 0)
        {
            _cellSizeInPx.width = 8;
            _cellSizeInPx.height = 12;
        }
    }
}
