#include <math.h>
#include <SFML/Graphics.hpp>
#include "classes/graphics/UIManager.h"

constexpr float GOLDEN_RATIO{ 1.618f };
constexpr unsigned int XDIM{ 800 };
constexpr unsigned int YDIM{ 800 };
constexpr float ESCAPE_RADIUS{ 2.0f };
constexpr int MAX_ITERATIONS{ 1000 };

int main() {
	sf::Vector2f C = sf::Vector2f{ 0.0f, 0.0f };
	if (!sf::Shader::isAvailable()) {
		return -1;
	}
	
	sf::Shader* julia{ new sf::Shader };
	if (!julia->loadFromFile("src/shaders/julia.frag", sf::Shader::Fragment)) {
		return -1;
	}

	sf::Shader* mandelbrot{ new sf::Shader };
	if (!mandelbrot->loadFromFile("src/shaders/mandelbrot.frag", sf::Shader::Fragment)) {
		return -1;
	}

	UIManager ui{ XDIM, YDIM, mandelbrot};

	mandelbrot->setUniform("viewportSize", sf::Vector2f{ ui.getWindowSize() });
	mandelbrot->setUniform("maxIteration", MAX_ITERATIONS);

	julia->setUniform("R", ESCAPE_RADIUS);
	julia->setUniform("viewportSize", sf::Vector2f{ ui.getWindowSize() });
	julia->setUniform("c", C);
	julia->setUniform("maxIteration", MAX_ITERATIONS);


	while (ui.isOpen()) {
		ui.update();
		ui.pollEvents();
		C.y += 0.0001f;
		C.x += 0.0001f;
		julia->setUniform("c", C);
	}
	return 0;
}