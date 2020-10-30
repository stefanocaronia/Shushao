#include "sepch.h"

#include "Node.h"

namespace Shushao {

	Node::Node()
	{
		name = Utility::classtitle(typeid(*this).name());
		isEnabled = true;
	}

	Node::~Node()
	{
		DEBUG_CORE_INFO("Node Destructor: {0}", name);
		for (auto child : children) {
			delete (child);
		}
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
			(*it)->SetParent(nullptr);
		}
	}

	void Node::AddChild(Node* child)
	{
		if (children.empty()) {
			children.push_back(child);
			child->SetParent(this);
			return;
		}
		auto it = find(children.begin(), children.end(), child);
		if (it == children.end()) {
			children.push_back(child);
			child->SetParent(this);
		}
	}

	Node* Node::GetChild(unsigned int index)
	{
		if (index >= children.size()) return nullptr;
		return children.at(index);
	}

	std::vector<Node*> Node::GetParents()
	{
		std::vector<Node*> parents;
		if (IsAtRoot()) return parents;

		Node* p = parent;
		while (p != nullptr && !p->isRoot) {
			parents.push_back(p);
			p = p->GetParent();
		}

		return parents;
	}
	std::vector<Node*> Node::GetDescendants()
	{
		std::vector<Node*> descendants;

		for (auto& child : children) {
			descendants = child->GetDescendants();
		}

		return descendants;		
	}

	bool Node::IsEnabled() const
	{
		if (!isEnabled) {
			return false;
		}

		Node* p = GetParent();
		while (p != nullptr) {
			if (!p->IsEnabled()) {
				return false;
			}
			p = p->GetParent();
		}

		return true;
	}

	#pragma region lifecycle

	void Node::Init()
	{
		isReady = OnReady();		
	}

	void Node::Fixed()
	{
		if (IsEnabled()) 
			return;

		OnFixedUpdate();
	}

	void Node::Update()
	{
		if (!IsEnabled()) 
			return;

		if (!isStarted) {
			OnStart();
			isStarted = true;
		}

		Update();
		ResumeCoroutines();
	}

	void Node::Exit()
	{
		OnDestroy();
	}

	#pragma endregion
}
