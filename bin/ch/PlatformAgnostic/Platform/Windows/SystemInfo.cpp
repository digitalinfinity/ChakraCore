//-------------------------------------------------------------------------------------------------------
// Copyright (C) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.
//-------------------------------------------------------------------------------------------------------

#include "RuntimePlatformAgnosticPch.h"
#include "Common.h"
#include "ChakraPlatform.h"

namespace PlatformAgnostic
{
#define SET_BINARY_PATH_ERROR_MESSAGE(path, msg) \
    str_len = (int) strlen(msg);                 \
    memcpy((char*) path, msg, (size_t)str_len);          \
    path[str_len] = char(0)

    bool SystemInfo::GetBinaryLocation(char* const path, const charcount_t size, charcount_t* const resultStrLength)
    {
        size_t bufferSize = sizeof(WCHAR) * size;
        DWORD str_len;

        if (path == nullptr || bufferSize < size) {
            SET_BINARY_PATH_ERROR_MESSAGE(path, "GetBinaryLocation: Invalid parameters");
            return false;
        }

        LPWSTR wpath = (WCHAR*)malloc(bufferSize);
        if (!wpath)
        {
            SET_BINARY_PATH_ERROR_MESSAGE(path, "GetBinaryLocation: GetModuleFileName has failed. OutOfMemory!");
            return false;
        }
        str_len = GetModuleFileNameW(NULL, wpath, size - 1);
        if (str_len <= 0)
        {
            SET_BINARY_PATH_ERROR_MESSAGE(path, "GetBinaryLocation: GetModuleFileName has failed.");
            free(wpath);
            return false;
        }

        str_len = WideCharToMultiByte(CP_UTF8, 0, wpath, str_len, path, size, NULL, NULL);
        free(wpath);

        if (str_len <= 0)
        {
            SET_BINARY_PATH_ERROR_MESSAGE(path, "GetBinaryLocation: GetModuleFileName (WideCharToMultiByte) has failed.");
            return false;
        }

        if ((unsigned)str_len > size - 1)
        {
            str_len = (int)size - 1;
        }
        path[str_len] = char(0);

        *resultStrLength = str_len;
        return true;
    }
}
