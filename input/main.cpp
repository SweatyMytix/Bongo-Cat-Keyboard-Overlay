// rev-c4a91e-20260825 main.cpp
#include "../overlay/BongoCat.h"
#include "../overlay/Config.h"
#include <windows.h>

// Bongo Cat Keyboard Overlay - chroma-keyed popup + low-level hooks.
// Paw frames follow typing so the overlay reads well on stream.

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (msg == WM_DESTROY) { PostQuitMessage(0); return 0; }
    if (msg == WM_RBUTTONUP) { BongoCat::popupSkinMenu(hwnd); return 0; }
    return DefWindowProc(hwnd, msg, wp, lp);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int) {
    BongoCat::Config cfg;
    cfg.load("config/settings.json");

    WNDCLASSW wc{};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = L"BongoCatKeyboardWnd";
    RegisterClassW(&wc);

    // magenta chroma key so OBS can cut the background cleanly
    HWND hwnd = CreateWindowExW(WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
        L"BongoCatKeyboardWnd", L"BongoCat", WS_POPUP,
        cfg.posX, cfg.posY, 340, 300, nullptr, nullptr, hInst, nullptr);
    SetLayeredWindowAttributes(hwnd, RGB(255, 0, 255), 0, LWA_COLORKEY);
    ShowWindow(hwnd, SW_SHOWNORMAL);

    BongoCat::CatEngine engine(hwnd, cfg);
    engine.loadSkin(cfg.activeSkin);   // skins/*.json
    engine.hookAllInput();

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        engine.tick();
    }
    return 0;
}
