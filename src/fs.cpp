#define UNICODE

#include <string>
#include <Windows.h>
#include <fileapi.h>
#include <Shlobj.h>
#include <cstdio>

BOOL RmDir(const std::wstring &strDir);
BOOL IsDots(const std::wstring &strName);
BOOL IsDir(const WIN32_FIND_DATA &fdFile);

int main() {
    WCHAR desktop[MAX_PATH];
    SHGetSpecialFolderPath(HWND_DESKTOP, desktop, CSIDL_DESKTOPDIRECTORY, FALSE);
    std::wstring path = std::wstring(desktop) + L"\\test";
    wprintf(L"The full path name is: %s\n", path.data());
    if (GetFileAttributes(path.data()) != INVALID_FILE_ATTRIBUTES) {
        wprintf(L"Path exists\n");
        RmDir(path);
    }
    CreateDirectory(path.data(), nullptr);
    return ERROR_SUCCESS;
}

BOOL RmDir(const std::wstring &strDir) {
    WIN32_FIND_DATA fdFile ;
    memset(&fdFile, 0, sizeof(fdFile));
    HANDLE hFind = INVALID_HANDLE_VALUE;
    std::wstring strSearch = strDir + L"\\*.*";
    hFind = FindFirstFile(strSearch.data(), &fdFile);

    if (hFind == INVALID_HANDLE_VALUE) {
        return FALSE;
    }

    do {
        std::wstring strDelete = strDir + L"\\" + fdFile.cFileName;
        if (IsDir(fdFile) == TRUE) {
            if (IsDots(fdFile.cFileName) == TRUE) {
                continue;
            }

            RmDir(strDelete);
        } else {
            DeleteFile(strDelete.data());
        }
    } while(FindNextFile(hFind, &fdFile) == TRUE);

    FindClose(hFind);
    RemoveDirectory(strDir.data());

    return TRUE;
}

BOOL IsDots(const std::wstring &strName) {
    return strName == L"." || strName == L".." ;
}

BOOL IsDir(const WIN32_FIND_DATA &fdFile) {
    return (fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0 ;
}