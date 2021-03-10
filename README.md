# Lab1 Banco.Cardenas Javier-Cabuya Alberto-Roncancio Brayan 

# Laboratorio 1 Banco
A continuación se desarrolla una breve explicación de cada una de las clases,
y sus métodos, utilizados para el desarrollo del laboratorio.

## BankClient
Esta clase de BankClient, como su nombre lo indica representa los métodos 
y propiedades que tiene el cliente del banco, estos se pueden encontrar de
manera reducida en el BankClient.h, como se muestra en este código:

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

	char** get_accounts();

	int nAccounts();

	};

	#endif
Donde se decidió hacer las propiedades privadas, para protegerlas de cambios
no deseados, y se puede observar que basicamente las propiedades que se tienen,
son para consultar y editar las propiedades de cliente, se puede observar que 
cliente, no necesariamente depende de cuenta, pero para la aplicación si 
debido a que para crear un cliente, este debe tener una cuenta, o si no, no 
seria cliente, cabe resaltar que en el BankClient.cpp, solo hay que incluir la libreria BankClient.h, debido a que todas las otras ya se incluyeron en dicho codigo.

## BankAccount
En esta clase se encuerntra descrito, las propiedades y métodos de una cuenta
creada en el banco, al igual que en la clase anterior, las propiedades estan privadas, para protejerlas, los métodos creados en dicha clase se fundamentan en 
consultar, o editar las propiedades de la  cuenta, como se observa en el .h

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

Cabe destacar que el balance utilizado, sirve para saber la cantidad de dinero
que tiene la cuenta, es decir, este método tiene como fin controlar las finanzas del Banco, esto con el fin de evitar que usuarios le deban al mismo, esta 
comprobación se hace en el metódo de Retirar; se puede observar que BankAccount
depende directamente de BankClient, debido a que si no se tiene un cliente, que se representa por la clase BankClient, no se va a poder contar con un número de cuenta.

## Bank
Esta clase es la más compleja, debido a que en esta clase se usan las clases creadas anteriormente,
además sus metódos no tienen nada más la función de consulta y edición, sino que también involucra 
procesos lógicos para comprovar los valores de identificación de cliente, cuenta,
contraseña de cada cliente, y la cantidad de clientes y cuentas que posee el banco, 
con el propocito de generar identificaciones de cuentas, esto con el fin de evitar cruce de datos.
Las funciones resumidas se pueden observar en el Bank.h. 
	
	#ifndef BANK_H
	#define BANK_H

	#include "BankAccount.h"
	#include "BankClient.h"
	#include <iostream>
	#include <string>
	#include <sstream>

	struct Account_information{
	char* id_account;
	bool state;
	int balance;
	BankClient* cliente;
	Account_information() {
		id_account = 0;
		state = 0;
		balance = 0;
	}
	};

	struct Client_information{
	char* firstName;
	char* lastName;
	char* id_client;
	char** accounts;
	int nAccount;

	Client_information() {
		firstName = 0;
		lastName = 0;
		id_client = 0;
	}
	};

	class Bank
	{
	char* name;
	BankClient** list_clients;
	BankAccount** list_accounts;
	int How_many_client; 
	int How_many_account;
	int next_account;
	int initial_accounts;
	int initial_clients; 

	public:
	Bank(char*, BankClient**, BankAccount**);
	~Bank();

	char* get_name();

	bool create_client(char*, char*, char*, int, char**); 

	bool create_client(char*, char*, char*, int, char*, char*, int);

	bool update_client(BankClient*, char*, char*, char*, int);

	Client_information* consult_client(char* id_client);

	bool create_account(char*, char*, BankClient*, int);

	Account_information* consult_account(char*, char*);

	bool block_unblock_account(char*, char*, bool);

	bool deposit(char*, int);

	int withdrawal(char*, int, char*);

	bool transfer_money(char*, char*, char*, Bank* banco, int);	

	bool id_account_exist(char*);

	bool id_client_exist(char*);
	
	BankAccount* select_count(char*);

	BankClient* select_client(char*);
	
	BankClient* select_client_lastName(char*);

	int get_how_accounts();

	void fail_account();

	int LongitudCadena(char*);
	};
	
	#endif

Como se puede observar en el Bank.h, en esta clase se realiza por decir el proceso pesado del Banco, pues en este código se lleva a cabo la selección de cuenta, el conteo de número de cuentas por cliente, la selección de cliete, consulta de cuenta, etc... En cuestión, esta clase se podria tomar como el eje central del funcionamiento del banco, pues es la que se encarga de enlazar los procesos de las clases BankAccount y BankClient.  

## main
En la funcion main, se tiene la parte gráfica del programa, además, que es el archivo, que une todas las clases descritas anteriormente, y en si es en donde se hace toda la comunicación con el usuario, a con tinuación se mostraran las funciones y variables que se usaron para este programa:


	#ifndef MAIN_H
	#define MAIN_H

	#include "Bank.h"
	#include <curses.h>	
	#include <iostream>
	#include <sstream>
	#include <cstring>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>


	using namespace std;

	char exitkey;
	char optionkey;
	char* key ;
	char* accnum;
	int main (int, char**);	
	char* ask_name();
	char* ask_lastname();
	int ask_age();
	char* ask_id();
	char* ask_id_client();
	void ask_consulsaldo(int);
	bool ask_status();
	int ask_deposit_money();
	char* ask_key();
	char* ask_accountnum();
	#endif
