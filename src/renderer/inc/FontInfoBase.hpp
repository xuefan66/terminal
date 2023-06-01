/*++
Copyright (c) Microsoft Corporation
Licensed under the MIT license.

Module Name:
- FontInfoBase.hpp

Abstract:
- This serves as the structure defining font information.

- FontInfoBase - the base class that holds the font's GDI's LOGFONT
  lfFaceName, lfWeight and lfPitchAndFamily, as well as the code page
  to use for WideCharToMultiByte and font name.

Author(s):
- Michael Niksa (MiNiksa) 17-Nov-2015
--*/

#pragma once

#include "IFontDefaultList.hpp"

inline constexpr wchar_t DEFAULT_TT_FONT_FACENAME[]{ L"__DefaultTTFont__" };
inline constexpr wchar_t DEFAULT_RASTER_FONT_FACENAME[]{ L"Terminal" };

// Populates a fixed-length **null-terminated** buffer with the name of this font, truncating it as necessary.
// Positions within the buffer that are not filled by the font name are zeroed.
inline void FillLogFontNameBuffer(const std::wstring& faceName, wchar_t (&buffer)[LF_FACESIZE]) noexcept
{
    const auto toCopy = std::min(std::size(buffer) - 1, faceName.size());
    const auto last = std::copy_n(faceName.data(), toCopy, &buffer[0]);
    *last = L'\0';
}

class FontInfoBase
{
public:
    FontInfoBase(const std::wstring_view& faceName, unsigned char family, unsigned int weight, bool fSetDefaultRasterFont, unsigned int uiCodePage) noexcept;

    bool operator==(const FontInfoBase& other) noexcept;

    unsigned char GetFamily() const noexcept;
    unsigned int GetWeight() const noexcept;
    const std::wstring& GetFaceName() const noexcept;
    unsigned int GetCodePage() const noexcept;
    void FillLegacyNameBuffer(wchar_t (&buffer)[LF_FACESIZE]) const noexcept;
    bool IsTrueTypeFont() const noexcept;
    void SetFromEngine(const std::wstring_view& faceName, unsigned char family, unsigned int weight, bool fSetDefaultRasterFont) noexcept;
    bool WasDefaultRasterSetFromEngine() const noexcept;
    void ValidateFont() noexcept;

    static Microsoft::Console::Render::IFontDefaultList* s_pFontDefaultList;
    static void s_SetFontDefaultList(_In_ Microsoft::Console::Render::IFontDefaultList* pFontDefaultList) noexcept;

protected:
    bool IsDefaultRasterFontNoSize() const noexcept;

private:
    std::wstring _faceName;
    unsigned int _weight = 0;
    unsigned char _family = 0;
    unsigned int _codePage = 0;
    bool _fDefaultRasterSetFromEngine = false;
};
