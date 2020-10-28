#pragma once

#include "Object.h"
#include "Transform.h"

namespace Shushao {

    class Node : public Object
    {
    public:

        bool IsAtRoot();
        inline bool IsRoot() const { return isRoot; }
        inline void SetRoot(bool _root) { isRoot = _root; }
        virtual inline bool HasTransform() const { return false; }

        inline Node* GetParent() const { return parent; }
        Node* GetChild(unsigned int);
        inline std::vector<Node*>& GetChildren() { return children; }
        std::vector<Node*> GetParents();

        virtual void SetParent(Node* parent);
        void RemoveChild(Node* child);
        void AddChild(Node* child);
        inline void SetAsRoot() { isRoot = true; parent = nullptr; }

    protected:
        Node* parent = nullptr;
        std::vector<Node*> children;

        bool isRoot = false;
    };
}

