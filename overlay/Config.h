// rev-c4a91e-20260825 Config.h
#pragma once
#include <string>

namespace BongoCat {

struct Config {
    std::string activeSkin = "skin_default";
    std::string keyboardLayout = "qwerty"; // qwerty | azerty | dvorak | colemak | jis
    int posX = 100;
    int posY = 100;
    int pawResetMs = 120;
    bool twitchAlerts = false;
    bool controllerEnabled = true;

    bool load(const std::string& path);

private:
    void parse(const std::string& js);
    static std::string str(const std::string& js, const std::string& key,
                           const std::string& fallback);
    static int num(const std::string& js, const std::string& key, int fallback);
};

} // namespace BongoCat
