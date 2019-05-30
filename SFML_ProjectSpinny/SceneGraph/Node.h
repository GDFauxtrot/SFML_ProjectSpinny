#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>

/// A "node" is a transformable object in a scene that
/// has a parent node, any number of children nodes.

/// A special case is a node with no parent, which will
/// be treated in the scene as the one and only "root" node.

/// A node also tracks two transforms behind the scenes, a
/// local and world sf::Transformable. Changes to one will always
/// affect the other. Separating the two this way also allows
/// for arbitrary edit of a node's local or world transform
/// depending on the desired result.


class Node
{
private:
	sf::Transform localTransform;
	sf::Vector2f position;
	sf::Vector2f scale = sf::Vector2f(1.f, 1.f);
	float rotation = 0;

	void updateLocalTransform();

public:
	std::vector<Node*> children;
	Node* parent = nullptr;
	std::string name;

	Node();
	Node(Node* newParent);
	Node(std::string name, Node* newParent);
	~Node();

////////////////////////////////////////////////////////////

	/// Returns the sf::Transform of this node in local-space.
	sf::Transform getLocalTransform();

	/// Returns the sf::Transform of this node in world-space.
	sf::Transform getWorldTransform();

	/// Returns the position of this node in local-space.
	sf::Vector2f getLocalPosition();

	/// Returns the position of this node in world-space.
	sf::Vector2f getWorldPosition();

	/// Returns the euler rotation of this node in local-space.
	float getLocalRotation();

	/// Returns the euler rotation of this node in world-space.
	float getWorldRotation();

	/// Returns the scale of this node in local-space.
	sf::Vector2f getLocalScale();

	/// Returns the scale of this node in world-space.
	sf::Vector2f getWorldScale();

////////////////////////////////////////////////////////////

	/// Sets the position of this node in local-space.
	void setLocalPosition(sf::Vector2f v2f);

	/// Sets the position of this node in world-space.
	void setWorldPosition(sf::Vector2f v2f);

	/// Sets the euler rotation of this node in local-space.
	void setLocalRotation(float rot);

	/// Sets the euler rotation of this node in world-space.
	void setWorldRotation(float rot);

	/// Sets the scale of this node in local-space.
	void setLocalScale(sf::Vector2f v2f);

	/// Sets the scale of this node in world-space.
	void setWorldScale(sf::Vector2f v2f);

////////////////////////////////////////////////////////////

	/// Updates the transforms of this node and its children.
	virtual void update();

	/// Assigns a parent to this child, preserving its world-space transform.
	void setParent(Node* newParent);
};
