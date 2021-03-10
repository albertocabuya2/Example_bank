
#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include "BankClient.h"

class BankAccount{

	//Propiedades

	bool accState; //true = activo, false = inactivo
	char* key;
	int balance;
	char* id_client;

public:
	char* accountnumber;

	//Constructor
	BankAccount(char*, char*, char*, int);

	//Metodos
 	void Block();
 	void UnBlock();
 	bool CheckKey(char*);
 	void deposit(int);
 	bool Retirar(int);
 	bool updateKey(char*);
	bool ConsultState();
	int ConsultBalance();
	char* ConsultUser();
	void ChangeClient(char*);
};

#endif
