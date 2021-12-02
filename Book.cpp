#include<iostream>
#include<fstream>
#include<ctime>
#include<cstdlib>
#include<cstring>
using namespace std;

int main()
{
	char nm[40],name[40],company[20], author[20];
	double price;
	int no,BookID,lgth;
	
	ofstream write; //store/write to the file
	write.open("Book.txt");    //out.open
	
	for( int count=0; count<10; count++)
	{
	srand((unsigned)time(0));
	BookID = (rand()% 999) + 1000;	
	
	cout << BookID <<endl;
	cout << "Enter book name                   : ";
	cin.getline(nm,40);
	lgth = strlen(nm);
	memset(name,0x20,sizeof(name)-1);
	memcpy(name,nm,lgth);
	cout << "Enter author name                 : ";
	cin.getline(author,20);
	cout << "Enter price  (Put in 0.00 format) : ";
	cin >> price;
	cout << "Enter no. of units available      : ";
	cin >> no;
	cout << "Enter company name (1 word only!) : ";
	cin >> company;
	
	cout << endl;
	cin.ignore();
	BookID++;
	
	write << BookID << " " << author << " " << name << " " << price << " " << no << " " << company << endl;
	
	}
	write.close();
	
	return 0;
}
