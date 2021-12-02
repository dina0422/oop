#include<iostream>
#include<fstream>
#include<ctime>
#include<cstdlib>
#include<cstring>
using namespace std;

int main()
{
	char nm[30],name[30],company[20],month[10];
	double price;
	int no,MagazineID,lgth,year;
	
	ofstream write; //store/write to the file
	write.open("Magazine.txt");    //out.open
	
	for( int count=0; count<10; count++)
	{
	srand((unsigned)time(0));
	MagazineID = (rand()% 999) + 2000;	
	
	cout << MagazineID <<endl;
	cout << "Enter magazine name               : ";
	cin.getline(nm,30);
	lgth = strlen(nm);
	memset(name,0x20,sizeof(name)-1);
	memcpy(name,nm,lgth);
	cout << "Month of Publication (word form)  : ";
	cin.getline(month,10);
	cout << "Year of Publication               :";
	cin >> year;
	cout << "Enter price (Put in 0.00 format)  : ";
	cin >> price;
	cout << "Enter no. of units available      : ";
	cin >> no;
	cout << "Enter company name (1 word only!) : ";
	cin >> company;
	cout << endl;
	cin.ignore();
//	MagazineID++;
	
	write << MagazineID << " " << name << " " << month << " " << year << " " << price << " " << no << " " << company << endl;
	
	}
	write.close();
	
	return 0;
}
