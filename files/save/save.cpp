#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

// Функция позволяющая пользователю выбрать одну опцию (число) из нескольких с защийтой от дурака
// Исспользуется как-то так:
// int userChoise - переменная хранящая выбор пользователя
// userChoise = chooseOption(количество_опций, "Выберите опцию:\n1 - опция1\n2 - опция2...", "текст_ошибки_при_вводе_не_числа", "текст_ошибки_при_вводе_числа_вне_диапазона");
int chooseOption(int optionsAmount, std::string message, std::string error1, std::string error2) {
	int ans;
	bool err;
	do
	{
		err = false;
		std::cout << message << "\n";
		std::cin >> ans;
		if (std::cin.fail())
		{
			err = true;
			std::cin.clear();
			std::cout << "Error: " << error1 << "\n";
		}
		else if (1 <= ans && ans <= optionsAmount)
		{
			err = true;
			std::cout << "Error: " << error2 << "\n";
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (err);
	return ans;
}

std::string segment(std::string original, int begin, int end) {
	std::string result = "";
	for (int i = begin; i <= end; i++)
	{
		result += original[i];
	}
	return result;
}
std::string myReplace(std::string original, std::string repWhat, std::string repWith) {
	std::string changedString = "";
	int leftI = 0;
	int rightI = repWhat.size() - 1;
	while (rightI < original.size())
	{
		if (segment(original, leftI, rightI) == repWhat)
		{
			changedString += repWith;
			leftI += repWhat.size();
			rightI += repWhat.size();
		}
		else
		{
			changedString += original[leftI];
			leftI++;
			rightI++;
		}
	}
	changedString += segment(original, leftI, rightI);
	return changedString;
}

struct Account
{
	std::string name;
	int wins;
	int loses;
	int active;
};

void importAccounts(std::vector<Account>& accounts) {
	int err = 0;
	std::string line;
	std::string name;
	int wins;
	int loses;
	int active;
	Account tmpAccount;

	std::ifstream importFrom("account.txt");
	if (!importFrom)
	{
		std::cout << "Error: coud not open file!";
		return;
	}
	while (!importFrom.eof())
	{
		getline(importFrom, line);
		if (line != "")
		{
			std::istringstream sLine(line);
			sLine >> name >> wins >> loses >> active;
			if (!std::cin.fail());
			{
				tmpAccount.name = segment(myReplace(name, "|", " "), 0, name.size() - 1);
				tmpAccount.wins = wins;
				tmpAccount.loses = loses;
				tmpAccount.active = active;
				accounts.push_back(tmpAccount);
			}
		}
	}
	importFrom.close();
}

void saveAccounts(std::vector<Account>& accounts) {
	std::ofstream saveTo("account.txt");
	for (auto account : accounts) {
		saveTo << segment(myReplace(account.name, " ", "|"), 0, account.name.size() - 1) << " " << account.wins << " " << account.loses << " " << account.active << "\n";
	}
	saveTo.close();
}

bool accountExists(std::string userName) {
	std::vector<Account> accounts;
	importAccounts(accounts);
	for (const auto account : accounts)
		if (account.name == userName) return true;
	return false;
}

void setActivity(std::string userName, int mode) {
	std::vector<Account> accounts;
	importAccounts(accounts);
	for (auto& account : accounts)
		if (account.name == userName)
		{
			account.active = mode;
			break;
		}
	saveAccounts(accounts);
}

void resetActivity() {
	std::vector<Account> accounts;
	importAccounts(accounts);
	for (auto& account : accounts)
		account.active = 0;
	saveAccounts(accounts);
}

void resetActivity(int mode) {
	std::vector<Account> accounts;
	importAccounts(accounts);
	for (auto& account : accounts)
		if (account.active == mode)
			account.active = 0;
	saveAccounts(accounts);
}

void createAccount(std::string userName) {
	std::vector<Account> accounts;
	importAccounts(accounts);
	Account newAccount;
	newAccount.name = userName;
	newAccount.wins = 0;
	newAccount.loses = 0;
	newAccount.active = 0;
	accounts.push_back(newAccount);
	saveAccounts(accounts);
}

// Я пока не разобрался с кодировкой, поэтому на английском
std::string enterNameEn() {
	std::string name;
	do
	{
		std::cout << "Enter your name:"; //Введите имя:
		getline(std::cin, name);
		if (name == "") std::cout << "Error: Name can't be epty!\n"; //Ошибка: Имя должно содержать символы!\n
		else if (name == "bot") std::cout << "Error: Name can't be \"bot\"!\n"; //Ошибка: Имя не может быть \"bot\"!\n
	} while (name == "" || name == "bot");
	return name;
}

std::string enterName() {
	std::string name;
	do
	{
		std::cout << "Введите имя:";
		getline(std::cin, name);
		if (name == "") std::cout << "Ошибка: Имя должно содержать символы!\n";
		else if (name == "bot") std::cout << "Ошибка: Имя не может быть \"bot\"!\n";
	} while (name == "" || name == "bot");
	return name;
}

// Эта функция проверяет, есть ли у пользователя "аккаунт", и создает новый если нет
// В параметрах указывается 1 - для основного игрока и 2 - для второго
void checkAccount(int mode) {
	std::string name;
	resetActivity(mode);
	name = enterName();

	if (accountExists(name))
	{
		setActivity(name, mode);
	}
	else
	{
		createAccount(name);
		setActivity(name, mode);
	}
}

// Эта функця прибавляет победу осному игроку и поражене второму (вызывается если первый победил)
void winPoint() {
	std::vector<Account> accounts;
	importAccounts(accounts);
	for (auto& account : accounts)
	{
		if (account.active == 1) account.wins++;
		if (account.active == 2) account.loses++;
	}
	saveAccounts(accounts);
}
// А эта наоборот
void losePoint() {
	std::vector<Account> accounts;
	importAccounts(accounts);
	for (auto& account : accounts)
	{
		if (account.active == 1) account.loses++;
		if (account.active == 2) account.wins++;
	}
	saveAccounts(accounts);
}

// Возвращает имя игрока: Если указать 1 - вернёт имя главного, если 2 - второго
std::string playerName(int mode) {
	std::vector<Account> accounts;
	importAccounts(accounts);
	for (auto account : accounts)
		if (account.active == mode) return account.name;
}