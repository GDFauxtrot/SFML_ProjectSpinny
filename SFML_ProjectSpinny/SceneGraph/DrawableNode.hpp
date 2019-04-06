#pragma once
#include "Node.hpp"


class DrawableNode : Node, public sf::Drawable
{
private:
	sf::Vertex vertices[4];
	sf::VertexBuffer vertexBuffer;
	sf::Texture* texture;
	sf::IntRect textureRect;

public:
	bool visible;

	DrawableNode();
	~DrawableNode();

};