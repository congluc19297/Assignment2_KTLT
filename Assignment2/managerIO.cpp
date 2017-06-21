#include "managerIO.h"
#include <iostream>
///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       printWarn
// Purpose:    In ra man hinh thong bao loi
// Parameters:
// - str
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void printWarn(string str) {
	short x = wherex(), y = wherey();
	setColor(Bright_White, Light_Red);
	gotoxy(x, y + 2);
	cout << "    " << str << endl << endl;
	setColor(Bright_White, Black);
	gotoxy(x, y);
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       printTitle
// Purpose:    Ghi tieu de cua so tac vu
// Parameters:
// - str
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void printTitle(string str) {
	gotoxy((79 - str.length()) / 2, 1);
	cout << str;
	gotoxy((79 - str.length()) / 2, 2);
	cout << setfill('=') << setw(str.length()) << '=' << endl << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       processUserChoose
// Purpose:    Su ly yeu cau chon lua cua nguoi dung tren menu
// Parameters:
// - userChoose
// - selector
// - numOfFunction
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void processUserChoose(const int userChoose, int &selector, const int numOfFunction) {
	switch (userChoose) {
	case Up:
		if (selector == 0) {
			selector = numOfFunction - 1;
		}
		else {
			--selector;
		}
		break;
	case Down:
		if (selector == numOfFunction - 1) {
			selector = 0;
		}
		else {
			++selector;
		}
		break;
	}
	if (userChoose - 48 >= 1 && userChoose - 48 <= numOfFunction) {
		selector = userChoose - 48 - 1;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       printMenu
// Purpose:    Hien thi Menu
// Parameters:
// - nameOfFunction[]
// - numOfFunction
// - selector
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void printMenu(const string nameOfFunction[], const int numOfFunction, const int selector) {
	short x, y;
	for (int i = 0; i < numOfFunction; ++i) {
		if (i == selector) {
			setColor(Bright_White, Light_Red);
			cout << "    " << (i + 1) << ". " << nameOfFunction[i];

			x = wherex();
			y = wherey();
			cout << endl << endl;
			setColor(Bright_White, Black);
		}
		else {
			cout << "    " << (i + 1) << ". " << nameOfFunction[i] << endl << endl;
		}
	}
	gotoxy(x, y);
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       inputUserName
// Purpose:    Dieu khien viec nhap username, kiem soat loi
// Parameters:
// Return:     string
///////////////////////////////////////////////////////////////////////////////////////////////
string inputUserName(void) {
	string	str = "";
	string	strWarn = "";
	short	x = wherex();
	short	y = wherey();

	while (1) {
		clreop(x, y);
		cout << "    Nhap username:" << endl << endl;
		printWarn(strWarn);
		cout << " >> ";
		getline(cin, str);
		if (str.length() == 0 || str.find(" ") < str.length()) {
			strWarn = "Username bao gom ki tu a-z, so va khong co khoang trang!";
		}
		else {
			cout << endl;
			return str;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       inputPassword
// Purpose:    Dieu khien viec nhap password, ma hoa ki tu
// Parameters:
// Return:     string
///////////////////////////////////////////////////////////////////////////////////////////////
string inputPassword(string request) {
	string	str = "";
	int		readKey;
	short	x, y;

	clreop(wherex(), wherey());
	cout << "    " << request << endl << endl;
	cout << " >> ";
	x = wherex();
	y = wherey();
	do {
		readKey = _getch();
		if (readKey >= 32 && readKey <= 126) {
			str = str + (char)readKey;
		}
		else if (readKey == 8 && str.length() != 0) {
			str = str.erase(str.length() - 1, 1);
		}
		clreop(x, y);
		for (int i = 0; i < str.length(); ++i) {
			cout << '*';
		}
	} while (readKey != 13);
	cout << endl << endl;
	return str;
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       inputString
// Purpose:    Thuc hien nhap chuoi, chuan hoa chuoi truoc khi tra ve
// Parameters:
// Return:     string
///////////////////////////////////////////////////////////////////////////////////////////////
string inputString(string request) {
	string	str = "";
	string  strWarn = "";
	short   x, y;

	x = wherex();
	y = wherey();
	while (1) {
		clreop(x, y);
		cout << "    " << request << endl << endl;
		printWarn(strWarn);
		cout << " >> ";
		getline(cin, str);
		str = formatString(str);
		if (str == "") {
			strWarn = "Chuoi khong duoc rong!";
		}
		else {
			break;
		}
	}
	cout << endl;
	return formatString(str);
}
string inputString(string request, bool check) {
	string	str = "";
	string  strWarn = "";
	short   x, y;

	x = wherex();
	y = wherey();
	while (1) {
		clreop(x, y);
		cout << "    " << request << endl << endl;
		printWarn(strWarn);
		cout << " >> ";
		getline(cin, str);
		if (check == false) {
			str = formatString(str, check);
		}
		else {
			str = formatString(str);
		}
		if (str == "") {
			strWarn = "Chuoi khong duoc rong!";
		}
		else {
			break;
		}
	}
	cout << endl;
	return str;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       inputDate
// Purpose:    Dieu khien viec nhap ngay thang, kiem soat loi
// Parameters:
// - str
// Return:     date_t
///////////////////////////////////////////////////////////////////////////////////////////////
date_t inputDate(string request) {
	date_t	date;
	string	strWarn = "";
	short	x = wherex();
	short	y = wherey();

	while (1) {
		clreop(x, y);
		cout << "    " << request << endl << endl;
		printWarn(strWarn);
		cout << " >> Ngay:          Thang:          Nam:";
		gotoxy(x + 9, y + 2);
		cin >> date.day;
		if (!inputGood() || date.day < 1 || date.day > 31) {
			strWarn = "Ngay khong hop le!";
		}
		else {
			gotoxy(x + 25, y + 2);
			cin >> date.month;
			if (
				!inputGood() ||
				date.month < 1 || date.month > 12 ||
				((date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11) && date.day == 31) ||
				(date.month == 2 && (date.day == 30 || date.day == 31))
				) {
				strWarn = "Thang khong hop le!";
			}
			else {
				gotoxy(x + 40, y + 2);
				cin >> date.year;
				if (
					!inputGood() ||
					date.year < 1900 ||
					(!((date.year % 4 == 0 && date.year % 100 != 0) || date.year % 400 == 0) && date.month == 2 && date.day == 29)
					) {
					strWarn = "Nam khong hop le!";
				}
				else {
					cout << endl;
					return date;
				}
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       printBook
// Purpose:    Hien thi danh sach san pham
// Parameters:
// - list
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void printBook(const vector<Borrow_Book> &list, const Customer &customer) {
	ofstream fout;
	fout.open("ExportBook.txt");

	fout << "Co " << list.size() << " cuon sach ban da chon!" << endl;
	fout << setw(119) << setfill('=') << '=' << endl;
	fout << left << "|" << setw(20) << setfill(' ') << "Username"
		<< left << "|" << setw(10) << setfill(' ') << "Trang thai"
		<< left << "|" << setw(12) << setfill(' ') << "Ngay muon"
		<< left << "|" << setw(12) << setfill(' ') << "Ngay tra"
		<< left << "|" << setw(60) << setfill(' ') << "Ten sach"
		<< left << "|" << endl;
	fout << setw(118) << setfill('=') << '=' << endl;
	for (int i = 0; i < list.size(); ++i) {
		if (list[i].accountNo == customer.c_accounts.accountNo) {
			string status = "";

			if (list[i].acc_Book.countBook != 0) status = "Active";
			else status = "UnActive";

			fout << left << "|" << setw(20) << setfill(' ') << list[i].accountNo
				<< left << "|" << setw(10) << setfill(' ') << status
				<< left << "|" << setw(12) << setfill(' ') << toString(list[i].dateBorrowBook)
				<< left << "|" << setw(12) << setfill(' ') << toString(list[i].dateReturnBook)
				<< left << "|" << setw(60) << setfill(' ') << list[i].acc_Book.bookTitle
				<< endl;
		}
	}
	fout << setw(118) << setfill('=') << '=' << endl;

	fout.close();
	system("ExportBook.txt");
	return;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       printBook
// Purpose:    Hien thi danh sach san pham
// Parameters:
// - list
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void printSingleBook(const Book &BOOK) {
	ofstream fout;
	fout.open("ExportBook.txt");

	fout << "Thong tin sach ban vua chon!" << endl;
	fout << setw(115) << setfill('=') << '=' << endl;
	fout << left << "|" << setw(10) << setfill(' ') << "ID"
		<< left << "|" << setw(10) << setfill(' ') << "So luong"
		<< left << "|" << setw(30) << setfill(' ') << "Tac gia"
		<< left << "|" << setw(60) << setfill(' ') << "Ten sach"
		<< left << "|" << endl;
	fout << setw(115) << setfill('=') << '=' << endl;

	fout << left << "|" << setw(10) << setfill(' ') << BOOK.book_no
		<< left << "|" << setw(10) << setfill(' ') << BOOK.countBook
		<< left << "|" << setw(30) << setfill(' ') << BOOK.author
		<< left << "|" << setw(60) << setfill(' ') << BOOK.bookTitle
		<< endl;

	fout << setw(115) << setfill('=') << '=' << endl;

	fout.close();
	system("ExportBook.txt");
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       printAccount
// Purpose:    Hien thi danh sach tai khoan
// Parameters:
// - list
// - users
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void printAccount(const vector<Account> &list, const vector<User> &users) {

	cout << setw(93) << setfill('=') << '=' << endl;
	cout << left << "|" << setw(13) << setfill(' ') << "ID/CMND"
		<< left << "|" << setw(19) << setfill(' ') << "USERNAME"
		<< left << "|" << setw(30) << setfill(' ') << "HO VA TEN"
		<< left << "|" << setw(15) << setfill(' ') << "DOB"
		<< left << "|" << setw(10) << setfill(' ') << "Trang thai"
		<< left << "|" << endl;
	cout << setw(93) << setfill('=') << '=' << endl;

	for (int i = 0; i < list.size(); ++i) {
		User _user = users[searchUser(users, list[i].userNo)];
		cout << left << "|" << setw(13) << setfill(' ') << _user.userNo
			<< left << "|" << setw(19) << setfill(' ') << list[i].accountNo.substr(0, 19)
			<< left << "|" << setw(30) << setfill(' ') << _user.userName.substr(0, 20)
			<< left << "|" << setw(15) << setfill(' ') << toString(_user.BOD)
			<< left << "|" << setw(10) << setfill(' ') << ((list[i].isActive == true) ? "Enable" : "Disable")
			<< left << "|" << endl;
	}
	cout << setw(93) << setfill('=') << '=' << endl << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       printAccDetail
// Purpose:    In thong tin chi tiet cua tai khoan
// Parameters:
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void printAccDetail(Account acc, const vector<User> &users, const vector<Role> &roles, const vector<AccountRoleMap> &accRoles) {
	int				indexUser, indexRole, indexRoleMap;
	string			strWarn = "", accountNo;
	
	indexUser = searchUser(users, acc.userNo);
	indexRoleMap = searchRoleMap(accRoles, acc.accountNo);
	indexRole = searchRole(roles, accRoles[indexRoleMap].roleID);
	if (indexUser == -1 || indexRoleMap == -1 || indexRole == -1) {
		printWarn("Co loi xay ra, vui long thu lai!");
		wait(2);
		return;
	}
	else {
		
		printUser(users[indexUser]);
		printRole(roles[indexRole], accRoles[indexRoleMap]);
		setColor(Bright_White, Light_Red);
		cout << "\n\nNhan phim bat ky de tiep tuc!\n";
		_getch();
		setColor(Bright_White, Black);

	}

}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       printUser
// Purpose:    In thong tin chi tiet cua user
// Parameters: singleUser
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void printUser(const User &singleUser) {
	cout << setw(108) << setfill('=') << '=' << endl;
	cout << left << "|" << setw(13) << setfill(' ') << "ID/CMND"
		<< left << "|" << setw(29) << setfill(' ') << "HO VA TEN"
		<< left << "|" << setw(30) << setfill(' ') << "EMAIL"
		<< left << "|" << setw(15) << setfill(' ') << "NGHE NGHIEP"
		<< left << "|" << setw(15) << setfill(' ') << "NGAY SINH"
		<< left << "|" << endl;
	cout << setw(108) << setfill('=') << '=' << endl;

	cout << left << "|" << setw(13) << setfill(' ') << singleUser.userNo
		<< left << "|" << setw(29) << setfill(' ') << singleUser.userName.substr(0, 19)
		<< left << "|" << setw(30) << setfill(' ') << singleUser.email.substr(0, 19)
		<< left << "|" << setw(15) << setfill(' ') << singleUser.career
		<< left << "|" << setw(15) << setfill(' ') << toString(singleUser.BOD)
		<< left << "|" << endl;

	cout << setw(108) << setfill('=') << '=' << endl << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       printUser
// Purpose:    In thong tin chi tiet cua user
// Parameters: singleUser
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void printRole(const Role &singleRole, const AccountRoleMap &singleRoleMap) {
	bool	temp1 = false, temp2 = false, temp3 = false;
	
	cout << "\nAccount ";
	setColor(Bright_White, Light_Red);
	cout << singleRoleMap.accountNo;
	setColor(Bright_White, Black);
	cout << " co " << singleRole.countRole << " quyen trong he thong nhu sau: " << endl << endl;
	short	x = wherex();
	short	y = wherey();
	cout << "Doc gia:    " << "       Quan ly nguoi dung:    " << "       Thu thu:    ";
	for (int i = 0; i < MaxRole; i++)
	{
		if (singleRole.roleDesc[i] == DOC_GIA && temp1 != true) {
			gotoxy(x + 9, y);
			cout << "Yes";
			temp1 = true;
		}
		else if (temp1 != true) {
			gotoxy(x + 9, y);
			cout << "No ";
		}
		if (singleRole.roleDesc[i] == QUAN_LY_NGUOI_DUNG && temp2 != true) {
			gotoxy(x + 40, y);
			cout << "Yes";
			temp2 = true;
		}
		else if (temp2 != true) {
			gotoxy(x + 40, y);
			cout << "No ";
		}
		if (singleRole.roleDesc[i] == THU_THU && temp3 != true) {
			gotoxy(x + 60, y);
			cout << "Yes";
			temp3 = true;
		}
		else if (temp3 != true) {
			gotoxy(x + 60, y);
			cout << "No ";
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       printBorrowBook
// Purpose:    Thong ke lich su muon sach
// Parameters: singleUser
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void printBorrowBook(const vector<Borrow_Book> &BBB) {

	setWindows(120);
	cout << setw(100) << setfill('=') << '=' << endl;
	cout << left << "|" << setw(20) << setfill(' ') << "USERNAME"
		<< left << "|" << setw(40) << setfill(' ') << "TEN SACH"
		<< left << "|" << setw(12) << setfill(' ') << "TRANG THAI"
		<< left << "|" << setw(11) << setfill(' ') << "NGAY MUON"
		<< left << "|" << setw(11) << setfill(' ') << "NGAY TRA"
		<< left << "|" << endl;
	cout << setw(100) << setfill('=') << '=' << endl;
	for (int i = 0; i < BBB.size(); i++)
	{
		string status = "";
		if (BBB[i].acc_Book.countBook == 0) status = "Chua duyet";
		else if (BBB[i].acc_Book.countBook == 1) status = "Dang muon";
		else if (BBB[i].acc_Book.countBook == -1) status = "Da tra sach";
		else if (BBB[i].acc_Book.countBook < -1) status = "Bi phat";
		cout << left << "|" << setw(20) << setfill(' ') << BBB[i].accountNo.substr(0, 30)
			<< left << "|" << setw(40) << setfill(' ') << BBB[i].acc_Book.bookTitle.substr(0, 50)
			<< left << "|" << setw(12) << setfill(' ') << status
			<< left << "|" << setw(11) << setfill(' ') << toString(BBB[i].dateBorrowBook)
			<< left << "|" << setw(11) << setfill(' ') << toString(BBB[i].dateReturnBook)
			<< left << "|" << endl;
	}
	
	cout << setw(100) << setfill('=') << '=' << endl << endl;
	setColor(Bright_White, Light_Red);
	cout << "\n\nNhan phim bat ky de thoat! ";
	setColor(Bright_White, Black);
	_getch();
	setWindows();
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       inputInt
// Purpose:    Thuc hien nhap so
// Parameters:
// Return:     int
///////////////////////////////////////////////////////////////////////////////////////////////
int inputInt(string request) {
	string  str = "";
	string strEnd;
	string  strWarn = "";
	short   x, y;
	int intRes;
	int lengRes = 0;

	x = wherex();
	y = wherey();
	while (1) {
		clreop(x, y);
		cout << "    " << request << endl << endl;
		printWarn(strWarn);
		cout << " >> ";
		getline(cin, str);
		str = formatString(str);
		if (str == "") {
			strWarn = "Khong duoc rong!";
		}
		else {
			break;
		}
	}
	lengRes = 0;
	for (int i = 0; i < str.length(); i++)
	{
		char c = str[i];
		int ascii_c = c;
		if (ascii_c >= 48 && ascii_c <= 57){
			strEnd.push_back(c);
			lengRes++;
		}
	}
	cout << endl;
	intRes = stringToint(strEnd);
	return intRes;
}
