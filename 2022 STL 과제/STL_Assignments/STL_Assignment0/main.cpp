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
	std::ifstream in{ "2022 STL ���� ����", std::ios::binary };
	
	std::cout << sizeof(Player) << std::endl;

	// 1. ������ �о� ���� ������ ��ü�� ������ ������ ���� �������� ����϶�.
	Player tmp{};
	while (in >> tmp)
		plist.push_back(tmp);
	plist.back().print();

	// 2. ��� Player�� ���� ��հ��� ����Ͽ� ����϶�.
	long long sum = 0;
	for (const Player& i : plist)
		sum += i.getScore();
	std::cout << "��հ�: " << sum / 2'000'000 << std::endl;

	// 3. Ȯ���� �޸� ����Ʈ ���� 999�� Player ��ü�� ��� ã�� "����Ʈ �� 999"��� �̸��� ���Ͽ� �����϶�.
	std::ofstream out{ "����Ʈ �� 999", std::ios::binary };
	plist.sort([](Player& a, Player& b) {return a.getNum() < b.getNum(); });
	std::list<Player>::iterator targetPlayer = std::lower_bound(plist.begin(), plist.end(), 999, [](const Player& p, const size_t n) {return p.getNum() < n; });
	while (targetPlayer->getNum() == 999)
		(targetPlayer++)->write(out);

	// 4. id�� �Է¹޾� �����ϴ� id��� ���� ������ �ѹ��� ȭ�鿡 ����϶�
	/*	-Player�� id ������������ �����Ͽ��� ��
		�ش� id ���� �հ� �� Player�� ������ ����Ѵ�.
		id�� ���� Player�� �� �̻��̸� �̵��� ������ ��� ����Ͽ��� �Ѵ�. 

		- Player�� name ������������ �����Ͽ��� ��
		�ش� id ���� �հ� �� Player�� ������ ����Ѵ�. 

		- Player�� score ������������ �����Ͽ��� ��
		�ش� id ���� �հ� �� Player�� ������ ����Ѵ�. * ���α׷��� 4�� ������ ������ �ݺ��� �� �־�� �Ѵ�.*/
	int id;

	while (true)
	{
		std::cout << "ID�� �Է����ּ���: ";
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
				std::cout << "�������� �ʴ� ID�Դϴ�." << std::endl;
				continue;
			}
			clock_t end = clock();
			double result = (double)(end - start);
			std::cout << "����ð�: " << ((result) / CLOCKS_PER_SEC) << " seconds" << std::endl;
		}
		else
			break;
	}
	
}