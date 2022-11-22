#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

enum class Arrow{ 
	Left = sf::Keyboard::Left,
	Right = sf::Keyboard::Right, 
	Up = sf::Keyboard::Up, 
	Down = sf::Keyboard::Down
};


class Grid {
public:
	Grid(sf::RenderWindow* window) {
		font.loadFromFile("OpenSans-Bold.ttf");
		val.setFont(font);
		val.setCharacterSize(window->getSize().x / (2 * sizeGrid));
		val.setFillColor(sf::Color::Black);
		val.setOrigin(val.getCharacterSize() / 2.f, val.getCharacterSize() / 2.f);

		for (int i{ 0 }; i < sizeGrid; i++)
			for (int j{ 0 }; j < sizeGrid; j++)
				value[i][j] = 0;

		gen();
		gen();
	}

	void show(sf::RenderWindow* window) {
		sf::Vector2f sizeRec(window->getSize() / sizeGrid);
		sf::RectangleShape rec(sizeRec);
		rec.setOutlineThickness(4);
		rec.setOutlineColor(sf::Color(120, 120, 120));
		rec.setOrigin(sf::Vector2f(sizeRec / 2.f));


		for (int i{ 0 }; i < sizeGrid; i++)
			for (int j{ 0 }; j < sizeGrid; j++) {
				sf::Vector2f pos(j * sizeRec.x + sizeRec.x / 2.f, i * sizeRec.y + sizeRec.y / 2.f);
				sf::Color color(sf::Color::White);
				rec.setPosition(pos);

				rec.setFillColor(color);
				window->draw(rec);
				if (value[i][j] != 0) {
					val.setString(std::to_string(value[i][j]));
					sf::FloatRect recVal{ val.getGlobalBounds() };
					val.setPosition(pos);
					//val.setScale(sizeRec / recVal.width);
					window->draw(val);
				}
			}
	}
	void gen() {
		int i{ 0 };
		int j{ 0 };
		
		do
		{
			i = rand() % (sizeGrid + 1);
			j = rand() % (sizeGrid + 1);

		} while (value[i][j] != 0);


		value[i][j] = 2 * (rand() % 2 + 1);
	}
	void afficheScore() {
		std::cout << score << std::endl;
	}
	void move(int key) {
		bool genNumber{ false };
		if (key == sf::Keyboard::Left) {
			for (int i{ 0 }; i < sizeGrid; i++)
				for (int j{ 0 }; j < sizeGrid; j++)
					if (value[i][j] != 0) {
						int rangMove{ 0 };
						bool bo{ false };
						bool canDouble{ true };
						for (int c{ 1 }; c <= j; c++)
							if (value[i][j - c] == 0)
								rangMove++;
							else if (value[i][j - c] != value[i][j])
								canDouble = false;
							else if (canDouble)
								bo = true;
						if (rangMove != 0 && !bo) {
							value[i][j - rangMove] = value[i][j];
							value[i][j] = 0;
							genNumber = true;
						}
						if (bo) {
							genNumber = true;
							value[i][j - rangMove - 1] *= 2;
							value[i][j] = 0;
							score += value[i][j - rangMove - 1];
							afficheScore();
						}
					}
		}
		else if (key == sf::Keyboard::Right) {
			for (int i{ 0 }; i < sizeGrid; i++)
				for (int j{ sizeGrid - 1 }; j >= 0; j--)
					if (value[i][j] != 0) {
						int rangMove{ 0 };
						bool bo{ false };
						bool canDouble{ true };
						for (int c{ j + 1 }; c < sizeGrid; c++)
							if (value[i][c] == 0)
								rangMove++;
							else if (value[i][c] != value[i][j])
								canDouble = false;
							else if (canDouble)
								bo = true;
						if (rangMove != 0 && !bo) {
							value[i][j + rangMove] = value[i][j];
							value[i][j] = 0;
							genNumber = true;
						}
						if (bo) {
							value[i][j + rangMove + 1] *= 2;
							value[i][j] = 0;
							score += value[i][j + rangMove + 1];
							afficheScore();
							genNumber = true;

						}
					}
		}
		else if (key == sf::Keyboard::Up) {
			for (int j{ 0 }; j< sizeGrid; j++)
				for (int i{ 0 }; i < sizeGrid; i++)
					if (value[i][j] != 0) {
						int rangMove{ 0 };
						bool bo{ false };
						bool canDouble{ true };
						for (int c{ 1 }; c <= i; c++)
							if (value[i - c][j] == 0)
								rangMove++;
							else if (value[i - c][j] != value[i][j])
								canDouble = false;
							else if (canDouble)
								bo = true;
						if (rangMove != 0 && !bo) {
							value[i - rangMove][j] = value[i][j];
							value[i][j] = 0;
							genNumber = true;
						}
						if (bo) {
							genNumber = true;
							value[i - rangMove - 1][j] *= 2;
							value[i][j] = 0;
							score += value[i - rangMove - 1][j];
							afficheScore();
						}
					}
		}
		else if (key == sf::Keyboard::Down) {
			for (int j{ 0 }; j < sizeGrid; j++)
				for (int i{ sizeGrid - 1 }; i >= 0; i--)
					if (value[i][j] != 0) {
						int rangMove{ 0 };
						bool bo{ false };
						bool canDouble{ true };
						for (int c{ i + 1 }; c < sizeGrid; c++)
							if (value[c][j] == 0)
								rangMove++;
							else if (value[c][j] != value[i][j])
								canDouble = false;
							else if (canDouble)
								bo = true;
						if (rangMove != 0 && !bo) {
							value[i + rangMove][j] = value[i][j];
							value[i][j] = 0;
							genNumber = true;
						}
						if (bo) {
							genNumber = true;
							value[i + rangMove + 1][j] *= 2;
							value[i][j] = 0;
							score += value[i + rangMove + 1][j];
							afficheScore();
						}
					}
		}
		if (genNumber)
			gen();
	}
	void reset() {
		for (int i{ 0 }; i < sizeGrid; i++)
			for (int j{ 0 }; j < sizeGrid; j++)
				value[i][j] = 0;

		gen();
		gen();

		score = 0;
	}

	bool endGame() {
		for (int i{ 0 }; i < sizeGrid; i++)
			for (int j{ 0 }; j < sizeGrid; j++)
				if (value[i][j] == 0)
					return false;
		return true;
	}
	unsigned int getScore() {
		return score;
	}

private:
	static const unsigned int sizeGrid{ 4 };
	unsigned int value[sizeGrid][sizeGrid] = {};
	sf::Font font;
	sf::Text val;
	unsigned int score{ 0 };
};


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "chess");
	Grid grid(&window);



	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
				grid.move(event.key.code);
		}

		if (grid.endGame())
			grid.reset();

		window.clear();
		grid.show(&window);
		window.display();
	}

	return 0;
}