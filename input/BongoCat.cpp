// rev-c4a91e-20260825 BongoCat.cpp
#include "../overlay/BongoCat.h"

// Keyboard and mouse hooks feed the paw FSM. Still works when a
// fullscreen game holds focus — that is the overlay's job.

namespace BongoCat {

static HHOOK g_kb = nullptr;
static HHOOK g_mouse = nullptr;
static CatEngine* g_engine = nullptr;

static LRESULT CALLBACK KeyHook(int code, WPARAM wp, LPARAM lp) {
    if (code == HC_ACTION && (wp == WM_KEYDOWN || wp == WM_SYSKEYDOWN)) {
        auto* k = reinterpret_cast<KBDLLHOOKSTRUCT*>(lp);
        g_engine->keyHit(static_cast<int>(k->vkCode));
    }
    return CallNextHookEx(g_kb, code, wp, lp);
}

static LRESULT CALLBACK MouseHook(int code, WPARAM wp, LPARAM lp) {
    if (code == HC_ACTION && wp == WM_LBUTTONDOWN && g_engine)
        g_engine->clickHit();
    return CallNextHookEx(g_mouse, code, wp, lp);
}

void CatEngine::hookAllInput() {
    g_engine = this;
    HMODULE mod = GetModuleHandle(nullptr);
    g_kb = SetWindowsHookEx(WH_KEYBOARD_LL, KeyHook, mod, 0);
    g_mouse = SetWindowsHookEx(WH_MOUSE_LL, MouseHook, mod, 0);
    if (cfg_.controllerEnabled) startGamepadPolling();
}

void CatEngine::keyHit(int vk) {
    activePaw_ = (vk % 2 == 0) ? Paw::Left : Paw::Right;
    pawTimer_ = cfg_.pawResetMs;
    repaint();
}

void CatEngine::tick() {
    if (pawTimer_ > 0 && --pawTimer_ == 0) {
        activePaw_ = Paw::Idle;
        repaint();
    }
}

} // namespace BongoCat
