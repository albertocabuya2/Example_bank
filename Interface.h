	#ifndef  INTERFACE_H
	#define INTERFACE_H
	#include "Bank.h"

			char* ask_accountnum();
			char* ask_key();
			int ask_deposit_money();
			bool ask_status();
			void ask_consulsaldo(int);
			char* ask_name();
			char* ask_lastname();
			int ask_age();
			char* ask_id();
			char* ask_id_client();
			//int TransferinterBank(int , char *, char *);
			class Interface{

				public:
					Bank* banco1;
					Interface(Bank*);
					void mostrar();
					
			};

		#endif 