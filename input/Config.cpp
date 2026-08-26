// rev-c4a91e-20260825 Config.cpp
#include "../overlay/Config.h"
#include <fstream>
#include <sstream>

namespace BongoCat {

bool Config::load(const std::string& path) {
    std::ifstream f(path);
    if (!f) return false;
    std::stringstream ss;
    ss << f.rdbuf();
    parse(ss.str());
    return true;
}

void Config::parse(const std::string& js) {
    activeSkin = str(js, "skin", "skin_default");
    keyboardLayout = str(js, "keyboard_layout", "qwerty");
    posX = num(js, "pos_x", 100);
    posY = num(js, "pos_y", 100);
    pawResetMs = num(js, "paw_reset_ms", 120);
    twitchAlerts = str(js, "twitch_alerts", "false") == "true";
    controllerEnabled = str(js, "controller_support", "true") == "true";
}

std::string Config::str(const std::string& js, const std::string& key,
                        const std::string& fallback) {
    auto k = js.find("\"" + key + "\"");
    if (k == std::string::npos) return fallback;
    auto colon = js.find(':', k);
    auto q1 = js.find('"', colon + 1);
    auto q2 = js.find('"', q1 + 1);
    if (q1 == std::string::npos || q2 == std::string::npos) return fallback;
    return js.substr(q1 + 1, q2 - q1 - 1);
}

int Config::num(const std::string& js, const std::string& key, int fallback) {
    auto k = js.find("\"" + key + "\"");
    if (k == std::string::npos) return fallback;
    auto colon = js.find(':', k);
    return std::atoi(js.c_str() + colon + 1);
}

} // namespace BongoCat
