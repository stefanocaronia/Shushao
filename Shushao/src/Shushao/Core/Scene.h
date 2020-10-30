#pragma once 

#include "Entity.h"

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

        virtual void Init();
        virtual void Update();

    private:
        std::shared_ptr<Entity> root = nullptr;
        std::multiset<std::shared_ptr<Node>> nodes;
        bool invalid = true;
    };

}
