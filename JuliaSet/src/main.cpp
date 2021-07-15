#include <iostream>
#include <SFML/Graphics.hpp>

constexpr unsigned int XDIM{ 500 };
constexpr unsigned int YDIM{ 500 };

int main() {
	if (!sf::Shader::isAvailable()) {
		return -1;
	}
	sf::RenderWindow window;
	window.create(sf::VideoMode{ XDIM, YDIM }, "Julia Set", sf::Style::Close);
	window.setFramerateLimit(0);

	sf::Texture texture;
	if (!texture.create(XDIM, YDIM)) {
		return -1;
	}
	sf::Sprite sprite{ texture };

	sf::Shader fragmentShader;
	if (!fragmentShader.loadFromFile("src/shaders/julia_shader.frag", sf::Shader::Fragment)) {
		
	}

	while (window.isOpen()) {
		window.clear();
		window.draw(sprite, &fragmentShader);
		window.display();
		sf::Event e;
		while (window.pollEvent(e)) {
			switch (e.type) {
				case sf::Event::Closed: {
					window.close();
				} break;
				case sf::Event::MouseWheelScrolled: {
					sf::Vector2i{ sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y };
				} break;
			}
		}
	}
	return 0;
}