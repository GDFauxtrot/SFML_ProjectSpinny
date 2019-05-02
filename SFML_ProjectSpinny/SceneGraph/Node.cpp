#include "Node.hpp"

Node::Node()
{
	name = "ROOT";
}

Node::Node(Node* parentNode)
{
	name = parentNode->name + " (child)";
	setParent(parentNode);
}

Node::Node(std::string newName, Node* parentNode)
{
	name = newName;
	setParent(parentNode);
}

Node::~Node()
{
	// If not the root, remove self from parent's child list
	if (parent)
	{
		parent->children.erase(
			std::remove(parent->children.begin(), parent->children.end(), this),
			parent->children.end());
	}

	// Remove own children, if we have any
	for (auto child : children)
	{
		delete child;
	}
}

////////////////////////////////////////////////////////////

sf::Transform Node::getLocalTransform()
{
	return localTransform;
}
const sf::Transform& Node::getWorldTransform() const
{
	if (parent)
		return parent->getWorldTransform() * localTransform;

	return localTransform;
}
sf::Vector2f Node::getLocalPosition()
{
	return position;
}
sf::Vector2f Node::getWorldPosition()
{
	if (parent)
		return parent->getWorldTransform().transformPoint(position);

	return position;
}
float Node::getLocalRotation()
{
	return rotation;
}
float Node::getWorldRotation()
{
	if (parent)
		return parent->getWorldRotation() + rotation;

	return rotation;
}
sf::Vector2f Node::getLocalScale()
{
	return scale;
}
sf::Vector2f Node::getWorldScale()
{
	if (parent)
		return sf::Vector2f(
			parent->getWorldScale().x * scale.x,
			parent->getWorldScale().y * scale.y);

	return scale;
}

////////////////////////////////////////////////////////////

void Node::setLocalPosition(sf::Vector2f newPosition)
{
	sf::Vector2f posDiff = newPosition - position;

	position = newPosition;

	updateLocalTransform();
}
void Node::setWorldPosition(sf::Vector2f newPosition)
{
	// Not implemented yet!
}
void Node::setLocalRotation(float newRotation)
{
	float rotDiff = newRotation - rotation;

	rotation = newRotation;

	updateLocalTransform();
}
void Node::setWorldRotation(float rotation)
{
	// Not implemented yet!
}
void Node::setLocalScale(sf::Vector2f newScale)
{
	sf::Vector2f scaleDiff = sf::Vector2f(newScale.x / scale.x, newScale.y / scale.y);

	scale = newScale;

	updateLocalTransform();
}
void Node::setWorldScale(sf::Vector2f scale)
{
	// Not implemented yet!
}

////////////////////////////////////////////////////////////

void Node::update()
{
	// TODO new Transform system! Fix the two lines here to reflect the changes, they're errors otherwise.
	if (parent)
	{
		// Update transform from parent


	}
	else
	{
		// I am root -- do nothing!
	}

	// Cascade update onto children
	for (auto child : children)
	{
		child->update();
	}
}

void Node::updateLocalTransform()
{
	localTransform = sf::Transform();
	localTransform.translate(position).rotate(rotation).scale(scale);
}

void Node::setParent(Node* newParent)
{
	// Assign parent, add to its child list
	parent = newParent;
	parent->children.push_back(this);
	
	// TODO edit localTransform to reflect new info. worldTransform should stay the exact same!
}