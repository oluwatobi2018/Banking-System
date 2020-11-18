#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<map>
#define ll long long
using namespace std;
#define MIN_BALANCE 1000
class Account
{
private:
 ll accountNumber;
 string firstName;
 string lastName;
 string email;
 string homeCity;
 double balance;
 static ll NextAccountNumber;
public:
 Account(){}
 Account(string fname,string lname,string email,string homeCity,double balance);
 ll getAccNo(){return accountNumber;}
 string getFirstName(){return firstName;}
 string getLastName(){return lastName;}
 string getEmail(){return email;}
 string getHomeCity(){return homeCity;}
 void setHomeCity(string s){homeCity=s;}
 void setEmail(string s){email=s;}
 double getBalance(){return balance;}
 void Deposit(double amount);
 void Withdraw(double amount);
 static void setLastAccountNumber(long accountNumber);
 static long getLastAccountNumber();
 friend ofstream & operator<<(ofstream &ofs,Account &acc);
 friend ifstream & operator>>(ifstream &ifs,Account &acc);
 friend ostream & operator<<(ostream &os,Account &acc);
};
ll Account::NextAccountNumber=0;
class Bank
{
private:
 map<ll,Account> accounts;
public:
 Bank();
 Account OpenAccount(string fname,string lname,string email,string homeCity,double balance);
 Account BalanceEnquiry(ll accountNumber);
 Account Deposit(ll accountNumber,double amount);
 Account Withdraw(ll accountNumber,double amount);
 void CloseAccount(ll accountNumber);
 void ShowAllAccounts();
 ~Bank();
};
int main()
{
 Bank b;
 Account acc;
 int choice;
 string fname,lname,email,home;
 ll accountNumber;
 double balance;
 double amount;
 cout<<"***Banking System***"<<endl;
 do
 {
 cout<<"\n\tSelect one option below ";
 cout<<"\n\t1 Open an Account";
 cout<<"\n\t2 Balance inquiry";
 cout<<"\n\t3 Deposit Money";
 cout<<"\n\t4 Withdraw Money";
 cout<<"\n\t5 Close an Account";
 cout<<"\n\t6 Show All Accounts";
 cout<<"\n\t7 Quit";
 cout<<"\nEnter your choice: ";
 cin>>choice;
 switch(choice)
 {
 case 1:{
 cout<<"Enter First Name: ";
cin>>fname;
cout<<"Enter Last Name: ";
cin>>lname;
cout<<"Enter Home City: ";
cin>>home;
cout<<"Enter email: ";
cin>>email;
cout<<"Enter initial Balance: ";
cin>>balance;
int temp=email.find('@');
if(temp!=string::npos)
{
    temp=email.find('.',temp+1);
    if(temp==string::npos || temp==email.length()-1)
    {
        cout<<"Not valid mail id !";
        return 0;
    }
}
else
{
    cout<<"Not valid mail id !";
        return 0;
}
 acc=b.OpenAccount(fname,lname,email,home,balance);
 cout<<endl<<"Congratulations Account is Created"<<endl;
 cout<<acc;
    break;
 }
 case 2:
 cout<<"Enter Account Number:";
    cin>>accountNumber;
 acc=b.BalanceEnquiry(accountNumber);
 cout<<endl<<"Your Account Details"<<endl;
 cout<<acc;
    break;
 case 3:
    cout<<"Enter Account Number:";
    cin>>accountNumber;
    cout<<"Enter Balance:";
    cin>>amount;
    acc=b.Deposit(accountNumber, amount);
    cout<<endl<<"Amount is Deposited"<<endl;
    cout<<acc;
    break;
 case 4:
    cout<<"Enter Account Number:";
    cin>>accountNumber;
    cout<<"Enter Balance:";
    cin>>amount;
    acc=b.Withdraw(accountNumber, amount);
    cout<<endl<<"Amount Withdrawn"<<endl;
    cout<<acc;
    break;
 case 5:
    cout<<"Enter Account Number:";
    cin>>accountNumber;
    b.CloseAccount(accountNumber);
    cout<<endl<<"Account is Closed"<<endl;
    cout<<acc;
 case 6:
    b.ShowAllAccounts();
 break;
 case 7: break;
 default:
 cout<<"\nEnter correct choice";
exit(0);
 }
 }while(choice!=7);

 return 0;
}
Account::Account(string fname,string lname,string email,string homeCity,double balance)
{
 NextAccountNumber++;
 accountNumber=NextAccountNumber;
 firstName=fname;
 lastName=lname;
 this->email=email;
 this->homeCity=homeCity;
 this->balance=balance;
}
void Account::Deposit(double amount)
{
        balance+=amount;
}
void Account::Withdraw(double amount)
{
 if(balance-amount<MIN_BALANCE)
 {
     cout<<"Not enough balance\n";
     return;
 }
 balance-=amount;
}
void Account::setLastAccountNumber(long accountNumber)
{
 NextAccountNumber=accountNumber;
}
long Account::getLastAccountNumber()
{
 return NextAccountNumber;
}
ofstream & operator<<(ofstream &ofs,Account &acc)
{
 ofs<<acc.accountNumber<<endl;
 ofs<<acc.firstName<<endl;
 ofs<<acc.lastName<<endl;
 ofs<<acc.email<<endl;
 ofs<<acc.homeCity<<endl;
 ofs<<acc.balance<<endl;
 return ofs;
}
ifstream & operator>>(ifstream &ifs,Account &acc)
{
 ifs>>acc.accountNumber;
 ifs>>acc.firstName;
 ifs>>acc.lastName;
 ifs>>acc.email;
 ifs>>acc.homeCity;
 ifs>>acc.balance;
 return ifs;

}
ostream & operator<<(ostream &os,Account &acc)
{
 os<<"First Name:"<<acc.getFirstName()<<endl;
 os<<"Last Name:"<<acc.getLastName()<<endl;
 os<<"Account Number:"<<acc.getAccNo()<<endl;
 os<<"Email Id:"<<acc.getEmail()<<endl;
 os<<"Home Branch:"<<acc.getHomeCity()<<endl;
 os<<"Balance:"<<acc.getBalance()<<endl;
 return os;
}
Bank::Bank()
{

 Account account;
 ifstream infile;
 infile.open("Bank.data");
 if(!infile)
 {
 return;
 }
 while(!infile.eof())
 {
 infile>>account;
 accounts.insert(pair<ll,Account>(account.getAccNo(),account));
 }
 Account::setLastAccountNumber(account.getAccNo());
 infile.close();
}
Account Bank::OpenAccount(string fname,string lname,string email, string homeCity, double balance)
{
 ofstream outfile;
 Account account(fname,lname,email, homeCity,balance);
 accounts.insert(pair<ll,Account>(account.getAccNo(),account));
 outfile.open("Bank.data", ios::trunc);
 map<ll,Account>::iterator itr;
 for(itr=accounts.begin();itr!=accounts.end();itr++)
 {
 outfile<<itr->second;
 }
 outfile.close();
 return account;
}
Account Bank::BalanceEnquiry(ll accountNumber)
{
 map<ll,Account>::iterator itr=accounts.find(accountNumber);
 return itr->second;
}
Account Bank::Deposit(ll accountNumber,double amount)
{
 map<ll,Account>::iterator itr=accounts.find(accountNumber);
 itr->second.Deposit(amount);
 return itr->second;
}
Account Bank::Withdraw(ll accountNumber,double amount)
{
 map<ll,Account>::iterator itr=accounts.find(accountNumber);
 itr->second.Withdraw(amount);
 return itr->second;
}
void Bank::CloseAccount(ll accountNumber)
{
 map<ll,Account>::iterator itr=accounts.find(accountNumber);
 cout<<"Account Deleted"<<itr->second;
 accounts.erase(accountNumber);
}
void Bank::ShowAllAccounts()
{
 map<ll,Account>::iterator itr;
 for(itr=accounts.begin();itr!=accounts.end();itr++)
 {
 cout<<"Account "<<itr->first<<endl<<itr->second<<endl;
 }
}
Bank::~Bank()
{
 ofstream outfile;
 outfile.open("Bank.data", ios::trunc);
 map<ll,Account>::iterator itr;
 for(itr=accounts.begin();itr!=accounts.end();itr++)
 {
 outfile<<itr->second;
 }
 outfile.close();
}
