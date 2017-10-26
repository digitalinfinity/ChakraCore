//-------------------------------------------------------------------------------------------------------
// Copyright (C) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.
//-------------------------------------------------------------------------------------------------------

#include "RuntimePlatformAgnosticPch.h"
#include "../../Common/Core/CommonTypedefs.h"
#include "../../Common/PlatformAgnostic/SystemInfo.h"

#if defined(__APPLE__)
#include <mach-o/dyld.h> // _NSGetExecutablePath
#elif defined(__linux__)
#include <unistd.h> // readlink
#endif

// Defined in PAL
extern errno_t __cdecl strcpy_s(char *_Dst, size_t _SizeInBytes, const char *_Src);

namespace PlatformAgnostic
{
    bool SystemInfo::GetBinaryLocation(char* const path, const charcount_t size, charcount_t* const resultStrLength)
    {
        if (path == nullptr || resultStrLength == nullptr || size > UINT_MAX) return false;

#ifdef __APPLE__
        uint32_t path_size = (uint32_t)size;
        char *tmp = nullptr;
        int str_len;
        if (_NSGetExecutablePath(path, &path_size))
        {
            strcpy_s(path, size, "GetBinaryLocation: _NSGetExecutablePath has failed.");
            return false;
        }

        tmp = (char*)malloc(size);
        char *result = realpath(path, tmp);
        str_len = strlen(result);
        memcpy(path, result, str_len);
        free(tmp);
        path[str_len] = char(0);
#elif defined(__linux__)
        int str_len = readlink("/proc/self/exe", path, size - 1);
        if (str_len <= 0)
        {
            strcpy_s(path, size,  "GetBinaryLocation: /proc/self/exe has failed.");
            return;
        }
        path[str_len] = char(0);
#else
        #warning "Implement GetBinaryLocation for this platform"
#endif

        *resultStrLength = str_len;
        return true;
    }

} // namespace PlatformAgnostic
