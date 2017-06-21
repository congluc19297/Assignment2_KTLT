/*********************************************************************************************
* Module:   Source.cpp
* Author:   Group 6
* Purpose:  Source code chay chinh cua app LIBPRO
**********************************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <iomanip>
#include <Windows.h> //set tieu de 
#include "managerIO.h"


using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////
// Purpose: Khai bao CSDL
///////////////////////////////////////////////////////////////////////////////////////////////
vector<Account> accounts;
vector<Account> newAccounts;
vector<User> users;
vector<AccountRoleMap> accRoleMaps;
vector<Role> roles;
vector<Book> books;
vector<Borrow_Book> borrowBooks;
vector<NotificationAcc> accNotifications;
Customer customer;

///////////////////////////////////////////////////////////////////////////////////////////////
// Purpose: Khai bao Prototype
///////////////////////////////////////////////////////////////////////////////////////////////
void readData(void);
void runMenuStart(void);
void runMenuManageUser(void);
void runMenuReader(void);
void runMenuLibrarian(void);
void searchBook(void);
void changePassword(const Customer &cus, bool check_Manager);
void createAccount(void);
void processingMultiRole(void);
void enable_disableAccount(void);
void searchAccDetail(void);
void newNotification(void);
void viewNotifications(void);
void deleteAccount(void);
void returnBook(void);
void createBook(void);
bool doLogin(void);

int main(){
	customer.c_accounts.accountNo = "";
	setWindows();
	printStart();
	readData();
	runMenuStart();
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       readData
// Purpose:    Doc co so du lieu tu file
// Parameters:
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void readData() {
	ifstream		fileIn;
	Account			acc;
	Account			newacc;
	User			user;
	AccountRoleMap	accRoleMap;
	Role			role;
	Book			book;
	Borrow_Book		borrowBook;
	NotificationAcc accNoti;
	int				count;
	bool			isReadGood = true;
	string			headerFile;

#pragma region ReadAccounts.dat
	//Read accounts.dat
	fileIn.open("accounts.dat");
	fileIn >> headerFile;
	if (headerFile == "Ass2_Accounts") {
		fileIn >> count;
		for (int i = 0; i < count; i++) {
			fileIn.ignore();
			fileIn >> acc.accountNo
				>> acc.userNo
				>> acc.password
				>> acc.isActive;
			accounts.push_back(acc);
		}
	}
	else {
		isReadGood = false;
	}
	fileIn.close();
#pragma endregion

#pragma region ReadNewAccounts.dat
	//Read accounts.dat
	fileIn.open("newaccounts.dat");
	fileIn >> headerFile;
	if (headerFile == "Ass2_NewAccounts") {
		fileIn >> count;
		for (int i = 0; i < count; i++) {
			fileIn.ignore();
			fileIn >> newacc.accountNo
				>> newacc.userNo
				>> newacc.password
				>> newacc.isActive;
			newAccounts.push_back(newacc);
		}
	}
	else {
		isReadGood = false;
	}
	fileIn.close();
#pragma endregion

#pragma region ReadUsers.dat
	//Read users.dat
	fileIn.open("users.dat");
	fileIn >> headerFile;
	if (headerFile == "Ass2_Users") {
		fileIn >> count;
		for (int i = 0; i < count; i++) {
			fileIn.ignore();
			fileIn >> user.userNo;

			fileIn.ignore();
			getline(fileIn, user.userName);
			fileIn >> user.email;

			fileIn.ignore();
			getline(fileIn, user.career);
			fileIn >> user.BOD.day
				>> user.BOD.month
				>> user.BOD.year;
			users.push_back(user);
		}
	}
	else {
		isReadGood = false;
	}
	fileIn.close();
#pragma endregion

#pragma region ReadRolemap.dat
	//Read rolemap.dat
	fileIn.open("rolemap.dat");
	fileIn >> headerFile;
	if (headerFile == "Ass2_AccountsRoleMap") {
		fileIn >> count;
		for (int i = 0; i < count; i++) {
			fileIn >> accRoleMap.accountNo
				>> accRoleMap.roleID;

			accRoleMaps.push_back(accRoleMap);
		}
	}
	else {
		isReadGood = false;
	}
	fileIn.close();
#pragma endregion

#pragma region ReadRole.dat
	//Read role.dat
	fileIn.open("role.dat");
	fileIn >> headerFile;
	if (headerFile == "Ass2_Role") {
		fileIn >> count;
		for (int i = 0; i < count; i++) {

			for (int j = 0; j < MaxRole; j++) *(int*)&role.roleDesc[j] = NONE;
			fileIn >> role.roleID;
			fileIn >> role.countRole;
			for (int j = 0; j < role.countRole; j++) {

				fileIn >> *(int*)&role.roleDesc[j];
			}

			roles.push_back(role);
		}
	}
	else {
		isReadGood = false;
	}
	fileIn.close();
#pragma endregion

#pragma region ReadBooks.dat
	//Read books.dat
	fileIn.open("books.dat");
	fileIn >> headerFile;
	if (headerFile == "Ass2_Books") {
		fileIn >> count;
		for (int i = 0; i < count; i++) {
			fileIn >> book.book_no;

			fileIn.ignore();
			getline(fileIn, book.bookTitle);
			book.bookTitle = formatString(book.bookTitle);
			getline(fileIn, book.author);

			fileIn >> book.countBook;

			books.push_back(book);
		}
	}
	else {
		isReadGood = false;
	}
	fileIn.close();
#pragma endregion

#pragma region ReadBorrow_book.dat
	//Read books.dat
	fileIn.open("borrow_book.dat");
	fileIn >> headerFile;
	if (headerFile == "Ass2_BorrowBooks") {
		fileIn >> count;
		for (int i = 0; i < count; i++)
		{
			fileIn >> borrowBook.accountNo
				>> borrowBook.acc_Book.book_no;

			fileIn.ignore();
			getline(fileIn, borrowBook.acc_Book.bookTitle);
			borrowBook.acc_Book.bookTitle = formatString(borrowBook.acc_Book.bookTitle);
			getline(fileIn, borrowBook.acc_Book.author);

			fileIn >> borrowBook.acc_Book.countBook
				>> borrowBook.dateBorrowBook.day
				>> borrowBook.dateBorrowBook.month
				>> borrowBook.dateBorrowBook.year
				>> borrowBook.dateReturnBook.day
				>> borrowBook.dateReturnBook.month
				>> borrowBook.dateReturnBook.year;

			borrowBooks.push_back(borrowBook);
		}
	}
	else {
		isReadGood = false;
	}

	fileIn.close();
#pragma endregion


#pragma region ReadNotifications.dat
	//Read books.dat
	fileIn.open("notifications.dat");
	fileIn >> headerFile;
	if (headerFile == "Ass2_Notifications") {
		fileIn >> count;
		for (int i = 0; i < count; i++) {
			fileIn >> accNoti.accountNo;

			fileIn.ignore();
			getline(fileIn, accNoti.noti);


			accNotifications.push_back(accNoti);
		}
	}
	else {
		isReadGood = false;
	}
	fileIn.close();
#pragma endregion

	if (!isReadGood) {
		cout << endl;
		printWarn("Qua trinh doc database bi loi!");
		wait(3);
		exit(0);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       quit
// Purpose:    Ghi du lieu xuong dia cung va thoat chuong trinh
// Parameters:
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void quit(void) {
	ofstream fout;
#pragma region Write_accounts.dat
	fout.open("accounts.dat");
	fout << "Ass2_Accounts" << endl;
	fout << accounts.size() << endl;
	for (int i = 0; i < accounts.size(); ++i) {
		fout << accounts[i].accountNo << endl
			<< accounts[i].userNo << endl
			<< accounts[i].password << endl
			<< accounts[i].isActive << endl;
	}
	fout.close();
#pragma endregion

#pragma region Write_newaccounts.dat
	fout.open("newaccounts.dat");
	fout << "Ass2_NewAccounts" << endl;
	fout << newAccounts.size() << endl;
	for (int i = 0; i < newAccounts.size(); ++i) {
		fout << newAccounts[i].accountNo << endl
			<< newAccounts[i].userNo << endl
			<< newAccounts[i].password << endl
			<< newAccounts[i].isActive << endl;
	}
	fout.close();
#pragma endregion

#pragma region Write_users.dat
	fout.open("users.dat");
	fout << "Ass2_Users" << endl;
	fout << users.size() << endl;
	for (int i = 0; i < users.size(); ++i) {
		fout << users[i].userNo << endl
			<< users[i].userName << endl
			<< users[i].email << endl
			<< users[i].career << endl
			<< users[i].BOD.day << endl
			<< users[i].BOD.month << endl
			<< users[i].BOD.year << endl;
	}
	fout.close();
#pragma endregion

#pragma region Write_rolemap.dat
	fout.open("rolemap.dat");
	fout << "Ass2_AccountsRoleMap" << endl;
	fout << accRoleMaps.size() << endl;
	for (int i = 0; i < accRoleMaps.size(); ++i) {
		fout << accRoleMaps[i].accountNo << endl
			<< accRoleMaps[i].roleID << endl;
	}
	fout.close();
#pragma endregion

#pragma region Write_role.dat

	fout.open("role.dat");
	fout << "Ass2_Role" << endl;
	fout << roles.size() << endl;
	for (int i = 0; i < accRoleMaps.size(); ++i) {
		fout << roles[i].roleID << endl
			<< roles[i].countRole;
		for (int j = 0; j < roles[i].countRole; j++) {
			fout << " " << roles[i].roleDesc[j];
		}
		fout << endl;
	}
	fout.close();
#pragma endregion

#pragma region Write_books.dat

	fout.open("books.dat");
	fout << "Ass2_Books" << endl;
	fout << books.size() << endl;
	for (int i = 0; i < books.size(); i++)
	{
		fout << books[i].book_no << endl
			<< books[i].bookTitle << endl
			<< books[i].author << endl
			<< books[i].countBook << endl;
	}
	fout.close();
#pragma endregion

#pragma region Write_borrow_book.dat
	fout.open("borrow_book.dat");
	fout << "Ass2_BorrowBooks" << endl;
	fout << borrowBooks.size() << endl;
	for (int i = 0; i < borrowBooks.size(); i++)
	{
		fout << borrowBooks[i].accountNo << endl
			<< borrowBooks[i].acc_Book.book_no << endl
			<< borrowBooks[i].acc_Book.bookTitle << endl
			<< borrowBooks[i].acc_Book.author << endl
			<< borrowBooks[i].acc_Book.countBook << endl
			<< borrowBooks[i].dateBorrowBook.day << endl
			<< borrowBooks[i].dateBorrowBook.month << endl
			<< borrowBooks[i].dateBorrowBook.year << endl
			<< borrowBooks[i].dateReturnBook.day << endl
			<< borrowBooks[i].dateReturnBook.month << endl
			<< borrowBooks[i].dateReturnBook.year << endl;
	}
	fout.close();
#pragma endregion

#pragma region Write_notifications.dat
	fout.open("notifications.dat");
	fout << "Ass2_Notifications" << endl;
	fout << accNotifications.size() << endl;
	for (int i = 0; i < accNotifications.size(); i++)
	{
		fout << accNotifications[i].accountNo << endl
			<< accNotifications[i].noti << endl;
	}
	fout.close();
#pragma endregion

	exit(0);
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       doLogin
// Purpose:    Thuc hien chuc nang dang nhap va thong bao ket qua dang nhap
// Parameters:
// Return:     bool
///////////////////////////////////////////////////////////////////////////////////////////////
bool doLogin(void) {
	string	strName;
	string	strPass;
	string  strWarn = "";
	int		indexAcc, indexUser, indexRoleMap, indexRole;

	system("cls");
	printTitle("DANG NHAP");
	strName = inputUserName();
	strPass = inputPassword("Nhap mat khau:");
	indexAcc = searchAcc(accounts, strName);
	if (indexAcc != -1) {
		if (accounts[indexAcc].isActive == true) {
			if (accounts[indexAcc].password == strPass) {
				customer.c_accounts = accounts[indexAcc];

				indexUser = searchUser(users, customer.c_accounts.userNo);
				if (indexUser != -1) customer.c_users = users[indexUser];

				indexRoleMap = searchRoleMap(accRoleMaps, customer.c_accounts.accountNo);
				if (indexRoleMap != -1) customer.c_accRoleMaps = accRoleMaps[indexRoleMap];

				indexRole = searchRole(roles, customer.c_accRoleMaps.roleID);
				if (indexRole != -1) customer.c_roles = roles[indexRole];
				return true;
			}
			else {
				strWarn = "Tai khoan hoac mat khau khong dung!";
			}
		}
		else {
			strWarn = "Tai khoan chua kich hoat!";
		}
	}
	else {
		strWarn = "Account does not exist. You should create new account!";
	}
	printWarn(strWarn);
	wait(2);
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       runMenuStart
// Purpose:    Hien thi menu dau tien khi khoi dong chuong trinh
// Parameters:
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void runMenuStart(void) {
	int		userChoose, selector = 0, numOfFunction = 5;
	string  nameOfFunction[] = {
		"Dang nhap",
		"Tim kiem sach",
		"Dang ky tai khoan",
		"Thay doi mat khau",
		"Thoat"
	};
	//customer.accounts->accountNo
	while (1) {

		system("cls");
		printTitle("WELCOME TO LIBPRO");
		printMenu(nameOfFunction, numOfFunction, selector);
		userChoose = readKey();
		if (userChoose == Enter) {
			switch (selector + 1) {
			case 1:
				if (doLogin()) {

					if (customer.c_roles.countRole == 1) {
						switch (customer.c_roles.roleDesc[0]) {
						case QUAN_LY_NGUOI_DUNG:
							runMenuManageUser();
							break;
						case DOC_GIA:
							runMenuReader();
							break;
						case THU_THU:
							runMenuLibrarian();
							break;
						}
					}
					else if (customer.c_roles.countRole > 1) {
						processingMultiRole();
						break;
					}
				}
				break;
			case 2:
				searchBook();
				break;
			case 3:
				createAccount();
				break;
			case 4:
				changePassword(customer, true);
				break;
			case 5:
				quit();
				break;
			}
		}
		else {
			processUserChoose(userChoose, selector, numOfFunction);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       runMenuManageUser
// Purpose:    Hien thi Menu danh cho Quan ly nguoi dung
// Parameters:
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void runMenuManageUser(void) {
	int		userChoose, selector = 0, numOfFunction = 7;
	string  nameOfFuncManagerAcc[] = {
		"Them tai khoan moi",
		"Thong bao cac user moi tao",
		"Kich hoat/Vo hieu hoa tai khoan",
		"Tim kiem tai khoan",
		"Thay doi mat khau",
		"Xoa tai khoan",
		"Dang xuat"
	};

	while (1) {
		printUserLogin(customer.c_accounts.accountNo);
		printTitle("QUAN LY NGUOI DUNG");
		printMenu(nameOfFuncManagerAcc, numOfFunction, selector);
		userChoose = readKey();
		if (userChoose == Enter) {
			switch (selector + 1) {
			case 1:
				system("cls");
				printWarn("Them tai khoan moi - Ai lam thi viet ham o day");
				wait(3);
				break;
			case 2:
				newNotification();
				break;
			case 3:
				enable_disableAccount();
				break;
			case 4:
				searchAccDetail();
				break;
			case 5:
				changePassword(customer, true);
				break;
			case 6:
				deleteAccount();
				break;
			case 7:
				return;
			}
		}
		else {
			processUserChoose(userChoose, selector, numOfFunction);
		}
	}
}



///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       runMenuReader
// Purpose:    Hien thi Menu danh cho Doc gia
// Parameters:
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void runMenuReader(void) {
	int		userChoose, selector = 0, numOfFunction = 6;
	string  nameOfFuncReader[] = {
		"Gui yeu cau muon sach",
		"Tra sach",
		"Xem thong bao",
		"Xem lich su",
		"Thay doi mat khau",
		"Dang xuat"
	};
	while (1)
	{
		printUserLogin(customer.c_accounts.accountNo);
		printTitle("DOC GIA");
		printMenu(nameOfFuncReader, numOfFunction, selector);
		userChoose = readKey();
		if (userChoose == Enter) {
			switch (selector + 1) {
			case 1:
				searchBook();
				break;
			case 2:
				returnBook();
				break;
			case 3:
				viewNotifications();
				break;
			case 4:
				system("cls");
				printUserLogin(customer.c_accounts.accountNo);
				printTitle("XEM LICH SU MUON SACH");
				printBorrowBook(borrowBooks);
				break;
			case 5:
				changePassword(customer, false);
				break;
			case 6:
				return;
			}
		}
		else {
			processUserChoose(userChoose, selector, numOfFunction);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       runMenuLibrarian
// Purpose:    Hien thi Menu danh cho Thu thu
// Parameters:
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void runMenuLibrarian(void) {
	int		userChoose, selector = 0, numOfFunction = 9;
	string  nameOfFuncLibrarian[] = {
		"Them sach",
		"Chinh sua",
		"Xoa sach",
		"Tim kiem sach",
		"Ghi nhan muon sach",
		"Ghi nhan tra sach",
		"Quan ly thoi gian muon sach",
		"Thay doi mat khau",
		"Dang xuat"
	};
	while (1)
	{
		printUserLogin(customer.c_accounts.accountNo);
		printTitle("THU THU");
		printMenu(nameOfFuncLibrarian, numOfFunction, selector);
		userChoose = readKey();
		if (userChoose == Enter) {
			switch (selector + 1) {
			case 1:
				createBook();
				break;
			case 2:
				printWarn("Chinh sua thong tin sach - Ai lam thi viet ham o day");
				wait(3);
				break;
			case 3:
				printWarn("Xoa sach nao do - Ai lam thi viet ham o day");
				wait(3);
				break;
			case 4:
				printWarn("Tim kiem sach - Ai lam thi viet ham o day");
				wait(3);
				break;
			case 5:
				printWarn("Ghi nhan muon sach - Ai lam thi viet ham o day");
				wait(3);
				break;
			case 6:
				printWarn("Ghi nhan tra sach - Ai lam thi viet ham o day");
				wait(3);
				break;
			case 7:
				printWarn("Quan ly thoi gian muon sach - Ai lam thi viet ham o day");
				wait(3);
				break;
			case 8:
				changePassword(customer, false);
				break;
			case 9:
				return;
			}
		}
		else {
			processUserChoose(userChoose, selector, numOfFunction);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       searchBook
// Purpose:    Dieu khien thuc hien tim kiem va them san pham vao gio hang
// Parameters:
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void searchBook(void) {
	short             x0, y0, x1, y1, x2, y2;
	int               selector = 0;
	int               indexProduct;
	int               item = 1;
	int               keyword;
	unsigned __int64  userChoose;
	vector <int>      idofBooks(books.size() + 1);
	vector<Book>   list;
	string            strName = "", strWarn = "";
	if (customer.c_accounts.accountNo == "") {
		system("cls");
	}
	else {
		printUserLogin(customer.c_accounts.accountNo);
	}
	printTitle("Tim kiem thong tin sach");
	cout << setfill(' ') << "    Nhap ten cuon sach muon tim : " << endl << endl;
	x0 = wherex(); y0 = wherey();
	do {
		clreop(x0, y0);
		for (int i = 0; i < item; i++) {
			if (i == 0) {
				cout << setw(4) << " >> " << strName;
				x1 = wherex(); y1 = wherey();
				cout << endl << endl;
			}
			else {
				if (formatString(strName).length() != 0)
				{
					//Xu li Up/Down va to mau RED full ten san pham
					int found = formatString(books[idofBooks[i]].bookTitle).find(formatString(strName));
					if (i == selector) {
						cout << setw(4) << " >> ";
						setColor(Bright_White, Light_Red);
						cout << books[idofBooks[i]].bookTitle;

					}
					else {
						cout << setw(4) << setfill(' ') << " ";
						for (int j = 0; j < books[idofBooks[i]].bookTitle.length(); ++j) {
							if (j >= found && j < (found + formatString(strName).length())) {
								setColor(Bright_White, Light_Red);
								cout << books[idofBooks[i]].bookTitle[j];
							}
							else {
								setColor(Bright_White, Black);
								cout << books[idofBooks[i]].bookTitle[j];
							}
						}

					}
					setColor(Bright_White, Black);
					cout << endl;
				}
			}
		}
		x2 = wherex(); y2 = wherey();
		gotoxy(x1, y1);
		keyword = _getch();
		if ((keyword >= 'a' && keyword <= 'z') || keyword == ' ' || (keyword >= 'A' && keyword <= 'Z') || (keyword >= '0' && keyword <= '9')) {
			item = 1;
			selector = 0;
			strName += keyword;

			for (int i = 0; i < books.size(); i++) {
				if (books[i].bookTitle.find(formatString(strName)) != books[i].bookTitle.npos) {
					item++;
					idofBooks[item - 1] = i;
					if (item == 16)			/*So san pham hien thi tren console toi da la 15*/
						break;
				}
			}
		}
		else if (keyword == 8 && strName.length() != 0) {
			item = 1;
			selector = 0;
			strName = strName.substr(0, strName.length() - 1);
			for (int i = 0; i < books.size(); i++) {
				if (books[i].bookTitle.find(formatString(strName)) != books[i].bookTitle.npos) {
					item++;
					idofBooks[item - 1] = i;
					if (item == 16)			/*So san pham hien thi tren console toi da la 15*/
						break;
				}
			}
		}
		else if (keyword == Control) {
			keyword = _getch();
			processUserChoose(keyword, selector, item);
		}
		else if (keyword == Enter && strName.size() != 0) {
			if (selector == 0) {
				indexProduct = searchBook(books, strName);
				if (indexProduct == -1) {
					strWarn = "Khong tim thay cuon sach nao theo yeu cau!";
				}
				else if (searchBorrowBook(borrowBooks, customer.c_accounts.accountNo, strName) != -1) {
					strWarn = "Trong gio hang ban da muon cuon sach nay roi!";
				}
				else {
					//PrintBook
					if (customer.c_accounts.accountNo == "") {
						strWarn = "Ban can phai dang nhap!";
						printSingleBook(books[indexProduct]);

						return;
					}
					else if (books[indexProduct].countBook > 0) {
						while (1) {
							clreop(x1, y1);
							cout << "\n\n    Ban co muon gui yeu cau muon cuon sach nay khong? (1:Yes / 0:No):" << endl << endl;
							printWarn(strWarn);
							cout << " >> ";
							cin >> userChoose;
							if (!inputGood() || userChoose < 0 || userChoose > 1) {
								strWarn = "Ghi chu: 1:Yes / 0:No";
							}
							else if (userChoose == 0) {
								return;
							}
							else {

								strWarn = "";
								cout << endl;
								break;
							}
						}
						while (1) {
							clreop(x1, y1);
							cout << "\n\n    So ngay muon (Nhieu nhat 7 ngay):" << endl;
							printWarn(strWarn);
							cout << " >> ";
							cin >> userChoose;
							if (!inputGood() || userChoose < 1 || userChoose > 7) {
								strWarn = "Khong hop le, nhap lai!";
							}
							else {
								Borrow_Book BB;
								date_t dateBorrow = getTimeCurr();
								BB.acc_Book = books[indexProduct];
								BB.acc_Book.countBook = 0;
								BB.accountNo = customer.c_accounts.accountNo;
								BB.dateBorrowBook = dateBorrow;
								BB.dateReturnBook = increaseDate(dateBorrow, userChoose);
								borrowBooks.push_back(BB);

								printBook(borrowBooks, customer);
								strWarn = "Thanh Cong!";
								wait(3);
								return;
							}
						}
					}
				}
			}
			else {

				if (searchBorrowBook(borrowBooks, customer.c_accounts.accountNo, books[idofBooks[selector]].bookTitle) != -1) {
					strWarn = "Trong gio hang ban da muon cuon sach nay roi!";
				}
				else{

					if (customer.c_accounts.accountNo == "") {
						strWarn = "Ban can phai dang nhap!";
						printSingleBook(books[idofBooks[selector]]);
					}
					else if (books[idofBooks[selector]].countBook > 0) {
						while (1) {
							clreop(x1, y1);
							cout << " \n\n    Ban co muon gui yeu cau muon cuon sach nay khong? (1:Yes / 0:No):" << endl << endl;
							printWarn(strWarn);
							cout << " >> ";
							cin >> userChoose;
							if (!inputGood() || userChoose < 0 || userChoose > 1) {
								strWarn = "Ghi chu: 1:Yes / 0:No";
							}
							else if (userChoose == 0) {
								return;
							}
							else {
								strWarn = "";
								cout << endl;
								break;
							}
						}
						while (1) {
							clreop(x1, y1);
							cout << "\n\n    So ngay muon (Nhieu nhat 7 ngay):" << endl;
							printWarn(strWarn);
							cout << " >> ";
							cin >> userChoose;
							if (!inputGood() || userChoose < 1 || userChoose > 7) {
								strWarn = "Khong hop le, nhap lai!";
							}
							else {
								Borrow_Book BB;
								date_t dateBorrow = getTimeCurr();
								BB.acc_Book = books[idofBooks[selector]];
								BB.acc_Book.countBook = 0;
								BB.accountNo = customer.c_accounts.accountNo;
								BB.dateBorrowBook = dateBorrow;
								BB.dateReturnBook = increaseDate(dateBorrow, userChoose);
								borrowBooks.push_back(BB);

								printBook(borrowBooks, customer);
								strWarn = "Thanh Cong!";
								wait(3);
								return;
							}
						}
					}
				}


			}
			cout << endl;
			clreop(wherex(), wherey());
			printWarn(strWarn);
			wait(2);
		}
	} while (keyword != Enter || strName.length() == 0);
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       changePassword
// Purpose:    Thuc hien cho phep thay doi password
// Parameters:
// - cus
// - check_Manager
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void changePassword(const Customer &cus, bool check_Manager) {
	string	strTemp, strTemp2;
	string	strWarn = "";
	Account acc;
	User	user;
	int		indexAcc, indexUser;

	system("cls");
	printTitle("THAY DOI MAT KHAU");
	acc.accountNo = inputUserName();

	indexAcc = searchAcc(accounts, acc.accountNo);

	if (check_Manager == false && accounts[indexAcc].accountNo != cus.c_accounts.accountNo) {
		indexAcc = -1;
	}

	if (indexAcc != -1) {
		acc = accounts[indexAcc];
		indexUser = searchUser(users, acc.userNo);

		if (indexUser != -1) {
			user.BOD = inputDate("Nhap ngay thang nam sinh:");

			if (
				user.BOD.day == users[indexUser].BOD.day &&
				user.BOD.month == users[indexUser].BOD.month &&
				user.BOD.year == users[indexUser].BOD.year
				) {
				user = users[indexUser];
				strTemp = inputPassword("Mat khau hien tai:");
				if (strTemp == acc.password) {
					acc.password = inputPassword("Nhap mat khau moi:");
					strTemp2 = inputPassword("Xac nhan lai mat khau moi:");
					if (acc.password == strTemp2) {
						accounts[indexAcc].password = acc.password;
						strWarn = "Doi mat khau thanh cong!";
					}
					else {
						strWarn = "Khong trung khop!";
					}
				}
				else {
					strWarn = "Mat khau hien tai khong dung!";
				}
			}
			else {
				strWarn = "Username và ngay sinh khong trung khop!";
			}
		}
	}
	else {
		strWarn = "Username khong hop le!";
	}
	clreop(wherex(), wherey());
	printWarn(strWarn);
	wait(2);
}

void processingMultiRole(void) {
	int		userChoose, selector = 0, numOfFunction = customer.c_roles.countRole;
	string *nameOfFuncLibrarian = new string[customer.c_roles.countRole];
	for (int i = 0; i < customer.c_roles.countRole; i++) {
		if (customer.c_roles.roleDesc[i] == DOC_GIA) {
			nameOfFuncLibrarian[i] = "Doc gia";
		}
		else if (customer.c_roles.roleDesc[i] == QUAN_LY_NGUOI_DUNG) {
			nameOfFuncLibrarian[i] = "Quan ly nguoi dung";
		}
		else if (customer.c_roles.roleDesc[i] == THU_THU) {
			nameOfFuncLibrarian[i] = "Thu thu";
		}
	}

	while (1)
	{
		printUserLogin(customer.c_accounts.accountNo);
		printTitle("BAN MUON THAO TAC VOI QUYEN NAO?");
		printMenu(nameOfFuncLibrarian, numOfFunction, selector);
		userChoose = readKey();
		if (userChoose == Enter) {
			if (nameOfFuncLibrarian[selector] == "Doc gia") {
				runMenuReader();
				break;
			}
			else if (nameOfFuncLibrarian[selector] == "Quan ly nguoi dung") {
				runMenuManageUser();
				break;
			}
			else if (nameOfFuncLibrarian[selector] == "Thu thu") {
				runMenuLibrarian();
				break;
			}
		}
		else {
			processUserChoose(userChoose, selector, numOfFunction);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       createAccount
// Purpose:    Thuc hien chuc nang tao tai khoan nguoi dung moi
// Parameters:
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void createAccount(void) {
	string  strTemp, str_roleID = "R", warn = ""; //Bien luu password nhap lan 2
	short x, y;
	int idxUser;
	Account acc;
	Role role;
	AccountRoleMap roleMap;
	User	user;

	system("cls");
	printTitle("Tao tai khoan");

	user.userNo = inputString("Nhap ID/CMND: ");
	user.email = inputString("Nhap email: ", false);

	clreop(wherex(), wherey());
	idxUser = searchUser(users, user.userNo);
	if (idxUser != -1) {
		//User da ton tai, lap tai khoan moi
		if (user.email == users[idxUser].email) {
			user = users[idxUser];
			acc.accountNo = inputString("Nhap username: ", false);
			acc.password = inputPassword("Nhap password: ");
			acc.userNo = user.userNo;
			acc.isActive = false;
			int count = 0;
			while (true)
			{
				x = wherex();
				y = wherey();
				clreop(x, y);
				strTemp = inputPassword("Xac nhan lai password: ");

				if (strTemp != acc.password) {
					count++;
					printWarn("Mat khau khong hop le!");
					wait(1);
					gotoxy(x, y);

				}
				else break;
				if (count > 3) return;
			}

			role.countRole = 1;
			for (int i = 0; i < MaxRole; i++) {
				if (i == 0) role.roleDesc[i] = DOC_GIA;
				else role.roleDesc[i] = NONE;
			}
			srand(time(NULL));
			while (1)
			{
				int roleID = rand() % 1000 + 1;
				str_roleID += intTostring(roleID);
				if (searchRole(roles, str_roleID) != -1) continue;
				else break;
			}
			role.roleID = str_roleID;

			roleMap.accountNo = acc.accountNo;
			roleMap.roleID = role.roleID;

			newAccounts.push_back(acc);
			accRoleMaps.push_back(roleMap);
			roles.push_back(role);

			printWarn("Tao account moi thanh khong");

		}
		else {
			printWarn("User nay da ton tai, khong trung khop email!");
		}
	}
	else {
		user.userName = inputString("Nhap ho va ten: ", false);
		user.career = inputString("Nghe nghiep: ", false);
		user.BOD = inputDate("Nhap ngay thang nam sinh: ");

		acc.accountNo = inputString("Nhap username: ", false);
		acc.password = inputPassword("Nhap password: ");
		acc.userNo = user.userNo;
		acc.isActive = false;

		int count = 0;
		while (true)
		{
			x = wherex();
			y = wherey();
			clreop(x, y);
			strTemp = inputPassword("Xac nhan lai password: ");

			if (strTemp != acc.password) {
				count++;
				printWarn("Mat khau khong hop le!");
				wait(1);
				gotoxy(x, y);

			}
			else break;
			if (count > 3) return;
		}

		role.countRole = 1;
		for (int i = 0; i < MaxRole; i++) {
			if (i == 0) role.roleDesc[i] = DOC_GIA;
			else role.roleDesc[i] = NONE;
		}
		srand(time(NULL));
		while (1)
		{
			int roleID = rand() % 1000 + 1;
			str_roleID += intTostring(roleID);
			if (searchRole(roles, str_roleID) != -1) continue;
			else break;
		}
		role.roleID = str_roleID;

		roleMap.accountNo = acc.accountNo;
		roleMap.roleID = role.roleID;

		users.push_back(user);
		newAccounts.push_back(acc);
		accRoleMaps.push_back(roleMap);
		roles.push_back(role);

		printWarn("Tao account moi thanh khong");

	}

	wait(2);
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       enable_disableAccount
// Purpose:    Kich hoat hoac vo hieu hoa tai khoan
// Parameters:
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void enable_disableAccount(void) {
	int				indexAcc, userChoose;
	bool			checkNewAcc = false;
	short			x, y;
	string			strWarn = "", accountNo;
	vector<Account> listAcc;

	printUserLogin(customer.c_accounts.accountNo);
	printTitle("KICH HOAT/VO HIEU HOA TAI KHOAN");
	accountNo = inputUserName();

	indexAcc = searchAcc(accounts, accountNo);
	if (indexAcc == -1) {
		indexAcc = searchAcc(newAccounts, accountNo);
		if (indexAcc != -1) {
			listAcc.push_back(newAccounts[indexAcc]);
			checkNewAcc = true;
			setColor(Bright_White, Light_Red);
			cout << "\nLuu y, day la tai khoan moi duoc tao gan day!" << endl;
			setColor(Bright_White, Black);
		}
	}
	else {
		listAcc.push_back(accounts[indexAcc]);
	}

	if (indexAcc != -1) {
		
		printAccount(listAcc, users);
		x = wherex();
		y = wherey();
		while (1) {
			clreop(x, y);
			if (listAcc[0].isActive == true) {
				cout << "    Vo hieu hoa tai khoan nay (1:Yes / 0:No): " << endl << endl;
			}
			else {
				cout << "    Kich hoat tai khoan nay (1:Yes / 0:No): " << endl << endl;
			}
			printWarn(strWarn);
			cout << " >> ";
			cin >> userChoose;
			if (!inputGood() || userChoose < 0 || userChoose > 1) {
				strWarn = "Ghi chu: 1:Yes / 0:No";
			}
			else {
				if (userChoose == 1 && checkNewAcc != true) {
					accounts[indexAcc].isActive = !accounts[indexAcc].isActive;
				}
				else if (userChoose == 1 && checkNewAcc == true) {
					newAccounts[indexAcc].isActive = !newAccounts[indexAcc].isActive;
					accounts.push_back(newAccounts[indexAcc]);
					newAccounts.erase(newAccounts.begin() + indexAcc);
				}
				
				strWarn = "Thanh Cong!";
				break;
			}
		}
	}
	else {
		strWarn = "Tai khoan khong ton tai!";
	}
	clreop(wherex(), wherey());
	printWarn(strWarn);
	wait(2);
}

void searchAccDetail(void) {
	int				indexAcc;
	string			accountNo;

	printUserLogin(customer.c_accounts.accountNo);
	printTitle("TIM KIEM CHI TIET ACCOUNT");
	accountNo = inputUserName();
	indexAcc = searchAcc(accounts, accountNo);

	if (indexAcc != -1) {
		printAccDetail(accounts[indexAcc], users, roles, accRoleMaps);
	}
	else {
		printWarn("Username khong ton tai!");
	}

	wait(2);
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       newNotification
// Purpose:    Show thong tin account moi tao
// Parameters:
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void newNotification(void) {
	setWindows(120);
	printUserLogin(customer.c_accounts.accountNo);
	printTitle("THONG BAO MOI");
	cout << "Co ";
	setColor(Bright_White, Light_Red);
	cout << newAccounts.size();
	setColor(Bright_White, Black);
	cout << " tai khoan moi tao!" << endl << endl;
	printAccount(newAccounts, users);
	system("pause");
	setWindows();
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       viewNotifications
// Purpose:    Xem thong bao danh cho doc gia khi muon sach
// Parameters:
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void viewNotifications(void) {
	setWindows(120);

	vector<Account> listAcc;
	short x, y, x1, y1;
	int count = 0;

	listAcc.push_back(customer.c_accounts);
	printUserLogin(customer.c_accounts.accountNo);
	printTitle("THONG BAO");
	
	printAccount(listAcc, users);
	x = wherex(); y = wherey();
	cout << endl << endl;
	
	for (int i = 0; i < accNotifications.size(); i++)
	{
		if (accNotifications[i].accountNo == customer.c_accounts.accountNo) {
			count++;
			cout << ">> " << count << ". " << accNotifications[i].noti << endl;
		}
	}
	x1 = wherex(); y1 = wherey();
	gotoxy(x, y);
	if (count > 0) {
		cout << "    Ban co tat ca ";
		setColor(Bright_White, Light_Red);
		cout << right << setw(2) << setfill('0') << count;
		setColor(Bright_White, Black);
		cout << " thong bao!";
	}
	else {
		setColor(Bright_White, Light_Red);
		cout << "    Ban khong co thong bao nao ca!";
		setColor(Bright_White, Black);
	}
	gotoxy(x1, y1);

	setColor(Bright_White, Light_Red);
	cout << "\n    Nham phim bat ky de thoat!";
	setColor(Bright_White, Black);
	_getch();
	

	
	setWindows();
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       deleteAccount
// Purpose:    Xoa mot tai khoan hien co (ngoai tru tai khoan admin)
// Parameters:
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void deleteAccount(void) {
	int				indexAcc;
	short			x, y;
	int				userChoose;
	string			strWarn = "";

	printUserLogin(customer.c_accounts.accountNo);
	printTitle("XOA TAI KHOAN");
	indexAcc = searchAcc(accounts, inputUserName());
	if (indexAcc != -1 && accounts[indexAcc].accountNo != customer.c_accounts.accountNo) {

		setWindows(120);
		printAccDetail(accounts[indexAcc], users, roles, accRoleMaps);
		x = wherex();
		y = wherey();
		while (1) {
			clreop(x, y);
			cout << "    Xoa toan bo thong tin cua tai khoan nay (1:Yes / 0:No): " << endl << endl;
			printWarn(strWarn);
			cout << " >> ";
			cin >> userChoose;
			if (!inputGood() || userChoose < 0 || userChoose > 1) {
				strWarn = "Khong hop le: 1:Yes / 0:No";
			}
			else {
				if (userChoose == 1) {
					int count = 0, indexUser, indexRole, indexRoleMap;
					for (int i = 0; i < accounts.size(); i++)
					{
						if (accounts[i].accountNo == accounts[indexAcc].accountNo) count++;
					}
					indexUser = searchUser(users, accounts[indexAcc].userNo);
					indexRoleMap = searchRoleMap(accRoleMaps, accounts[indexAcc].accountNo);
					if (indexUser == -1 || indexRoleMap == -1) strWarn = "Co loi xay ra trong luc thuc hien!";
					indexRole = searchRole(roles, accRoleMaps[indexRoleMap].roleID);
					if (indexRole == -1) strWarn = "Co loi xay ra trong luc thuc hien!";

					if (strWarn == "") {
						roles.erase(roles.begin() + indexRole);
						accRoleMaps.erase(accRoleMaps.begin() + indexRoleMap);
						accounts.erase(accounts.begin() + indexAcc);
						if (count == 1) users.erase(users.begin() + indexUser);

						strWarn = "Thanh Cong!";
						setWindows();
					}
					break;
					
				}
				
			}
		}
	}
	else {
		strWarn = "Username khong hop le!";
	}
	clreop(wherex(), wherey());
	printWarn(strWarn);
	wait(2);
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       returnBook
// Purpose:    Thuc hien viec tra sach
// Parameters:
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void returnBook(void) {
	string BookNo, strWarn = "";
	int indexBook;
	printUserLogin(customer.c_accounts.accountNo);
	printTitle("GUI TRA SACH");

	BookNo = inputString("    Nhap ID sach muon tra: ");
	indexBook = searchBorrowBookID(borrowBooks, customer.c_accounts.accountNo,BookNo);

	if (indexBook != -1) {
		date_t currTime = getTimeCurr();
		if (borrowBooks[indexBook].dateReturnBook < currTime) {
			borrowBooks[indexBook].acc_Book.countBook = -1;
		}
		else {
			int n = subTwoDays(currTime, borrowBooks[indexBook].dateReturnBook);
			if (n == 0) borrowBooks[indexBook].acc_Book.countBook = -1;
			else {
				//Gui thong bao tre han n ngay
				borrowBooks[indexBook].acc_Book.countBook = n + 2;
			}
			
		}
	}
	else {
		strWarn = "ID khong ton tai trong lich su muon sach!";
	}

	clreop(wherex(), wherey());
	printWarn(strWarn);
	wait(2);
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       createBook
// Purpose:    Thuc hien viec them 1 cuon sach cho thu thu
// Parameters:
// Return:    
///////////////////////////////////////////////////////////////////////////////////////////////
void createBook(void){
	Book book;
	int intID = 1;
	int totalBook;
	short x, y;
	string nameBook, authBook;
	string noBook = "BOOK";

	//Xoa man hinh
	system("cls");

	//Set title
	printTitle("Them mot dau sach");

	x = wherex();
	y = wherey();
	nameBook = inputString("Nhap ten sach: ");

	nameBook = formatString(nameBook);
	intID = searchBook(books, nameBook);

	//Kiem tra ten sach co bi trung khong
	while (intID > 0)
	{
		clreop(x, y);
		printWarn("Ten sach da ton tai!");
		wait(1);
		nameBook = inputString("Nhap lai ten sach: ");
		intID = searchBook(books, nameBook);
		if (intID > 0){
			gotoxy(x, y);
		}
	}
	authBook = inputString("Nhap ten tac gia: ");
	authBook = formatString(authBook);
	totalBook = inputInt("Nhap so luong sach: ");

	//Lay ngau nhien ID cho book
	while (1)
	{
		int roleID = rand() % 1000 + 1;
		noBook += intTostring(roleID);
		if (searchBook(books, noBook) != -1) continue;
		else break;
	}
	book.author = authBook;
	book.bookTitle = nameBook;
	book.countBook = totalBook;
	book.book_no = noBook;

	books.push_back(book);
	printWarn("Them 1 dau sach thanh cong!!!");
	wait(2);
}