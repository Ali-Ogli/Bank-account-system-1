#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>
#include <memory>
#include <regex>
#include <fstream>

// try to store the infos in .txt file and reopen them!

using text = std::string;

std::vector<text> names = { "Amelia", "Charlotte", "Eleanor", "Everly", "Grace", "Harper", "Isla", "Lily", "Maeve", "Mia", "Nora", "Olivia", "Sophia", "Violet" };

class Account {
	std::vector<text> History;


	text firstName;
	text lastName;
	text password;

	int ID{0};

	double money;
	double debt;

	bool locked;
public:
	Account() = delete;
	//Account();
	~Account() = default;
	Account(double mon, text fn, text ln, text p): money(mon), firstName(fn), lastName(ln), password(p){
		locked = true;
		debt = 0;
		ID = (rand() % 999) + 1;
	}


	// Methods

	void accountMenu() {
		
		std::cout << "Please ensure that you are the owner: \n";

		checkSecurity();
		
		if (locked) {
			std::cout << "Access denied\n";
			return;
		}

		std::cout << "\n=============:::=============\n";

		int choose{0};
		std::cout << "Welcome " << firstName << ". What you like to do now?:\n";


		while (true) {
			std::cout << "Debosit 1\nWithdraw 2\nCheck balance 3\nTo exit please enter 0\n";
			std::cin >> choose;
			switch (choose) {
			case 0:
				return;
				break;
			case 1:
				Deposit();
				break;
			case 2:
				Withdraw();
				break;
			case 3:
				std::cout << "Your current balance is " << money << "$\n";
				break;
			default:
				break;
			}

		}
		std::cout << "\n=============:::=============\n";
	}

	double Withdraw() {
		double w;

		std::cout << "\nHow much you like to withdraw: ";
		std::cin >> w;

		if (w < 5) {
			std::cout << "You can only Withdraw 5 or more!\n";
			return 0;
		}
		else if (w > money) {
			std::cout << "You don't have this amont of money!\n";
			return 0;
		}
		money -= w;
		return w;
	}

	void Deposit() {
		double w;
		std::cout << "\nHow much you like to deposit : ";
		std::cin >> w;
		if (w > 0) {
			money += w;
		}
		else {
			std::cout << "You can't deposit less than 5$\n";
		}

	}

	void checkSecurity() {
		text name;
		text pass;

		bool check[2] = { true, true };

		std::cout << "\n=============INFOS=============\n";

		std::cout << firstName << std::endl;
		std::cout << password << std::endl;


		std::cout << "Welcome, Please enter your first name and password.\n";
		std::cout << "Name: ";

		std::cin >> name;
		name.at(0) = tolower(name.at(0));

		if (firstName.size() != name.size()) {
			std::cout << "The name is not found!\n";
			check[0] = false;
			return;
				
		}
			
		std::cout << "Password: ";

		std::cin >> pass;


		if (password.size() != pass.size()) {
			std::cout << "The password is not correct!\n";
			check[0] = false;
			return;
				
		}



		for (int i = 0; i < name.size(); i++) {
			if (firstName.at(i) == name.at(i))
				continue;
			else
			{
				check[0] = false;
				break;
			}
		}

		for (int i = 0; i < pass.size(); i++) {
			if (password.at(i) == pass.at(i))
				continue;
			else
			{
				check[1] = false;
				break;
			}
		}

		if (check[0]) {
			std::cout << "Name is correct!\n";
			if (check[1]) {
				std::cout << "Password is correct!\n";
			}
			else {
				std::cout << "Password is wrong!\n";
			}
		}
		else {
			std::cout << "Name not found\n";
			
		}

		//std::cout << "name " << check[0] << ", pass " << check[1] << std::endl;

		locked = check[0] && check[1] ? false : true;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}


	// Setters

	void setMoney(int amont) {
		money = amont;
	}
	void setDebt(int amont) {
		debt = amont;
	}
	



	// Getters

	double getMoney() const {
		return money;
	}

	double getDebt() const {
		return debt;
	}

	text getName() const {
		return firstName;
	}

	int getID() const {
		return ID;
	}

	text getPass() const {
		return password;
	}
};

class Bank {
	std::vector<std::shared_ptr<Account>> accounts;
	static int account_count;
	text name;

	text Fname = "save_file.txt";
	std::fstream save_file;
	

	char choice{'x'};
public:
	Bank(text nam): name(nam){
		
	}

	void saveInfos() {



		save_file.open(Fname, std::ios::out);

		text orLine = "Account counted : " + std::to_string(account_count);

		save_file << orLine << '\n';

		
		//save_file.close();



		//save_file.open(Fname, std::ios::app);
		
		if (save_file.is_open()) {

			for (int i = 0; i < accounts.size(); i++) {
					save_file << "\n========================\n";
					save_file << "Account name		:  " << accounts.at(i)->getName() << std::endl;
					save_file << "Account ID		:  " << accounts.at(i)->getID() << "\n";
					save_file << "Account balance	:  " << accounts.at(i)->getMoney() << "$\n";
					save_file << "Account debt		:  " << accounts.at(i)->getDebt() << "\n";
					save_file << "Account password	:  " << accounts.at(i)->getPass() << "\n";
					save_file << "\n========================\n";
			}
		}



		save_file.close();

	}

	void greeting() {
		std::cout << "Welcome to " << name << " Bank!\n";
	}


	void createAccount(text& firstName, text& secondName) {
		text fname;
		text lname;
		text pass;
		double dep{0};



		if (firstName.empty()) {

			std::cout << "Would you like to create accout?: y, n\n";
			std::cin >> choice;
			choice = tolower(choice);
			if (choice == 'n')
				return;
			std::cout << "Please enter your first name: ";
			std::cin >> fname;
			std::cout << "Please enter your last name: ";
			std::cin >> lname;
		
			std::cout << "Please enter password: ";
			std::cin >> pass;
		
			while (dep < 25) {
				std::cout << "To create the account you should deposit at least 25$: ";
				std::cin >> dep;
			}
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		}
		else {
			fname = firstName;
			lname = secondName;
			pass = "1234";
			int num = std::rand() % 500;
			dep = num < 25 ? 25 : (rand() % 500) + 25;
		}
		std::cout << "The account has been created for Mr." << fname << " " << lname << ", with " << dep << "$\n";

		fname.at(0) = tolower(fname.at(0));
		lname.at(0) = tolower(lname.at(0));


		account_count++;
		//Account* acc = new Account(dep, fname, lname, pass);
		//accounts.push_back(std::make_unique<Account>(dep, fname, lname, pass));
		std::shared_ptr<Account> acc = std::make_shared<Account>(dep, fname, lname, pass);
		accounts.push_back(acc);
		saveInfos();
	}

	void ChooseAccount() {
		if (accounts.empty()) {
			std::cout << "No accounts to view!\n";
			return;
		}

		int chos{0};

		std::cout << "The bank has " << account_count << " accounts in total!\n";

		for (int i = 0; i < account_count; i++) {
			std::cout << accounts.at(i)->getName() << '[' << i + 1 << "] : " << accounts.at(i)->getID() << std::endl;
		}

		//std::cout << "Choose account to login to or 0 to get out.\n";
		//std::cin >> chos;

		while (true) {
			std::cout << "Choose account to login to or 0 to get out.\n";
			std::cin >> chos;
			if (chos == 0) {
				std::cout << "Get out!\n";
				return;
			}
			else if (chos > accounts.size()) {
				std::cout << "Indix out of bound!\n";
			}
			else if (chos < 0) {
				std::cout << "Indix out of bound!\n";
			}
			else
				break;
		}


		chos -= 1;


		accounts.at(chos)->accountMenu();

	}
	~Bank() {}
};


int Bank::account_count = 0;



int main() {




	Bank TurosoBank("Turoso Bank");

	TurosoBank.createAccount(names.at((rand() % names.size()) - 1), names.at((rand() % names.size()) - 1));

	for (int i = 0; i < 5; i++) {
		
		TurosoBank.createAccount(names.at((rand() % names.size())), names.at((rand() % names.size())));
		/*names.at((rand() % names.size()) - 1)*/;
			
	}

	return 0;
}
