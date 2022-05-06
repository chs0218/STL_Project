#include "Player.h"
Player::Player() 
{
	// std::cout << "기본생성자"<<std::endl;
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
	 //std::cout << this << " 복사생성\n";
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

	std::cout << this << " 복사할당";
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
	std::cout << this << " 이름:" << name << ",\t아이디:" << id << ",\t점수:" << score << ",\t자원수:" << num << std::endl;
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