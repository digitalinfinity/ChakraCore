//-------------------------------------------------------------------------------------------------------
// Copyright (C) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.
//-------------------------------------------------------------------------------------------------------
#pragma once

namespace PlatformAgnostic
{
    class SystemInfo
    {
    public:
        static bool GetMaxVirtualMemory(size_t *totalAS);
        static bool GetBinaryLocation(char* const path, const charcount_t size, charcount_t* const resultStrLength);
    };
} // namespace PlatformAgnostic
