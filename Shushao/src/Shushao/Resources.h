#pragma once

#include "Object.h"
#include "Resource.h"
#include "Resources/Resources.h"

namespace Shushao {

    class Resources
    {
    public:
        std::vector<float> aci;
        static std::map<std::string, Object*> Assets;

        static std::vector<char> GetEmbeddedData(int IDRES, std::string library = "", LPWSTR type = RT_RCDATA);
        static std::string GetEmbeddedText(int IDRES, std::string library = "");

        template <class T>
        static T* Load(std::string filename, std::string name)
        {
            T* resource = new T(filename, name);
            auto it = Assets.find(resource->name);
            if (it != Assets.end()) {
                DEBUG_CORE_WARN("Resource '" + resource->name + "' already loaded");
                delete (resource);
                resource = nullptr;
                return nullptr;
            }
            Assets[name] = resource;
            return resource;
        }

        template <class T>
        static T* Load(std::string name, int IDRES, std::string library = "")
        {
            if (Assets.find(name) != Assets.end()) {
                DEBUG_CORE_WARN("Resource '" + name + "' already loaded");
                return nullptr;
            }

            T* resource = new T("", name);
            if (!((T*)resource)->LoadEmbedded(IDRES, library)) {
                DEBUG_CORE_WARN("Resource '" + name + "' not loaded");
                return nullptr;
            }

            Assets[name] = resource;
            return resource;
        }

        template <class T>
        static T* Add(std::string name)
        {
            T* resource = new T(name);
            auto it = Assets.find(resource->name);
            if (it != Assets.end()) {
                DEBUG_CORE_WARN("Resource '" + resource->name + "' already loaded");
                delete (resource);
                resource = nullptr;
                return nullptr;
            }
            Assets[name] = resource;
            return resource;
        }

        template <class T>
        static T* Add(T* asset, std::string name = "")
        {
            auto it = Assets.find(asset->name);
            if (it != Assets.end()) {
                DEBUG_CORE_WARN("Resource '" + asset->name + "' already loaded");
                return nullptr;
            }
            Assets[name == "" ? asset->name : name] = (T*)asset;
            return (T*)asset;
        }

        template <class T>
        static T* Load(std::string filename)
        {
            T* resource = new T(filename);
            auto it = Assets.find(resource->name);
            if (it != Assets.end()) {
                DEBUG_CORE_WARN("Resource '" + resource->name + "' already loaded");

                delete (resource);
                resource = nullptr;
                return nullptr;
            }
            Assets[resource->name] = (T*)resource;
            return (T*)resource;
        }

        template <class T>
        static T* Get(std::string name)
        {
            auto it = Assets.find(name);
            if (it == Assets.end()) return nullptr;
            return (T*)Assets[name];
        }

        static void Delete(std::string name)
        {
            auto it = Assets.find(name);
            if (it == Assets.end()) return;
            Assets.erase(name);
            delete (Assets[name]);
        }

        static void toString();
        static void Clear();
    };

}  // namespace se
