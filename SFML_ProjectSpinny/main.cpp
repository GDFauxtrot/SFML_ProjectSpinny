#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <SceneGraph/Node.hpp>
#include <SFML/Graphics/Text.hpp>

/// <summary>
/// Returns a recursively-produced, indented string that
/// represents names of nodes and their children.
/// </summary>
std::string getChildrenGraph(std::string indent, std::string currentIndent, Node *node)
{
	std::string str;

	for (auto child : node->children)
	{
		str += currentIndent + child->name + '\n';
		str.append(getChildrenGraph(indent, currentIndent + indent, child));
	}

	return str;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "Main: Scene Graph Testing");
	sf::RenderWindow graphWindow(sf::VideoMode(512, 768), "Scene Graph Window");

	// Move the graph window over a bit, refocus main window
	graphWindow.setPosition(graphWindow.getPosition() + sf::Vector2i(-512, 0));
	window.requestFocus();

	// Establish update loop timer
	sf::Clock clock;
	sf::Time delta = clock.getElapsedTime();

	// TEST NODES FOR SCENE GRAPH - DELETE THEM AT SOME POINT
	Node root;
	Node nodeParent("Parent", &root);
	Node nodeChild("Child", &nodeParent);

	sf::Font font;
	font.loadFromFile("consola.ttf");

	sf::Text textPositions("", font, 12);

	sf::RectangleShape parentShape(sf::Vector2f(20.f, 20.f));
	sf::RectangleShape childShape(sf::Vector2f(10.f, 10.f));
	parentShape.setFillColor(sf::Color(128, 0, 128, 255));
	childShape.setFillColor(sf::Color::Cyan);

	sf::Text textGraph("", font, 12);

	while (window.isOpen())
	{
		// Window event handling
		sf::Event event;
		sf::Event graphEvent;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				graphWindow.close();
				window.close();
			}
		}
		while (graphWindow.pollEvent(graphEvent))
		{
			if (graphEvent.type == sf::Event::Closed)
				graphWindow.close();
		}

		// Shortening deltaTime, why not
		float dT = delta.asSeconds();

		// Update all nodes in the scene
		root.update();

		// Inputs for node testing (just collapse it in IDE)
		{
			float speed = 100.f;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				nodeParent.setLocalPosition(nodeParent.getLocalPosition() + sf::Vector2f(1.f, 0.f) * dT * -speed);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				nodeParent.setLocalPosition(nodeParent.getLocalPosition() + sf::Vector2f(1.f, 0.f) * dT * speed);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				nodeParent.setLocalPosition(nodeParent.getLocalPosition() + sf::Vector2f(0.f, 1.f) * dT * speed);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				nodeParent.setLocalPosition(nodeParent.getLocalPosition() + sf::Vector2f(0.f, 1.f) * dT * -speed);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				nodeChild.setLocalPosition(nodeChild.getLocalPosition() + sf::Vector2f(1.f, 0.f) * dT * -speed);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				nodeChild.setLocalPosition(nodeChild.getLocalPosition() + sf::Vector2f(1.f, 0.f) * dT * speed);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				nodeChild.setLocalPosition(nodeChild.getLocalPosition() + sf::Vector2f(0.f, 1.f) * dT * speed);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				nodeChild.setLocalPosition(nodeChild.getLocalPosition() + sf::Vector2f(0.f, 1.f) * dT * -speed);
			}

			float rot = 100.f;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			{
				nodeChild.setLocalRotation(nodeChild.getLocalRotation() + dT  * -rot);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				nodeChild.setLocalRotation(nodeChild.getLocalRotation() + dT * rot);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period))
			{
				nodeParent.setLocalRotation(nodeParent.getLocalRotation() + dT  * -rot);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Slash))
			{
				nodeParent.setLocalRotation(nodeParent.getLocalRotation() + dT * rot);
			}

			float scale = 2.5f;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			{
				nodeChild.setLocalScale(nodeChild.getLocalScale() + sf::Vector2f(1.f, 1.f) * dT * -scale);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
			{
				nodeChild.setLocalScale(nodeChild.getLocalScale() + sf::Vector2f(1.f, 1.f) * dT * scale);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Semicolon))
			{
				nodeParent.setLocalScale(nodeParent.getLocalScale() + sf::Vector2f(1.f, 1.f) * dT * -scale);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Quote))
			{
				nodeParent.setLocalScale(nodeParent.getLocalScale() + sf::Vector2f(1.f, 1.f) * dT * scale);
			}
		}

		// Printing node testing (just collapse it in IDE)
		{
			std::ostringstream stream;
			stream << "PARENT: Local Pos:   "
				<< nodeParent.getLocalPosition().x << " "
				<< nodeParent.getLocalPosition().y << "\n        "
				<< "World Pos:   "
				<< nodeParent.getWorldPosition().x << " "
				<< nodeParent.getWorldPosition().y << "\n        "
				<< "Local Rot:   "
				<< nodeParent.getLocalRotation() << "\n        "
				<< "World Rot:   "
				<< nodeParent.getWorldRotation() << "\n        "
				<< "Local Scale: "
				<< nodeParent.getLocalScale().x << " "
				<< nodeParent.getLocalScale().y << "\n        "
				<< "World Scale: "
				<< nodeParent.getWorldScale().x << " "
				<< nodeParent.getWorldScale().y << "\n        "
				<< std::endl;
			stream << "CHILD:  Local Pos:   "
				<< nodeChild.getLocalPosition().x << " "
				<< nodeChild.getLocalPosition().y << "\n        "
				<< "World Pos:   "
				<< nodeChild.getWorldPosition().x << " "
				<< nodeChild.getWorldPosition().y << "\n        "
				<< "Local Rot:   "
				<< nodeChild.getLocalRotation() << "\n        "
				<< "World Rot:   "
				<< nodeChild.getWorldRotation() << "\n        "
				<< "Local Scale: "
				<< nodeChild.getLocalScale().x << " "
				<< nodeChild.getLocalScale().y << "\n        "
				<< "World Scale: "
				<< nodeChild.getWorldScale().x << " "
				<< nodeChild.getWorldScale().y << "\n        "
				<< std::endl;
			textPositions.setString(stream.str());
		}


		// Main window update loop!
		window.clear();
		window.draw(parentShape, nodeParent.getWorldTransform());
		window.draw(childShape, nodeChild.getWorldTransform());
		window.draw(textPositions);
		window.display();


		// Draw on graph window:  printing all nodes in the scene
		if (graphWindow.isOpen())
		{
			textGraph.setString(getChildrenGraph("  ", "", &root));

			graphWindow.clear();
			graphWindow.draw(textGraph);
			graphWindow.display();
		}

		// Restart clock, collecting deltaTime (LAST THING TO DO)
		delta = clock.restart();
	}

	return 0;
}