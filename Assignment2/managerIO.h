#pragma once
#ifndef MANAGERIO_H
#define MANAGERIO_H

#include <fstream>
#include "LibsWindow.h"
#include "functions.h"

void printWarn(string);
void printTitle(string);
void processUserChoose(const int, int &, const int);
void printMenu(const string[], const int, const int);
void printBook(const vector<Borrow_Book> &, const Customer &);
void printSingleBook(const Book &);
void printAccount(const vector<Account> &, const vector<User> &);
void printAccDetail(Account, const vector<User> &, const vector<Role> &, const vector<AccountRoleMap> &);
void printUser(const User &);
void printRole(const Role &, const AccountRoleMap &);
void printBorrowBook(const vector<Borrow_Book> &);
void printBookDetail(const vector<Book>&, const int &);
void inputRole(string, role_t []);
string inputUserName(void);
string inputPassword(string);
string inputString(string);
string inputString(string, bool);
date_t inputDate(string request);
int inputInt(string request);
#endif