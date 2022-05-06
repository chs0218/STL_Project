#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <list>
#include <time.h>
#include "Player.h"

std::list<Player> plist;

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


void printPlayer(const std::list<Player>::iterator& target);
void printPlayer(const std::list<Player>::iterator& target)
{
	int targetId = target->getId();
	std::list<Player>::iterator tmptarget = target;
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
	
	std::cout << sizeof(Player) << std::endl;

	// 1. 파일을 읽어 제일 마지막 객체의 정보를 다음과 같은 형식으로 출력하라.
	Player tmp{};
	while (in >> tmp)
		plist.push_back(tmp);
	plist.back().print();

	// 2. 모든 Player의 점수 평균값을 계산하여 출력하라.
	long long sum = 0;
	for (const Player& i : plist)
		sum += i.getScore();
	std::cout << "평균값: " << sum / 2'000'000 << std::endl;

	// 3. 확보한 메모리 바이트 수가 999인 Player 객체를 모두 찾아 "바이트 수 999"라는 이름인 파일에 복사하라.
	std::ofstream out{ "바이트 수 999", std::ios::binary };
	plist.sort([](Player& a, Player& b) {return a.getNum() < b.getNum(); });
	std::list<Player>::iterator targetPlayer = std::lower_bound(plist.begin(), plist.end(), 999, [](const Player& p, const size_t n) {return p.getNum() < n; });
	while (targetPlayer->getNum() == 999)
		(targetPlayer++)->write(out);

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
			plist.sort([](Player& a, Player& b) {return a.getId() < b.getId(); });
			targetPlayer = std::lower_bound(plist.begin(), plist.end(), id, [](const Player& p, const size_t n) {return p.getId() < n; });
			if (targetPlayer->getId() == id)
			{
				std::vector<std::list<Player>::iterator> vPlayer;
				vPlayer.reserve(5);
				while (targetPlayer->getId() == id)
					vPlayer.push_back((targetPlayer++));

				std::cout << "==============================ID==============================" << std::endl;
				for (const std::list<Player>::iterator& i : vPlayer)
					printPlayer(i);
				std::cout << "==============================================================" << std::endl << std::endl;

				plist.sort([](Player& a, Player& b) {return a.getName() < b.getName(); });
				std::cout << "=============================Name=============================" << std::endl;
				for (const std::list<Player>::iterator& i : vPlayer)
					printPlayer(i);
				std::cout << "==============================================================" << std::endl << std::endl;

				plist.sort([](Player& a, Player& b) {return a.getScore() < b.getScore(); });
				std::cout << "============================Score============================" << std::endl;
				for (const std::list<Player>::iterator& i : vPlayer)
					printPlayer(i);
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