#pragma once

#include "Object.h"
#include "Transform.h"

namespace Shushao {

    class Node : public Object
    {
    public:

        bool isAtRoot();

        inline Node* GetParent() const { return parent; }
        Node* GetSpatialParent() const;
        Node* GetChild(unsigned int);
        std::vector<Node*> GetParents();

        virtual void SetParent(Node* parent);
        void RemoveChild(Node* child);
        void AddChild(Node* child);

    protected:
        Node* parent;
        std::vector<Node*> children;

        bool isRoot = false;
    };
}

