
/*
AIM:
A Dictionary stores keywords & its meanings.
Use Binary Search Tree-AVL concept for implementation.
Provide facility to:
i. Insert new Keyword
ii.Display whole data sorted in dictionary.
iii. Use Height Balance Tree concept to balance the AVL

INPUT: Keyword - meaning
OUTPUT: Balanced AVL with keywords as the data 

Author: Dr. Sunil Damodar Rathod.
Date: 09.03.2023
*/

#include<iostream>
#include<cstring>
#include<ios> //used to get stream size
#include<limits> //used to get numeric limits

using namespace std;
typedef struct keyword{
	char key[20];
	char meaning[100];
}WORD;
typedef struct node
{
   struct node *LC;
   WORD data;
   int height;
   struct node *RC;
}NODE;
 
class AVL
{
	NODE *root;
	int count;
	public:
	AVL()
	{
		root=NULL;
		count=0;
	}
	NODE* getroot()
	{
		return root;
	}
	
	//Function to calculate the height of any given node
	int height(NODE *T)
	{
		int lh,rh;
		if(T==NULL)
			return 0;
		if(T->LC ==NULL && T->RC==NULL)//if leaf node then retrun height '0'
			return 0;
		lh=height(T->LC);//travel left recursively
		rh=height(T->RC);//travel right recursively
		if(lh>rh)//For every node see left height is greater than right 
			return lh+1;//return left height 
		else
			return rh+1;//return left height
	}
	
	//Function to calculate the Balance Factor of a node
    int difference(NODE* T)
	{
		int l_height = height(T->LC);//calculate a left height of a node
		int r_height = height(T->RC);//calculate a right height of a node
		int b_factor = l_height - r_height;// Find the difference of Left and rigth height to get balance factor
		return b_factor;//return banance factor	
	}
	
	//Function to perform RR-Rotation
    NODE *rr_rotate(NODE* Pptr)
	{
		NODE *Aptr;
		Aptr = Pptr->RC;//set a pointer to right child of the pivot
		Pptr->RC = Aptr->LC; //set right child pointer of the pivot to left child of the child node of pivot
		Aptr->LC = Pptr;//set a left child pointer of the right child of pivot to pivot itself
		cout<<"\nRight-Right Rotation";
		return Aptr;
	}
	
	//Function to perform LL-Rotation
    NODE *ll_rotate(NODE* Pptr)
	{
		NODE *Aptr;
		Aptr = Pptr->LC; //set a pointer to left child of the pivot
		Pptr->LC = Aptr->RC; //set left child pointer of the pivot to right child of the child node of pivot
		Aptr->RC = Pptr; //set a left child pointer of the left child of pivot to pivot itself
		cout<<"\nLeft-Left Rotation";
		return Aptr;
	}
	
	//Function to perform LR-Rotation
    NODE *lr_rotate(NODE* Pptr)
	{
		NODE *Aptr;
		Aptr = Pptr->LC;
		Pptr->LC = rr_rotate(Pptr);//First rotate tree to left by applying RR rotation
		cout<<"\nLeft-Right Rotation";
		return ll_rotate(Pptr);	//Next rotate tree to right by applying LL rotation
	}
	
	//Function to perform RL-Rotation
    NODE *rl_rotate(NODE * Pptr)
	{
		NODE *Aptr;
		Aptr = Pptr->RC;
		Pptr->RC = ll_rotate(Pptr);//First rotate tree to right by applying LL rotation
		cout<<"\nRight-Left Rotation";
		return rr_rotate(Pptr); //Next rotate tree to left by applying RR rotation
	}
	
	//Function to balance the tree
    NODE* balance(NODE* T)
	{
		int bal_factor = difference(T);
		//if BF of pivot is positive then check its left child
		if (bal_factor > 1) {
			//if left child of pivot is having BF positive 
			if (difference(T->LC) > 0)
				T = ll_rotate(T);//Apply LL rotation
			else //if left child of pivot is having BF is also negative
				T = lr_rotate(T); ;//Apply LR rotation
		} else if (bal_factor < -1) { //if BF of pivot is negative then check its right child
			if (difference(T->RC) > 0)//if right child of pivot is having BF positive 
				T = rl_rotate(T); //Apply RL rotation
			else
				T = rr_rotate(T);//Apply RR rotation
		}
		return T;	
	}
	
	//Recursive insertion in BST
    NODE* insert(NODE* T,WORD w)
	{
		
		if (T == NULL) {
			T = new NODE;
			T->data = w;
			T->LC = NULL;
			T->RC = NULL;
			root=T;
			return T;
		} else if(strcmp(w.key,T->data.key)<0) { //if new node is smaller than the current
				T->LC = insert(T->LC, w);//Add node to the left of current
				T = balance(T);//Check balance of the current 
		} else if (strcmp(w.key,T->data.key)>0) {//if new node is larger than the current
				T->RC = insert(T->RC, w); //Add node to the right of current
				T = balance(T); //Check balance of the current
		} 
		
		root=T;//update root after rotations
		return T;
	}
	
	//Search node
	void searchNode(string key){
			int count=0;
			if(root==NULL){
				cout<<"\nTree Empty!!";
						return;
			}
			else{
				NODE *cur;
				cur=root;
				
				while(cur){
					count++;
					if(key == cur->data.key){
						cout<<"\nWord found!";
						cout<<"\nThe number of comparisons are::"<<count;
						return;
					}
					else if(key > cur->data.key)
						cur=cur->RC;
					else
						cur=cur->LC;
				}	
			}
			cout<<"\nNode not found";
			
		}

	//INORDER Traversal of tree
	void displayIN(NODE *T)
	{
		if(T)
		{
			displayIN(T->LC);
			cout<<T->data.key<<":"<<T->data.meaning<<endl;
			displayIN(T->RC);
		}
	}
	
	
	
};


int main(void)
{
   AVL B;
   int val,cho,n,cho1;
   WORD w;
   NODE* r;
   char key[30];
   cho=0;
   while(cho != 4)
   {
     cout<<"\n********DICTIONARY STORAGE using AVL*********";
     cout<<"\n1-ADD WORD";
     cout<<"\n2-DISPLAY DICTIONARY";
	 cout<<"\n3-SEARCH KEY";
     cout<<"\n4-EXIT";
     cout<<"\nEnter ur choice:";
     cin>>cho;
	 cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer before taking new
     switch(cho)
     {
       case 1:
		cout<<"\nEnter keyword:";
		cin.clear();//to clear the std in stream
		fflush(stdin);// to flush the input buffer
		cin.getline(w.key,20);//getline function to read multiword string
		cout<<"\nEnter meaning of the word:";
		cin.clear();
		fflush(stdin);
		cin.getline(w.meaning,100);
		r=B.insert(B.getroot(),w);
		break;
		
       case 2:
		B.displayIN(B.getroot());
		break;
		
	   case 3:
		cout<<"\nEnter keyword:";
		cin.clear();//to clear the std in stream
		fflush(stdin);// to flush the input buffer
	    cin.getline(key,20);//getline function to read multiword string
		B.searchNode(key);
		break;
		
	   case 4:
		cout<<"\nProgram Exits!!";
		break;
       default:
		cout<<"\nWrong choice!";
     }
   }

   return 0;
}


/*
D:\ICEM\AY-2022-23\SE\DSAL_Lab>a

********DICTIONARY STORAGE using AVL*********
1-ADD WORD
2-DISPLAY DICTIONARY
3-EXIT
Enter ur choice:1

Enter keyword:f

Enter meaning of the word:f

********DICTIONARY STORAGE using AVL*********
1-ADD WORD
2-DISPLAY DICTIONARY
3-EXIT
Enter ur choice:2
f:f

********DICTIONARY STORAGE using AVL*********
1-ADD WORD
2-DISPLAY DICTIONARY
3-EXIT
Enter ur choice:1

Enter keyword:c

Enter meaning of the word:c

********DICTIONARY STORAGE using AVL*********
1-ADD WORD
2-DISPLAY DICTIONARY
3-EXIT
Enter ur choice:2
c:c
f:f

********DICTIONARY STORAGE using AVL*********
1-ADD WORD
2-DISPLAY DICTIONARY
3-EXIT
Enter ur choice:1

Enter keyword:b

Enter meaning of the word:b

********DICTIONARY STORAGE using AVL*********
1-ADD WORD
2-DISPLAY DICTIONARY
3-EXIT
Enter ur choice:2
b:b
c:c
f:f

********DICTIONARY STORAGE using AVL*********
1-ADD WORD
2-DISPLAY DICTIONARY
3-EXIT
Enter ur choice:1

Enter keyword:a

Enter meaning of the word:a
Left-Left Rotation
********DICTIONARY STORAGE using AVL*********
1-ADD WORD
2-DISPLAY DICTIONARY
3-EXIT
Enter ur choice:2
a:a
b:b
c:c
f:f

********DICTIONARY STORAGE using AVL*********
1-ADD WORD
2-DISPLAY DICTIONARY
3-EXIT
Enter ur choice:3

Program Exits!!

*/
