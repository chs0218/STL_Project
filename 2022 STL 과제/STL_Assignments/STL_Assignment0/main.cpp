#include <iostream>
#include <fstream>
#include <vector>
#include "Player.h"

std::istream& operator>>(std::istream& is, Player& p) {
	p.read(is);
	return is;
}

int main()
{
	std::ifstream in{ "2022 STL 과제 파일", std::ios::binary };
	std::vector<Player> v;
	Player tmp;
	while (in >> tmp)
		v.push_back(tmp);

	v.back().print();
}