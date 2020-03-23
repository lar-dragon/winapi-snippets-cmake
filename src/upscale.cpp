#include <windows.h>
#include <shellapi.h>
#include <winuser.h>
#include <synchapi.h>
#include <winbase.h>
#include <handleapi.h>
#include <winerror.h>

int main() {
    SHELLEXECUTEINFO shExInfo = {0};
    shExInfo.cbSize = sizeof(shExInfo);
    shExInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    shExInfo.hwnd = 0;
    shExInfo.lpVerb = "runas"; // Operation to perform
    shExInfo.lpFile = "cmd"; // Application to start
    shExInfo.lpParameters = "/K echo 123"; // Additional parameters
    shExInfo.lpDirectory = 0;
    shExInfo.nShow = SW_SHOW;
    shExInfo.hInstApp = 0;

    if (ShellExecuteEx(&shExInfo))
    {
        WaitForSingleObject(shExInfo.hProcess, INFINITE);
        CloseHandle(shExInfo.hProcess);
    }

    return ERROR_SUCCESS;
}