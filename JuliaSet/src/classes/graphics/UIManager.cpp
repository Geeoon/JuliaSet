#include "UIManager.h"

UIManager::UIManager(unsigned int x, unsigned int y, sf::Shader* s) : isPanning{ false }, xDim { x }, yDim{ y }, shader{ s }, zoom{ 1.0f }, position{ -0.5f, -0.5f } {
	shader->setUniform("zoom", zoom);
	shader->setUniform("position", position);
	window.create(sf::VideoMode{ xDim, yDim }, "Julia Set", sf::Style::Close);
	window.setFramerateLimit(0);
	if (!texture.create(xDim, yDim)) {
		// failed to create texture
	}
	sprite = sf::Sprite{ texture };
}

void UIManager::update() {
	window.clear();
	window.draw(sprite, shader);
	window.display();
}

void UIManager::pollEvents() {
	sf::Event e;
	while (window.pollEvent(e)) {
		switch (e.type) {
			case sf::Event::MouseButtonPressed: {
				isPanning = true;
				mousePosition = sf::Mouse::getPosition(window);
			} break;
			case sf::Event::MouseButtonReleased: {
				isPanning = false;
			} break;
			case sf::Event::MouseMoved: {
				if (isPanning) {
					sf::Vector2f deltaMouse{ (sf::Mouse::getPosition(window) - mousePosition) };
					sf::Vector2f windowSize{ window.getSize() };
					deltaMouse.x /= -windowSize.x;
					deltaMouse.y /= windowSize.y;
					position += deltaMouse;
					mousePosition = sf::Mouse::getPosition(window);
					shader->setUniform("position", position);
				}
			} break;
			case sf::Event::Closed: {
				window.close();
			} break;
			case sf::Event::MouseWheelScrolled: {
				sf::Vector2i{ sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y };
				zoom /= std::powf(1.25, e.mouseWheelScroll.delta);
				shader->setUniform("zoom", zoom);
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
				shader->setUniform("position", position);
			} break;
		}
	}
}

bool UIManager::isOpen() {
	return window.isOpen();
}