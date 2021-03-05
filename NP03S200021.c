/*
C Programming Coursework
Developer: Pawana Shrestha (NP03S2000021)
Section  : DC13
*/

#include <stdio.h>                                                            //header section
#include <string.h>
#include <conio.h> 
#include <unistd.h>
#include <process.h>

void authentication();         //line number 37
void loader();                 //line number 116
void options();                //line number 131
void bookticket();             //line number 169
int count_digits_in_num();     //line number 299
void flight_time();            //line number 312
void list_booked_tickets();    //line number 341
void search_ticket();          //line number 376
void edit_ticket();            //line number 422
void cancel_ticket();          //line number 530
void exit_terminal();          //line number 608
void main();                   //line number 626

struct variables                                                                //structure to store the data of the function in the variables 
{
	char fname[10], lname[10], dep[4], des[4], deptime[8], destime[8];
	long long num;
	int refno, noofseats;
}booking[25];

FILE *fp;                                                                       //file pointer
int i, end_of_file, pw_tries=0;                                                 //global variables 


void authentication()                                                           //function for the authentication
{
	char username[5], password[10], input;
	system ("COLOR 0A"); //to change bg to black and fg to light green
	system ("cls"); //to clear screen
	printf("---------------------------------------------------------------\n");
	printf("************** |  WELCOME TO CAPTCHA AIRLINES | ***************\n");
	printf("---------------------------------------------------------------\n");
	printf("\n\n\t\t\t| LOGIN PAGE |\n\n");
	printf("\n\t\tEnter username:\t");                                                    
	scanf("%s",&username);
	int pass=0;
	printf("\n\n\t\tEnter password:\t");     
	while(1)                                                        //loop to enter password
	{
		password[pass] = getch();
		if(password[pass] == 13) //break loop if 'Enter' key is pressed
		break;
		else if (password[pass] == 8 && pass!=0) //to operate backspace key in the program
		{ 
		    printf("\b");
		    printf(" ");
		    printf("\b");
			pass--;  
		}
		else
		{
			printf("*"); //to print * while password is typed
			pass++;
		}
	}
	password[pass]='\0';
	if (strcmp(username,"admin")==0 && strcmp(password,"captcha")==0)              //condition to check password and execute accordingly
	{
		pw_tries = 0; //to count the number of times username and password is tried
		loader("loading");
		options();
	}
	else if (pw_tries == 3) //condition if username and password is typed wrong for more than 3 times
	{
		system ("cls"); //to clear screen
		system ("COLOR 0C"); //changes bg to black and fg to light red
		printf("\t\t |---------------------------------------------------------------|\n");
		printf("\t\t |************** |  WELCOME TO CAPTCHA AIRLINES | ***************|\n");
		printf("\t\t |---------------------------------------------------------------|\n");
		printf("\n\n\t\t\t\t\t  LOGIN PAGE\n\n");
		printf("\t|----------------------------------------------------------------------------------|\n");
		printf ("\a\t\t\t\tYou have failed the login 3 times.\n\n"); //login failed msg with alert bell
		printf("\t\t\tPlease check the correct username and password\n\t\tin the login function of the program at line number 69 and try again.\n");
		printf("\t|----------------------------------------------------------------------------------|\n");
		printf ("\n\nEnter any key to exit.");
		getch();
		exit(0); //to exit terminal
	}
	else
	{
		pw_tries++; //increase number of password tries as username or password is wrong 
		system ("cls"); //to clear screen
		system ("COLOR 0C"); //changes bg to black and fg to light red
		printf("---------------------------------------------------------------\n");
		printf("************** |  WELCOME TO CAPTCHA AIRLINES | ***************\n");
		printf("---------------------------------------------------------------\n");
		printf("\n\n\t\t\tLOGIN PAGE\n\n");
		printf("  |--------------------------------------------------------|\n");
		printf("\a\n\t     Incorrect Username or Password!!!\n\n\t  Please press 'Enter' key to try again.\n\n"); //error message with alert bell
		printf("  |--------------------------------------------------------|\n");
		input=getch();
		if (input == 13)  
		{
		main();
		}
		else 
		{
		exit(0); //to exit terminal
		}
	}
}


void loader(char value[10])                                                         //function to show LOADING...
{                                                        
	int loader;
	if (value == "loading")  { printf ("\n\n\n\n\t  Loading..."); }
	if (value == "updating") { printf ("\n\n\t\tUpdating..."); }
	if (value == "deleting") { printf ("\n\n\n\t\tDeleting..."); }
	if (value == "loggingout") { printf ("\n\n\t\tLogging out..."); } 
	for (loader=1; loader<=25; loader++) //loop to print the loading animation
	{
		printf ("%c", 219); 	
		Sleep(80); //for the loader to load
	}
}


void options()                                                                  //function to display options of program
{
	char choice;
	system("cls"); //to clear the screen
	system("COLOR 0B"); //changes bg to black and fg to light aqua
	printf(" ____             ____   _______   _____ \n");
	printf("|          /\\    |    |     |     |       |    |     /\\ \n");
	printf("|         /__\\   |____|     |     |       |____|    /__\\ \n");
	printf("|        /    \\  |          |     |       |    |   /    \\ \n");
	printf("|____   /      \\ |          |     |_____  |    |  /      \\    AIRLINES...\n\n\n\n");
	printf("-------------------------- ADMIN PANEL --------------------------\n\n\n");
	printf("1.	Book a ticket\n\n2.	View the list of tickets booked\n\n3.	Search ticket information by REF number\n\n"); //to print the options
	printf("4.	Edit a ticket details by REF number\n\n5.	Cancel a ticket by REF number\n\n6.	Exit the system\n\n\n");	
	printf("Enter your choice.\n\n");
	choice:
	choice = getch();
	switch(choice)
	{
		system("cls"); 
		case '1' : bookticket();
		break;
		case '2' : list_booked_tickets();
		break;
		case '3' : search_ticket();
		break;
		case '4' : edit_ticket();
		break;	
		case '5' : cancel_ticket();
		break;
		case '6' : exit_terminal();
		break;
		default: 
		printf ("\t\tInvalid option chosen. Please only choose options that are mentioned.\n\nPlease enter your choice again:\n");
		goto choice; //goes to line number 145
	}
}


void bookticket()                                                               //function to book the requested ticket 
{    
	int j, digits_in_num;
	char request, ans;
	book_ticket:
	j=1;
	system ("cls");
	system("COLOR 0E"); //changes the bg to black and fg to light yellow
	fp = fopen ("ticket_details.txt","r"); //opens the file ticket_details.txt in read mode
	while (fp != NULL) //loop to read the data from the file
	{
		end_of_file = fscanf (fp,"%d %s %s %lli %s %s %s %s %d", &booking[j].refno, booking[j].fname, booking[j].lname, &booking[j].num, 
		booking[j].dep, booking[j].des, booking[j].deptime, booking[j].destime, &booking[j].noofseats);
		if (end_of_file == -1){break;} //breaks the loop at end of file
		j++;
	}
	fclose(fp); //close file pointer
	fp = fopen ("ticket_details.txt","a+"); //opens the file ticket_details.txt in append+ mode
		printf ("----------------------------------------------------------------------------------------------------------------\n");
		printf ("**********************************   |   BOOK TICKETS AT CAPTCHA AIRLINES  |   *********************************\n");
		printf ("----------------------------------------------------------------------------------------------------------------\n\n\n");
		printf ("Please enter the following details:\n\n"); //start of user detail input
		printf("\nFirst name    :\t");                                           
		scanf("%s",booking[i].fname);
		//to change first letter of first name to uppercase if it is in lowercase
		if (booking[i].fname[0]>=97 && booking[i].fname[0]<=122) { booking[i].fname[0] = booking[i].fname[0]-32; } 
		printf("\nLast name     :\t");
		scanf("%s",booking[i].lname);
		//to change first letter of last name to uppercase if it is in lowercase
		if (booking[i].lname[0]>=97 && booking[i].lname[0]<=122) { booking[i].lname[0] = booking[i].lname[0]-32; } 
		enter_number:
		printf("\nContact Number:\t");
		scanf("%lli",&booking[i].num);
		digits_in_num = count_digits_in_num (booking[i].num);
		if (digits_in_num != 10) //condition to check if the entered contact number is of 10 digits or not
		{
			printf ("\t\tInvalid number. Please enter correct contact number."); //msg to display of the contact number is not of 10 digits
			goto enter_number; //goes to line number 199
		}
		booking[i].refno = booking[j-1].refno+1 ; //the new ref number given 1 more than the last ref number 
		
		dep_des:
		printf("\nEnter your Derparture and Destination Location.\n\t\tType\n");
		printf("\t KTM for Kathmandu\n\t PKR for Pokhara\n\t KEP for Nepalgunj\n\t BIR for Biratnagar.\n\n");
		printf("DEPARTURE  -\t");
		scanf("%s",booking[i].dep);
		printf("DESTINATION-\t");
		scanf("%s",booking[i].des);
		
		//to check if both departure and destination is same and display error msg accordingly
		if (strcmp(booking[i].dep, booking[i].des) == 0)
		{
			printf ("You have entered same Departure and Destination place. Please enter again.\n");
			goto dep_des; //goes to line number 210
		}
		//to check if the deprature is correct or not
		if ((strcmp(booking[i].dep,"KTM")!=0)&&(strcmp(booking[i].dep,"PKR")!=0)&&(strcmp(booking[i].dep,"KEP")!=0)&&(strcmp(booking[i].dep,"BIR")!=0))
		{
			printf("\nInvalid Departure or Destination.");
			goto dep_des; //goes to line number 210
		}
		//to check if the destination is correct or not
		if ((strcmp(booking[i].des,"KTM")!=0)&&(strcmp(booking[i].des,"PKR")!=0)&&(strcmp(booking[i].des,"KEP")!=0)&&(strcmp(booking[i].des,"BIR")!=0))
		{
			printf("\nInvalid Departure or Destination.");
			goto dep_des; //goes to line number 210
		}
		
		system("cls");
		printf ("----------------------------------------------------------------------------------------------------------------\n");
		printf ("****************************************   |   TICKET CONFIRMATION  |   ****************************************\n");
		printf ("----------------------------------------------------------------------------------------------------------------\n\n\n");
		//giving customer the flight information
		printf("\nDear %s,\n\tYour Flight Reference Number is %d.\n\nThe available flight timing as per your request is:",booking[i].fname, booking[i].refno);
		flight_time(booking[i].dep, booking[i].des);
		printf("\nDeparture time:\t%s\nArrival time:\t%s\n", booking[i].deptime, booking[i].destime);
		
		ticket_confirmation:	
		printf("\n\nDo you want to confirm your Ticket?\t");
		scanf(" %c",&request);
		if (request == 'Y' || request == 'y') 
		{
			no_of_tickets:
			printf("\nHow many seats do you want to reserve?\t");
			scanf("%d",&booking[i].noofseats);
			if (booking[i].noofseats == 0) //condition is user tried to book 0 tickets 
			{ 
			printf ("\n\t\tYou cannot book 0 tickets. Enter the number of tickets again."); 
			goto no_of_tickets; //goes to line number 251
			}
			fflush(stdin);
			printf("\n%d seats confirmed.",booking[i].noofseats);
			fprintf (fp, "%d %s %s %lli %s %s %s %s %d\n", booking[i].refno, booking[i].fname, booking[i].lname, booking[i].num, booking[i].dep, 
			booking[i].des, booking[i].deptime, booking[i].destime, booking[i].noofseats);
			fclose(fp);
		}
		else if (request == 'N' || request == 'n') //condition to go back to options page if ticket confirmation is cancelled
		{
			printf("\n\n\t\tYou will be redirected to the OPTIONS page in 3 seconds.");
			sleep(3); //to wait for 3 seconds before executing the option function
			options();
		}
		else
		{
			printf("\nEnter either Y or N.\nPlease enter your confirmation again.");
			goto ticket_confirmation; //goes to line number 246
		}
		
		
		more_data:
		printf ("\n\nDo you want to enter more data?\t");
		scanf (" %c", &ans);
		if (ans == 'y' || ans == 'Y')
		{
			goto book_ticket; //goes to line number 173
		}
		else if (ans == 'n' || ans == 'N')
		{
			printf("\nData has been successfully saved.\n\n\t\tPress any key to go to the options page...");
			getch();
		}
		else
		{
			printf("\nEnter either Y or N.\nPlease enter your confirmation again.");
			goto more_data; //goes to line number 278
		}
		options();	
}


int count_digits_in_num(long long number)                                     //function to check if the entered contact number has 10 digits or not
{
	int digits_in_num=0;
	while (number != 0)
	{
		number = number/10;
		digits_in_num ++;
	}
	return digits_in_num;
}



void flight_time(char dep[3], char des[3])                                      //function to check dep and des to give flight time
{
	if (strcmp(dep,"KTM")==0) 
		{
			if (strcmp(des,"PKR")==0) {strcpy(booking[i].deptime, "06:00am"); strcpy(booking[i].destime, "06:30am");} 
			if (strcmp(des,"KEP")==0) {strcpy(booking[i].deptime, "09:20am"); strcpy(booking[i].destime, "10:15am");} 
			if (strcmp(des,"BIR")==0) {strcpy(booking[i].deptime, "11:40pm"); strcpy(booking[i].destime, "12:30pm");} 
		}
	else if (strcmp(dep,"PKR")==0) 
		{
			if (strcmp(des,"KTM")==0) {strcpy(booking[i].deptime,"01:20am"); strcpy(booking[i].destime,"01:50am");} 
			if (strcmp(des,"KEP")==0) {strcpy(booking[i].deptime,"02:35pm"); strcpy(booking[i].destime,"04:40pm");}
			if (strcmp(des,"BIR")==0) {strcpy(booking[i].deptime,"07:00am"); strcpy(booking[i].destime,"08:05am");}
		} 
	else if(strcmp(dep,"KEP")==0) 
		{
			if (strcmp(des,"KTM")==0) {strcpy(booking[i].deptime,"10:25am"); strcpy(booking[i].destime,"11:20am");}
			if (strcmp(des,"PKR")==0) {strcpy(booking[i].deptime,"10:45am"); strcpy(booking[i].destime,"12:50am");}
			if (strcmp(des,"BIR")==0) {strcpy(booking[i].deptime,"05:10pm"); strcpy(booking[i].destime,"07:30pm");}
		} 
	else if (strcmp(dep,"BIR")==0) 
		{
			if (strcmp(des,"KTM")==0) {strcpy(booking[i].deptime,"08:00pm"); strcpy(booking[i].destime,"08:50pm");}
			if (strcmp(des,"PKR")==0) {strcpy(booking[i].deptime,"01:00pm"); strcpy(booking[i].destime,"02:05pm");}
			if (strcmp(des,"KEP")==0) {strcpy(booking[i].deptime,"08:35am"); strcpy(booking[i].destime,"09:55am");}
		} 
}

 
void list_booked_tickets()                                                                //function to display all the booked tickets
{
	system ("cls");
	system ("COLOR 0E");
	printf ("----------------------------------------------------------------------------------------------------------------\n");
	printf ("******************************************   LIST OF BOOKED TICKETS   ******************************************\n");
	printf ("----------------------------------------------------------------------------------------------------------------\n\n\n");
	fp = fopen ("ticket_details.txt","r"); //to open file ticket.txt in read mode
	if (fp == NULL) //condition to check if file is empty and displpay msg accordingly
	{
		printf ("\t\t\t\t\tNo ticket has been booked yet.");
		getch();
		options();
	}
	int j=1;
	printf ("________________________________________________________________________________________________________________\n\n");
	printf ("Ref No.\t| Name\t\t\t| Number\t| Dep\t| Des\t| Dep-time\t| Des-time\t| No. of Seats\n");
	printf ("________________________________________________________________________________________________________________\n\n");
	while (1) //loop to read data from file and print them
	{
		end_of_file = fscanf (fp, "%d %s %s %lli %s %s %s %s %d", &booking[j].refno, booking[j].fname, booking[j].lname, &booking[j].num, 
		booking[j].dep, booking[j].des, booking[j].deptime, booking[j].destime, &booking[j].noofseats);
		if (end_of_file == -1){break;} //breaks loop at the end of file
		printf ("   %d\t| %s, %s\t| %lli\t| %s\t| %s\t| %s\t| %s\t|\t%d\n\n",booking[j].refno, booking[j].lname, booking[j].fname, booking[j].num, 
		booking[j].dep, booking[j].des, booking[j].deptime, booking[j].destime, booking[j].noofseats);
		j++;
	}		
				
	fclose(fp);	//to close file pointer
		
	getch();
	options();
}


void search_ticket()                                                            //function to search the ticket by REF No
{
	system ("cls");
	system ("COLOR 0E");
	printf ("---------------------------------------------------------------------------------------------\n");
	printf ("*****************************  | SEARCH TICKET BY REF NUMBER |  *****************************\n");
	printf ("---------------------------------------------------------------------------------------------\n\n\n");
	fp = fopen ("ticket_details.txt","r"); //open file pointer in read mode
	if (fp == NULL) //condition to check if file is empty and displpay msg accordingly
	{
		printf ("\t\t\t\tNo ticket has been booked yet.");
		getch();
		options();
	}
	int ref_no, p, j=1;
	printf ("Enter Reference Number: \t");
	scanf("%d", &ref_no);
	while (1)
	{
		end_of_file = fscanf (fp,"%d %s %s %lli %s %s %s %s %d", &booking[j].refno, booking[j].fname, booking[j].lname, &booking[j].num, 
		booking[j].dep, booking[j].des, booking[j].deptime, booking[j].destime, &booking[j].noofseats);
		if (end_of_file == -1){break;} //breaks loop at the end of file
		j++;
	}
	fclose(fp);
	for (p=1; p<j; p++)  //loop to check if input ref number matches ref number in the list
	{
		if (booking[p].refno == ref_no)  //condition if the inpute ref number matches the ref number in list
		{
			printf ("\n\n\nREF_No.\t\t:\t%d\n\nName\t\t:\t%s, %s\n\nNumber\t\t:\t%lli\n\nDeparture\t:\t%s\n\n",
			booking[p].refno, booking[p].fname, booking[p].lname, booking[p].num, booking[p].dep);
			printf ("Destination\t:\t%s\n\nDep-time\t:\t%s\n\nDes-time\t:\t%s\n\nNo. of Seats\t:\t%d",
			booking[p].des, booking[p].deptime, booking[p].destime, booking[p].noofseats);
			getch();
			options();	
		}
	}
	printf ("\nPlease make sure that the Reference Number you entered is in the list of tickets.\n"); //message to display if the ref no is not found
	getch();
	options();
}


void edit_ticket()                                                               //function to edit the ticket by REF No
{
	int digits_in_num;
	system ("cls");
	system ("COLOR 0E");
	printf ("---------------------------------------------------------------------------------------------\n");
	printf ("******************************  | EDIT TICKET BY REF NUMBER |  ******************************\n");
	printf ("---------------------------------------------------------------------------------------------\n\n\n");
	fp = fopen ("ticket_details.txt", "r+"); //open file pointer in read+ mode
	if (fp == NULL) //condition to check if file is empty and displpay msg accordingly
	{
		printf ("\t\t\t\tNo tickets has been booked yet.");
		getch();
		options();
	}
	int ref_no, j=1, p, d;
	while (1)
	{
		end_of_file = fscanf (fp,"%d %s %s %lli %s %s %s %s %d", &booking[j].refno, booking[j].fname, booking[j].lname, &booking[j].num, 
		booking[j].dep, booking[j].des, booking[j].deptime, booking[j].destime, &booking[j].noofseats);
		if (end_of_file == -1){break;} //breaks loop at the end of file
		j++;
	}
	
	printf ("Enter Reference Number to edit: \t");
	scanf("%d", &ref_no);

	rewind(fp); //to put the cursor in the beginning of file
	for (p=1; p<j; p++)
	{
		if (booking[p].refno == ref_no)
		{
			printf ("\n\nFirst name\t[Old data: %s ]:\t", booking[p].fname);
			scanf ("%s", booking[p].fname);
			//to change first letter of first name to uppercase if it is in lowercase
			if (booking[p].fname[0]>=97 && booking[p].fname[0]<=122) { booking[p].fname[0] = booking[p].fname[0]-32; }
			printf ("\nLast name\t[Old data: %s ]:\t", booking[p].lname);
			scanf ("%s", booking[p].lname);
			//to change first letter of last name to uppercase if it is in lowercase
			if (booking[p].lname[0]>=97 && booking[p].lname[0]<=122) { booking[p].lname[0] = booking[p].lname[0]-32; }
			enter_number:
			printf ("\nNumber\t[Old data: %lli ]:\t", booking[p].num);
			scanf ("%lli", &booking[p].num);
			digits_in_num = count_digits_in_num (booking[p].num); //calling of count_digits_in_num function 
			if (digits_in_num != 10) //condition if input number is of 10 digits or not
			{
				printf ("\t\tInvalid number. Please enter correct contact number.");
				goto enter_number; //goes to line number 459
			}
				
			dep_des:
			printf("\nEnter your Derparture and Destination Location.\n\t\tType\n");
			printf("\t KTM for Kathmandu\n\t PKR for Pokhara\n\t KEP for Nepalgunj\n\t BIR for Biratnagar.\n\n");
			printf ("Departure\t[Old data: %s ]:\t", booking[p].dep);
			scanf ("%s", booking[p].dep);
			printf ("Destination\t[Old data: %s ]:\t", booking[p].des);
			scanf ("%s", booking[p].des);
			if (strcmp(booking[p].dep, booking[p].des) == 0)
			{
				printf ("You have entered same Departure and Destination place. Please enter again.\n");
				goto dep_des; //goes to line number 469
			}
			if ((strcmp(booking[p].dep,"KTM")!=0)&&(strcmp(booking[p].dep,"PKR")!=0)&&(strcmp(booking[p].dep,"KEP")!=0)&&(strcmp(booking[p].dep,"BIR")!=0))
			{
				printf("\nInvalid Departure or Destination.");
				goto dep_des; //goes to line number 469
			}
			if ((strcmp(booking[p].des,"KTM")!=0)&&(strcmp(booking[p].des,"PKR")!=0)&&(strcmp(booking[p].des,"KEP")!=0)&&(strcmp(booking[p].des,"BIR")!=0))
			{
				printf("\nInvalid Departure or Destination.");
				goto dep_des; //goes to line number 469
			}
			fflush(stdin);
			no_of_tickets:
			printf ("\nNumber of tickets\t[Old data: %d ]:\t", booking[p].noofseats);
			scanf ("%d", &booking[p].noofseats);
			if (booking[p].noofseats == 0) 
			{ 
			printf ("\t\tYou cannot book 0 tickets. Enter the number of tickets again.\n"); 
			goto no_of_tickets;
			}
			printf("\n\nDear %s,\n\tThe new flight timing as per your request is:",booking[p].fname);
			flight_time(booking[p].dep, booking[p].des);
			strcpy (booking[p].deptime, booking[i].deptime);
			strcpy (booking[p].destime, booking[i].destime);
			printf("\nDeparture time:\t%s\nArrival time:\t%s\n\n", booking[p].deptime, booking[p].destime);
			loader("updating");
			printf ("\n\nThe new data is successfully updated.");
			
			for (p=1; p<j; p++)
			{
				fprintf (fp, "%d %s %s %lli %s %s %s %s %d\n",booking[p].refno, booking[p].fname, booking[p].lname, booking[p].num, 
				booking[p].dep, booking[p].des, booking[p].deptime, booking[p].destime, booking[p].noofseats);
			}
			fclose (fp);
			getch();
			options();
		}
	}
	
	
	printf ("\nPlease make sure that the Reference Number you entered is in the list of tickets.\n"); //message to display if the ref no is not found
	getch();
	options();
}


void cancel_ticket()                                                             //function to cancel the ticket by REF No
{
	char confirmation;
	system ("cls");
	system ("COLOR 0E");
	printf ("---------------------------------------------------------------------------------------------\n");
	printf ("****************************** | CANCEL TICKET BY REF NUMBER | ******************************\n");
	printf ("---------------------------------------------------------------------------------------------\n\n\n");
	fp = fopen ("ticket_details.txt", "r");
	if (fp == NULL) //condition to check if file is empty and displpay msg accordingly
	{
		printf ("\t\t\t\tNo ticket has been booked yet.");
		getch();
		options();
	}
	int ref_no, j=1, p, d;
	while (1)
	{
		end_of_file = fscanf (fp,"%d %s %s %lli %s %s %s %s %d", &booking[j].refno, booking[j].fname, booking[j].lname, &booking[j].num, 
		booking[j].dep, booking[j].des, booking[j].deptime, booking[j].destime, &booking[j].noofseats);
		if (end_of_file == -1){break;} //breaks loop at the end of file
		j++;
	}
	fclose(fp); //closes file pointer
	
	printf ("Enter Reference Number to be deleted: \t");
	scanf("%d", &ref_no);
	for (p=1; p<j; p++) //loop to find the entered ref number
		{
			if (booking[p].refno == ref_no) //condition when ref number is found
			{	
				printf("\n\nAre you sure you want to delete the ticket details of REF No. %d ?\t", ref_no); //cancellation confirmation
				scanf (" %c", &confirmation);
				if ( confirmation == 'Y' || confirmation == 'y')
				{
					for (d=p; d<j; d++) //loop to replace the index number of entered ref number with preceeding structure
					{
						booking[d] = booking[d+1]; //preceeding structure replaces the place of the previous one
					}
					j--;
					loader("deleting"); //deleting animation
					printf ("\n\n\nThe data is successfully deleted.");
				
					fp = fopen ("ticket_details.txt", "w"); //to write the updated information after deletion in file
					for (p=1; p<j; p++)
					{
						fprintf (fp, "%d %s %s %lli %s %s %s %s %d\n", booking[p].refno, booking[p].fname, booking[p].lname, booking[p].num, 
						booking[p].dep, booking[p].des, booking[p].deptime, booking[p].destime, booking[p].noofseats);
					}
					fclose (fp); //closes file pointer
					getch();
					options();
				}
				else if ( confirmation == 'N' || confirmation == 'n')
				{
					printf("\n\n\t\tYou will be redirected to the OPTIONS page in 3 seconds.");
					sleep(3); //to wait for 3 seconds before executing the option function
					options();	
				}
				else 
				{
					printf ("\n\nPlease type 'Y' or 'N' for the confirmation.");
				}
			}
		}
	
	printf ("\nPlease make sure that the Reference Number you entered is in the list of tickets.\n"); //message to display if the ref no is not found
	getch();
	options();
}


void exit_terminal()                                                            //function to end the program
{
	system("cls");
	system("COLOR 0A");
	printf(" ____             ____   _______   _____ \n");
	printf("|          /\\    |    |     |     |       |    |     /\\ \n");
	printf("|         /__\\   |____|     |     |       |____|    /__\\ \n");
	printf("|        /    \\  |          |     |       |    |   /    \\ \n");
	printf("|____   /      \\ |          |     |_____  |    |  /      \\    AIRLINES...\n\n\n\n");
	loader ("loggingout"); //logging out animation
	printf ("\n\n\n\t\t\tYOU HAVE SUCCESSFULLY LOGGED OUT.");
	printf ("\n\n\n\n\n\t\t\t\t\t\t Thank you for using this program.");
	printf ("\n\t\t\t\t\t\t\t\t- Pawana Shrestha");
	printf ("\n\t\t\t\t\t\t\t\t    (Developer)\n\n\n\n\n");
	exit(0); //to exit terminal
}


void main()                                                                       //main function
{
	authentication();
}

