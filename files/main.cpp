#include <iostream>
#include "game/game.h"
#include "save/save.h"
// заголовки находятся строго в files/game/game.h и files/save/save.h
int main() {

	// CheckAccount() это void, находящийся в save/save.cpp
	// эта функция проверяет, есть ли у пользователя "аккаунт", и создает новый если нет.
	// он делает это, считывая файл save/account.txt, если он пуст или его нет, то он просит игрока ввести имя и сохраняет аккаунт
	// к аккаунту привязано количество побед и поражений	

	int modeChoice = chooseOption(2, "Какой режим игры ты хочешь выбрать?\n1. Играть против человека\n2. Играть против бота", "Введи число!!!!!!", "введи от 1 до 2!!!");
	switch(modeChoice) {
		case 1:
			for (int i = 1; i < 3; i++) {
				std::cout << "Игрок " << i << ":" << std::endl;
				checkAccount(i);
			}
			vsPlayer();
			break;
		case 2:
			checkAccount(1);
			vsBot();
			break;	
	}
	// функции vsPlayer() и vsBot() -- это два void, находящиеся в game/game.cpp
	// vsPlayer() активирует игру против игрока, где каждый ход дается вариант поставить крестик или нолик вручную
	// vsBot() активирует игру против бота, где каждый ход нолики автоматически ставятся на случайную клетку
}
