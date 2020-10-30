#pragma once

#include "Scene.h"
#include "Application.h"

namespace Shushao {

    class SceneManager
    {
    public:

        SceneManager(const SceneManager&) = delete;

        static SceneManager& Get()
        {
            static SceneManager instance;
            return instance;
        }

        template <class T>
        static T* LoadScene(std::string _name = "")
        { 
            SceneManager& instance = Get();
            T* scene = new T();
            scene->name = (_name == "" ? Utility::classtitle<T>() : _name);

            instance.SetScene(scene);
            return scene;
        }

        static void SetScene(Scene* _scene)
        {
            SceneManager& instance = Get();
            instance.activeScene.reset(_scene);
            instance.sceneSet = true;
        }

        static void SceneManager::Clear()
        {
            SceneManager& instance = Get();
            instance.activeScene.reset();
            //instance.scenes.clear();
            instance.sceneSet = false;
        }

    private:
        bool sceneSet = false; 
        //std::vector<std::weak_ptr<Scene>> scenes;
        std::shared_ptr<Scene> activeScene;

        SceneManager() {}
    };
}

