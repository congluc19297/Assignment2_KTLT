/*********************************************************************************************
* Module:   functions.cpp
* Author:   Group 6
* Purpose:  Hien thuc cac ham ho tro assignment
**********************************************************************************************/
#pragma warning(disable:4996)
#include "functions.h"
#include "LibsWindow.h"

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       printStart
// Purpose:    Hien thi man hinh khoi dong voi logo chuong trinh
// Parameters:
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void printStart(void) {
	short start_x = 25, start_y = 7;
	system("color f0");
	setColor(Bright_White, Green);
	gotoxy(start_x, start_y++);
	cout << char(219) << "     " << char(219) << "  " << char(219) << char(219) << char(219) << "   " << char(219) << char(219) << char(219) << "   " << char(219) << char(219) << char(219) << "   " << " " << char(219) << char(219);
	gotoxy(start_x, start_y++);
	cout << char(219) << "     " << char(219) << "  " << char(219) << "  " << char(219) << "  " << char(219) << "  " << char(219) << "  " << char(219) << "  " << char(219) << "  " << char(219) << "  " << char(219);
	gotoxy(start_x, start_y++);
	cout << char(219) << "     " << char(219) << "  " << char(219) << char(219) << char(219) << "   " << char(219) << char(219) << char(219) << "   " << char(219) << char(219) << char(219) << "   " << char(219) << "  " << char(219);
	gotoxy(start_x, start_y++);
	cout << char(219) << "     " << char(219) << "  " << char(219) << "  " << char(219) << "  " << char(219) << "   " << "  " << char(219) << " " << char(219) << "   " << char(219) << "  " << char(219);
	gotoxy(start_x, start_y++);
	cout << char(219) << "     " << char(219) << "  " << char(219) << char(219) << char(219) << "   " << char(219) << "   " << "  " << char(219) << "  " << char(219) << "  " << " " << char(219) << char(219);
	gotoxy(start_x, start_y++);
	cout << char(219) << char(219) << char(219) << char(219);
	gotoxy(start_x + 6, start_y);
	setColor(Bright_White, Light_Red);
	cout << "  M A N A G E R";
	gotoxy(start_x + 6, start_y + 2);
	setColor(Bright_White, Black);
	cout << "Loading...";
	wait(3);
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       printUserLogin
// Purpose:    Hien thi tai khoan dang dang nhap len goc man hinh
// Parameters:
// - str
// Return:     
///////////////////////////////////////////////////////////////////////////////////////////////
void   printUserLogin(string strName) {
	setColor(Bright_White, Light_Blue);
	system("cls");
	cout << right << setw(79) << setfill(' ') << "Welcome: " + strName.substr(0, 20);
	setColor(Bright_White, Black);
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       formatString
// Purpose:    Xuat chuoi sau khi chuan hoa
// Parameters:
// - Num
// Return:     string
///////////////////////////////////////////////////////////////////////////////////////////////
string formatString(string str) {
	while (str.length() > 0 && str[0] == ' ') {
		str.erase(0, 1);
	}
	while (str.length() > 0 && str[str.length() - 1] == ' ') {
		str.erase(str.length() - 1, 1);
	}
	while (str.find("  ") < str.length()) {
		str.erase(str.find("  "), 1);
	}
	for (int i = 0; i < str.length(); ++i) {
		str[i] = toupper(str[i]);
	}
	return str;
}
string formatString(string str, bool check) {
	while (str.length() > 0 && str[0] == ' ') {
		str.erase(0, 1);
	}
	while (str.length() > 0 && str[str.length() - 1] == ' ') {
		str.erase(str.length() - 1, 1);
	}
	while (str.find("  ") < str.length()) {
		str.erase(str.find("  "), 1);
	}
	if (check == true) {
		for (int i = 0; i < str.length(); ++i) {
			str[i] = toupper(str[i]);
		}
	}
	
	return str;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       searchAcc
// Purpose:    Tim kiem va tra ve chi so thanh vien thanh vien co tai khoan la strAcc
// Parameters:
// - _account
// - strAcc
// Return:     int
///////////////////////////////////////////////////////////////////////////////////////////////
int searchAcc(const vector<Account> &_account, const string &strAcc) {
	int length = _account.size();
	for (int i = 0; i < length; ++i) {
		if (_account[i].accountNo == strAcc) {
			return i;
		}
	}
	return -1;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       searchAcc
// Purpose:    Tim kiem va tra ve chi so cua username dua vao userNo
// Parameters:
// - users
// - strUser
// Return:     int
///////////////////////////////////////////////////////////////////////////////////////////////
int searchUser(const vector<User> &_user, const string &strUser) {
	int length = _user.size();
	for (int i = 0; i < length; ++i) {
		if (_user[i].userNo == strUser) {
			return i;
		}
	}
	return -1;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       searchRoleMap
// Purpose:    Tim kiem va tra ve chi so thanh vien theo strAcc
// Parameters:
// - _accRoleMap
// - strAcc
// Return:     int
///////////////////////////////////////////////////////////////////////////////////////////////
int searchRoleMap(const vector<AccountRoleMap> &_accRoleMap, const string &strAcc) {
	int length = _accRoleMap.size();
	for (int i = 0; i < length; ++i) {
		if (_accRoleMap[i].accountNo == strAcc) {
			return i;
		}
	}
	return -1;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       searchRole
// Purpose:    Tim kiem va tra ve chi so cua role dua vao strRoleID
// Parameters:
// - _accRole
// - strRoleID
// Return:     int
///////////////////////////////////////////////////////////////////////////////////////////////
int searchRole(const vector<Role> &_accRole, const string &strRoleID) {
	int length = _accRole.size();
	for (int i = 0; i < length; ++i) {
		if (_accRole[i].roleID == strRoleID) {
			return i;
		}
	}
	return -1;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       inputGood
// Purpose:    xac dinh viec nhap lieu co thanh cong hay khong
// Parameters:
// Return:     bool
///////////////////////////////////////////////////////////////////////////////////////////////
bool inputGood(void) {
	string str;
	cin.clear();
	getline(cin, str);
	if (str.length() == 0) {
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       searchBook
// Purpose:    Tim kiem va tra ve chi so san phem theo ten
// Parameters:
// - books
// - strName
// Return:     int
///////////////////////////////////////////////////////////////////////////////////////////////
int searchBook(const vector<Book> &books, const string &strName) {
	for (int i = 0; i < books.size(); ++i) {
		if (books[i].bookTitle == strName || books[i].book_no == strName) {
			return i;
		}
	}
	return -1;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       searchBorrowBook
// Purpose:    Tim kiem va tra ve chi so san phem da muon theo ten
// Parameters:
// - borrow_book
// - accountNo
// - strName
// Return:     int
///////////////////////////////////////////////////////////////////////////////////////////////
int searchBorrowBook(const vector<Borrow_Book> &borrow_book, const string &accountNo, const string &strName) {
	for (int i = 0; i < borrow_book.size(); ++i) {

		if (borrow_book[i].accountNo == accountNo && borrow_book[i].acc_Book.bookTitle == strName) {
			return i;
		}
	}
	return -1;
}
int searchBorrowBookID(const vector<Borrow_Book> &borrow_book, const string &accountNo, const string &strName) {
	for (int i = 0; i < borrow_book.size(); ++i) {

		if (borrow_book[i].accountNo == accountNo && borrow_book[i].acc_Book.book_no == strName) {
			return i;
		}
	}
	return -1;
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       getTimeCurr
// Purpose:    Lay ngay thang nam hien tai cua he thong
// Parameters:
// Return:     date_t
///////////////////////////////////////////////////////////////////////////////////////////////
date_t getTimeCurr() {
	time_t t = time(0);   // get time now
	date_t timeCurr;
	struct tm * now = localtime(&t);
	//cout << (now->tm_year + 1900) << '-'
	//	<< (now->tm_mon + 1) << '-'
	//	<< now->tm_mday
	//	<< endl;
	timeCurr.year	= now->tm_year + 1900;
	timeCurr.month	= now->tm_mon + 1;
	timeCurr.day	= now->tm_mday;

	return timeCurr;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       increaseDate
// Purpose:    Cong so ngay
// Parameters:
//- int day
// Return:     date_t
///////////////////////////////////////////////////////////////////////////////////////////////
date_t increaseDate(date_t CurrTime, int day) {
	date_t nextDay;
	int maxDay;
	if (CurrTime.month == 1 || CurrTime.month == 3 || CurrTime.month == 5 ||
		CurrTime.month == 7 || CurrTime.month == 8 || CurrTime.month == 10 || CurrTime.month == 2) {
		maxDay = 31;
	}
	else if (CurrTime.month != 2) {
		maxDay = 30;
	}
	else {
		if ((CurrTime.year % 4 == 0 && CurrTime.year % 100 != 0) || CurrTime.year % 400 == 0) {
			maxDay = 29;
		}
		else {
			maxDay = 28;
		}
	}
	if (CurrTime.month == 12 && (CurrTime.day + day) > maxDay) {
		nextDay.month = 1;
		nextDay.year = CurrTime.year + 1;
		nextDay.day = CurrTime.day + day - maxDay;
	}
	else if ((CurrTime.day + day) > maxDay) {
		nextDay.month = CurrTime.month + 1;
		nextDay.year = CurrTime.year;
		nextDay.day = CurrTime.day + day - maxDay;
	}
	else {
		nextDay.month = CurrTime.month;
		nextDay.year = CurrTime.year;
		nextDay.day = CurrTime.day + day;
	}

	return nextDay;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       operator<
// Purpose:    So sanh 2 ngay
// Parameters:
//- date_t d1, d2
// Return:     bool
///////////////////////////////////////////////////////////////////////////////////////////////
bool operator<(const date_t &d1, const date_t &d2) {
	if (d1.year < d2.year) return true;
	else if (d1.year == d2.year) {
		if (d1.month < d2.month) return true;
		else if (d1.month == d2.month) {
			if (d1.day < d2.day) return true;
			else return false;
		}
		else return false;
	}
	else return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       operator-
// Purpose:    Tru hai ngay
// Parameters:
//- date_t d1, d2
// Return:     int
///////////////////////////////////////////////////////////////////////////////////////////////
int operator-(const date_t &d1, const date_t &d2) {
	if (d1 < d2) {
		return -1;
	}
	else {

		if (d1.year > d2.year) {
			return (d1.day + 31 - d2.day);
		}
		else if(d1.year == d2.year) {
			int maxDay;
			if (d2.month == 1 || d2.month == 3 || d2.month == 5 ||
				d2.month == 7 || d2.month == 8 || d2.month == 10 || d2.month == 2) {
				maxDay = 31;
			}
			else if (d2.month != 2) {
				maxDay = 30;
			}
			else {
				if ((d2.year % 4 == 0 && d2.year % 100 != 0) || d2.year % 400 == 0) {
					maxDay = 29;
				}
				else {
					maxDay = 28;
				}
			}
			if (d1.month > d2.month) {
				return (d1.day + maxDay - d2.day);
			}
			else if (d1.month == d2.month) {
				return (d1.day - d2.day);
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       operator<<
// Purpose:    Xuat ngay
// Parameters:
//- date_t dt
// Return:  ostream
///////////////////////////////////////////////////////////////////////////////////////////////
ostream& operator<<(ostream& os, const date_t &dt)
{
	os << dt.day << '/' << dt.month << '/' << dt.year;
	return os;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       toString
// Purpose:    Chuyen ngay thang nam dang so ve dang chuoi
// Parameters:
// - day
// - month
// - year
// Return:     string
///////////////////////////////////////////////////////////////////////////////////////////////
string toString(date_t dt) {
	ostringstream date;
	date << setw(2) << setfill('0') << dt.day << '/'
		<< setw(2) << setfill('0') << dt.month << '/'
		<< setw(4) << setfill('0') << dt.year;
	return date.str();
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       intTostring
// Purpose:    Chuyen mot so kieu int thanh chuoi kieu string
// Parameters:
// - N
// Return:     string
///////////////////////////////////////////////////////////////////////////////////////////////
string intTostring(int N) {
	stringstream s;
	s << N;
	string ss;
	ss = s.str();
	return ss;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       subTwoDays
// Purpose:    Tru hai ngay voi nhau, tra ve so ngay chenh lech
// Parameters:
// - d1, d2
// Return:     int
///////////////////////////////////////////////////////////////////////////////////////////////
int subTwoDays(const date_t &d1, const date_t &d2) {
	double difference = -1;
	struct tm a = { 0, 0, 0, d1.day, d1.month - 1, d1.year - 1900 };
	struct tm b = { 0, 0, 0, d2.day, d2.month - 1, d2.year - 1900 };

	time_t x = mktime(&a);
	time_t y = mktime(&b);
	if (x != (time_t)(-1) && y != (time_t)(-1)) {
		difference = difftime(y, x) / (60 * 60 * 24);
	}

	return difference;

}

///////////////////////////////////////////////////////////////////////////////////////////////
// Name:       stringToint
// Purpose:    Chuyen mot chuoi sang int
// Parameters:
// Input:       str
// Return:     int
///////////////////////////////////////////////////////////////////////////////////////////////
int stringToint(string str) {
	return atoi(str.c_str());
}