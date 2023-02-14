#include "precomp.h"

#include "UTextAdapter.h"

#include "textBuffer.hpp"
#include "../renderer/inc/IRenderData.hpp"

#include <icu.h>

using Microsoft::Console::Render::IRenderData;

static int64_t U_CALLCONV utextLength(UText* ut)
{
    if (!ut->p)
    {
        const auto& renderData = *static_cast<const IRenderData*>(ut->context);
        const auto& textBuffer = renderData.GetTextBuffer();
        size_t total = 0;

        for (int32_t i = 0, c = ut->c; i < c; ++i)
        {
            total += textBuffer.GetRowByOffset(i).GetText().size();
        }

        ut->p = til::bit_cast<void*>(gsl::narrow_cast<intptr_t>(total));
    }

    return til::bit_cast<intptr_t>(ut->p);
}

/*
 * @param ut          the UText being accessed.
 * @param nativeIndex Requested index of the text to be accessed.
 * @param forward     If true, then the returned chunk must contain text
 *                    starting from the index, so that start<=index<limit.
 *                    If false, then the returned chunk must contain text
 *                    before the index, so that start<index<=limit.
 * @return            True if the requested index could be accessed.  The chunk
 *                    will contain the requested text.
 *                    False value if a chunk cannot be accessed
 *                    (the requested index is out of bounds).
 */
static UBool U_CALLCONV utextAccess(UText* ut, int64_t index, UBool forward)
{
    const auto& renderData = *static_cast<const IRenderData*>(ut->context);
    const auto& textBuffer = renderData.GetTextBuffer();
    
    return false;
}

static int32_t U_CALLCONV utextExtract(UText* ut, int64_t start, int64_t limit, char16_t* dest, int32_t destCapacity, UErrorCode* pErrorCode)
{
    if (U_FAILURE(*pErrorCode))
    {
        return 0;
    }
    if (destCapacity < 0 || (dest == nullptr && destCapacity > 0) || start > limit)
    {
        *pErrorCode = U_ILLEGAL_ARGUMENT_ERROR;
        return 0;
    }
    
    const auto& renderData = *static_cast<const IRenderData*>(ut->context);
    const auto& textBuffer = renderData.GetTextBuffer();
    
    return 0;
}

static void U_CALLCONV utextClose(UText* ut)
{
}

static constexpr UTextFuncs ucstrFuncs{
    .tableSize = sizeof(UTextFuncs),
    .nativeLength = utextLength,
    .access = utextAccess,
    .extract = utextExtract,
    .close = utextClose,
};

UText* utext_openUChars(UText* ut, const IRenderData& renderData, UErrorCode* status)
{
    if (U_FAILURE(*status))
    {
        return nullptr;
    }
    ut = utext_setup(ut, 0, status);
    if (U_SUCCESS(*status))
    {
        ut->pFuncs = &ucstrFuncs;
        ut->context = &renderData;
        ut->p = nullptr; // total text length
        ut->a = 0; // the row the current chunk is pointing to
        ut->b = renderData.GetTextBufferEndPosition().y; // total rows
        ut->providerProperties = UTEXT_PROVIDER_LENGTH_IS_EXPENSIVE | UTEXT_PROVIDER_STABLE_CHUNKS;
    }
    return ut;
}
