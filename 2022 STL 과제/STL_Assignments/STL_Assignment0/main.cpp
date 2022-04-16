#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "Player.h"

std::istream& operator>>(std::istream& is, Player& p) {
	p.read(is);
	return is;
}

std::ostream& operator<<(std::ostream& os, const Player& p)
{
	p.print();
	return os;
}

int main()
{
	std::ifstream in{ "2022 STL 과제 파일", std::ios::binary };
	std::vector<Player> v;

	v.reserve(200'0000);

	Player tmp;
	for (int i = 0; i < 10; ++i)
	{
		in >> tmp;
		v.push_back(tmp);
	}
	std::sort(v.begin(), v.end(), [](const Player& a, const Player& b) {return a.getId() < b.getId(); });
	std::cout << "============================================================\n";
	for (const Player& i : v)
		i.print();
	std::cout << "============================================================\n";
	int fid;
	std::cout << "찾을 ID를 입력해주세요: ";
	while (std::cin >> fid)
	{
		std::sort(v.begin(), v.end(), [](const Player& a, const Player& b) {return a.getId() < b.getId(); });
		auto result = lower_bound(v.cbegin(), v.cend(), fid, [](const Player& target, int fid) {return target.getId() < fid; });
		if (result->getId() != fid)
			std::cout << "해당 ID는 존재하지 않습니다." << std::endl;
		else
		{
			std::cout << *result;
			std::sort(v.begin(), v.end(), [](const Player& a, const Player& b) {return a.getName() < b.getName(); });
			std::cout << "============================================================\n";
			for (const Player& i : v)
				i.print();
			std::cout << "============================================================\n";
			result = lower_bound(v.cbegin(), v.cend(), fid, [](const Player& target, int fid) {return target.getId() < fid; });
		}
		std::cout << "찾을 ID를 입력해주세요: ";
		/*std::sort(v.begin(), v.end(), [](const Player& a, const Player& b) {return a.getName() < b.getName(); });
		std::sort(v.begin(), v.end(), [](const Player& a, const Player& b) {return a.getScore() < b.getScore(); });*/
	}

}