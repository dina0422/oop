/**********|**********|**********|
Program: TT02.1191200368.Irdina.cpp 
Course: Object Oriented Programming
Year: 2020/11 Trimester 1
Name: Irdina binti Ahmad Hilmi
ID: 1191200368
Lecture Section: TC01
Tutorial Section: TT02
Email: 1191200368@student.mmu.edu.my
Phone: 013-2217568
**********|**********|**********/

/*Updated code starts around 114-125
and in each class'(book,magazine & movie) analysis function*/

#include<iostream>
#include<iomanip>  //setprecision
#include<fstream>  //file processing
#include<ctime>   //random number generator
#include<cstdlib>  
#include<cstring> //strlen
using namespace std;

class Owner{
	string username, password;
	bool loginSuccess;	//to check the username and password
	
	public:
		Owner() : loginSuccess(false) //initialize to false
		{
		}
		void login()
		{
			char login;
			//login
		cout << "=====================================" << endl;
		cout << "||                                 ||" << endl;
		cout << "||         FOR OWNER USE           ||" << endl;
		cout << "||                                 ||" << endl;
		cout << "=====================================" << endl;
		cout << "Welcome, Please login below\n";
		
		do{
		ofstream write;	//store details to file
		write.open("login.txt");  //text file open
		
			cout << "\nUsername : ";
			getline(cin,username);
			cout << "Password : ";
			getline(cin,password);
		
		write << username << endl;
		write << password << endl;
		
		write.close();
		
		if(username == "mmu" && password == "010422") //initial login username and password
		{
			cout << "\nYayyy Successful Login!! :D Press Enter";
			loginSuccess = true;
			login = getchar();
			system("cls");
		}
		else
			cout << "\nOops, wrong username or password!! :(\nPlease re-enter.\n";
		}while(!loginSuccess); //loop until its true
		//login ends
		}
};

class Update : public Owner{  //change username and password
	char next;
	
	public:
		void change()
		{
			string username, password;
				
			cout << "~Change username and password~" << endl;
			
			ofstream write;	//store details to file
			write.open("login.txt");  
			
				//cin.ignore();
				cout << "\nUsername : ";
				getline(cin,username);
				cout << "Password : ";
				getline(cin,password);
			
			write << username << endl;
			write << password << endl;
			
			write.close();
			cout << "\nYayy! Username and password successfully updated!!" << endl;
		}
};

class ShopItem{	
	public:
//		virtual void display();
//		{
//			//3 items to choose from
//			cout << "[1]Book";
//			cout << "\n[2]Magazine";
//			cout << "\n[3]Movie\n";
//		}

		void view_item()
		{	//3 items to choose from
			cout << "[1]Book";
			cout << "\n[2]Magazine";
			cout << "\n[3]Movie\n";
		}
		
		void view_byPriceRange()    //Updated code
		{
			int range1,range2,totalqty,no;
			double totalprice,price;
				
			fstream total;
			total.open("item.txt",ios::in|ios::out);
			
			system("cls");
			
			cout << "=====Total sales amount and the total sales unit=====" << endl;
			
				while(!total.eof())
				{
					cout << "\nPlease enter your price range " << endl;
					cout << "1st range : RM";
					cin >> range1;
					cout << "2nd range : RM";
					cin >> range2;
					
					if(price >= range1 && price <= range2)
					{
						totalprice += price * no;
						totalqty += no;
					}
					cout << "\nTotal Sales amount : " << totalprice << endl;
					cout << "Total sales unit     : " << totalqty <<endl;
				}
			total.close();
		}
}; 

class Book: public ShopItem{
	string line,BookID,name,author,price,no,company;
	char update;
	
	public:
		Book()
		{
		}
		
		void BookRecord() //view book records
		{
			ifstream read;
			read.open("Book.txt");
			
			cout << "==================================================================================================================================" << endl;
		 	cout << "| BookID |             Book title                   |       author       |   Price   |  No. of availability |    Company name    |" << endl;
			while(getline(read,line))
			{
				BookID  = line.substr(0,4);
				name    = line.substr(5,40);
				author  = line.substr(45,20);
				price   = line.substr(66,5);
				no      = line.substr(71,3);
				company = line.substr(74,20);
				
				cout << "==================================================================================================================================" << endl;																															
				cout << "|  " << BookID << "  |" << name << "  |" << author << "|   RM" << price << " |           " << no << "        |" << company << endl;
				
			}
				cout << "==================================================================================================================================" << endl;																															

			read.close();
			
			cout << "Press Enter if done :D" << endl;
		}	
		
		void BookInsert() //add on book record
		{			
			char nm[40],name[40],company[20],author[20];
			double price;
			int no,BookID,lgth,AddOn;
			
			cout << "Number of information to add on : ";
			cin >> AddOn;
			
			ofstream write; //store/write to the file
			write.open("Book.txt",ios::app);    //out.open
			
			for( int count=0; count<AddOn; count++)
			{
			srand((unsigned)time(0));
			BookID = (rand()% 999) + 1000;	
			
			cout << BookID <<endl;
			cout << "Enter book name                  : ";
			cin.ignore();
			cin.getline(nm,40);
			lgth = strlen(nm);
			memset(name,0x20,sizeof(name)-1);
			memcpy(name,nm,lgth);
			cout << "Enter author name                : ";
			cin.getline(author,20);
			cout << "Enter price (Put in 0.00 format) : ";
			cin >> price;
			cout << "Enter no. of units available     : ";
			cin >> no;
			cout << "Enter company name (1 word only!): ";
			cin >> company;
			cout << endl;
			cin.ignore();
			BookID++;
			
			write << BookID << " " << author << " " << name << " " << price << " " << no << " " << company << endl;
			}
		}
		
		void BookUpdate()
		{
			char nm[40],name[40],company[20],author[20];
			double price;
			int no,lgth,AddOn;
			string idsearch;
			
			ifstream read;
			ofstream write;
			
			read.open("Book.txt");
			write.open("Book.txt");
			
			BookID = line.substr(0,4);
			
			cout << "Search the BookID you want to update on : ";
			cin >> idsearch;
			cout << endl;
			
			while (getline(read,BookID))
			{
				if(line != idsearch)
					write << line << endl;
			}
			read.close();
			write.close();
			remove("Book.txt");
			rename("Book.txt","Book.txt");
			
			cout << "Enter book name                  : ";
			cin.ignore();
			cin.getline(nm,40);
			lgth = strlen(nm);
			memset(name,0x20,sizeof(name)-1);
			memcpy(name,nm,lgth);
			cout << "Enter author name                : ";
			cin.getline(author,20);
			cout << "Enter price (Put in 0.00 format) : ";
			cin >> price;
			cout << "Enter no. of units available     : ";
			cin >> no;
			cout << "Enter company name (1 word only!): ";
			cin >> company;
			
			ofstream write2;
			write2.open("Book.txt", ios::app | ios::out);
			
			write2 << BookID << " " << author << " " << name << " " << price << " " << no << " " << company << endl;
		}
		
		void BookDelete()
		{
		}
		
		void BookAnalyze()
		{
			int choice,no;
			char name[20],author[20],company[20];
			double price,total_price;
			
		//	total_price = price * no;
			
			cout << "  =============================================================="  << endl;
			cout << " ||Choose your choice of analysis based on view by :           ||" << endl;
			cout << "  =============================================================="  << endl;
			cout << " ||[1] total sales amount by Book                              ||" << endl;
			cout << " ||[2] total sales amount by company name                      ||" << endl;
			cout << " ||[3] total sales amount and total sales unit by product name ||" << endl;
			cout << " ||[4] total amount of sales by unit price range               ||" << endl;
			cout << "  =============================================================="  << endl;
			
			cout << "Enter choice";
			cin >> choice;
			
			if(choice==1)
			{
				ifstream read;
				read.open("TotalSalesbyBook.txt");
				
				read >> BookID;
				read >> author;
				read >> price;
				read >> no;
				read >> total_price;
				
				cout << BookID << endl;
				cout << author << endl;
				cout << "RM " << price << endl;
				cout << no << endl;
				cout << total_price << endl;
			}
			else if(choice == 4)  //the updated code
			{
				view_byPriceRange();
			}
//			
//			ifstream read;
//			read.open("Book.txt");
//			
//			while(read >> BookID)
//			{
//				char nm[40],name[40],company[20], author[20];
//				double price;
//				int no,BookID,lgth;
//				
//				read.getline(name,40);
//				read >> company;
//				read >> price;
//				read >> no;
//				read >> price >> no;
//								
//				cout << "BookID                 : " << BookID << endl;
//				cout << "Book name              : " << name << endl;
//				cout << "Company name           : " << company << endl;
//				cout << "Price                  : RM " << price << endl;
//				cout << "No. of units available : " << no << endl << endl;
//				cout << "total sales amount     : RM " << fixed << setprecision(2) << price * no << endl;
//				cout << endl;
//			}
//			read.close();
		}
};

class Magazine: public ShopItem{
	string line,MagazineID,month,year,name,price,no,company;
	int update;
	char next;
	
	public:
		Magazine()
		{
		}
		
		void MagazineRecord() //view magazine records
		{
			ifstream read;
			read.open("Magazine.txt");
			
			cout << "===================================================================================================================================================================" << endl;
		 	cout << "| Magazine ID |             Magazine title               |      Published month       |  Published year  |    Price   |  No. of availability |    Company name    |" << endl;
		 	
			while(getline(read,line))
			{
				MagazineID  = line.substr(0,4);
				name        = line.substr(5,30);
				month       = line.substr(35,10);
				year        = line.substr(45,5);
				price       = line.substr(50,6);
				no          = line.substr(56,3);
				company     = line.substr(59,20);
				
			cout << "==================================================================================================================================================================" << endl;																															
			cout << "|    " << MagazineID << "     |"<< name << "            |" << month << "                  |      " << year << "       | RM " << price << "  |          " << no << "         |" << company << endl;
			
			}
			read.close();	
			
			cout << "Press Enter if done :D" << endl;		
		}
		
		void MagazineInsert() //add on magazine record
		{		
			char nm[30],name[30],company[20],month[10];
			double price;
			int no,MagazineID,lgth,year,AddOn;
			
			cout << "Number of information to add on : ";
			cin >> AddOn;
	
			ofstream write; //store/write to the file
			write.open("Magazine.txt");    //out.open
			
			for( int count=0; count<AddOn; count++)
			{
			srand((unsigned)time(0));
			MagazineID = (rand()% 999) + 2000;	
			
			cout << MagazineID <<endl;
			cout << "Enter magazine name               : ";
			cin.getline(nm,30);
			lgth = strlen(nm);
			memset(name,0x20,sizeof(name)-1);
			memcpy(name,nm,lgth);
			cout << "Enter price (Put in 0.00 format)  : ";
			cin >> price;
			cout << "Month of Publication (word form)  : ";
			cin.getline(month,10);
			cout << "Year of Publication               :";
			cin >> year;
			cout << "Enter no. of units available      : ";
			cin >> no;
			cout << "Enter company name (1 word only!) : ";
			cin >> company;
			cout << endl;
			cin.ignore();
			MagazineID++;
			
			write << MagazineID << " " << name << " " << month << " " << year << " " << price << " " << no << " " << company << endl;
			}
			write.close();
			cout << "Press Enter if done :D" << endl;
		}
		
		void MagazineUpdate()
		{
			char nm[30],name[30],company[20],month[10];
			double price;
			int no,lgth,year,AddOn;
			string idsearch;
			
			ifstream read;
			ofstream write;
			
			read.open("Magazine.txt");
			write.open("Magazine.txt");
			
	//		MagazineID = line.substr(0,4);
			
			cout << "Search the MagazineID you want to update on : ";
			cin >> idsearch;
			cout << endl;
			
			while (getline(read,line))
			{
				if(line != idsearch)
					write << line << endl;
			}
			read.close();
			write.close();
			remove("Magazine.txt");
			rename("Magazine.txt","Magazine.txt");
			
			cout << "Enter magazine name                  : ";
			cin.ignore();
			cin.getline(nm,40);
			lgth = strlen(nm);
			memset(name,0x20,sizeof(name)-1);
			memcpy(name,nm,lgth);
			
			cout << "Enter price (Put in 0.00 format) : ";
			cin >> price;
			
			cout << "Enter no. of units available     : ";
			cin >> no;
			
			cout << "Enter company name (1 word only!): ";
			cin >> company;
			
			ofstream write2;
			write2.open("Magazine.txt", ios::app | ios::out);
			
			write << MagazineID << name <<  month << year << price << no << company << endl;
		}
		
		void MagazineDelete()
		{
			
		}
		
		void MagazineAnalyze()
		{
			int choice;
			
			cout << "  =============================================================="  << endl;
			cout << " ||Choose your choice of analysis based on view by :           ||" << endl;
			cout << "  =============================================================="  << endl;
			cout << " ||[1] total sales amount by Magazine                          ||" << endl;
			cout << " ||[2] total sales amount by company name                      ||" << endl;
			cout << " ||[3] total sales amount and total sales unit by product name ||" << endl;
			cout << " ||[4] total amount of sales by unit price range               ||" << endl;
			cout << "  =============================================================="  << endl;
			
			cout << "Enter choice";
			cin >> choice;
			
			if(choice == 4)  //the updated code
			{
				view_byPriceRange();
			}
			
		}
};

class Movie : public ShopItem{
	string line,MovieID,name,actor,price,no,company;
	int update;
	
	public:
		Movie()
		{
		}
		
		void MovieRecord() //view movie record
		{
			ifstream read;
			read.open("Movie.txt");
				
			   cout << "==================================================================================================================================" << endl;
		 	   cout << "| Movie ID |             Movie title               |      Main actor       |  Price  | No. of availability |    Company name     |" << endl;

			while(getline(read,line))
			{
				MovieID = line.substr(0,4);
				name    = line.substr(5,30);
				actor   = line.substr(35,20);
				price   = line.substr(55,5);
				no      = line.substr(61,3);
				company = line.substr(64,20);
						
				cout <<"==================================================================================================================================" << endl;																															
				cout << "|  " << MovieID << "    |"<< name << "         |" << actor << "   | RM" << price << " |         " << no << "         |" << company << endl;
			}
				cout << "\n==================================================================================================================================" << endl;
			read.close();

		}
		
		void MovieInsert() //add on movie record
		{			
			char nm[30],name[30],company[20],actor[20];
			double price;
			int no,MovieID,lgth,AddOn;
			
			cout << "Number of information to add on : ";
			cin >> AddOn;
			
			ofstream write; //store/write to the file
			write.open("Movie.txt",ios::app);    //out.open
			
			for( int count=0; count<AddOn; count++)
			{
			srand((unsigned)time(0));
			MovieID = (rand()% 999) + 2000;	
			
			cout << MovieID <<endl;
			cout << "Enter movie name                  : ";
			cin.ignore();
			cin.getline(nm,30);
			lgth = strlen(nm);
			memset(name,0x20,sizeof(name)-1);
			memcpy(name,nm,lgth);
			cout << "Enter main actor name             : ";
			cin.getline(actor,20);
			cout << "Enter price (Put in 0.00 format)  : ";
			cin >> price;
			cout << "Enter no. of units available      : ";
			cin >> no;
			cout << "Enter company name (1 word only!) : ";
			cin >> company;
			cout << endl;
			cin.ignore();
			MovieID++;
			
			write << MovieID << " " << name << " " << actor << " " << price << " " << no << " " << company << endl;
			}
			write.close();
		}
		void MovieUpdate()
		{
			char nm[30],name[30],company[20],actor[20];
			double price;
			int no,MovieID,lgth,AddOn;
			string idsearch;
			
			cout << "Please enter the MovieID to delete data: ";
			getline(cin, idsearch);
			
			ifstream read;
			read.open("Movie.txt");
			
			ofstream write;
			write.open("newMovie.txt");
			
			while(getline(read, line))
			{
				if(line != idsearch)
				{
					write << line << endl;
				}
			}
			read.close();
			write.close();
			remove("Movie.txt");
			rename("newMovie","Movie.txt");
			
			cout << "Enter movie name : ";
			cin.getline(name,30);
			
			cout << "Enter main actor name             : ";
			cin.getline(actor,20);
			lgth = strlen(nm);
			memset(name,0x20,sizeof(name)-1);
			memcpy(name,nm,lgth);
			
			cout << "Enter price (Put in 0.00 format)  : ";
			cin >> price;
			
			cout << "Enter no. of units available      : ";
			cin >> no;
			
			cout << "Enter company name (1 word only!) : ";
			cin >> company;
			
			ofstream write2; 
			write2.open("Movie.txt",ios::app | ios::out);
			
			write2 << name << actor << price << no << company << endl;
		}
		
		void MovieDelete()
		{
				
		}
		
		void MovieAnalyze()
		{
			int choice;
			
			cout << "  =============================================================="  << endl;
			cout << " ||Choose your choice of analysis based on view by :           ||" << endl;
			cout << "  =============================================================="  << endl;
			cout << " ||[1] total sales amount by Movie                             ||" << endl;
			cout << " ||[2] total sales amount by company name                      ||" << endl;
			cout << " ||[3] total sales amount and total sales unit by product name ||" << endl;
			cout << " ||[4] total amount of sales by unit price range               ||" << endl;
			cout << "  =============================================================="  << endl;
			
			cout << "Enter choice";
			cin >> choice;
			
			if(choice == 4)  //the updated code
			{
				view_byPriceRange();
			}
		}
};

int range()
{
	
}

int menu()
{
	int task;
	char choice;
	
	//Choose task
	cout << "  =================================="  << endl;
	cout << " ||        Choose task ^_^         ||" << endl;
	cout << "  =================================="  << endl;
	cout << " ||[1] Change username and password||" << endl;
	cout << " ||[2] View items                  ||" << endl;
	cout << " ||[3] Insert new items            ||" << endl;
	cout << " ||[4] Update information of items ||" << endl;
	cout << " ||[5] Delete items                ||" << endl;
	cout << " ||[6] Analyze sales               ||" << endl;
	cout << " ||[7] Logout                      ||" << endl;
	cout << "  =================================="  << endl;
	
	cout << " " ;cin >> task; 	//user key in choice of task
	choice = getchar();
	system("cls");
	
	return task;
}

double Analysis()
{
	string line,MovieID,BookID,MagazineID,name,actor,author,month,year,price,no,company;
	
	ifstream read;
	read.open("Book.txt");
	
		while(getline(read,line))
		{
			MovieID = line.substr(0,4);
			name    = line.substr(5,30);
			actor   = line.substr(35,20);
			price   = line.substr(55,5);
			no      = line.substr(61,3);
			company = line.substr(64,20);
		}
			read.open("Magazine.txt");
			
			while(getline(read,line))
			{
				MagazineID  = line.substr(0,4);
				name        = line.substr(5,30);
				month       = line.substr(35,10);
				year        = line.substr(45,5);
				price       = line.substr(50,6);
				no          = line.substr(56,3);
				company     = line.substr(59,20);
			}
			
			read.open("Movie.txt");
			
			while(getline(read,line))
			{
				MovieID = line.substr(0,4);
				name    = line.substr(5,30);
				actor   = line.substr(35,20);
				price   = line.substr(55,5);
				no      = line.substr(61,3);
				company = line.substr(64,20);
			}
			
			
				
		
}

int main()
{
	int task,choose;
	char next,ans;
	bool Menu = true;
	
	Owner O;		
	Update U;	
	ShopItem I;		//Object created
	Book B;
	Magazine Mg;
	Movie M;
	
//	I = new ShopItem;
	
	
	O.login();	//call login
	
	do{   //do while function will keep repeating until user chooses to end the program
		task = menu();   //call menu
	switch(task){	
		case 1 : U.change();
				 break;
		case 2 :  do{
				 	 I.view_item();   //call view_item and user choose
					 cin >> choose;  //user choose item choice
					 next = getchar();
					 system("cls");   //clear the screen
					
					 if(choose == 1)
					 {
						B.BookRecord();
						next = getchar();
					 	system("cls");
					 }
					 else if(choose == 2)
					 {
					 	Mg.MagazineRecord();
					 }
					 else if(choose == 3)
					 {
						M.MovieRecord();
					 }
					 else 
						cout << "Error! T_T choose again\n";
					 }while(choose > 3);   //loop repeats until one of the correct choice
				 break;
		case 3 : cout << "Which item do you want to add new record? :o" << endl;
				 I.view_item();
			  	 do{
					 cin >> choose;  //user choose item for new items
					 next = getchar();
					 system("cls");
					
					 if(choose == 1)
					 {
						B.BookInsert();
					 }
					 else if(choose == 2)
					 {
					 	Mg.MagazineInsert();
					 	cout << "Press Enter if done! :)" <<endl;
					 	choose = getchar();
						system("cls");
					 }
					 else if(choose == 3)
					 {
						M.MovieInsert();
						cout << "Press Enter if done! :)" <<endl;
						choose = getchar();
						system("cls");
					 }
					 else 
						cout << "Error! T_T choose again\n\n";
					 }while(choose > 3);   //loop repeats until one of the correct choice
				 break;
		case 4 : cout << "Which item do you want to update/edit? :o" << endl;
				 I.view_item();
				 do{
					 cin >> choose;  //user choose item for new items
					 next = getchar();
					 system("cls");
					 
					 if(choose == 1)
					 {
						B.BookUpdate();
					 }
					 else if(choose == 2)
					 {
					 	Mg.MagazineUpdate();
					 }
					 else if(choose == 3)
					 {
						M.MovieUpdate();				
					 }
					 else 
						cout << "Error! T_T choose again\n\n";
					 }while(choose > 3);   
				 cout << "\nRecord Updated successfully!";
				 break;
				 break;
		case 5 : cout << "Which item do you want to delete? :<" << endl;
				 I.view_item();
			  	 do{
					 cin >> choose;   //user choose item to delete
					 next = getchar();
					 system("cls");
					 
					 if(choose == 1)
					 {
						B.BookDelete();
					 }
					 else if(choose == 2)
					 {
					 	Mg.MagazineDelete();
					 }
					 else if(choose == 3)
					 {
						M.MovieDelete();				
					 }
					 else 
						cout << "Error! T_T choose again\n\n";
					 }while(choose > 3);   
				 cout << "\nRecord deleted successfully!";
				 break;
		case 6 : cout << "Which item do you want to analyze sales? :o" << endl;
				 I.view_item();
			  	 do{
					 cin >> choose;  //user choose item for new items
					 next = getchar();
					 system("cls");
					 
				 	 cout << "\n\t  ==========SALES DATA ANALYSIS==========" << endl;
					 
					 if(choose == 1)
					 {
						B.BookAnalyze();
					 }
					 else if(choose == 2)
					 {
					 	Mg.MagazineAnalyze();
					 }
					 else if(choose == 3)
					 {
						M.MovieAnalyze();				
					 }
					 else 
						cout << "Error! T_T choose again\n\n";
					 }while(choose > 3);   
				 break;
		case 7 : cout << "Your done!\n\nSEE YOU AGAIN! :3";
				 exit(1);
				 break;
		}
		
		cout << "\nDo you still want to continue? [Y/N]";
		cin >> ans; 
		
		system("cls");
		
	}while(ans == 'Y' || ans=='y');
		
		system("cls");
		cout << "Your done!\n\nSEE YOU AGAIN! :3";
	
	return 0;
}
