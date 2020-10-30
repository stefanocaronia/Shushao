#include "sepch.h"

#include "Config.h"

//#include "LevelMap.h"
#include "Resources.h"

namespace Config {

std::string title = "Shushao Engine";
std::string startScene = "";
bool debug = false;

// textures
unsigned int pixelPerUnit = 16;

// display
float displayAspect = 16.0f / 9.0f;
unsigned int displayWidth = 1024;
unsigned int displayHeight = (int)(displayWidth / displayAspect);
bool fullscreen = false;
const std::map<std::string, std::pair<int, int>> DisplayModes{
    {"1920x1080", {1920, 1080}},
    {"1400x1600", {1400, 1600}},
    {"1280x1024", {1280, 1024}},
    {"1024x576", {1024, 576}},
    {"1024x768", {1024, 768}}};

// Time
namespace Time {
    float fixedRateLimit = 60.0f;  // 0.0f -> unlimited
    float frameRateLimit = 0.0f;  // 0.0f -> unlimited
}  // namespace Time

// Physics (Box2d)
namespace Physics {
    bool enabled = true;
    bool debug = false;
    glm::vec2 gravity = {0, -8.8};
    bool doSleep = true;
    int velocityIterations = 8;
    int positionIterations = 3;
}  // namespace Physics

//Shushao::LevelMap Layers;
//Shushao::LevelMap SortingLayers;

std::map<std::string, std::string> data;

bool LoadUserConfig() {
    std::ifstream cfile;
    cfile.open(USER_CONFIG_FILE);

    if (!cfile.is_open()) {
        DEBUG_CORE_ERROR("Can't load user config from {0}", USER_CONFIG_FILE);
        return false;
    }

    if (!processConfigData<std::ifstream>(cfile)) {
        DEBUG_CORE_ERROR("Can't process config data");
        cfile.close();
        return false;
    }

    cfile.close();

    if (!parseUserConfig()) {
        DEBUG_CORE_ERROR("Can't parse user config");
        return false;
    }

    return true;
}

bool LoadEngineConfig() {
    std::string engine_config = Shushao::Resources::GetEmbeddedText(CONFIG_ENGINE);

    if (engine_config == "") {
        DEBUG_CORE_ERROR("Can't load engine config");
        return false;
    }

    std::istringstream cstring(engine_config);

    if (!processConfigData<std::istringstream>(cstring)) {
        DEBUG_CORE_ERROR("Can't process config data");
        return false;
    }

    if (!parseUserConfig()) {
        DEBUG_CORE_ERROR("Can't parse user config");
        return false;
    }

    if (!parseEngineConfig()) {
        DEBUG_CORE_ERROR("Can't parse engine config");
        return false;
    }

    return true;
}

bool parseUserConfig() {
    if (data.find("mode") != data.end()) {
        auto mode = DisplayModes.find(data["mode"]);
        if (mode != DisplayModes.end()) {
            displayWidth = mode->second.first;
            displayHeight = mode->second.second;
            displayAspect = (float)(displayWidth / displayHeight);
        }
    }

    if (data.find("fullscreen") != data.end()) {
        fullscreen = (data["fullscreen"] == "Y");
    }

    return true;
}

bool parseEngineConfig() {
    if (data.find("title") != data.end()) {
        title = data["title"];
    }

    if (data.find("start_scene") != data.end()) {
        startScene = data["start_scene"];
    }

    if (data.find("framerate_limit") != data.end()) {
        Time::frameRateLimit = stof(data["framerate_limit"]);
    }

    if (data.find("fixedrate_limit") != data.end()) {
        Time::fixedRateLimit = stof(data["fixedrate_limit"]);
    }

    if (data.find("pixel_per_unit") != data.end()) {
        pixelPerUnit = stoi(data["pixel_per_unit"]);
    }

    if (data.find("debug_enabled") != data.end()) {
        Shushao::Debug::enabled = (data["debug_enabled"] == "Y");
    }

    if (data.find("debuginfo_enabled") != data.end()) {
        Shushao::Debug::infoEnabled = (data["debuginfo_enabled"] == "Y");
    }

    if (data.find("debug_draw_transforms") != data.end()) {
        Shushao::Debug::drawTransforms = (data["debug_draw_transforms"] == "Y");
    }

    if (data.find("debug_draw_rect_transforms") != data.end()) {
        Shushao::Debug::drawRectTransforms = (data["debug_draw_rect_transforms"] == "Y");
    }

    if (data.find("physics_debug") != data.end()) {
        Physics::debug = (data["physics_debug"] == "Y");
    }

    if (data.find("debug_level") != data.end()) {
        if (data["debug_level"] == "INFO")
            Shushao::Debug::level = Shushao::DebugLevel::INFO;
        else if (data["debug_level"] == "WARNING")
            Shushao::Debug::level = Shushao::DebugLevel::WARNING;
        else if (data["debug_level"] == "ERROR")
            Shushao::Debug::level = Shushao::DebugLevel::ERROR;
    }

    if (data.find("debuggrid_mode") != data.end()) {
        if (data["debuggrid_mode"] == "ORTHOGRAFIC")
            Shushao::Debug::debugGridMode = Shushao::GridMode::ORTHOGRAFIC;
        else if (data["debuggrid_mode"] == "PERSPECTIVE")
            Shushao::Debug::debugGridMode = Shushao::GridMode::PERSPECTIVE;
    }

    //if (data.find("layers") != data.end()) {
    //    Config::Layers = Shushao::Utility::split(data["layers"], ',');
    //}

    //if (data.find("sorting_layers") != data.end()) {
    //    Config::SortingLayers = Shushao::Utility::split(data["sorting_layers"], ',');
    //}

    //if (data.find("max_layers") != data.end()) {
    //    Config::Layers.setMaxElements(stoi(data["max_layers"]));
    //}

    //if (data.find("max_sorting_layers") != data.end()) {
    //    Config::SortingLayers.setMaxElements(stoi(data["max_sorting_layers"]));
    //}

    return true;
}

}  // namespace Config