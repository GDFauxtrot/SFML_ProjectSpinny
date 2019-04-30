#include "SpriteNode.hpp"

SpriteNode::SpriteNode() :
vertexBuffer(sf::TrianglesStrip, sf::VertexBuffer::Stream)
{
	if (sf::VertexBuffer::isAvailable())
		vertexBuffer.create(4);
}

SpriteNode::SpriteNode(const sf::Texture& texture)
{
	
}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& rect)
{

}

SpriteNode::~SpriteNode() {}

void SpriteNode::setTexture(const sf::Texture& tex, bool resetRect)
{
	if (resetRect || (!texture && (textureRect == sf::IntRect())))
		setTextureRect(sf::IntRect(0, 0, tex.getSize().x, tex.getSize().y));

	texture = &tex;
}

void SpriteNode::setTextureRect(sf::IntRect rect)
{
	textureRect = rect;
}

void SpriteNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (texture)
	{
		states.transform *= getWorldTransform();
		states.texture = texture;

		if (sf::VertexBuffer::isAvailable())
		{
			target.draw(vertexBuffer, states);
		}
		else
		{
			target.draw(vertices, 4, sf::TriangleStrip, states);
		}
	}
}