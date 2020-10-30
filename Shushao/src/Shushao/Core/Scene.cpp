#include "sepch.h"

#include "Scene.h"

namespace Shushao {

    Scene::Scene()
    {
        root = std::make_shared<Entity>();
        root->SetName("ROOT");
        root->SetAsRoot();
        root->SetScene(this);
    }

    Scene::~Scene()
    {
        DEBUG_CORE_INFO("Scene Destructor: {0}", name);
        nodes.clear();
    }

    void Scene::Init()
    {
        for (auto node : nodes) {
            if (node != nullptr && !node->IsReady()) {
                node->Init();
            }
        }
    }

    void Scene::Update()
    {
        for (auto& node : root->GetDescendants()) {
            if (!node->IsReady()) {
                node->Init();
            }
            if (node->IsReady() && node->IsEnabled()) {
                node->Update();
            }
        }
    }
}
