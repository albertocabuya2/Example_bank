	#include "Interface.h"
	#include <iostream>
	#include <sstream>
	#include <cstring>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	using namespace std;

		Interface::Interface(Bank* banco){

				banco1= banco;
		};
		void Interface::mostrar(){

					char optionkey;
					char* key ;
					char* accnum;
					printf("\033[1;31m\n 							  BIENVENIDO 	");
					printf("\033[0;37m\n 	¿Qué desea hacer?");
					printf("\033[0;37m\n 	Escoja una de las opciones mostradas\n");
					printf("\033[0;31m\n 		->Consultar:\n");
					printf("\033[0;36m				Nombre del banco 			-> \033[1;32m'n'\n");
					printf("\033[0;36m 				Cliente          			-> \033[1;32m'p'\n"); 
					printf("\033[0;36m 				Cuenta           			-> \033[1;32m'c'\n"); 
					printf("\033[0;31m\n 		->Cliente:\n");
					printf("\033[0;36m				Crear cliente 				-> \033[1;32m'm'\n");
					printf("\033[0;36m				Actualizar datos cliente 		-> \033[1;32m'u'\n");
					printf("\033[0;31m\n 		->Cuenta:\n");
					printf("\033[0;36m				Crear cuenta 					-> \033[1;32m'a'\n");
					printf("\033[0;36m				Transferir 					-> \033[1;32m't'\n");
					printf("\033[0;36m				Cambiar estado cuenta 				-> \033[1;32m'e'\n");
					printf("\033[0;36m				Depositar 					-> \033[1;32m'd'\n");
					printf("\033[0;36m				Retirar dinero					-> \033[1;32m'r'\n");
					printf("\033[0;31m\n 		->Banco:\n");
					printf("\033[0;36m				Transferir entre bancos 	-> \033[1;32m'k'\n");
					printf("\033[0;36m				Recibir transferencia 		-> \033[1;32m'i'\n");
					std::cin>>optionkey ;
					char* id_client = new char [20];
					switch(optionkey){
						
						case 'N':
						case 'n':printf("\033[1;36m\n 		*Nombre del banco= %s \n",banco1-> get_name());
					break;
						case 'I':
						case 'i':{
							banco1->receivetransfer();
							cout<<"Transferencia hecha"<<endl;
						
						}
						break;
						case 'K':
						case 'k':{
							char* id_cuenta = new char[20];
							std::cout << "Ingrese el numero de su cuenta" << endl;
							cin >> id_cuenta;
							char* contra = new char[10];
							std::cout << "Ingrese su contraseña" << endl;
							cin >> contra;
							int money = 0;
							int salir=0;
							do{
									try{
								std::cout << "Ingrese el dinero a transferir" << endl;
								cin >> money;
								if(!cin)
									throw 125;
								salir=1;
								}catch(int){
									std::cout<<"\nCantidad no valida"<<std::endl;
									cin.clear();
									cin.ignore();

								}
							}while(salir==0);
							std:cout<<"\nInserte el nombre del banco donde se va a depositar"<<std::endl;
							char* bankname= new char[20];
							cin>> bankname;
							std::cout<< "\nInserte el numero de cuenta a donde va a transferir"<<endl;
							char* accnum2= new char[20];
							cin >> accnum2;
							int transferstate;
							
							do{
							 transferstate = banco1->TransferinterBank(money, bankname, accnum2,id_cuenta ,contra);
							 //-1 banco no encontrado
							//-2 cuenta bloqueada
							// -3 Dinero unsuficiente inexistente
							//-4 contraseña incorrecta
							//-5 banco ocupado
							 if (transferstate==-5)
							 {
							 	
							 	std::cout<<"digite cualquier tecla para intentar de nuevo la acción"<<std::endl;
							 	getchar();
							 }
							 else if(transferstate==-1){
							 	cout << "\nError banco no encontrado" << endl;
							 	
							 }
							 else if(transferstate==-2){
							 	std::cout << "\nCuenta local bloqueada" << endl;
							 	
							 }
							 else if (transferstate==-3){
							 	std::cout << "\nNo hay suficiente dinero en la cuenta" << endl;
							 	
							 }
							 else if (transferstate==-4)
							 {
							 	std::cout << "\nDatos de cuenta incorrectos" << endl;
							 	
							 }
							//printf("kks" );
							}while(transferstate==-5);
	
						
							
							}
						break;
					case 'P':
						case  'p':{ 
							printf("\033[1;37m\n 	->Inserte numero de identificacion del cliente\n");
							id_client = new char [20];
							std::cin >> id_client;
							Client_information* cliente = banco1->consult_client(id_client);
							if(cliente==NULL){ printf("\033[0;37m 				Clientre no encontrado"); }
							else {
								printf("\033[0;36m 		*Nombre: %s \n",cliente->firstName);
								printf("\033[0;36m 		*Apellido: %s \n",cliente->lastName);
								printf("\033[0;36m 		*Id: %s \n",cliente->id_client);
								printf("\033[0;36m 		*Cuentas: \n");
								char* a;
								for (int i = 0; i < cliente->nAccount; i++) {
									a = cliente->accounts[i];
									printf("\033[0;36m 		Numero de Cuenta [%i] =  %s\n",i,a);
								}
							}
						}
						break;
						
						case 'C':
						case 'c' :{
							char* id_cuenta = new char[20];
							printf("\033[0;37m 	->Ingrese numero de la cuenta \n");
							cin >> id_cuenta;
							char* contra = new char[10];
							printf("\033[0;37m 	->Ingrese su contraseña \n");
							cin >> contra;
							Account_information* cuenta = banco1-> consult_account(id_cuenta, contra);
							if (cuenta != NULL) {
								Client_information* cliente = banco1->consult_client(cuenta->cliente->id_client);

								printf("\033[0;36m 		*Propietario: %s %s \n",cliente->firstName ,cliente->lastName);
								printf("\033[0;36m 		*Id Cliente: %i \n",(atoi)(cliente->id_client));
								printf("\033[0;36m 		*Id Cuenta: %i \n",(atoi)(cuenta->id_account));
								
								char state[10];
								if (cuenta->state) {
									printf("\033[0;36m 		*Estado: Activo\n");
								}
								else
								{
									printf("\033[0;31m 		*Estado: Inactivo\n");
								}
								
								printf("\033[0;36m 		*Saldo: %i $\n",cuenta->balance);
							}
							else {
								printf("\033[0;31m 		No se encontro la cuenta o contraseña incorrecta \n");
							}

						}
						break; 
						
						case 'M':
						case 'm':{ 
								printf("\033[0;37m 		->Inserte nombre del cliente: \n");
								char*nameclient= new char[15];
								cin>> nameclient+0;
								
								printf("\033[0;37m 		->Inserte apellido del cliente: \n");
								char*lastnameclient = new char[15];
								cin>> lastnameclient + 0;
							
								printf("\033[0;37m 		->Inserte numero de identificacion del cliente: \n");
								char* id = new char[20];
								cin>> id + 0;
							
								printf("\033[0;37m 		->Inserte edad del cliente: \n");
								int age;
								cin>> age;
								
								int a = banco1->get_how_accounts();
								char* id_account = new char[10];
								sprintf(id_account, "%d\0", a);

								printf("\033[1;36m 		Se le asigno la cuenta número: %i \n",atoi(id_account));

								key = ask_key();
								int initial_amount = ask_deposit_money();

								bool state= banco1-> create_client(nameclient, lastnameclient, id, age, id_account, key, initial_amount);
							    if(state){
									printf("\033[1;36m 		Cliente creado \n");
							    }
							    else{
									printf("\033[0;31m 		No se logoro realizar la acción \n");
							    }
							}
						break;
						
						case 'U':
						case 'u':{
							
							printf("\033[0;37m 		->Inserte numero de identificacion del cliente: \n");
								id_client = new char[20];
								cin >> id_client;
								bool  clinetstate= banco1->id_client_exist(id_client);
								if(clinetstate){
									BankClient* cliente; 
									Client_information* client; 
									char* tecla = new char[2];
										cliente = banco1->select_client(id_client);
										client = banco1->consult_client(id_client);
										printf("\033[0;37m 			Hola %s %s.\n 			¿Qué parametro desea modificar? \n",client->firstName,client->lastName);
										printf("\033[0;36m 			1) Nombre\n");
										printf("\033[0;36m 			2) Apellido\n");
										printf("\033[0;36m 			3) Id\n");
										printf("\033[0;36m 			4) Edad\n");
										printf("\033[0;36m 			5) Todo\n");
										printf("\033[0;36m 			E) Salir\n");
										cin >> tecla;
										bool indic = false;
										char* name = new char[20];
										char* lastname = new char[20];
										char* ID = new char[20];
										int age = 0;
										switch (*tecla)
										{
										case '1':
											printf("\033[0;37m 		->Inserte su nuevo Nombre \n");
											cin >> name;
											indic = banco1->update_client(cliente, name, cliente->get_lastName(), cliente->id_client, cliente->get_age());
											printf("Interface %s\n",cliente->get_firstName());
											break;
										case '2':
											printf("\033[0;37m 		->Inserte su nuevo Apellido \n");
											cin >> lastname;
											indic = banco1->update_client(cliente, cliente->get_firstName(), lastname, cliente->id_client, cliente->get_age());
											break;
										case '3': 
											printf("\033[0;37m 		->Inserte su nuevo ID \n");
											cin >> ID;
											indic = banco1->update_client(cliente, cliente->get_firstName(), cliente->get_lastName(), ID, cliente->get_age());
											id_client = ID;
											break; 
										case '4': 
											printf("\033[0;37m 		->Inserte su nueva Edad \n");
											cin >> age;
											indic = banco1->update_client(cliente, cliente->get_firstName(), cliente->get_lastName(), cliente->id_client, age);
											break;
										case '5': 
											printf("\033[0;37m 		->Inserte su nuevo Nombre \n");
											cin >> name;
											printf("\033[0;37m 		->Inserte su nuevo Apellido \n");
											cin >> lastname;
											printf("\033[0;37m 		->Inserte su nuevo ID \n");
											cin >> ID;
											printf("\033[0;37m 		->Inserte su nueva Edad \n");
											cin >> age;
											indic = banco1->update_client(cliente, name, lastname, ID, age);
											id_client = ID;

											break;
										default: 
											printf("\033[0;31m 		Tecla no valida.\nPor favor ingrese segun el menu \n");
											break;
										}
										if (indic) {
											printf("\033[1;36m 		Datos Actualizados con Exito \n");
										}
										else {
											printf("\033[0;31m 		No se ha podido realizar operacion \n");
										}
									delete tecla;
								}
								
								else {
									printf("\033[0;31m 		Cliente no encontrado \n");
								}


							}
						break;
						
						case 'A':
						case 'a':{
							
							printf("\033[0;37m 		->Inserte numero de identificacion del cliente: \n");
							char* client_id = new char[20];
							cin >> client_id;

							bool clientexists= banco1-> id_client_exist(client_id);

							if(clientexists){
									BankClient* clientee= banco1->select_client(client_id);
									int money= ask_deposit_money();
									key= ask_key();
									printf("Exito2\n");
									int a = banco1->get_how_accounts();
									printf("Exito3\n");
									char* id_account = new char[10];
									printf("Exito4\n");
									sprintf(id_account, "%d\0", a);
									printf("Exito5\n");
									printf("\033[1;36m 		Numero de cuenta: %s\n",id_account);
									bool createclientstate= banco1->create_account(id_account, key, clientee, money );
									 if(createclientstate){
										 printf("\033[1;36m 		Cuenta creada \n");
									}
									else {
										 printf("\033[0;31m 		No se pudo realizar la operacion \n");
									}

							}
							else{
								printf("\033[0;31m 		Cliente no encontrado \n");

								printf("\033[0;37m 		->Crear Cliente \n");

								printf("\033[0;37m 		->Inserte nombre del cliente: \n");
								char*nameclient= new char[15];
								cin>> nameclient+0;
								
								printf("\033[0;37m 		->Inserte apellido del cliente: \n");
								char*lastnameclient = new char[15];
								cin>> lastnameclient + 0;

							
								printf("\033[0;37m 		->Inserte edad del cliente: \n");
								int age;
								cin>> age;
								
								int a = banco1->get_how_accounts();
								char* id_account = new char[10];
								sprintf(id_account, "%d\0", a);

								printf("\033[1;36m 		Se le asigno la cuenta Numero: %s \n", atoi(id_account));

								key = ask_key();
								int initial_amount = ask_deposit_money();

								bool state= banco1-> create_client(nameclient, lastnameclient, client_id, age, id_account, key, initial_amount);

								if (state) {
									printf("\033[1;36m 		Cuenta creada \n");
								}
								else {
									printf("\033[0;31m 		No se logoro realizar la accion \n");
								}
							}
						}
						break;
						
						case 'T':
						case 't':{
							char* id_cuenta = new char[20];
							printf("\033[0;37m 		->Ingrese el numero de su cuenta \n");
							cin >> id_cuenta;
							char* contra = new char[10];
							printf("\033[0;37m 		->Ingrese su contraseña \n");
							cin >> contra;
							int money = 0;
							int salir=0;
							do{
								try{
							printf("\033[0;37m 		->Ingrese el dinero a transferir \n");
							cin >> money;
							if(!cin)
								throw 125;
							salir=1;
							}catch(int){
								printf("\033[0;31m 		Cantidad no valida \n");
								cin.clear();
								cin.ignore();

							}
						}while(salir==0);
							printf("\033[0;37m 		->Inserte el numero de cuenta a donde va a transferir \n");
							char* accnum2= new char[20];
							cin >> accnum2;

							bool transferstate = banco1->transfer_money(id_cuenta, contra, accnum2, banco1, money);
							if (transferstate) {
								printf("\033[1;36m 		Transferencia realizada \n");
							}
							else { printf("\033[0;31m 		Error en la transferencia \n"); }
						
						}
							break;

						case 'E':
						case 'e':{
							char* id_cuenta = new char[20];
							printf("\033[0;37m 		->Ingrese numero de la cuenta \n");
							cin >> id_cuenta;
							char* contra = new char[10];
							printf("\033[0;37m 		->Ingrese su contraseña \n");
							cin >> contra;
							printf("\033[0;37m 		->Presione 1 para activar la cuenta y 2 o cualquier tecla para bloquear \n");
							char getstatus;
							getchar();
							 getstatus = getchar();
							bool status;
							printf("%c\n",getstatus );
							switch (getstatus)
							{
							case '1':
								status = true;
								break;
							case '2':
								status = false;
								break;
							default:
								status= false;
								break;
							}
							
								bool askopstate = banco1->block_unblock_account(id_cuenta, contra, !status);
								if (askopstate) printf("\033[1;36m 		Proceso realizado correctamente \n");
								else printf("\033[0;31m 		Proceso no completado satisfactoriamente \n");
							
							

						}
							break;

						case 'D':
						case 'd':{
							char* id_cuenta = new char[20];
							printf("\033[0;37m 		->Ingrese numero de la cuenta \n");
							cin >> id_cuenta;
							int money = ask_deposit_money();
							
							
							bool status = false;
							if (banco1->get_how_accounts()!=0) {
								status = banco1->deposit(id_cuenta, money);
							}
							if(status) printf("\033[1;36m 		Proceso realizado correctamente \n");
							else printf("\033[0;31m 		Proceso completado insatisfactoriamente, por favor verifique los datos \n");
						}
						break;
						
						case 'R':
						case 'r':{
							char* id_cuenta = new char[20];
							printf("\033[0;37m 		->Ingrese numero de la cuenta \n");
							cin >> id_cuenta;
							char* contra = new char[10];
							printf("\033[0;37m 		->Ingrese su contraseña \n");
							cin >> contra;
							int money = 0;
							int salir=0;
							do{
							try{
								printf("\033[0;37m 		->Ingrese el dinero a retirar\n");
								cin >> money;
								if(!cin)
									throw 125;
								salir=1;
							}catch(int){
									printf("\033[0;31m 		Cantidad no valida \n");
									cin.clear();
									cin.ignore();
								}
							}while(salir==0);
							int saldo = -1;
							if (banco1->get_how_accounts() != 0 && banco1->id_account_exist(id_cuenta)) {
								saldo = banco1->withdrawal(id_cuenta, money, contra);
								if (saldo == -1) {
									printf("\033[0;31m 		No tiene suficiente dinero \n");
								}
								else {
									ask_consulsaldo(saldo);
								}
							}
							else {
								printf("\033[0;31m 		No se pudo realizar el retiro, verifique los datos \n");
							}
						}
						break;
						default:{
							printf("\033[0;31m 		Opcion no valida \n");
						}
						break;

					}	
		}
		char* ask_accountnum(){
			printf("\033[0;37m 		->Inserte su numero de cuenta \n");
						char* accnum = 0;
						cin >> accnum ;
						return accnum;
		}
		char* ask_key(){
			printf("\033[0;37m 		->Inserte la clave de su cuenta \n");
			char* enteredkey= new char[20];
			cin>> enteredkey;
			//printf("Exito" );
			return enteredkey;
		}

		int ask_deposit_money(){
			
			int money=0;
			do{
				try{
					printf("\033[0;37m 		->Digite la cantidad de dinero a depositar \n");		
					cin>> money;
					 if(!cin)
		            throw 127;
					return money;
				}catch(int ){
					printf("\033[0;31m 		Cantidad no valida \n");
					cin.clear();
					cin.ignore();
					money=0;
				}
			}while(1);
		}
		bool ask_status(){
			printf("\033[0;37m 		->Presione 1 para activar la cuenta y 2 para bloquear \n");
			char* getstatus = new char[10];
			cin>> getstatus;
			switch (*getstatus)
			{
			case 'a':
			case 'A':
				return true;

			case 'b':
			case 'B':
				return false;
			default: 

				break;
			}
		}
		void ask_consulsaldo(int saldo){
			printf("\033[0;37m 		Desea consultar su saldo? y:si, n:no\n");
			char op;
			cin>> op;
			switch(op){
				case'y':
					printf("\033[1;36m 		Su saldo es: %i",saldo);
				case 'n':
				break;
				default:
					printf("\033[0;31m 		Opcion no valida \n");
				break;
			}
		} 
		char* ask_name(){
			printf("\033[0;37m 		->Inserte su nombre \n");
			char* name= new char[20];
			cin>> name ;
			return name;
		}
		char* ask_lastname(){
			printf("\033[0;37m 		->Inserte su apellido \n");
			char* lastname= new char[20];
			cin>> lastname;
			return lastname;
		}
		int ask_age(){
			do{
				try{
				printf("\033[0;37m 		>Inserte su edad \n");
				int age;
				cin>> age;
					if(!cin)
		            throw 127;
					return age;
				}catch(int ){
					printf("\033[0;31m 		Cantidad no valida \n");
					cin.clear();
					cin.ignore();
				
				}
			}while(1);
		}
		char* ask_id(){
			printf("\033[0;37m 		->Inserte id de la cuenta \n");
			char* acc_id = 0;
			cin>> acc_id;
			return acc_id;
		}
		char* ask_id_client(){
			printf("\033[0;37m 		->Inserte id del cliente \n");
			char* acc_id= new char [12];
			cin>> acc_id;
			return acc_id;
		}