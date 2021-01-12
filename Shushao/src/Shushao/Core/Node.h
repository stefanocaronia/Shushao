#pragma once

#include "Object.h"
#include "Transform.h"
#include "CoroutineHolder.h"

namespace Shushao {

    class Scene;

    class Node : public Object, public CoroutineHolder
    {
        friend Scene;

    public:

        Node();
        ~Node();

        inline bool IsAtRoot() { return (parent == nullptr || IsRoot() || (parent != nullptr && parent->IsRoot())); }
        
        inline void Enable() { isEnabled = true; }
        inline void Disable() { isEnabled = false; }
        inline void SetReady(bool _ready) { isReady = _ready; }
        inline void SetRoot(bool _root) { isRoot = _root; }
        inline bool IsRoot() const { return isRoot; }
        inline bool IsReady() const { return isReady; }
        bool IsEnabled() const;
        virtual inline bool HasTransform() const { return false; }

        inline Node* GetParent() const { return parent; }
        Node* GetChild(unsigned int index);
        inline std::vector<Node*>& GetChildren() { return children; }
        std::vector<Node*> GetDescendants();
        std::vector<Node*> GetParents();

        virtual void SetParent(Node* parent);
        void RemoveChild(Node* child);
        void AddChild(Node* child);
        inline void SetAsRoot() { isRoot = true; parent = nullptr; }
        inline void SetScene(Scene* _scene) { scene.reset(_scene); }
        inline std::shared_ptr<Scene> GetScene() const { return scene; }

        template <class T>
        T* AddNode(std::string _name = "")
        {
            T* node = new T();
            node->name = (_name == "" ? Utility::classtitle<T>() : _name);
            node->SetParent(this);
            node->Init();  // va sempre chiamato
            nodes.insert(node);
            return (T*)node;
        }

        void Init();
        void Update();
        void Fixed();
        void Exit();

    protected:
        Node* parent = nullptr;
        std::shared_ptr<Scene> scene = nullptr;
        std::vector<Node*> children;

        bool isRoot = false;
        bool isReady = false;
        bool isEnabled = true;
        bool isStarted = false;

        virtual bool OnReady() { return true; }
        virtual void OnStart() {}
        virtual void OnUpdate() {}
        virtual void OnFixedUpdate() {}
        virtual void OnEnable() {}
        virtual void OnDisable() {}
        virtual void OnDestroy() {}

    };
}

