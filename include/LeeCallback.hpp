#pragma once
#include <iostream>
#include <Windows.h>


#pragma pack(push, 1)
struct MyThunk
{
    unsigned char PopEAX_1;     // POP the caller's return address off the stack
    unsigned char PushThis;     // PUSH the object 'this' pointer on to the stack
    void* ThisValue;
    unsigned char PushEAX_1;    // PUSH the caller's return address back on to the stack
    unsigned char Call;         // CALL the callback function
    __int32 CallAddr;
    unsigned char PopEAX_2;     // POP the caller's return address off the stack
    unsigned char AddESP[3];    // Remove the object 'this' pointer from the stack
    unsigned char PushEAX_2;    // PUSH the caller's return address back on to the stack
    unsigned char Return;       // return to the caller
};
#pragma pack(pop)

typedef void (*CallbackType)(int);

class LeeCallback
{
    CallbackType exObjCallback;
    LeeCallback()
    {
        MyThunk* thunk = (MyThunk*)VirtualAlloc(NULL, sizeof(MyThunk), MEM_COMMIT, PAGE_READWRITE);
        if (thunk)
        {
            thunk->PopEAX_1 = 0x58;
            thunk->PushThis = 0x68;
            thunk->ThisValue = this;
            thunk->PushEAX_1 = 0x50;
            thunk->Call = 0xE8;
            thunk->CallAddr = reinterpret_cast<__int32>(Callback) - (reinterpret_cast<__int32>(&thunk->Call) + 5);
            thunk->PopEAX_2 = 0x58;
            thunk->AddESP[0] = 0x83;
            thunk->AddESP[1] = 0xC4;
            thunk->AddESP[2] = 0x04;
            thunk->PushEAX_2 = 0x50;
            thunk->Return = 0xC3;

            DWORD dwOldProtect;
            VirtualProtect(thunk, sizeof(MyThunk), PAGE_EXECUTE, &dwOldProtect);

            FlushInstructionCache(GetCurrentProcess(), thunk, sizeof(MyThunk));

            exObjCallback = (CallbackType)thunk;
        }
    }

    ~LeeCallback()
    {
        if (exObjCallback)
            VirtualFree(exObjCallback, 0, MEM_RELEASE);
    }

    //somestuff
    ExternalClass m_ExObj;

    // NOTE: pCtx is the return address inside of ExternalFunc()
    // where the callback is being called from.  Because the
    // callback is using the __cdecl calling convention, the
    // thunk needs to remember this value and restore it after
    // Callback() exits.  Passing it as a parameter to Callback()
    // is a quick-n-dirty way for the thunk to do that...
    static void Callback(void* pCtx, LeeCallback* pThis, int x)
    {
        //dosomething with pThis
    }

    void MyFunc()
    {
        //m_ExObj.ExternalFunc(*&Callback, this);
    }
};

class ExternalClass //This I cannot mess with.
{
    //somestuff
    void ExternalFunc(void(*callback)(void*,LeeCallback*,int), const void*) {
        std::cout << "" << std::endl;
    }
};