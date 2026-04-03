
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
		Aptr = Pptr->RC;
		Pptr->RC = Aptr->LC;
		Aptr->LC = Pptr;
		cout<<"\nRight-Right Rotation";
		return Aptr;
	}
	
	//Function to perform LL-Rotation
    NODE *ll_rotate(NODE* Pptr)
	{
		NODE *Aptr;
		Aptr = Pptr->LC;
		Pptr->LC = Aptr->RC;
		Aptr->RC = Pptr;
		cout<<"\nLeft-Left Rotation";
		return Aptr;
	}
	
	//Function to perform LR-Rotation
    NODE *lr_rotate(NODE* Pptr)
	{
		NODE *Aptr;
		Aptr = Pptr->LC;
		Pptr->LC = rr_rotate(Pptr);
		cout<<"\nLeft-Right Rotation";
		return ll_rotate(Pptr);	
	}
	
	//Function to perform RL-Rotation
    NODE *rl_rotate(NODE * Pptr)
	{
		NODE *Aptr;
		Aptr = Pptr->RC;
		Pptr->RC = ll_rotate(Pptr);
		cout<<"\nRight-Left Rotation";
		return rr_rotate(Pptr);
	}
	
	//Function to balance the tree
    NODE* balance(NODE* T)
	{
		int bal_factor = difference(T);
		if (bal_factor > 1) {
			if (difference(T->LC) > 0)
				T = ll_rotate(T);
			else
				T = lr_rotate(T);
		} else if (bal_factor < -1) {
			if (difference(T->RC) > 0)
				T = rl_rotate(T);
			else
				T = rr_rotate(T);
		}
		return T;	
	}
	
	
    NODE* insert(NODE* T,WORD w)
	{
		
		if (T == NULL) {
			T = new NODE;
			T->data = w;
			T->LC = NULL;
			T->RC = NULL;
			root=T;
			return T;
		} else if(strcmp(w.key,T->data.key)<0) {
				T->LC = insert(T->LC, w);
				T = balance(T);
		} else if (strcmp(w.key,T->data.key)>0) {
				T->RC = insert(T->RC, w);
				T = balance(T);
		} 
		
		root=T;//update root after rotations
		return T;
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
   while(cho != 3)
   {
     cout<<"\n********DICTIONARY STORAGE using AVL*********";
     cout<<"\n1-ADD WORD";
     cout<<"\n2-DISPLAY DICTIONARY";
     cout<<"\n3-EXIT";
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
