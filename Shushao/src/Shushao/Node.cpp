#include "sepch.h"

#include "Node.h"

namespace Shushao {

	bool Node::isAtRoot()
	{
		return (parent == nullptr || isRoot || (parent != nullptr && parent->isRoot));
	}

	void Node::SetParent(Node* newParent)
	{
		if (parent != nullptr) {
			parent->RemoveChild(this);
		}

		parent = newParent;
		parent->AddChild(this);
	}

	void Node::RemoveChild(Node* child)
	{
		if (children.empty()) return;
		auto it = find(children.begin(), children.end(), child);
		if (it != children.end()) {
			children.erase(it);
		}
	}

	void Node::AddChild(Node* child)
	{
		if (children.empty()) {
			children.push_back(child);
			return;
		}
		auto it = find(children.begin(), children.end(), child);
		if (it == children.end()) children.push_back(t);
	}

	Node* Node::GetChild(unsigned int index)
	{
		if (index >= children.size()) return nullptr;
		return children.at(index);
	}

	std::vector<Node*> Node::GetParents()
	{
		std::vector<Node*> parents;
		if (isAtRoot()) return parents;

		Node* p = parent;
		while (p != nullptr && !p->isRoot) {
			parents.push_back(p);
			p = p->GetParent();
		}

		return parents;
	}

	Node* Node::GetSpatialParent() const
	{
		/// TODO: Iterate parents and find the first with transform
		/// if not fount get nullptr
		return parent;
	}
}
