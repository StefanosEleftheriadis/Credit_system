#include "interface.h"

//Constructor
//********************************************
files::files(FILE *Cfile_ptr)
{
	file_ptr=Cfile_ptr;
}
//********************************************

//Administrator Menu
//********************************************
void files::admi_menu()
{
	struct clientData Client={0,"",0.0,0.0};
	bool empty_file=false;
	int choice;
	
	system("CLS");
	
	do{
		printf("1.Create Account\n2.Delete Account\n3.Update Account\n4.Exit\nChoice: ");
		scanf("%d",&choice);
				
		switch(choice)
		{
			case 1:
					files::create_bfile();
					system("pause");
					break;
			case 2:
					if((file_ptr=fopen("credit.dat","r+"))!=NULL)
					{
						empty_file=files::EmptyFileYN();
						
						if(!empty_file)
						{
							files::delete_record();
						}
						else
						{
							printf("The binary file is empty!\n");
						}
						fclose(file_ptr);
					}
					system("pause");
					break;
			case 3:
					if((file_ptr=fopen("credit.dat","r+"))!=NULL)
					{
						empty_file=files::EmptyFileYN();
						
						if(!empty_file)
						{
							files::update_record();
						}
						else
						{
							printf("The binary file is empty!\n");
						}
						fclose(file_ptr);
					}
					system("pause");
					break;		
			case 4:
					cout<<"Exit from administrator!"<<endl;
					break;		
			default:
					printf("Wrong Input!\n");
					system("pause");
					break;						
		}
		
		system("CLS");
	}while(choice!=4);
}



//Update Account
void files::update_record()
{
	struct clientData Client={0,"",0.0,0.0};
	
	fread(&Client,sizeof(struct clientData),1,file_ptr);
	fseek(file_ptr,(Client.account_number/50-1)*sizeof(struct clientData),SEEK_SET);
	
	fflush(stdin);
	printf("Enter Name: ");
	cin.getline (Client.customer_name,100);
	
	fflush(stdin);
	printf("Enter Credit Limit: ");
	scanf("%f",&Client.credit_limit);
	
	fwrite(&Client,sizeof(struct clientData),1,file_ptr);
	fseek(file_ptr,(Client.account_number/50-1)*sizeof(struct clientData),SEEK_SET);
}

//Delete Account
void files::delete_record()
{
	struct clientData blankClient={0,"",0.0,0.0};
	
	fwrite(&blankClient,sizeof(struct clientData),1,file_ptr);
	fseek(file_ptr,(blankClient.account_number/50-1)*sizeof(struct clientData),SEEK_SET);
	
	printf("Successfully deleted!\n");
}

//Create Binary File
void files::create_bfile()
{
	struct clientData Clientlist={0,"",0.0,0.0};
	int counter;
	char exit;
	
	if((file_ptr=fopen("credit.dat","w"))!=NULL)
	{
		for(counter=1;counter<=200;counter++)
		{
			fwrite(&Clientlist,sizeof(struct clientData),1,file_ptr);
		}
		
		printf("Now write the records!\n");
		
		counter=1;
		
		do{
			fflush(stdin);
			printf("Enter Name[%d]:",counter);
			cin.getline (Clientlist.customer_name,100);
			
		
			do{
				fflush(stdin);
				printf("Enter account number[%d]: ",counter);
				scanf("%d",&Clientlist.account_number);
			
				if(Clientlist.account_number%50!=0 || Clientlist.account_number>10000 || Clientlist.account_number<50)
				{
					printf("Wrong Input!\n");
				}
				
			}while(Clientlist.account_number%50!=0 || Clientlist.account_number>10000 || Clientlist.account_number<50);
		
			Clientlist.current_balance=0;
			
			fflush(stdin);
			printf("Enter Credit Limit[%d]: ",counter);
			scanf("%f",&Clientlist.credit_limit);
		
			fseek(file_ptr,(Clientlist.account_number/50-1)*sizeof(struct clientData),SEEK_SET);
			fwrite(&Clientlist,sizeof(struct clientData),1,file_ptr);
			
			fflush(stdin);
			printf("If you want to stop entering clients, enter Y: ");
			scanf("%c",&exit);
			
			counter++;
			
		}while(exit!='Y');
		fclose(file_ptr);
	}
	else
	{
		printf("The file couldn't be created!\n");
	}
}
//********************************************

//Check if the binary file is empty
//********************************************
bool files::EmptyFileYN()
{
	struct clientData Client={0,"",0.0,0.0};
	
	while(!feof(file_ptr))
	{
		fread(&Client,sizeof(struct clientData),1,file_ptr);
		
		if(Client.account_number!=0)
		{
			return false;
		}
	}
	
	return true;
}
//********************************************

//Customer Input
//********************************************
void files::customer()
{
	struct clientData Client={0,"",0.0,0.0};
	int accountNum,value;
	char new_accountYN,exit;
	char customerName[20];
	float creditLimit;
	
	do{
			system("CLS");
		do{
			
			printf("Enter account number(50-20000): ");
			scanf("%d",&accountNum);
		
			if(accountNum%50!=0 || accountNum>10000 || accountNum<50)
			{
				printf("Wrong Input!\n");
			}
		}while(accountNum%50!=0 || accountNum>10000 || accountNum<50);
		
		fseek(file_ptr,(accountNum/50-1)*sizeof(struct clientData),SEEK_SET);
		fread(&Client,sizeof(struct clientData),1,file_ptr);
	
	
		if(Client.account_number!=0)
		{
			fseek(file_ptr,(accountNum/50-1)*sizeof(struct clientData),SEEK_SET);
			system("CLS");
			files::transaction();
		}
		else
		{
			do{
				fflush(stdin);
				printf("Is this a new account number?(Y or N): ");
				scanf("%c",&new_accountYN);
			
				if(new_accountYN!='Y' && new_accountYN!='N')
				{
					printf("Wrong Input!\n");
				}
			}while(new_accountYN!='Y' && new_accountYN!='N');
		
		
			if(new_accountYN=='N')
			{
				printf("Invalid account number-re-enter data\n");
			}
			else
			{
				system("CLS");
				
				fseek(file_ptr,(accountNum/50-1)*sizeof(struct clientData),SEEK_SET);
				fread(&Client,sizeof(struct clientData),1,file_ptr);
				
				Client.account_number=accountNum;
				
				fseek(file_ptr,(Client.account_number/50-1)*sizeof(struct clientData),SEEK_SET);
				fwrite(&Client,sizeof(struct clientData),1,file_ptr);
				fseek(file_ptr,(Client.account_number/50-1)*sizeof(struct clientData),SEEK_SET);
				
				files::create_record();
			}
		}
		
		fflush(stdin);
		printf("If you want to exit from the customr checking enter Y: ");
		scanf("%s",&exit);
		
	}while(exit!='Y');
}
//Transaction
void files::transaction()
{
	SetConsoleOutputCP(1253);
	
	struct clientData Client={0,"",0.0,0.0};
	float money=0.0;
	bool wrong_money=false;
	
	fread(&Client,sizeof(struct clientData),1,file_ptr);
	fseek(file_ptr,(Client.account_number/50-1)*sizeof(struct clientData),SEEK_SET);
	
	do
	{
		wrong_money=false;
		printf("Enter account number(50-20000): %d\n",Client.account_number);
		printf("Enter amount of purchase: ");
		scanf("%f",&money);
		
	
		if(Client.current_balance+money<=Client.credit_limit)
		{
			Client.current_balance+=money;
			printf("Dear %s thank you for the business!\n",Client.customer_name);
			system("pause");
		}
		else
		{
			wrong_money=true;
			printf("Dear %s we cannot authorise this purchase at this time as it would put your current balance %c%.2f above your credit limit.\n",Client.customer_name,128,fabs(Client.credit_limit-money-Client.current_balance));
			system("pause");
		}
		
		system("CLS");
	}while(wrong_money);
	
	fwrite(&Client,sizeof(struct clientData),1,file_ptr);	
	fseek(file_ptr,(Client.account_number/50-1)*sizeof(struct clientData),SEEK_SET);
}

//New_record
void files::create_record()
{
	struct clientData Client={0,"",0.0,0.0};
	char temp_char;
	
	fread(&Client,sizeof(struct clientData),1,file_ptr);
	fseek(file_ptr,(Client.account_number/50-1)*sizeof(struct clientData),SEEK_SET);
	
	fflush(stdin);
	printf("Enter Name: ");
	cin.getline (Client.customer_name,100);
		
	Client.current_balance=0;
	
	fflush(stdin);
	printf("Enter Credit Limit: ");
	scanf("%f",&Client.credit_limit);
	
	fwrite(&Client,sizeof(struct clientData),1,file_ptr);
	fseek(file_ptr,(Client.account_number/50-1)*sizeof(struct clientData),SEEK_SET);
	
	printf("Successfully created!\n");
}
//********************************************

//Find the size of names
//*******************************************
int files::name_size(int Sizes[ArraySize])
{
	struct clientData Client={0,"",0.0,0.0};
	int counter,char_count,max_size, NSize_customer_count=0;
	char name[20];
	
	//Calculate the size of every name
	while(!feof(file_ptr))
	{
		char_count=0;
		fread(&Client,sizeof(struct clientData),1,file_ptr);
		strcpy(name,Client.customer_name);
		
		while(name[char_count]!='\0')
		{
			Sizes[NSize_customer_count]++;
			char_count++;
		}
		
		if(Client.account_number!=0)
		{
			Sizes[NSize_customer_count]++;
			NSize_customer_count++;
		}
	}
	
	//Find the maximum size of address
	max_size=Sizes[0];
	for(counter=1;counter<=NSize_customer_count;counter++)
	{
		if(max_size<Sizes[counter])
		{
			max_size=Sizes[counter];
		}
	}
	
	return max_size;
}
//********************************************

//********************************************
//Text File
void files::create_tfile()
{
	FILE *textfile_ptr;
	struct clientData Client={0,"",0.0,0.0};
	int Names_size[ArraySize]={0},Max_Size=0,icount,counter=0;
	
	if((file_ptr=fopen("credit.dat","r"))!=NULL)
	{
		if((textfile_ptr=fopen("creditTextFile.txt","w"))!=NULL)
		{
			Max_Size=name_size(Names_size);
			rewind(file_ptr);
			
			fprintf(textfile_ptr,"%s","Customer Name");
	
			if(Max_Size-13>0)
			{
				for(icount=0;icount<Max_Size-8;icount++)
				{
					fprintf(textfile_ptr," ");
				}
			}
			else
			{
				Max_Size=13;
				fprintf(textfile_ptr,"     ");
			}
		
			fprintf(textfile_ptr,"%s\t\t%s\t\t%s\n","Account Number","Current Balance","Credit Limit");
		
			while(!feof(file_ptr))
			{
				fread(&Client,sizeof(struct clientData),1,file_ptr);
			
				if(Client.account_number!=0)
				{
					fprintf(textfile_ptr,"%s",Client.customer_name);
					for(icount=0;icount<Max_Size-Names_size[counter]+5;icount++)
					{
						fprintf(textfile_ptr," ");
					}
					fprintf(textfile_ptr,"%14d\t\t%15.2f\t\t%12.2f\n",Client.account_number,Client.current_balance,Client.credit_limit);
					counter++;
				}
			}
		
			fclose(textfile_ptr);
	
		}
		else
		{
			printf("The file couldn't be created!\n");
		}
		
		fclose(file_ptr);
	}
	else
	{
		printf("The binary file doesn't exist!\n");
	}
}
//********************************************

