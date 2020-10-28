#include "sepch.h"

#include "Entity.h"

namespace Shushao {

	Entity::Entity()
	{
		transform = new Transform();
		transform->SetOwner(this);
		transform->SetEntity(this);
	}

	Entity::~Entity()
	{
		transform = nullptr;
		delete transform;
	}

	void Entity::SetParent(Node* newParent, bool worldPositionStays)
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

			transform->GetRectTransform()->init();

			Entity* parent = GetParentEntity();

			if (worldPositionStays && parent != nullptr) {
				transform->SetLocalPosition(transform->GetWorldPosition() - parent->GetTransform()->GetWorldPosition());
			} else {
				transform->SetLocalPosition(Transform::VEC3_ZERO);
			}

			transform->Invalidate();
		}
	}

	Entity* Entity::GetParentEntity() 
	{
		Node* current = (Node*)this;
		while (Node* parent = current->GetParent()) {
			if (parent->HasTransform()) {
				return (Entity*)parent;
			} else {
				current = parent;
			}
		}

		return nullptr;
	}
}
