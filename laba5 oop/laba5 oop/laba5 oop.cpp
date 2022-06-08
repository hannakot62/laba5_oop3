//Разработать набор классов : город(наименование, количество
//	жителей), магазин(наименование, тип), товар(наименование, сорт,
//		количество, цена), банк(номер счета, сумма денег на счете), покупатель
//		(фамилия, сумма денег, сумма покупки).Определить и реализовать связи
//	между этими классами.Класс «Покупатель» содержит методы выполнения
//	различных операций покупателя с товаром, приобретаемым в магазине и
//	оплачиваемом через банк.Использовать конструктор с параметрами,
//	конструктор без параметров, конструктор копирования.В класс добавить
//	необходимый набор полей и методов(минимум два поля и два метода) на
//	свое усмотрение.Предусмотреть метод для записи полученных данных в
//	файл.


#include <iostream>
#include <iomanip>
#include <windows.h>
#include <string.h>
#include <fstream>
using namespace std;

class Item {
private:
	string name;
	string sort;
	float quantity;
	int price;
public:
	Item() {
		name = "Яблоко";
		sort = "Карамелька";
		quantity = 50;
		price = 1;
	};
	Item(string name, string sort, float quantity, int price) {
		this->name = name;
		this->sort = sort;
		this->quantity = quantity;
		this->price = price; 
	};

	string GetName() {
		return name;
	};
	string GetSort() {
		return sort;
	};
	float GetQuantity() {
		return quantity;
	};
	int GetPrice() {
		return price;
	};
	//~Item() {};

	void BuyItem(int quantity) {
		if (this->quantity > quantity) {
			this->quantity = this->quantity - quantity;
			cout << "Покупатель приобрел товар -" << name << "-" << endl;
		}
	};

	//void ReturnItem(int quantity) {
	//	this->quantity = this->quantity + quantity;
	//	cout << "Товар -" << name << "- возвращен" << endl;
	//}

	void operator=(Item& newItem) {
		name = newItem.name;
		sort = newItem.sort;
		quantity = newItem.quantity;
		price = newItem.price;
	}
};

class Shop {
private:
	string name;
	string type;
	Item* items;
	int ItemsQuantity;
public:
	Shop() {
		name = "Доброном";
		type = "Универсам";
		ItemsQuantity = 2;
		items = new Item[ItemsQuantity];
	}
	Shop(string name, string type, int ItemsQuantity) {
		this->name = name;
		this->type = type;
		this->ItemsQuantity = ItemsQuantity;
		items = new Item[ItemsQuantity];
		string iname, sort;
		float quantity;
		int price;
		for (int i = 0; i < ItemsQuantity; i++) {
			cout << "Введите название товара" << endl;
			cin >> iname;
			cout << "Введите сорт товара" << endl;
			cin >> sort;
			cout << "Введите количество товара" << endl;
			cin >> quantity;
			cout << "Введите цену товара" << endl;
			cin >> price;
			Item n(iname, sort, quantity, price);
			items[i] = n;
		}
	}
	string GetName() { return name; }
	string GetType() { return type; }
	int GetItemsQuantity() { return ItemsQuantity; }

	void ShowItems() {
		cout << endl;
		for (int i = 0; i < ItemsQuantity; i++) {
			cout << i + 1 << endl;
			cout << "Товар: " << items[i].GetName() << endl;
			cout << "Сорт: " << items[i].GetSort() << endl;
			cout << "Количество: " << items[i].GetQuantity() << endl;
			cout << "Цена: " << items[i].GetPrice() << endl;
			cout << endl;
		}
	}

	//~Shop() {
	//	delete items;
	//}

	int ChooseItem() {
		int num;
		cout << "Введите номер товара" << endl;
		cin >> num;
		if (num > 0 && num <= ItemsQuantity) {
			return num - 1;
		}
		else {
			cout << "Такого товара нет" << endl;
			return -1;
		}
	}

	Item* GetItem(int choise) {
		return (&items[choise]);
	}
	void BuyItem(Item& item, int quantity) {
		item.BuyItem(quantity);
	}


	void AddItem() {
		Item* items1;
		int itemsQuantity1 = ItemsQuantity + 1;
		items1 = new Item[itemsQuantity1];

		string name;
		string sort;
		float quantity;
		int price;

		cout << "Введите название товара" << endl;
		cin >> name;
		cout << "Введите сорт товара" << endl;
		cin >> sort;
		cout << "Введите количетво товара" << endl;
		cin >> quantity;
		cout << "Введите цену" << endl;
		cin >> price;

		int i = 0;
		for (; i < ItemsQuantity; i++) {
			items1[i] = items[i];
		}
		Item n(name, sort, quantity, price);
		items1[i] = n;

		ItemsQuantity = itemsQuantity1;
		items = new Item[ItemsQuantity];
		i = 0;
		for (; i < ItemsQuantity; i++) {
			items[i]=items1[i];
		}
	}
};

class Customer {
protected:
	string surname;
	int money;
public:
	int purchaseMoney;
	Customer() {
		surname = "Котягова";
		money = 1000;
		purchaseMoney = 0;
	}
	Customer(string surname, int money) {
		this->surname = surname;
		this->money = money;
		purchaseMoney = 0;
	}
	Customer(const Customer& cus) {
		this->surname = cus.surname;
		this->money = cus.money;
		this->purchaseMoney = cus.purchaseMoney;
	}
	string GetSurname() { return surname; }
	int GetMoney() { return money; }
	void SetSurname(string surname) { this->surname = surname; }

	void SaveTransaction(Item& item, int itQuantity) {
		ofstream out;          // поток для записи
		string file = "transactions.txt";
		out.open(file, ios::app); // окрываем файл для записи
		if (out.is_open())
		{
			out << surname << "-" << item.GetName() << "-" << itQuantity << "-" << purchaseMoney << endl;
		}
		else {
			cout << "Error" << endl;
		}
		out.close();
	}

	virtual void BuyItem(Item& item, int quantity) {
		int price = item.GetPrice();
		if (money > quantity * price) {
			if (item.GetQuantity() >= quantity) {
				item.BuyItem(quantity);
				purchaseMoney = quantity * price;
				money = money - purchaseMoney;
				SaveTransaction(item, quantity);
			}
			else {
				cout << "Недостаточно товара" << endl;
			}
		}
		else {
			cout << "Недостаточно средств" << endl;
		}
	}

	void operator=(Customer& newCus) {
		surname = newCus.surname;
		money = newCus.money;
		purchaseMoney = newCus.purchaseMoney;
	}

	virtual void GetInfo() {
		cout << "Фамилия: " << surname << endl;
		cout << "Количество денег: " << money << endl;
	}
};

class BankAccount : public Customer {
private:
	 string accountNumber;
public:
	BankAccount() {
		surname = "Петрович";
		money = 1000;
		purchaseMoney = 0;
		accountNumber = "072304";
	}
	BankAccount(string surname, int money, string accountNumber) {
		this->surname = surname;
		this->money = money;
		this->accountNumber = accountNumber;
		purchaseMoney = 0;
	}
	string GetAccountNumber() { return accountNumber; }
	//~BankAccount(){}

	void BuyItem(Item& item, int quantity) override {
		int price = item.GetPrice();
		if (money > quantity * price) {
			if (item.GetQuantity() >= quantity) {
				item.BuyItem(quantity);
				purchaseMoney = quantity * price;
				money = money - purchaseMoney;
				cout << "Покупка совершена через банк" << endl;
				SaveTransaction(item, quantity);
			}
			else {
				cout << "Недостаточно товара" << endl;
			}
		}
		else {
			cout << "Недостаточно средств" << endl;
		}
	}

	void operator=(BankAccount& newCus) {
		Customer::operator=(newCus);
		accountNumber = newCus.accountNumber;
	}

	void GetInfo() override {
		cout << "Фамилия: " << surname << endl;
		cout << "Номер счета: " << accountNumber << endl;
		cout << "Количество денег на счете: " << money << endl;
	}

};

class Bank {
private:
	string name;
	BankAccount* accounts;
	int accountsQuantity;
public:
	Bank() {
		name = "Нарочанский";
		accountsQuantity = 2;
		accounts = new BankAccount[accountsQuantity];
		BankAccount n;
		accounts[0] = n;
		BankAccount m("Захаревич", 980, "010133");
		accounts[1] = m;
	}
	Bank(string name, int accountsQuantity) {
		this->name = name;
		this->accountsQuantity = accountsQuantity;
		accounts = new BankAccount[accountsQuantity];
		string surname, accNum;
		int money;
		for (int i = 0; i < accountsQuantity; i++) {
			cout << "Введите фамилию" << endl;
			cin >> surname;
			cout << "Введите количество денег на счете" << endl;
			cin >> money;
			cout << "Введите номер счета" << endl;
			cin >> accNum;
			BankAccount n(surname, money, accNum);
			accounts[i] = n;
		}
	}
	void GetBankInfo() {
		cout << "Название банка: " << name << endl;
		cout << "Количество клиентов: " << accountsQuantity << endl;
	}
	string GetName() { return name; }
	int GetAccountsQuantity() { return accountsQuantity; }
	void ShowCustomers() {
		for (int i = 0; i < accountsQuantity; i++) {
			cout << i + 1 << ". ";
			accounts[i].GetInfo();
			cout << endl;
		}
	}
	//~Bank() {
	//	delete accounts;
	//}

	void AddAccount(Customer customer) {
		BankAccount* accounts1;
		int accountsQuantity1 = accountsQuantity + 1;
		accounts1 = new BankAccount[accountsQuantity1];
		string surname1 = customer.GetSurname();
		cout << surname1 << endl;
		int money = customer.GetMoney();
		string accountNumber;
		cout << "Введите номер счета: " << endl;
		cin >> accountNumber;

		int i = 0;
		for (; i < accountsQuantity; i++) {
			accounts1[i] = accounts[i];
		}
		BankAccount n(surname1, money, accountNumber);
		accounts1[i] = n;

		accountsQuantity = accountsQuantity1;
		accounts = new BankAccount[accountsQuantity];
		i = 0;
		for (; i < accountsQuantity; i++) {
			accounts[i] = accounts1[i];
		}
	}

	int ChooseAccount() {
		int num;
		cout << "Введите номер аккаунта:" << endl;
		cin >> num;
		if (num > 0 && num <= accountsQuantity) {
			return num - 1;
		}
		else {
			cout << "Такого аккаунта не существует" << endl;
			return -1;
		}
	}
	BankAccount* GetAccount(int choise) {
		return (&accounts[choise]);
	}
};


class City {
private:
	string name;
	int UsualCustomersQuantity;
	Customer* customers;
	Shop* shops;
	int shopsQuantity;
	Bank* banks;
	int banksQuantity;
public:
	City() {
		name = "Минск";
		UsualCustomersQuantity = 1;
		customers = new Customer[UsualCustomersQuantity];
		shopsQuantity = 1;
		shops = new Shop[shopsQuantity];
		banksQuantity = 1;
		banks = new Bank[banksQuantity];
	}
	int GetBankAccountsQuantity() {
		int num = 0;
		for (int i = 0; i < banksQuantity; i++) {
			num += banks[i].GetAccountsQuantity();
		}
		return num;
	}
	int GetCitizensQuantity() { return UsualCustomersQuantity + GetBankAccountsQuantity(); }
	int GetBanksQuantity() { return banksQuantity; }
	int GetShopsQuantity() { return shopsQuantity; }
	void ShowUsualCustomers() {
		cout << endl;
		if (UsualCustomersQuantity == 0) { cout << "В городе нет покупателей без аккаунта в банке" << endl; }
		else {
			cout << "Покупатели без аккаунта в банке:" << endl << endl;
			for (int i = 0; i < UsualCustomersQuantity; i++) {
				cout << i + 1 << endl;
				cout << "Фамилия: " << customers[i].GetSurname() << endl;
				cout << "Бюджет: " << customers[i].GetMoney() << endl;
				cout << endl;
			}
		}
	}
	int ChooseUsualCustomer() {
		int num;
		cout << "Введите номер покупателя по порядку:" << endl;
		cin >> num;
		if (num > 0 && num <= UsualCustomersQuantity) {
			return num - 1;
		}
		else {
			cout << "Такого покупателя нет" << endl;
			return -1;
		}
	}
	Customer* GetUsualCustomer(int choise) {
		return (&customers[choise]);
	}

	void ShowShops() {
		cout << endl;
		if (shopsQuantity == 0) { cout << "В городе нет магазинов" << endl; }
		else {
			cout << "Магазины города:" << endl << endl;
			for (int i = 0; i < shopsQuantity; i++) { 
				cout << i + 1 << endl;
				cout << "Название магазина: " << shops[i].GetName() << endl;
				cout << "Тип: " << shops[i].GetType() << endl;
				cout << "Количество товаров: " << shops[i].GetItemsQuantity() << endl;
				cout << endl;
			}
		}
	}
	int ChooseShop() {
		int num;
		cout << "Введите номер магазина" << endl;
		cin >> num;
		if (num > 0 && num <= shopsQuantity) {
			return num - 1;
		}
		else {
			cout << "Такого магазина нет" << endl;
			return -1;
		}
	}
	Shop* GetShop(int choise) {
		return (&shops[choise]);
	}
	
	void ShowBanks() {
		cout << endl;
		if (banksQuantity == 0) { cout << "В городе нет банков" << endl; }
		else {
			cout << "Банки города:" << endl << endl;
			for (int i = 0; i < banksQuantity; i++) { // название тип количество
				cout << i + 1 << endl;
				cout << "Название банка: " << banks[i].GetName() << endl;
				cout << "Количество клиентов: " << banks[i].GetAccountsQuantity() << endl;
				cout << endl;
			}
		}
	}
	int ChooseBank() {
		int num;
		cout << "Введите номер банка" << endl;
		cin >> num;
		if (num > 0 && num <= banksQuantity) {
			return num - 1;
		}
		else {
			cout << "Такого банка нет" << endl;
			return -1;
		}
	}
	Bank* GetBank(int choise) {
		return (&banks[choise]);
	}
	void GetCityInfo() {
		cout << "Город: " << name << endl;
		cout << "Количество жителей: " << GetCitizensQuantity() << endl;
		cout << "Количество банков: " << banksQuantity << endl;
		cout << "Количество магазинов: " << shopsQuantity << endl;
	}
	

	Customer DeleteUsualCustomer(int choise) {
		int i = 0, k = 0;
		Customer* customers1 = new Customer[UsualCustomersQuantity];
		for (; i < UsualCustomersQuantity; i++) {
			if (i != choise) {
				customers1[k] = customers[i];
				k++;
			}
		}
		Customer deleted (customers[choise]);
		UsualCustomersQuantity = UsualCustomersQuantity - 1;
		customers = new Customer[UsualCustomersQuantity];
		i = 0;
		for (; i < UsualCustomersQuantity; i++) {
			customers[i] = customers1[i];
		}
		//cout << deleted.GetSurname() << " del" << endl; //здесь есть фамилия!
		return deleted;
	}

	void AddShop() {
		Shop* shops1;
		int shopsQuantity1 = shopsQuantity + 1;
		shops1 = new Shop[shopsQuantity1];

		string name;
		string type;
		int itemsQuantity;

		cout << "Введите название магазина:" << endl;
		cin >> name;
		cout << "Введите тип магазина:" << endl;
		cin >> type;
		cout << "Введите количество товаров:" << endl;
		cin >> itemsQuantity;

		int i = 0;
		for (; i < shopsQuantity; i++) {
			shops1[i] = shops[i];
		}
		Shop n(name, type, itemsQuantity);
		shops1[i] = n;

		shopsQuantity = shopsQuantity1;
		shops = new Shop[shopsQuantity1];
		i = 0;
		for (; i < shopsQuantity; i++) {
			shops[i] = shops1[i];
		}
	}
	void AddBank() {
		Bank* banks1;
		int banksQuantity1 = banksQuantity + 1;
		banks1 = new Bank[banksQuantity1];

		string name;
		int accountsQuantity;

		cout << "Введите название банка:" << endl;
		cin >> name;
		cout << "Введите количество клиентов:" << endl;
		cin >> accountsQuantity;

		int i = 0;
		for (; i < banksQuantity; i++) {
			banks1[i] = banks[i];
		}
		Bank n(name, accountsQuantity);
		banks1[i] = n;

		banksQuantity = banksQuantity1;
		banks = new Bank[banksQuantity1];
		i = 0;
		for (; i < banksQuantity; i++) {
			banks[i] = banks1[i];
		}
	}
	void AddUsualCustomer(){
		Customer* customers1;
		int customerQuantity1 = UsualCustomersQuantity + 1;
		customers1 = new Customer[customerQuantity1];

		string surname;
		int money;

		cout << "Введите фамилию покупателя:" << endl;
		cin >> surname;
		cout << "Введите бюджет покупателя:" << endl;
		cin >> money;

		int i = 0;
		for (; i < UsualCustomersQuantity; i++) {
			customers1[i] = customers[i];
		}
		Customer n(surname, money);
		customers1[i] = n;

		UsualCustomersQuantity = customerQuantity1;
		customers = new Customer[customerQuantity1];
		i = 0;
		for (; i < UsualCustomersQuantity; i++) {
			customers[i] = customers1[i];
		}
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BankMenu(Bank& bank, City& city) {
	int menu = 0;
	int cycle = 1;
	while (cycle) {
		cout << "Выберите необходимое действие:" << endl;
		cout << "1. Вывести список аккаунтов" << endl;
		cout << "2. Добавить аккаунт" << endl;
		cout << "3. Выйти" << endl;
		cin >> menu;
		switch (menu) {
		case 1: {
			bank.GetBankInfo();
			cout << endl;
			bank.ShowCustomers();
			break;
		}
		case 2: {
			city.ShowUsualCustomers();
			int choise = city.ChooseUsualCustomer();
			if (choise >= 0) {
				bank.AddAccount(city.DeleteUsualCustomer(choise));
			}
			break;
		}
		case 3: {
			cycle = 0;
			break;
		}
		default: {
			cout << "Некорректный ввод" << endl;
			break;
		}
		}
	}
}

void ShopMenu(Shop& shop) {
	int menu = 0;
	int cycle = 1;
	while (cycle) {
		cout << "Выберите необходимое действие:" << endl;
		cout << "1. Вывести список товаров" << endl;
		cout << "2. Добавить товар" << endl;
		cout << "3. Выйти" << endl;
		cin >> menu;
		switch (menu) {
		case 1: {
			shop.ShowItems();
			break;
		}
		case 2: {
			shop.AddItem();
			break;
		}
		case 3: {
			cycle = 0;
			break;
		}
		default: {
			cout << "Некорректный ввод" << endl;
			break;
		}
		}
	}
}

void Transaction(City& city) {
	cout << "Для какого пользователя совершается покупка?" << endl;
	cout << "1. Пользователь банка" << endl;
	cout << "2. Покупатель без аккаунта в банке" << endl;
	int menu = 0;
	cin >> menu;
	switch (menu) {
	case 1: {
		city.ShowBanks();
		cout << "Выберите банк:" << endl;
		int bank = city.ChooseBank();
		if (bank >= 0) {
			city.GetBank(bank)->ShowCustomers();
			cout << "Выберите клиента:" << endl;
			int acc = city.GetBank(bank)->ChooseAccount();////////////////////////////////////////////////////////////////////////////////////////
			if (acc >= 0) {
				cout << "Выберите магазин:" << endl;
				city.ShowShops();
				int shop = city.ChooseShop();
				if (shop >= 0) {
					cout << "Выберите товар:" << endl;
					city.GetShop(shop)->ShowItems();
					int it = city.GetShop(shop)->ChooseItem();
					if (it >= 0) {
						//этот товар мы хотим купить
						city.GetShop(shop)->GetItem(it);
						int quantity;
						cout << "Введите количество товара: ";
						cin >> quantity;
						city.GetBank(bank)->GetAccount(acc)->BuyItem(*city.GetShop(shop)->GetItem(it), quantity);
					}
				}
			}
		}
		break;
	}
	case 2: {
		city.ShowUsualCustomers();
		cout << "Выберите покупателя:" << endl;
		int cus = city.ChooseUsualCustomer();
		if (cus >= 0) {
			cout << "Выберите магазин:" << endl;
			city.ShowShops();
			int shop = city.ChooseShop();
			if (shop >= 0) {
				cout << "Выберите товар:" << endl;
				city.GetShop(shop)->ShowItems();
				int it = city.GetShop(shop)->ChooseItem();
				if (it >= 0) {
					//этот товар мы хотим купить
					city.GetShop(shop)->GetItem(it);
					int quantity;
					cout << "Введите количество товара: ";
					cin >> quantity;
					city.GetUsualCustomer(cus)->BuyItem(*city.GetShop(shop)->GetItem(it), quantity);
				}
			}
		}
		break;
	}
	default: {
		cout << "Некорректный ввод" << endl;
		break;
	}
	}
}

void CityMenu(City& city) {
	int menu = 0;
	int cycle = 1;
	while (cycle) {
		cout << "Выберите необходимое действие:" << endl;
		cout << "1. Вывести информацию о городе" << endl;
		cout << "2. Работа с выбранным магазином" << endl;
		cout << "3. Работа с выбранным банком " << endl;
		cout << "4. Добавить магазин" << endl;
		cout << "5. Добавить банк " << endl;
		cout << "6. Добавить обычного покупателя" << endl;
		cout << "7. Вывести информацию о покупателях" << endl;
		cout << "8. Совершить покупку для определенного покупателя" << endl;
		cout << "9. Выйти" << endl;
		cin >> menu;
		switch (menu) {
		case 1: {
			city.GetCityInfo();
			city.ShowBanks();
			city.ShowShops();
			break;
		}
		case 2: {
			city.ShowShops();
			int choise = city.ChooseShop();
			if (choise >= 0) {
				ShopMenu(*city.GetShop(choise));
			}
			break;
		}
		case 3: {
			city.ShowBanks();
			int choise = city.ChooseBank();
			if (choise >= 0) {
				BankMenu(*city.GetBank(choise), city);
			}
			break;
		}
		case 4: {
			city.AddShop();
			break;
		}
		case 5: {
			city.AddBank();
			break;
		}
		case 6: {
			city.AddUsualCustomer();
			break;
		}
		case 7: {
			for (int i = 0; i < city.GetBanksQuantity(); i++) {
				city.GetBank(i)->ShowCustomers();
			}
			city.ShowUsualCustomers();
			break;
		}
		case 8: {
			Transaction(city);
			break;
		}
		case 9: {
			cycle = 0;
			break;
		}
		default: {
			cout << "Некорректный ввод" << endl;
			break;
		}
		}
	}
};

	int main() {
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		City city1;
		int menu = 0;
		int cycle = 1;
		while (cycle) {
			cout << "Выберите необходимое действие:" << endl;
			cout << "1. Работа с городом по умолчанию" << endl;
			cout << "2. Выход" << endl;
			cin >> menu;
			switch (menu) {
			case 1: {
				CityMenu(city1);
				break; }
			case 2: {
				cycle = 0;
				break;
			}
			default: {
				cout << "Некорректный ввод" << endl;
				break;
			}
			}
		}

	}