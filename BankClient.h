
#ifndef BANKCLIENT_H
#define BANKCLIENT_H

#include<iostream>
#include<string>
#include<stdio.h>

#include "BankAccount.h"

class BankClient
{
		char* firstName;
		char* lastName;
		int age;
		char** id_accounts;
		int how_many_accounts;
		int initial_accounts;

public: 

		char* id_client;
		
	BankClient(char*, char*, char*, int, char**);

	void Update_data(char*, char*, char*, int, char**);

	void Add_account(char*);

	bool Delete_account(char*);

	char* get_firstName();

	char* get_lastName();

	char* get_id();

	int get_age();

	char** get_accounts();

	int nAccounts();
	int TransferinterBank(int , char * ,char * );

};

#endif
