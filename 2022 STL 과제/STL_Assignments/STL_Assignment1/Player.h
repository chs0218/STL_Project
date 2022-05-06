#pragma once
#include <iostream>
#include <vector>
#include <string>

class Player
{
	std::string name;
	int score;
	int id = 0;
	size_t num;
	char* p;

public:
	Player();
	~Player();

	Player(const Player& other);
	Player& operator=(const Player& other);

	Player(Player&& other) noexcept;
	Player& operator=(Player&& other) noexcept;

	void write(std::ostream& os);
	void read(std::istream& is);
	std::string getName() const;
	int getId() const;
	int getScore() const;
	size_t getNum() const;
	void print() const;

	bool operator==(const Player& rhs) {
		if (name == rhs.name && score == rhs.score && id == rhs.id && num == rhs.num)
			return true;
		return false;
	}
};
