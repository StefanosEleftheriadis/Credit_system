#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <windows.h>
#include <cmath>
#include  <bits/stdc++.h>
#define ArraySize 50

using namespace std;

class files{
	public:
		files(FILE *Cfile_ptr);
		bool EmptyFileYN();
		void create_bfile();
		void customer();
		void admi_menu();
		void create_tfile();
		int name_size(int Sizes[ArraySize]);
		void create_record();
		void update_record();
		void delete_record();
		void transaction();
	private:
		FILE *file_ptr;	
};

struct clientData
{
	int account_number;
	char customer_name[100];
	float current_balance;
	float credit_limit;
};
