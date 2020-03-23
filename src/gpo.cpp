#include <iostream>
#include <windows.h>
#include <Processthreadsapi.h>
#include <UserEnv.h>
#include <errhandlingapi.h>

#pragma comment(lib, "userenv.lib")

BOOL mapList(const std::string& str, PGROUP_POLICY_OBJECT pGPOList)
{
    std::cout << "== " << str.c_str() << " ==" << std::endl;
    do {
        std::cout << std::endl;
        std::cout << "lpDisplayName: " << pGPOList->lpDisplayName << std::endl;
        std::cout << "szGPOName: " << pGPOList->szGPOName << std::endl;
        std::cout << "lpFileSysPath: " << pGPOList->lpFileSysPath << std::endl;
        std::cout << "lpDSPath: " << pGPOList->lpDSPath << std::endl;
        pGPOList = pGPOList->pNext;
    } while (pGPOList != nullptr);
    std::cout << std::endl;
    return FreeGPOList(pGPOList);
}

int main()
{
    PGROUP_POLICY_OBJECT pGPOList;

    GUID guid = REGISTRY_EXTENSION_GUID;
    if (ERROR_SUCCESS == GetAppliedGPOList(GPO_LIST_FLAG_MACHINE, nullptr, nullptr, &guid, &pGPOList))
    {
        mapList("GetAppliedGPOList", pGPOList);
    }

    HANDLE hToken;
    if (ERROR_SUCCESS == OpenProcessToken(GetCurrentProcess(), TOKEN_IMPERSONATE | TOKEN_QUERY, &hToken)) {
        if (ERROR_SUCCESS == GetGPOList(hToken, nullptr, nullptr, nullptr, GPO_LIST_FLAG_MACHINE, &pGPOList))
        {
            mapList("GetGPOList", pGPOList);
        }
        CloseHandle(hToken);
    }

    return 0;
}
