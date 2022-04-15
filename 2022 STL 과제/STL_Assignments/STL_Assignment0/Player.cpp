#include "Player.h"
Player::Player() {
}
Player::~Player(){
}

void Player::write(std::ostream& os) {
	os.write((char*)this, sizeof(Player));
	os.write((char*)p, num);
}

void Player::read(std::istream& is) {
	is.read((char*)this, sizeof(Player));
	p = new char[num];
	is.read((char*)p, num);
}

void Player::print() {
	std::cout << "이름:" << name << ",\t아이디:" << id << ",\t점수:" << score << ",\t자원수:" << num << std::endl;
}