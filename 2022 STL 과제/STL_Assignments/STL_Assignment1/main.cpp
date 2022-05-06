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
	std::ifstream in{ "2022 STL ���� ����", std::ios::binary };

	// 1. ������ �о� ���� ������ ��ü�� ������ ������ ���� �������� ����϶�.
	for (auto i = arr.begin(); i != arr.end(); ++i)
		i->read(in);
	arr.back().print();
	// 2. ��� Player�� ���� ��հ��� ����Ͽ� ����϶�.
	long long sum = 0;
	for (const Player& i : arr)
		sum += i.getScore();

	std::cout << sum / arr.size() << std::endl;
	// 3. Ȯ���� �޸� ����Ʈ ���� 999�� Player ��ü�� ��� ã�� "����Ʈ �� 999"��� �̸��� ���Ͽ� �����϶�.
	std::ofstream out{ "����Ʈ �� 999", std::ios::binary };
	for (auto i : arr)
		if (i.getNum() == 999)
			i.write(out);


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