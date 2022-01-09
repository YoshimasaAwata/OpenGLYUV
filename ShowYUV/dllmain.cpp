// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include "pch.h"

#include "Window.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

static CWindow* pwin = NULL;

extern "C" HRESULT WINAPI CreateOpenGLWindow(const char* pFileName)
{
    HRESULT hr = S_OK;

    if (pwin != NULL)
    {
        delete pwin;
    }

    try 
    {
        UINT sideLen = CTexture::CIF_WIDTH;
        pwin = new CWindow(sideLen, sideLen, pFileName);
    }
    catch (std::exception e)
    {
        _RPT0(_CRT_ERROR, e.what());
        hr = S_FALSE;
    }

    return hr;
}

extern "C" HRESULT WINAPI Render()
{
    HRESULT hr = S_FALSE;
    if (pwin != NULL)
    {
        hr = pwin->Render();
    }
    return hr;
}
