/*A Dictionary stores keywords & its meanings.
Provide facility for:
i. adding new keywords
ii. deleting keywords
iii. updating values of any entry.
iv. Provide facility to display whole data sorted in ascending/ Descending order.
v. Also find how many maximum comparisons may require for finding any keyword.
Use Binary Search Tree for implementation.

INPUT: A word & its meaning

OUTPUT:BST of dictionary words

AUTHOR: Sunil Rathod


DATE:12.01.2026
log1000=
log1000=log2^10=10log2
*/
#include<iostream>
#include<ios> //used to get stream size
#include<limits> //used to get numeric limits
#include <cstring>
#define MAX 20
using namespace std;

//ADT BST node
typedef struct Node{
	struct Node *LC;//left child link
	string word;
	string meaning;
	struct Node *RC;//left child link	
}NODE;

class Stack{
   NODE *stk[MAX];
   int top;
   
   public:
	Stack(){
	   top=-1;
	}
   
   void push(NODE * val){
		if(!isFull())
			stk[++top]=val;
		else
			cout<<"\nStack Full!";
   }
	NODE* pop(){
		if(!isEmpty())
			return stk[top--];
		else
			cout<<"\nStack Empty!";
		return NULL;
	}
	
    bool isFull(){
		return (top==MAX-1);
	}
	
	bool isEmpty(){
		return (top==-1);
	}
};

class BST{
	private:
		NODE *root;
		Stack S;
	public:
		BST(){
			root=NULL;
		}
	
		void addNode(string word, string meaning){
			NODE *p;
			p=new NODE;
			p->LC=NULL;
			p->word=word;
			p->meaning=meaning;
			p->RC=NULL;
			
			if(root==NULL){
				root=p;
			}
			else{
				NODE *cur,*f;
				cur=root;
				
				while(cur){
					f=cur;
					if(word == cur->word){
						cout<<"\nDuplicate node!!";
						return;
					}
					else if(word > cur->word)
						cur=cur->RC;
					else
						cur=cur->LC;
				}
				if(word > f->word)
					f->RC=p;
				else
					f->LC=p;
			}
				
		}
		
		//ii. Delete Node 
	void deleteNode(string key)
	{
		NODE *parent,*cur,*p,*q,*t;
		bool found=false;
		if(root==NULL)
			cout<<"\nTree Empty!!";
		else
		{
			cur=root;

			while(cur)
			{
				//if key found then see its position before you delete
				cout<<"\n I am in while with "<<cur->word<<" node\n";
				if(key==cur->word)
				{
					cout<<cur->word<<" : "<<cur->meaning<<" will be deleted!";
					found=true;
					//Node to be deleted (cur) is root node
					if(cur == root)
					{
						cout<<"\nNode "<<cur->word<<" is root node!";
						//Root is only node having no child
						if(cur->LC ==NULL && cur->RC == NULL)
						{
							root=NULL;
							delete cur;
						}
						else
						//Root left subtree but no right child
						if(cur->LC !=NULL && cur->RC == NULL)
						{
							root=root->LC;//left child of root becomes root itself
							delete cur;
						}
						else
						//Root has right subtree then find it's inorder successor
						if(cur->RC != NULL)
						{
							if((cur->RC)->LC == NULL)//right child of cur itself is inorder successor
							{
								p=cur->RC;//set pointer 'p' to right child of cur
								cur->word=p->word;//copy right child data to cur
								cur->RC=p->RC;//set right child of 'p' as right child of cur
								delete p;
							}
							else//Find the inorder successor of cur
							{
								p=t=cur->RC;
								while(t)
								{
								q=p;//pointer 'q' follows 'p'
								p=t;//pointer 'p' follows 't'
								t=t->LC;
								}
								cur->word=p->word;
								q->LC=NULL;
								delete p;
							}
						}
					}
					else
					//Node to be deleted (cur) does not have any child-it's leaf node 
					if(cur->LC == NULL && cur->RC == NULL)
					{
						cout<<"\nLeaf Node of "<<parent->word;
						if((parent->LC)->word==key)//the leaf node is left child of it's parent
						{
							cout<<"\nLeft Child!!";
							parent->LC=NULL;
						}
						else	//the leaf node is right child of it's parent
						{
							cout<<"\nRight Child!!";
							parent->RC=NULL;
						}
						delete cur;
					}
					else
					//cur is left child of parent but not leaf node
					if((parent->LC)->word==key)
					{
						cout<<"\nLeft child Node of "<<parent->word;
						if(cur->LC != NULL && cur->RC == NULL)//Node to be deleted has left subtree but no right subtree
							parent->LC=cur->LC;//left child of cur becomes left child of parent
						else if(cur->LC == NULL && cur->RC != NULL)//Node to be deleted has right subtree but no left subtree
							parent->LC=cur->RC;//right child of cur becomes left child of parent
						
						delete cur;
					}
					else
					//cur is right child  of parent but not leaf node
					if((parent->LC)->word==key)//cur Node is right child of parent
					{
						cout<<"\nRight child Node of "<<parent->word;
						if(cur->LC != NULL && cur->RC == NULL)//Node to be deleted has left subtree but no right subtree
							parent->RC=cur->LC;//left child of cur becomes right child of parent
						else if(cur->LC == NULL && cur->RC != NULL)//cur Node to be deleted has right subtree but no left subtree
							parent->RC=cur->RC;//right child of cur becomes right child of parent
						
						delete cur;
					}
					else
					//Node to be deleted (cur) is either left of right child of parents  
					if(cur->LC != NULL && cur->RC != NULL)//But has both left and right subtree
					{
						cout<<"\nNode "<<cur->word<<" has both left & right child!";
						//Find inorder successor or cur and replace cur with its value
						if((cur->RC)->LC ==NULL)//right child of cur itself is inorder successor
						{
							p=cur->RC;//set pointer 'p' to right child of cur
							cur->word=p->word;//copy right child data to cur
							cur->RC=p->RC;//set right child of 'p' as right child of cur
							delete p;
						}
						else//Find the inorder successor of cur
						{
							p=t=cur->RC;
							while(t)
							{
								q=p;//pointer 'q' follows 'p'
								p=t;//pointer 'p' follows 't'
								t=t->LC;
							}
							cur->word=p->word;
							q->LC=NULL;
							delete p;
						}
					}
					
					return;
				}
				if(key<cur->word)
				{
					parent=cur;//Remember Parent
					cur=cur->LC;//Traverse to left
				}
				else
				{
					parent=cur;//Remember Parent
					cur=cur->RC;;//Traverse to right
				}
			}//end while
			cout<<"\nNode with "<<key<<" not found!!";
		}
		
	}
		
		void updateNode(string word){
			
			if(root==NULL){
				cout<<"\nTree Empty!!";
						return;
			}
			else{
				NODE *cur;
				cur=root;
				
				while(cur){
					if(word == cur->word){
						cout<<"\nEnter new meaning::";
						cin>>cur->meaning;
						break;
					}
					else if(word > cur->word)
						cur=cur->RC;
					else
						cur=cur->LC;
				}	
			}
		}
		
		
		void displayAscBST(NODE *t){
			if(t){
				displayAscBST(t->LC);
				cout<<"["<<t->word<<"|"<<t->meaning<<"]  ";
				displayAscBST(t->RC);
			}
		}
	
		void INORDBST(NODE *t){
			if(t){
				INORDBST(t->LC);
				S.push(t);
				INORDBST(t->RC);
			}
		}
		
		void displayDscBST(){
			INORDBST(returnroot());
			while(!S.isEmpty()){
				NODE* t=S.pop();
				cout<<"["<<t->word<<"|"<<t->meaning<<"]  ";
			}
		}
	
		
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
					if(key == cur->word){
						cout<<"\nWord found!";
						cout<<"\nThe number of comparisons are::"<<count;
						return;
					}
					else if(key > cur->word)
						cur=cur->RC;
					else
						cur=cur->LC;
				}	
			}
			cout<<"\nNode not found";
			
		}
		
		NODE* returnroot(){
			return root;
		}

};

int main(){
	BST P;
	int choice=0;
	string word, meaning;

	while(choice != 6){
		cout<<"\n****************BST Operations**************";
		cout<<"\n1. Add Node";
		cout<<"\n2. Display BST";
		cout<<"\n3. Delete Node";
		cout<<"\n4. Update Node";
		cout<<"\n5. Search Node";
		cout<<"\n6. Exit";
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer before taking new
		cout<<"\nWhat operation you want::";
		cin>>choice;
		
		switch(choice){
			case 1:
				cout<<"\nEnter word::";
				cin>>word;
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer before taking new
				cout<<"\nEnter meaning::";
				cin>>meaning;
				P.addNode(word,meaning);
				break;
			case 2:
				cout<<"\nPrint words in ascending:\n";
				P.displayAscBST(P.returnroot());
				
				cout<<"\n\nPrint words in descending:\n";
				P.displayDscBST();
				break;
			case 3:
				cout<<"\nEnter woderd to be deleted::";
				cin>>word;
				P.deleteNode(word);
				
				break;
			case 4:
				//cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer before taking new
				cout<<"\nEnter word::";
				cin>>word;
				P.updateNode(word);
				
				break;
			case 5:
				cout<<"\nEnter word to be searched::";
				cin>>word;
				P.searchNode(word);
				
				break;
			case 6:
				cout<<"\nThanks for using application!!";
				break;
			default:
				cout<<"\nWrong Choice!!";
		}
	}
	return 0;
}

