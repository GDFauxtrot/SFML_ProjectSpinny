#pragma once
#include "Node.hpp"

class SpriteNode : Node, public sf::Drawable
{
private:
	sf::Vertex vertices[4];
	sf::VertexBuffer vertexBuffer;
	const sf::Texture* texture;
	sf::IntRect textureRect;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	bool visible;

	SpriteNode();
	SpriteNode(const sf::Texture& texture);
	SpriteNode(const sf::Texture& texture, const sf::IntRect& rectangle);
	~SpriteNode();

	void setTexture(const sf::Texture& texture, bool resetRect);
	void setTextureRect(sf::IntRect rect);
};