#include<iostream>
using namespace std;
class user_account 
{
	char acc_holder_name[50];
	int acc_number;
	float acc_balance;
	public:
		user_account()
		{
			acc_number=0;
			acc_balance=0;
		}
		void create_account()
		{
			cout<<endl<<"enter account number:";
			cin>>acc_number;
			cout<<endl<<"enter account holder name:";
			cin>>acc_holder_name;
			cout<<endl<<"enter initial account balance:";
			cin>>acc_balance;
			if(acc_balance<500)
			{
				cout<<endl<<"initial deposit must be atleat 500";
				acc_balance=0;
				return;  //return to the menu
			}
			cout<<endl<<"account opened successfully!";
			cout<<"account number:"<<acc_number<<endl;
		}
		void deposit_money()//should not enter zero or negative value
		{
			float amount;
			cout<<endl<<"enter the amount to deposit";
			cin>>amount;
			if(amount<=0)
			{
				cout<<"invalid amount!"<<endl;
				return;
			}
			acc_balance+=amount;
			cout<<"deposited successfully! new balance=rs."<<acc_balance<<endl;

		}
		void withdraw()//cannot withdraw more than balance or negative or zero,maintain min balance of 500
		{
			float amount;
			cout<<endl<<"enter amount to withdraw";
			cin>>amount;
			if(amount<=0)
			{
				cout<<"invalid amount!"<<endl;
				return;
			}
			if(amount>acc_balance)
			{
				cout<<"insufficient balance!"<<endl;
				return;
			}
			if(acc_balance-amount<500)
			{
				cout<<"must maintain minimum balance of 500"<<endl;
				return;
			}
			cout<<"amount "<<amount<<" withdrawn sucessfully!"<<endl;
			acc_balance-=amount;
			cout<<"new balance=Rs." <<acc_balance<<endl;
			}
		void print_passbook()const //makes function data read only
		 //account number must be present
		{
			cout<<"=======ACCOUNT DETAILS======="<<endl;
			cout<<"Account number:"<<acc_number<<endl;
			cout<<"Account holder name:"<<acc_holder_name<<endl;
			cout<<"Balance:Rs."<<acc_balance<<endl;
		}
		int get_acc_no() const {return acc_number;}
		int is_valid() const {return acc_number!=0;}
};

int main()
{
	int choice;
	user_account accounts[10];
	int totalAccounts=0;
	start:
	do{
	cout<<"========BANKING APP========="<<endl;
	cout<<"enter choice:"<<endl;
	cout<<"1.create account"<<endl;
	cout<<"2.deposit money"<<endl;
	cout<<"3.withdraw money"<<endl;
	cout<<"4.print passbook"<<endl;
	cout<<"5.exit"<<endl;
	cin>>choice;
	switch(choice)
	{
		case 1:
			if(totalAccounts>=10)
			{
				cout<<"Bank is full!cannot open more accounts"<<endl;
			}
			else
			{
				accounts[totalAccounts].create_account();
				if(accounts[totalAccounts].is_valid()){
					totalAccounts++;
				}
			}
			break;
		case 2:{
			if(totalAccounts==0){
				cout<<"no accounts in the bank!"<<endl;
				break;
			}
			int accNo;
			cout<<"enter account number";
			cin>>accNo;
			int found=0;
			for(int i=0;i<totalAccounts;i++){//matching with every acc no
				if(accounts[i].get_acc_no()==accNo){
					accounts[i].deposit_money();
					found=1;
					break;
				}
			}
			if(!found) cout<<"account not found!"<<endl;
			break;
			}
		case 3: {
			if(totalAccounts==0){
				cout<<"no accounts in the bank!"<<endl;
				break;
			}
			int accNo;
			cout<<"enter account number";
			cin>>accNo;
			int found=0;
			for(int i=0;i<totalAccounts;i++){
				if(accounts[i].get_acc_no()==accNo){
					accounts[i].withdraw();
					found=1;
					break;
					}
				}
			if(!found) cout<<"account not found!"<<endl;
			break;
			}
		case 4: {
			if(totalAccounts==0){
			cout<<"no accounts in the bank!"<<endl;
			break;
			}
			int accNo;
			cout<<"enter account number";
			cin>>accNo;
			int found=0;
			for(int i=0;i<totalAccounts;i++){
			if(accounts[i].get_acc_no()==accNo){
			accounts[i].print_passbook();
			found=1;
			break;
			}}
			if(!found) cout<<"account not found!"<<endl;
			break;
			}
		case 5:
			exit(0);
			break;
		default:
			cout<<"incorrect option"<<endl;
			goto start;
		}
		}while(choice!=5);
	return 0;
}
