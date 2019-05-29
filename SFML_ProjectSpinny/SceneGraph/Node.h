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

	/// <summary>
	/// Returns the sf::Transform of this node in local-space.
	/// </summary>
	sf::Transform getLocalTransform();
	/// <summary>
	/// Returns the sf::Transform of this node in world-space.
	/// </summary>
	sf::Transform getWorldTransform();
	/// <summary>
	/// Returns the position of this node in local-space.
	/// </summary>
	sf::Vector2f getLocalPosition();
	/// <summary>
	/// Returns the position of this node in world-space.
	/// </summary>
	sf::Vector2f getWorldPosition();
	/// <summary>
	/// Returns the euler rotation of this node in local-space.
	/// </summary>
	float getLocalRotation();
	/// <summary>
	/// Returns the euler rotation of this node in world-space.
	/// </summary>
	float getWorldRotation();
	/// <summary>
	/// Returns the scale of this node in local-space.
	/// </summary>
	sf::Vector2f getLocalScale();
	/// <summary>
	/// Returns the scale of this node in world-space.
	/// </summary>
	sf::Vector2f getWorldScale();

////////////////////////////////////////////////////////////

	void setLocalPosition(sf::Vector2f v2f);
	/// <summary>
	/// Sets the position of this node in world-space.
	/// </summary>
	void setWorldPosition(sf::Vector2f v2f);
	/// <summary>
	/// Sets the euler rotation of this node in local-space.
	/// </summary>
	void setLocalRotation(float rot);
	/// <summary>
	/// Sets the euler rotation of this node in world-space.
	/// </summary>
	void setWorldRotation(float rot);
	/// <summary>
	/// Sets the scale of this node in local-space.
	/// </summary>
	void setLocalScale(sf::Vector2f v2f);
	/// <summary>
	/// Sets the scale of this node in world-space.
	/// </summary>
	void setWorldScale(sf::Vector2f v2f);

////////////////////////////////////////////////////////////

	/// <summary>
	/// Updates the transforms of this node and its children.
	/// </summary>
	virtual void update();

	/// <summary>
	/// Assigns a parent to this child, preserving its world-space transform.
	/// </summary>
	void setParent(Node* newParent);
};
