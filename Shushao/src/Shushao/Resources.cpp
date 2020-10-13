#include "sepch.h"

#include "Resources.h"
#include "Utility.h"
#include "Shaders/Shader.h"
#include "Texture.h"

namespace se {

std::vector<char> Resources::GetEmbeddedData(int IDRES, std::string library, LPWSTR type) {
    std::vector<char> output;

    HMODULE module;

    if (library != "") {
        module = LoadLibraryA(library.c_str());

        if (module == NULL) {
            unsigned int err = GetLastError();
            DEBUG_CORE_ERROR("Can't load dll '" + (library != "" ? library : "") + "' - Err. " + std::to_string(err));
            ::exit(5);
        }
    } else {
        module = GetModuleHandle(NULL);
    }

    auto resourceHandle = FindResource(module, MAKEINTRESOURCE(IDRES), type);

    if (resourceHandle != nullptr) {
        auto dataHandle = LoadResource(module, resourceHandle);
        if (dataHandle != nullptr) {
            auto resourceSize = ::SizeofResource(module, resourceHandle);
            if (resourceSize != 0) {
                auto firstByte = reinterpret_cast<const char*>(::LockResource(dataHandle));
                if (firstByte != nullptr) {
                    output.resize(resourceSize);
                    copy(firstByte, firstByte + resourceSize, output.begin());
                }
            }
        }
    } else {
        DEBUG_CORE_WARN("Can't load Resource " + std::to_string(IDRES) + (library != "" ? " from " + library : ""));
        return std::vector<char>();
    }

    return output;
}

std::string Resources::GetEmbeddedText(int IDRES, std::string library) {
    auto data = se::Resources::GetEmbeddedData(IDRES, library, RT_RCDATA);
    return std::string(data.begin(), data.end());
}

void Resources::Clear() {
    for (auto& asset : Assets) {
        if (asset.second != nullptr) {
            DEBUG_CORE_INFO("Cancello {0}", asset.second->name + " (" + util::classtitle(typeid(*asset.second).name()) + ")");
            delete (asset.second);
            asset.second = nullptr;
        }
    }
    Assets.clear();
}

void Resources::toString() {
    Logger::setColor(ConsoleColor::WHITE);
    std::cout << " Resources [" << Assets.size() << "] :" << std::endl;
    for (auto const& asset : Assets) {
        std::cout << "  - (" << util::classtitle(typeid(*asset.second).name()) << ") " << asset.first << std::endl;
    }
    Logger::setColor(ConsoleColor::LIGHTGREY);
}

std::map<std::string, Object*> Resources::Assets;

}  // namespace se
