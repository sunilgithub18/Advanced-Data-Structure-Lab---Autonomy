/*AIM:
Company maintains employee information as employee ID, name, designation and salary.
Allow user to add, delete information of employee. 
Display information of particular employee.
If employee does not exist an appropriate message is displayed.
If it is, then the system displays the employee details. 
Use sequential file to maintain the data.

1. Create File
2. Open File
3. Read File
4. Write in File
5. Update in File
6. Search in File
7. Display File

INPUT: Employee Information

OUTPUT: Employee Information in Sequential File  

Author: Dr. Sunil Damodar Rathod.

DATE:16.03.2026

*/
#include<iostream>
#include<ios> //used to get stream size
#include<limits> //used to get numeric limits
#include <cstring>
#include<fstream>
#include<iomanip>
#define MAX 20
using namespace std;

//Employee ATD
typedef struct Employee{
	 int EID;
	 string name;
	 string designation;
	 float salary;
}EMP;


//Implementation Class 
class SequentialFile
{
	private:
		EMP obj;
		
	public:
		//SequentialFile();
		void readData();
		void printData();
		void insertRecord();
		void displayRecords();
		void deleteRecord(string);
		void updateRecord(string);
		void searchRecord(string);
};
//Function to read user input data from keyboard	
void SequentialFile::readData(){
			cout<<"\nEnter Employee ID:";
			cin>>obj.EID;
			
			cout<<"\nEnter Employee Name:";
			cin>>obj.name;
			
			cout<<"\nEnter Employee Designation:";
			cin>>obj.designation;
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer before taking new input
			
			cout<<"\nEnter Employee Salary:";
			cin>>obj.salary;
}

//Function to print user input data on terminal		
void SequentialFile::printData(){
			cout<<"\nEmployee ID:"<<obj.EID;
			cout<<"\nEmployee Name:"<<obj.name;
			cout<<"\nEmployee Designation:"<<obj.designation;
			cout<<"\nEmployee Salary:"<<obj.salary;
}

//Function to add/insert a record in file		
void SequentialFile::insertRecord(){
			fstream out;//File stream object created under fstream class
			//Open a file using open() function with first argument as file name and
			//second argument as file modes.
			out.open("employee1.txt",ios::app|ios::binary);
			readData();
			//Write function will write data in file 
			out.write((char*)&obj,sizeof(obj));
			out.close();//close the file
}

//Function to display all records in file				
void SequentialFile::displayRecords(){
			fstream in;//File stream object created under fstream class
			//Open a file using open() function with first argument as file name and
			//second argument as file modes.
			
			in.open("employee1.txt",ios::in|ios::binary);
			//read from the file untill all records are fetched 
			//and End of the file occures
			while(in.read((char*)&obj,sizeof(obj))){
					cout<<"\n"<<obj.EID<<setw(15)<<obj.name<<setw(15)<<obj.designation<<setw(15)<<obj.salary;
			}
			
			cout<<"\n";
			in.close();
}

//Function to search a record in file
void SequentialFile::searchRecord(string name){
			fstream in;//File stream object created under fstream class
			//Open a file using open() function with first argument as file name and
			//second argument as file modes.
			
			in.open("employee1.txt",ios::in|ios::binary);
			//read from the file untill all records are fetched 
			//and End of the file occures
			while(in.read((char*)&obj,sizeof(obj))){
				//If name to be searched found then display it
				if(obj.name==name){
					cout<<"\nRecord Found";
					cout<<"\n"<<obj.EID<<setw(15)<<obj.name<<setw(15)<<obj.designation<<setw(15)<<obj.salary;
					return;
				}
			}
			cout<<"\nRecord not found";
			in.close();
}	

//Function to update a record in file
void SequentialFile::updateRecord(string name){
			fstream inout;
			int count=0;//count the number of recored visited
			inout.open("employee1.txt",ios::in| ios::out|ios::binary);
			
			while(inout.read((char*)&obj,sizeof(obj))){
				count++;
				if(obj.name==name){
					cout<<"\nRecord Found";
					cout<<"\n"<<obj.EID<<setw(15)<<obj.name<<setw(15)<<obj.designation<<setw(15)<<obj.salary;
					//if record found then read new data from user and update the file
					readData();
					//After reading a record, file pointer is set to end of the record
					inout.seekp(sizeof(obj)*(count-1),ios::beg);
					inout.write((char*)&obj,sizeof(obj));
					return;
				}
			}
			cout<<"\nRecord not found";
			inout.close();
}

void SequentialFile::deleteRecord(string name){
			fstream in;//File stream object created under fstream class
			//Open a file using open() function with first argument as file name and
			//second argument as file modes.
			in.open("employee1.txt",ios::in|ios::binary);
			
			//Open temp file for copying the records from original file
			fstream out;
			out.open("temp.txt",ios::out|ios::binary);
			
			//read from the original file untill all records are fetched 
			//and End of the file occures
			while(in.read((char*)&obj,sizeof(obj))){
				//Copy all the records from original file to temp file,
				//except one to be deleted
				if(obj.name != name){
					out.write((char*)&obj,sizeof(obj));
				}
			}
			in.close();
			out.close();
			//delete original file
			remove("employee1.txt");
			//rename the temp file to the original name
			rename("temp.txt","employee1.txt");
}

int main(){
	SequentialFile t1;
	string name;
	int ch=0;
	
	while(ch!=6)
	{
		cout<<"\n*******  SEQUENTIAL ACCESS FILE PROGRAM USING C++ ********** \n\n";
		cout<<"\n1.INSERT RECORD\n2.DISPLAY All RECORD\n3.SEARCH RECORD\n4.UPDATE RECORD\n5.DELETE RECORD\n6.EXIT.";
		cout<<"\nWhat operations:";
		cin >> ch;
		switch(ch)
		{
		case 1:
 			t1.insertRecord();
			cout<<"\n\nRecord is Inserted..\n\n";
			break;
		case 2:
			t1.displayRecords();
			break;
		case 3:
			cout<<"\nEnter the name to be searched::";
			cin>>name;
			t1.searchRecord(name);
			break;
		case 4:
			cout<<"\nEnter the name to be updated::";
			cin>>name;
			t1.updateRecord(name);
			break;
		case 5:
			cout<<"\nEnter the name to be deleted::";
			cin>>name;
			t1.deleteRecord(name);
			break;
		case 6:
			exit(0);
		}
	}
	return 0;
}
