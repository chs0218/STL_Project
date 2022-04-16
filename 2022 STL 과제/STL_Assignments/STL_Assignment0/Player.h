#pragma once
#include <iostream>
#include <vector>
#include <string>

class Player
{
	std::string name;
	int score;
	int id;
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
	int getName() const;
	int getId() const;
	int getScore() const;
	void print() const;
};
