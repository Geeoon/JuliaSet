#include <math.h>
#include <SFML/Graphics.hpp>
constexpr float GOLDEN_RATIO{ 1.618f };
constexpr unsigned int XDIM{ 500 };
constexpr unsigned int YDIM{ 500 };

int main() {
	constexpr float ESCAPE_RADIUS{ 2.0f };
	sf::Vector2f C = sf::Vector2f{ 1.0f - GOLDEN_RATIO, 0.0f };
	float zoom{ 1.0f };
	sf::Vector2f position = sf::Vector2f{ -0.5f, -0.5f };

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

	fragmentShader.setUniform("R", ESCAPE_RADIUS);
	fragmentShader.setUniform("viewportSize", sf::Vector2f{ static_cast<float>(XDIM), static_cast<float>(YDIM) });
	fragmentShader.setUniform("c", C);
	fragmentShader.setUniform("maxIteration", 1000);
	fragmentShader.setUniform("zoom", zoom);
	fragmentShader.setUniform("position", position);

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
					zoom /= std::powf(1.25, e.mouseWheelScroll.delta);
					fragmentShader.setUniform("zoom", zoom);
				} break;
				case sf::Event::KeyPressed: {
					switch (e.key.code) {
						case sf::Keyboard::Up: {
							position.y += 0.25f * zoom;
						} break;
						case sf::Keyboard::Down: {
							position.y -= 0.25f * zoom;
						} break;
						case sf::Keyboard::Right: {
							position.x += 0.25f * zoom;
						} break;
						case sf::Keyboard::Left: {
							position.x -= 0.25f * zoom;
						} break;
					}
					fragmentShader.setUniform("position", position);
				} break;
			}
		}
		C.y += 0.00001f;
		fragmentShader.setUniform("c", C);
	}
	return 0;
}