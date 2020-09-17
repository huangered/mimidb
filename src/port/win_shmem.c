#include "port/shmem.h"

#ifdef _WIN32
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <tchar.h>

TCHAR szName[] = TEXT("Local\\MyFileMappingObject");

HANDLE hMapFile;
LPCTSTR pBuf;

void* shmem_init(Size BUF_SIZE) {
    
    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // use paging file
        NULL,                    // default security
        PAGE_READWRITE,          // read/write access
        0,                       // maximum object size (high-order DWORD)
        BUF_SIZE,                // maximum object size (low-order DWORD)
        szName);                 // name of mapping object

    if (hMapFile == NULL)
    {
        _tprintf(TEXT("Could not create file mapping object (%d).\n"),
            GetLastError());
        return NULL;
    }
    pBuf = (LPTSTR)MapViewOfFile(hMapFile,   // handle to map object
        FILE_MAP_ALL_ACCESS, // read/write permission
        0,
        0,
        BUF_SIZE);

    if (pBuf == NULL)
    {
        _tprintf(TEXT("Could not map view of file (%d).\n"),
            GetLastError());

        CloseHandle(hMapFile);

        return NULL;
    }

    memset((PVOID)pBuf, 0, BUF_SIZE);

    return pBuf;
}

void shmem_close() {
    UnmapViewOfFile(pBuf);

    CloseHandle(hMapFile);
}

#endif