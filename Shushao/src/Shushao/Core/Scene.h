#pragma once 

#include "Entity.h"
#include "Shushao/Nodes/Camera.h"

namespace Shushao {

    class Scene : public Object
    {
    public:
        Scene();
        ~Scene();

        template <class T>
        T* AddNode(std::string _name = "")
        {
            T* node = new T();
            node->name = (_name == "" ? util::classtitle<T>() : _name);
            node->SetScene(this);
            node->SetParent(root);
            Invalidate();
            return node;
        }

        template <class T>
        T* GetNode()
        {
            for (auto node : nodes) {
                if (T* derived = dynamic_cast<T*>(node)) {
                    return derived;
                }
            }
            return nullptr;
        }

        void Invalidate()
        {
            invalid = true;
        }

        void SetActiveCamera(Camera* camera) { activeCamera.reset(camera); }
        std::shared_ptr<Camera> GetActiveCamera() const { return activeCamera; }

        virtual void Init();
        virtual void Update();

    private:
        std::shared_ptr<Entity> root = nullptr;
        std::multiset<std::shared_ptr<Node>> nodes;
        std::shared_ptr<Camera> activeCamera = nullptr;

        bool invalid = true;
        bool isLoaded = false;
    };

}
