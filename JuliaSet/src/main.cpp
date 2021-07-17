#include <math.h>
#include <SFML/Graphics.hpp>
#include "classes/graphics/UIManager.h"

constexpr float GOLDEN_RATIO{ 1.618f };
constexpr unsigned int XDIM{ 800 };
constexpr unsigned int YDIM{ 800 };
constexpr float ESCAPE_RADIUS{ 2.0f };

int main() {
	sf::Vector2f C = sf::Vector2f{ 1.0f - GOLDEN_RATIO, 0.0f };
	if (!sf::Shader::isAvailable()) {
		return -1;
	}
	
	sf::Shader* fragmentShader{ new sf::Shader };
	
	if (!fragmentShader->loadFromFile("src/shaders/julia_shader.frag", sf::Shader::Fragment)) {

	}
	UIManager ui{ XDIM, YDIM, fragmentShader };

	fragmentShader->setUniform("R", ESCAPE_RADIUS);
	fragmentShader->setUniform("viewportSize", sf::Vector2f{ static_cast<float>(ui.getWindowSize().x), static_cast<float>(ui.getWindowSize().y) });
	fragmentShader->setUniform("c", C);
	fragmentShader->setUniform("maxIteration", 1000);


	while (ui.isOpen()) {
		ui.update();
		ui.pollEvents();
		//C.y += 0.00001f;
		fragmentShader->setUniform("c", C);
	}
	return 0;
}