#include "interface.h"

int main()
{
	FILE *file_ptr;
	int choice;
	bool empty_file=false;
	
	files creator(file_ptr);
	
	do{
		
		printf("Enter:\n\t1.Administrator\n\t2.Customer\n\t3.Exit\nChoice: ");
		scanf("%d",&choice);
		
		switch(choice)
		{
			case 1:
					creator.admi_menu();
					system("pause");
					break;
			case 2:
					if((file_ptr=fopen("credit.dat","r+"))!=NULL)
					{
						files client(file_ptr);
						empty_file=client.EmptyFileYN();
						
						if(!empty_file)
						{
							client.customer();
						}
						else
						{
							printf("The binary file is empty!\n");
						}
						fclose(file_ptr);
					}
					else
					{
						printf("The binary file doesn't exist!\n");
					}
					system("pause");
					break;
			case 3:
					if((file_ptr=fopen("credit.dat","r"))!=NULL)
					{
						files readFile(file_ptr);
						empty_file=readFile.EmptyFileYN();
						fclose(file_ptr);
					}
					else
					{
						printf("The binary file doesn't exist!\n");
					}
					printf("Thanks for using our services!!!\n");
					system("pause");
					break;
			default:
					printf("Wrong Input!\n");
					system("pause");
					break;
		}
		system("CLS");
		
	}while(choice!=3);
	
	if(!empty_file)
	{
		creator.create_tfile();
		printf("Text file was created!\n");
		system("pause");
	}
	else
	{
		printf("There are no customers to be registerd in the text file!\n");
	}
	
	return 0;
}
