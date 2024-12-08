﻿#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
//Тест
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
		saveTo << myReplace(account.name, " ", "|") << " " << account.wins << " " << account.loses << " " << account.active << "\n";
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