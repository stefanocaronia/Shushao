#pragma once

#include "Node.h"

namespace Shushao {

    class Entity : public Node
    {
    public:
        Entity();
        ~Entity();

        Transform* GetTransform() const { return transform; }
        void SetParent(Node* newParent, bool worldPositionStays = false);

        Entity* GetParentEntity();

        virtual inline bool HasTransform() const override { return true; }

    protected:
        Transform* transform = nullptr;
    };

}
