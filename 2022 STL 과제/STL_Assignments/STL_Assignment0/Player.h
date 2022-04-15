#pragma once
#include <iostream>
#include <vector>
#include <string>

class Player
{
public:
	std::string name;
	int score;
	int id;
	size_t num;
	char* p;

	Player();
	~Player();
	void write(std::ostream& os);
	void read(std::istream& is);
	void print();
};
