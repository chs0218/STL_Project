#include "Player.h"
Player::Player() 
{
	// std::cout << "�⺻������"<<std::endl;
}

Player::~Player()
{
	delete[] p;
}

Player::Player(const Player& other) 
{
	name = other.name;
	score = other.score;
	id = other.id;
	num = other.num;
	p = new char[num];
	memcpy(p, other.p, num);
	 //std::cout << this << " �������\n";
}

Player& Player::operator=(const Player& other) 
{
	if (this == &other)
		return *this;
	if (num)
		delete[] p;

	name = other.name;
	score = other.score;
	id = other.id;
	num = other.num;
	p = new char[num];
	memcpy(p, other.p, num);

	 std::cout << this << " �����Ҵ�";
	return *this;
}

Player::Player(Player&& other) noexcept 
{
	name = other.name;
	score = other.score;
	id = other.id;
	num = other.num;
	p = other.p;

	other.p = nullptr;
	other.num = 0;
	other.name = "";
	other.score = 0;
	other.id = 0;

	 //std::cout << this << " �̵�����\n";
}

Player& Player::operator=(Player&& other) noexcept 
{
	if (this != &other)
	{
		if (num)
			delete[] p;

		name = other.name;
		score = other.score;
		id = other.id;
		num = other.num;
		p = other.p;

		other.num = 0;
		other.name = "";
		other.score = 0;
		other.id = 0;
		other.p = nullptr;
	}
	//std::cout << this << " �̵��Ҵ�\n";
	return *this;
}

void Player::write(std::ostream& os) 
{
	os.write((char*)this, sizeof(Player));
	os.write((char*)p, num);
}

void Player::read(std::istream& is) 
{
	is.read((char*)this, sizeof(Player));
	p = new char[num];
	is.read((char*)p, num);
}

void Player::print() const
{
	std::cout << this << " �̸�:" << name << ",\t���̵�:" << id << ",\t����:" << score << ",\t�ڿ���:" << num << std::endl;
}

std::string Player::getName() const 
{
	return name;
}

int Player::getId() const 
{
	return id;
}

int Player::getScore() const
{
	return score;
}

size_t Player::getNum() const
{
	return num;
}