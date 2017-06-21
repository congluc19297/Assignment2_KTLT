#pragma once
#ifndef FUNCTION_H
#define FUNCITON_H
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;
#define MaxRole 4

enum	role_t { QUAN_LY_NGUOI_DUNG, THU_THU, DOC_GIA, NONE };

struct date_t {
	int day;
	int month;
	int year;
};

struct Account {
	string  accountNo;		//Primary key
	string	userNo;		//Foreign Key -> User
	string  password;
	bool	isActive = false;
};

typedef struct {
	string	userNo;		//Primary key
	string	userName;
	string	email;
	string	career;
	date_t	BOD;
} User;

typedef struct {
	string  accountNo;		//Foreign Key -> Account
	string	roleID;			//Foreign Key -> Role
} AccountRoleMap;

typedef struct {
	string	roleID;		//Primary key
	int		countRole;
	role_t  roleDesc[MaxRole];
} Role;

typedef struct {
	string	book_no;
	string	bookTitle;
	string	author;
	int		countBook;
} Book;


typedef struct {
	string		accountNo;
	Book		acc_Book;
	date_t		dateBorrowBook;
	date_t		dateReturnBook;
} Borrow_Book;
/*
	countBook =  n + 2 cua acc_Book => Dang gui thong bao tra sach tre han n ngay
	countBook =  2 cua acc_Book => Dang gui thong bao tra sach kip thoi gian
	countBook =  0 cua acc_Book => Disable, dang gui thong bao muon sach
	countBook =  1 cua acc_Book => Enable, duoc thu thu duyet muon sach
	countBook = -1 cua acc_Book => Gui thong bao tra sach kip thoi han
	countBook = -(n + 1) cua acc_Book => Tra sach cham tre n ngay
*/

struct Customer {
	Account c_accounts;
	User c_users;
	AccountRoleMap c_accRoleMaps;
	Role c_roles;
};

struct NotificationAcc {
	string accountNo;
	string noti;
};

void printStart(void);
void printUserLogin(string);
int searchAcc(const vector<Account> &, const string &);
int searchUser(const vector<User> &, const string &);
int searchRoleMap(const vector<AccountRoleMap> &, const string &);
int searchRole(const vector<Role> &, const string &);
int searchBook(const vector<Book> &, const string &);
int searchBorrowBook(const vector<Borrow_Book> &, const string &, const string &);
int searchBorrowBookID(const vector<Borrow_Book> &, const string &, const string &);
int subTwoDays(const date_t &, const date_t &);
int stringToint(string);
string formatString(string);
string formatString(string, bool);
string toString(date_t dt);
string intTostring(int N);
date_t getTimeCurr(void);
date_t increaseDate(date_t CurrTime, int day);
bool inputGood(void);
bool operator<(const date_t &, const date_t &);
ostream& operator<<(ostream&, const date_t &);
#endif