#pragma once

#include "Node.h"

namespace Shushao {

    class SpatialNode : public Node
    {
    public:
        SpatialNode();
        ~SpatialNode();

        Transform* GetTransform() const { return transform; }
        void SetParent(Node* newParent, bool worldPositionStays = false);

    protected:
        Transform* transform = nullptr;
    };

}
