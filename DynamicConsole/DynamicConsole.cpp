#include <Windows.h>
#include <iostream>

typedef void(*FNPTR)(int pid, char* from, char* to);

int main(int argc, char* argv[])
{
    HINSTANCE hInstance = LoadLibrary(L"..\\Debug\\ReadWriteMemoryDLL.dll");

    if (hInstance)
    {
        FNPTR func = (FNPTR)GetProcAddress(hInstance, "run");

        if (func)
        {
            func(atoi(argv[1]), argv[2], argv[3]);

            FreeLibrary(hInstance);
        }
        else
        {
            printf("Coundn't find the function\n");
        }
    }
    else
    {
        printf("Couldn't load the library\n");
    }

    return 0;
}