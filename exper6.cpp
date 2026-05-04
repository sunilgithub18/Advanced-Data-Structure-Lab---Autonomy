/*AIM:
Consider telephone book database of N clients.
Make use of a hash table implementation to quickly look up 
client‘s telephone number.
Make use of two collision handling techniques and 
compare them using number of comparisons required 
to find a set of telephone numbers.

INPUT: Client Information, name and telephone number

OUTPUT: Search and display Client telephone number

Author: Dr. Sunil Damodar Rathod.

DATE:09.04.2026

Linear Probing - hf=key%sizeoftable
Quadratic Probing - 
	i=1
	hi= (i^2+key)%sizeoftable
*/
#include<iostream>
#include<ios> //used to get stream size
#include<limits> //used to get numeric limits
#include <cstring>
#define BSIZE 5
using namespace std;

//Client ATD
typedef struct Client{
	 long int telephoneNo;
	 string name;
}CLIENT;


//Implementation Class 
class TelephoneDirectory
{
	private:
		CLIENT LPHashTable[BSIZE];//Linear Probing Hash Table
		CLIENT QPHashTable[BSIZE];//Quadratic Probing Hash Table
		CLIENT cObj;
	public:
		TelephoneDirectory(){
			for(int i=0;i<BSIZE;i++){
				LPHashTable[i].telephoneNo=-1;
				QPHashTable[i].telephoneNo=-1;
			}
		}
		void init(){
			for(int i=0;i<BSIZE;i++){
				LPHashTable[i].telephoneNo=-1;
				QPHashTable[i].telephoneNo=-1;
			}
		}
		
		
		void readData();
		void printData();
		
		//Linear Probing
		void insertRecordLP();
		void displayRecordsLP();
		void searchRecordLP(long int);
		
		//Quadratic Probing
		void insertRecordQP();
		void displayRecordsQP();
		void searchRecordQP(long int);
};

void TelephoneDirectory::readData(){
	long int telephone;
	string name;
	cout<<"\nEnter client telephone No.::";
	cin>>cObj.telephoneNo;
	
	cout<<"\nEnter client name::";
	cin>>cObj.name;
}

void TelephoneDirectory::printData(){
	cout<<"\nThe client telephone No.::"<<cObj.telephoneNo;
	cout<<"\nThe client name::"<<cObj.name;
}

//Linear Probing
void TelephoneDirectory::insertRecordLP(){
	int hi,noc,i;
	readData();
	hi=cObj.telephoneNo%BSIZE;
	if(LPHashTable[hi].telephoneNo == -1)
		LPHashTable[hi]=cObj;
	else{
		 i=(hi+1)%BSIZE;
		 while(i != hi){
			if(LPHashTable[i].telephoneNo==-1){
				LPHashTable[i]=cObj;
				break;
			}
			i=(i+1)%BSIZE;
		 }
		if(i==hi)
			cout<<"\nHash Table Full!!";
	}
}

void TelephoneDirectory::searchRecordLP(long int telephoneNo){
	int hi,noc,i;
	hi=telephoneNo%BSIZE;
	noc=0;//number of comparisons
	if(LPHashTable[hi].telephoneNo == telephoneNo){
		noc++;
		cout<<"\nRecord found after "<<noc<<" comparisons!";
	}
	else{
		 i=(hi+1)%BSIZE;
		 while(i != hi){
			noc++;
			if(LPHashTable[i].telephoneNo==telephoneNo){
				cout<<"\nRecord found after "<<noc<<" comparisons!";
				break;
			}
			i=(i+1)%BSIZE;
		 }
		if(i==hi)
			cout<<"\nRecord NOT found even after "<<noc<<" comparisons!";
	}
}

void TelephoneDirectory::displayRecordsLP(){
	cout<<"\nTelephone No."<<"\t"<<"Name  ";
	for (int i=0;i<BSIZE;i++)
		cout<<"\n"<<LPHashTable[i].telephoneNo<<"\t\t"<<LPHashTable[i].name;
}

//Quadratic Probing
void TelephoneDirectory::insertRecordQP(){
	int hi,noc,i,newHI,j;
	readData();
	i=1;
	hi=(cObj.telephoneNo+i*i)%BSIZE;
	if(QPHashTable[hi].telephoneNo == -1)
		QPHashTable[hi]=cObj;
	else{
		 for (int j=1;j<=BSIZE;j++){
			newHI=(hi+i*i)%BSIZE;//new hash index
			noc++;
			if(QPHashTable[newHI].telephoneNo==-1){
				QPHashTable[newHI]=cObj;
				break;
			}
			i++;
		 }
		if(j>BSIZE)
			cout<<"\nRecord could not be stored!!";
	}
}

void TelephoneDirectory::searchRecordQP(long int telephoneNo){
	int hi,noc,i,j;
	int newHI;//new hash index
	hi=telephoneNo%BSIZE;
	noc=0;//number of comparisons
	if(LPHashTable[hi].telephoneNo == telephoneNo){
		noc++;
		cout<<"\nRecord found after "<<noc<<" comparisons!";
	}
	else{
		 for (int j=1;j<=BSIZE;j++){
			newHI=(hi+i*i)%BSIZE;
			noc++;
			if(QPHashTable[newHI].telephoneNo==telephoneNo){
				cout<<"\nRecord found after "<<noc<<" comparisons!";
				break;
			}
			i++;
		 }
		if(j>BSIZE)
			cout<<"\nRecord NOT found even after "<<noc<<" comparisons!";
	}
}

void TelephoneDirectory::displayRecordsQP(){
	cout<<"\nTelephone No."<<"\t"<<"   Name  ";
	for (int i=0;i<BSIZE;i++)
		cout<<"\n"<<QPHashTable[i].telephoneNo<<"\t"<<QPHashTable[i].name;
}
int main(){
	TelephoneDirectory t1;
	string name;
	int ch=0,ch1,telephoneNo;
	
	while(ch!=6)
	{
		cout<<"\n*******  HASH TABLE - LINEAR & QUADRATIC PROBING********** \n\n";
		cout<<"\n1.INSERT RECORD\n2.DISPLAY All RECORD\n3.SEARCH RECORD\n4.EXIT.";
		cout<<"\nWhat operations:";
		cin >> ch;
		switch(ch)
		{
		case 1:
			cout<<"\n1. Linear Probing";
			cout<<"\n2. Quadratic Probing";
			cout<<"\nWhich Probing:";
			cin>>ch1;
			if (ch1==1)
				t1.insertRecordLP();
			else 
				t1.insertRecordQP();
			
			break;
		case 2:
			cout<<"\n1. Linear Probing";
			cout<<"\n2. Quadratic Probing";
			cout<<"\nWhich Probing:";
			cin>>ch1;
			if (ch1==1)
				t1.displayRecordsLP();
			else 
				t1.displayRecordsQP();
			
			break;
		case 3:
			cout<<"\nEnter the telephone number to be searched::";
			cin>>telephoneNo;
			cout<<"\n1. Linear Probing";
			cout<<"\n2. Quadratic Probing";
			cout<<"\nWhich Probing:";
			cin>>ch1;
			if (ch1==1)
				t1.searchRecordLP(telephoneNo);
			else 
				t1.searchRecordQP(telephoneNo);
			break;
		case 4:
			exit(0);
			break;
		
		default:
			cout<<"\nWrong Choice!!";
		}
	}
	return 0;
}