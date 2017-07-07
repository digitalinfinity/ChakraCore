//-------------------------------------------------------------------------------------------------------
// Copyright (C) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.
//-------------------------------------------------------------------------------------------------------
#pragma once

namespace Js
{
    struct ConcatStringCacheKey
    {
        Js::JavascriptString* left;
        Js::JavascriptString* right;
    };

    typedef JsUtil::MruDictionary<ConcatStringCacheKey, Js::JavascriptString*> ConcatStringCache;
};

template <>
struct DefaultComparer<Js::ConcatStringCacheKey>
{
    inline static bool Equals(Js::ConcatStringCacheKey x, Js::ConcatStringCacheKey y)
    {
        return x.left == y.left && x.right == y.right;
    }

    inline static hash_t GetHashCode(Js::ConcatStringCacheKey d)
    {
        return (HeapBlockMap32::GetLevel2Id(d.left) << 16 | HeapBlockMap32::GetLevel2Id(d.right));
    }
};
