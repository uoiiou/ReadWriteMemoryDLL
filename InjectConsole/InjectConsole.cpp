#include <Windows.h>
#include <iostream>

#define FILEPATH "D:\\Uni\\5sem\\OSiSP\\LB\\LB3\\ReadWriteMemoryDLL\\Debug\\ReadWriteMemoryDLL.dll"
#define PROCID 15364

typedef HMODULE(WINAPI* LPLoadLibrary)(LPCSTR);

int main()
{
    HMODULE hdll = LoadLibraryA("Kernel32.dll");

    LPLoadLibrary LoadLibraryA = (LPLoadLibrary)GetProcAddress(hdll, "LoadLibraryA");

    HANDLE hProc = OpenProcess(PROCESS_VM_READ | PROCESS_VM_OPERATION | PROCESS_VM_WRITE |
        PROCESS_CREATE_THREAD | PROCESS_CREATE_PROCESS,
        FALSE, PROCID);

    LPVOID path = VirtualAllocEx(hProc, NULL, strlen(FILEPATH),
        MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    int er = WriteProcessMemory(hProc, path, FILEPATH,
        strlen(FILEPATH), NULL);

    DWORD threadID;

    HANDLE HThread = CreateRemoteThread(hProc, NULL, NULL,
        (LPTHREAD_START_ROUTINE)LoadLibraryA, (LPVOID)path, NULL, &threadID);

    WaitForSingleObject(HThread, INFINITE);
    
    FreeLibrary(hdll);
    CloseHandle(hProc);
}