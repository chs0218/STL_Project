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
	std::cout << "�̸�:" << name << ",\t���̵�:" << id << ",\t����:" << score << ",\t�ڿ���:" << num << std::endl;
}