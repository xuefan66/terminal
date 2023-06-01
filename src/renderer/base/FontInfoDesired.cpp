// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#include "precomp.h"

#include "../inc/FontInfoDesired.hpp"

// This helper determines if this object represents the default raster font. This can either be because internally we're
// using the empty facename and zeros for size, weight, and family, or it can be because we were given explicit
// dimensions from the engine that were the result of loading the default raster font. See GdiEngine::_GetProposedFont().
bool FontInfoDesired::IsDefaultRasterFont() const noexcept
{
    static constexpr DesiredCellSize cellSizeEmpty{ CSSLengthPercentage::FromPx(0), CSSLengthPercentage::FromPx(0) };
    static constexpr DesiredCellSize cellSizeRaster8x12{ CSSLengthPercentage::FromPx(8), CSSLengthPercentage::FromPx(12) };
    return faceName.empty() && (cellSize == cellSizeEmpty || cellSize == cellSizeRaster8x12);
}
