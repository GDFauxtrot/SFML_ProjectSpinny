#include "Node.hpp"

Node::Node() {}
Node::Node(Node* parentNode)
{
	setParent(parentNode);
}

Node::~Node()
{
	for (auto child : children)
	{
		delete child;
	}
}

////////////////////////////////////////////////////////////

sf::Transformable Node::getLocalTransform()
{
	return localTransform;
}
sf::Transformable Node::getWorldTransform()
{
	return worldTransform;
}
sf::Vector2f Node::getLocalPosition()
{
	return localTransform.getPosition();
}
sf::Vector2f Node::getWorldPosition()
{
	return worldTransform.getPosition();
}
float Node::getLocalRotation()
{
	return localTransform.getRotation();
}
float Node::getWorldRotation()
{
	return worldTransform.getRotation();
}
sf::Vector2f Node::getLocalScale()
{
	return localTransform.getScale();
}
sf::Vector2f Node::getWorldScale()
{
	return worldTransform.getScale();
}

////////////////////////////////////////////////////////////

void Node::setLocalPosition(sf::Vector2f position)
{
	sf::Vector2f posDiff = position - localTransform.getPosition();
	localTransform.setPosition(position);
	worldTransform.move(posDiff);
}
void Node::setWorldPosition(sf::Vector2f position)
{
	sf::Vector2f posDiff = position - worldTransform.getPosition();
	worldTransform.setPosition(position);
	localTransform.move(posDiff);
}
void Node::setLocalRotation(float rotation)
{
	float rotDiff = rotation - localTransform.getRotation();
	localTransform.setRotation(rotation);
	worldTransform.rotate(rotDiff);
}
void Node::setWorldRotation(float rotation)
{
	float rotDiff = rotation - worldTransform.getRotation();
	worldTransform.setRotation(rotation);
	localTransform.rotate(rotDiff);
}
void Node::setLocalScale(sf::Vector2f scale)
{
	sf::Vector2f scaleDiff = sf::Vector2f(scale.x / localTransform.getScale().x, scale.y / localTransform.getScale().y);
	localTransform.setScale(scale);
	worldTransform.scale(scaleDiff);

}
void Node::setWorldScale(sf::Vector2f scale)
{
	sf::Vector2f scaleDiff = sf::Vector2f(scale.x / worldTransform.getScale().x, scale.y / worldTransform.getScale().y);
	worldTransform.setScale(scale);
	localTransform.scale(scaleDiff);
}

////////////////////////////////////////////////////////////

void Node::update()
{
	// TODO new Transform system! Fix the two lines here to reflect the changes, they're errors otherwise.
	if (parent)
	{
		// Update transform from parent
		//worldTransform = parent->worldTransform * getTransform();
	}
	else
	{
		// I am root
		//worldTransform = getTransform();
	}

	// Cascade update onto children
	for (auto child : children)
	{
		child->update();
	}
}

void Node::setParent(Node* newParent)
{

	parent = newParent;
	
	// TODO edit localTransform to reflect new info. worldTransform should stay the exact same!
}