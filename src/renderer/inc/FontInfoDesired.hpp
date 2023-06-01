/*++
Copyright (c) Microsoft Corporation
Licensed under the MIT license.

Module Name:
- FontInfo.hpp

Abstract:
- This serves as the structure defining font information.

- FontInfoDesired - derived from FontInfoBase.  It also contains
  a desired size { X, Y }, to be supplied to the GDI's LOGFONT
  structure.  Unlike FontInfo, both desired X and Y can be zero.

Author(s):
- Michael Niksa (MiNiksa) 17-Nov-2015
--*/

#pragma once

#include "FontInfoBase.hpp"
#include "FontInfo.hpp"
#include "CSSLengthPercentage.h"

struct DesiredCellSize
{
    CSSLengthPercentage width;
    CSSLengthPercentage height;

    constexpr bool operator==(const DesiredCellSize&) const = default;
};

struct FontInfoDesired
{
    std::wstring faceName;
    unsigned int weight = 0;
    unsigned char family = 0;
    unsigned int codePage = 0;
    bool setDefaultRasterFont = false;

    float fontSize = 0;
    DesiredCellSize cellSize;
    
    bool IsDefaultRasterFont() const noexcept;
};
