#include <fstream.h>
#include <conio.h>
#include <stdio.h>
#include <ctype.h>
#include <iomanip.h>
#include <stdlib.h>

class bank
{ int accno;
  char custname[60];
  long int deposit;
  char type;

public:
  void enteraccno();
  void create();
  void display();
  void modify();
  void draw(long int);
  void depositamount(long int);
  void table();
  int retaccno();
  long int retdeposit();

	};

void bank::enteraccno()
	{cout<<"enter accno"<<endl;
	cin>>accno;}

 void bank::create()
 { cout<<"Enter your name"<<endl;
 gets(custname);
 cout<<"Enter the type of account (C-current, S-saving)";
 cin>>type;
 cout<<"Enter the amount you want to deposit"<<endl;
 cin>>deposit;
 cout<<"Account created, welcome to RSM International, together we rise";
 }

void bank::display()
{cout<<"Account no is: \t"<<accno<<"\n";
cout<<"Customer name is: \t";
puts(custname);
cout<<"Balance amount is: \t"<<deposit;
 }

void bank::modify()
{cout<<"Enter new account no."<<endl;
 cin>>accno;
 cout<<"Enter your name"<<endl;
 gets(custname);
 cout<<"Enter the amount you want to deposit P.S. \n We're a small bank less than \n 32000 please thank you"<<endl;
 cin>>deposit;
  }

void bank::draw(long int x)
{deposit-=x;}

void bank::depositamount(long int x)
{deposit+=x;}

void bank::table()
{cout<<accno<<setw(10)<<" "<<custname<<setw(10)<<" "<<type<<setw(6)<<deposit<<"\n";}

int bank::retaccno()
{return accno;}

long int bank::retdeposit()
{return deposit;}

void enter_record();
void display_record();
void modify_record();
void delete_record();
void depwithrecord();
void menu();
void allrecords();
void RSMinternational();

int main()
{menu();
 return 0;}

void enter_record()
{bank b,bk;fstream f1;
f1.open("bank.dat",ios::binary|ios::in|ios::out);
 b.enteraccno();
 while(f1.read((char *)&bk,sizeof(bk)))
 {if(bk.retaccno()==b.retaccno())
  {cout<<"record already exists";return;}
  else
  {b.create();
  f1.seekp(0,ios::end);
	f1.write((char *)&b,sizeof(b));
	}}
  f1.close();
  }

void display_record(int n)
{bank bk; int flag=0;
 ifstream if1;
 if1.open("bank.dat",ios::binary);

 while(if1.read((char *)&bk, sizeof(bk)))
 {if(bk.retaccno()==n)
  {flag=1;
	bk.display();}}
if(flag==0)
cout<<"Record does not exist.";}

void modify_record(int n)
{
  int found=0;
  bank bk;
  fstream of2;
  of2.open("bank.dat",ios::binary|ios::in|ios::out);
  while(of2.read((char *) &bk, sizeof(bk)) && found==0)
  {
	 if(bk.retaccno()==n)
	 {
		bk.display();
		cout<<"\n\nEnter The New Details of account"<<endl;
		bk.modify();
		int pos=(-1) * sizeof(bk);
		of2.seekp(pos,ios::cur);
		of2.write((char *) &bk, sizeof(bk));
		cout<<"\n\n\t Record Updated";
		found=1;
	 }
  }
  of2.close();
  if(found==0)
	 cout<<"\n\n Record Not Found ";
}

void delete_record(int n)
{
  bank bk;
  ifstream if3;
  ofstream of3;
  if3.open("bank.dat",ios::binary);
  of3.open("Temp.dat",ios::binary);
  if3.seekg(0,ios::beg);
  while(if3.read((char *) &bk, sizeof(bk)))
  {
	 if(bk.retaccno()!=n)
	 {
		of3.write((char *) &bk, sizeof(bk));
	 }
  }
  if3.close();
  of3.close();
  remove("bank.dat");
  rename("Temp.dat","bank.dat");
  cout<<"\n\n\tRecord Deleted ..";
}

void depwithrecord(int n, int option)
{
 long int amt;
  int found=0;
  bank bk;
  fstream fs;
  fs.open("bank.dat", ios::binary|ios::in|ios::out);
  while(fs.read((char *) &bk, sizeof(bk)) && found==0)
  {
	 if(bk.retaccno()==n)
	 {
		bk.display();
		if(option==1)
		{
		  cout<<"\n\n\tTO DEPOSITE AMOUNT ";
		  cout<<"\n\nEnter The amount to be deposited";
		  cin>>amt;
		  bk.depositamount(amt);
		}
		if(option==2)
		{
		  cout<<"\n\n\tTO WITHDRAW AMOUNT ";
		  cout<<"\n\nEnter The amount to be withdraw";
		  cin>>amt;
		  int bal=bk.retdeposit()-amt;
		  if(bal==0)
		  cout<<"Insufficient balance";
		  else
			 bk.draw(amt);
		}
		int pos=(-1)* sizeof(bk);
		fs.seekp(pos,ios::cur);
		fs.write((char *) &bk, sizeof(bk));
		cout<<"\n\n\t Record Updated";
		found=1;
			}
  }
  fs.close();
  if(found==0)
	 cout<<"\n\n Record Not Found ";
}

void menu()
{char ch;
  int num;
  clrscr();
  RSMinternational();
  do
  {
	 clrscr();
	 cout<<"\n\n\n\tMAIN MENU";
	 cout<<"\n\n\t01. NEW ACCOUNT";
	 cout<<"\n\n\t02. DEPOSIT AMOUNT";
	 cout<<"\n\n\t03. WITHDRAW AMOUNT";
	 cout<<"\n\n\t04. BALANCE ENQUIRY";
	 cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
	 cout<<"\n\n\t06. CLOSE AN ACCOUNT";
	 cout<<"\n\n\t07. MODIFY AN ACCOUNT";
	 cout<<"\n\n\t08. EXIT";
	 cout<<"\n\n\tSelect Your Option (1-8) ";
	 cin>>ch;
	 clrscr();
	 switch(ch)
	 {
	 case '1':
	  enter_record();
		break;
	 case '2':
		cout<<"\n\n\tEnter The account No. : "; cin>>num;
		depwithrecord(num, 1);
		break;
	 case '3':
		cout<<"\n\n\tEnter The account No. : "; cin>>num;
		depwithrecord(num, 2);
		break;
	 case '4':cout<<"\n\n\tEnter The account No. : "; cin>>num;
	 display_record(num);
		break;
	 case '5':
		allrecords();
		break;
	 case '6':
		cout<<"\n\n\tEnter The account No. : "; cin>>num;
		delete_record(num);
		break;
	  case '7':
		cout<<"\n\n\tEnter The account No. : "; cin>>num;
		modify_record(num);
		break;
	  case '8':
		cout<<"\n\n\tThanks for using RSM International Bank Management System";exit(0);
		break;
	  default :cout<<"\a";
	 }
	 getch();
  }while(ch!='8');}

  void allrecords()
  {bank bank;
  ifstream if4;
  if4.open("bank.dat",ios::binary);

  cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
  cout<<"====================================================\n";
  cout<<"A/c no.      NAME           Type  Balance\n";
  cout<<"====================================================\n";
  while(if4.read((char *) &bank, sizeof(bank)))
  {
	 bank.table();
  }
  if4.close();}

void RSMinternational()
{cout<<"\n\n\n\t  RSM";
  cout<<"\n\n\t International";
  cout<<"\n\n\t  System";
  cout<<"\n\n\n\nMADE BY : Rohan S Mathews";
  cout<<"\n\nSCHOOL : The Air Force School";
  getch();}














































































































































































































































































































































