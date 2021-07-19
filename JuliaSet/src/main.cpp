#include <math.h>
#include <SFML/Graphics.hpp>
#include "classes/graphics/UIManager.h"

constexpr float GOLDEN_RATIO{ 1.618f };
constexpr unsigned int XDIM{ 800 };
constexpr unsigned int YDIM{ 800 };
constexpr float ESCAPE_RADIUS{ 2.0f };
constexpr int MAX_ITERATIONS{ 1000 };

int main() {
	sf::Vector2f C = sf::Vector2f{ 1.0f - GOLDEN_RATIO, 0.0f };
	if (!sf::Shader::isAvailable()) {
		return -1;
	}
	
	sf::Shader* julia_shader{ new sf::Shader };
	if (!julia_shader->loadFromFile("src/shaders/julia_shader.frag", sf::Shader::Fragment)) {
		return -1;
	}

	sf::Shader* mandelbrot_shader{ new sf::Shader };
	if (!mandelbrot_shader->loadFromFile("src/shaders/mandelbrot_shader.frag", sf::Shader::Fragment)) {
		return -1;
	}

	UIManager ui{ XDIM, YDIM, julia_shader };

	mandelbrot_shader->setUniform("viewportSize", sf::Vector2f{ ui.getWindowSize() });
	mandelbrot_shader->setUniform("maxIteration", MAX_ITERATIONS);

	julia_shader->setUniform("R", ESCAPE_RADIUS);
	julia_shader->setUniform("viewportSize", sf::Vector2f{ ui.getWindowSize() });
	julia_shader->setUniform("c", C);
	julia_shader->setUniform("maxIteration", MAX_ITERATIONS);


	while (ui.isOpen()) {
		ui.update();
		ui.pollEvents();
		//C.y += 0.00001f;
		julia_shader->setUniform("c", C);
	}
	return 0;
}