#include <iostream>
#include <fstream>
#include <algorithm>
#include <array>
#include <vector>
#include "Player.h"

std::array<Player, 2'000'000> arr;

std::istream& operator>>(std::istream& is, Player& p);
std::istream& operator>>(std::istream& is, Player& p) 
{
	p.read(is);
	return is;
}

std::ostream& operator<<(std::ostream& os, const Player& p);
std::ostream& operator<<(std::ostream& os, const Player& p)
{
	p.print();
	return os;
}

void printPlayer(const std::array<Player, 2'000'000>::iterator& target);
void printPlayer(const std::array<Player, 2'000'000>::iterator& target)
{
	int targetId = target->getId();
	std::array<Player, 2'000'000>::iterator tmptarget = target;
	--tmptarget;
	if (tmptarget->getId() != targetId)
		tmptarget->print();
	(++tmptarget)->print();
	++tmptarget;
	if (tmptarget->getId() != targetId)
		tmptarget->print();
}

int main()
{
	std::ifstream in{ "2022 STL 과제 파일", std::ios::binary };

	// 1. 파일을 읽어 제일 마지막 객체의 정보를 다음과 같은 형식으로 출력하라.
	for (auto i = arr.begin(); i != arr.end(); ++i)
		i->read(in);
	arr.back().print();
	// 2. 모든 Player의 점수 평균값을 계산하여 출력하라.
	long long sum = 0;
	for (const Player& i : arr)
		sum += i.getScore();

	std::cout << sum / arr.size() << std::endl;
	// 3. 확보한 메모리 바이트 수가 999인 Player 객체를 모두 찾아 "바이트 수 999"라는 이름인 파일에 복사하라.
	std::ofstream out{ "바이트 수 999", std::ios::binary };
	for (auto i : arr)
		if (i.getNum() == 999)
			i.write(out);


	// 4. id를 입력받아 존재하는 id라면 다음 내용을 한번에 화면에 출력하라
	/*	-Player를 id 오름차순으로 정렬하였을 때
		해당 id 포함 앞과 뒤 Player의 정보를 출력한다.
		id가 같은 Player가 둘 이상이면 이들의 정보를 모두 출력하여야 한다.

		- Player를 name 오름차순으로 정렬하였을 때
		해당 id 포함 앞과 뒤 Player의 정보를 출력한다.

		- Player를 score 오름차순으로 정렬하였을 때
		해당 id 포함 앞과 뒤 Player의 정보를 출력한다. * 프로그램은 4번 과정을 무한히 반복할 수 있어야 한다.*/

	int id;
	while (true)
	{
		std::cout << "ID를 입력해주세요: ";
		if (std::cin >> id)
		{
			clock_t start = clock();

			std::sort(arr.begin(), arr.end(), [](Player& a, Player& b) {return a.getId() < b.getId(); });
			auto firstPlayer = std::lower_bound(arr.begin(), arr.end(), id, [](const Player& a, int rhsId) { return a.getId() < rhsId; });
			auto lastPlayer = std::upper_bound(arr.begin(), arr.end(), id, [](int rhsId, const Player& a) { return a.getId() > rhsId; });
			if (firstPlayer->getId() == id)
			{
				std::cout << "==============================ID==============================" << std::endl;
				std::vector<Player> v;
				v.reserve(size_t(lastPlayer - firstPlayer));

				for (auto i = firstPlayer; i != lastPlayer; ++i)
				{
					printPlayer(i);
					v.push_back(*i);
				}

				std::cout << "==============================================================" << std::endl << std::endl;
				std::cout << "=============================Name=============================" << std::endl;
				std::sort(arr.begin(), arr.end(), [](Player& a, Player& b) {return a.getName() < b.getName(); });
				for (int i=0; i< v.size(); ++i)
				{
					firstPlayer = std::lower_bound(arr.begin(), arr.end(), v[i].getName(), [](const Player& a, std::string rhsName) { return a.getName() < rhsName; });
					lastPlayer = std::upper_bound(arr.begin(), arr.end(), v[i].getName(), [](std::string rhsName, const Player& a) { return a.getName() > rhsName; });
					for (auto p = firstPlayer; p != lastPlayer; ++p)
					{
						if (*p == v[i])
						{
							printPlayer(p);
							break;
						}
					}
				}
				std::cout << "==============================================================" << std::endl << std::endl;

				std::cout << "============================Score============================" << std::endl;
				std::sort(arr.begin(), arr.end(), [](Player& a, Player& b) {return a.getScore() < b.getScore(); });
				for (int i = 0; i < v.size(); ++i)
				{
					firstPlayer = std::lower_bound(arr.begin(), arr.end(), v[i].getScore(), [](const Player& a, int rhsScore) { return a.getScore() < rhsScore; });
					lastPlayer = std::upper_bound(arr.begin(), arr.end(), v[i].getScore(), [](int rhsScore, const Player& a) { return a.getScore() > rhsScore; });
					for (auto p = firstPlayer; p != lastPlayer; ++p)
					{
						if (*p == v[i])
						{
							printPlayer(p);
							break;
						}
					}
				}
				std::cout << "=============================================================" << std::endl << std::endl;

			}
			else
			{
				std::cout << "존재하지 않는 ID입니다." << std::endl;
				continue;
			}

			clock_t end = clock();
			double result = (double)(end - start);
			std::cout << "경과시간: " << ((result) / CLOCKS_PER_SEC) << " seconds" << std::endl;
		}
		else
			break;
	}
	
}