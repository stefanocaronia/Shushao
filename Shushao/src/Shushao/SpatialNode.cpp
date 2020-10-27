#include "sepch.h"

#include "SpatialNode.h"

namespace Shushao {

	SpatialNode::SpatialNode()
	{
		transform = new Transform();
		transform->SetOwner(this);
	}

	SpatialNode::~SpatialNode()
	{
		transform = nullptr;
		delete transform;
	}

	void SpatialNode::SetParent(Node* newParent, bool worldPositionStays)
	{
		Node::SetParent(newParent);

		{ /// All this code must go in Transform
			/// TODO: restore this when canvas are back
			#if 0
			if (parent->entity->canvas != nullptr) {
				entity->canvas = parent->entity->canvas;
			} else if (entity->GetComponent<Canvas>() == nullptr) {
				entity->canvas = nullptr;
			}
			#endif

			transform->RectTransform->init();

			if (worldPositionStays && dynamic_cast<SpatialNode*>(parent)) {
				transform->SetLocalPosition(transform->GetWorldPosition() - ((SpatialNode*)parent)->GetTransform()->GetWorldPosition());
			} else {
				transform->SetLocalPosition(Transform::VEC3_ZERO);
			}

			transform->Invalidate();
		}
	}
}
