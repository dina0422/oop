#include<iostream>
#include<fstream>
#include<ctime>
#include<cstdlib>
#include<cstring>
using namespace std;

int main()
{
	char nm[30],name[30],company[20],actor[20];
	double price;
	int no,MovieID,lgth;
	
	ofstream write; //store/write to the file
	write.open("Movie.txt");    //out.open
	
	for( int count=0; count<10; count++)
	{
	srand((unsigned)time(0));
	MovieID = (rand()% 999) + 2000;	
	
	cout << MovieID <<endl;
	cout << "Enter movie name                  : ";
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
	
	return 0;
}
