// rev-c4a91e-20260825 BongoCat.h
#pragma once
#include <string>
#include <windows.h>
#include "Config.h"

namespace BongoCat {

enum class Paw { Idle, Left, Right, Both };

class SkinAtlas {
public:
    bool load(const std::string& jsonPath); // skins/*.json
    void drawPaw(HDC dc, Paw paw);
private:
    std::string dir_;
};

class CatEngine {
public:
    CatEngine(HWND hwnd, Config& cfg) : hwnd_(hwnd), cfg_(cfg) {}
    void loadSkin(const std::string& name);
    void hookAllInput();
    void keyHit(int vk);
    void clickHit();
    void startGamepadPolling();
    void tick();

private:
    void repaint();
    HWND hwnd_;
    Config& cfg_;
    SkinAtlas skin_;
    Paw activePaw_ = Paw::Idle;
    int pawTimer_ = 0;
};

void popupSkinMenu(HWND hwnd);

} // namespace BongoCat
