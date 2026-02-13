/*
Construct an expression tree from the given prefix expression 
eg. +--a*bc/def and 
traverse it using post-order traversal(non recursive) 
and then delete the entire tree.

INPUT: A prefix expression

OUTPUT: Expression tree

AUTHOR: Sunil Rathod

DATE:03.02.2026
*/

#include<iostream>
#include<ios> //used to get stream size
#include<limits> //used to get numeric limits
#include <cstring>

#define MAX 20
using namespace std;
//ADT Expression tree node
typedef struct Node{
	struct Node *LC;//left child link
	char data;
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

//Implementation class
class ExpressionTree{
	private:
		char exp[20];
		NODE* root;
	public:
		ExpressionTree(){
			root=NULL;
		}
		
		void readPrefixExp(){
			cout<<"\nEnter Prefix expression::";
			cin>>exp;
		}
		
		void printPrefixExp(){
			cout<<"\nThe Prefix expression is::"<<exp;
		}
		
		bool isOperator(char token){
			return (token=='+' || token=='-' || token=='*' || token=='/' || token=='^');
		}
		
		bool isOperand(char token){
			return ((token>='a' &&  token<='z') || (token>='A' &&  token<='Z'));
		}
		
		void generateExpTree(){
			Stack S;
			NODE *p;
			
			for (int i=strlen(exp)-1;i>=0;i--){
				p=new NODE;
				p->LC=NULL;
				p->data=exp[i];
				p->RC=NULL;
				if(isOperand(exp[i]))
					S.push(p);
				else if (isOperator(exp[i])){
					p->LC=S.pop();
					p->RC=S.pop();
					S.push(p);	
				}
			}
			root=S.pop();
		}
		
		void displayET(NODE *t){
			if(t){
				displayET(t->LC);
				cout<<t->data<<" ";
				displayET(t->RC);
			}
		}
		
		NODE* getRoot(){
			return root;
		}
		
		void nonRecursivePost(NODE* root)
		{
			if (root == NULL)
				return;

			//Local stacks - stack1 and stack2
			Stack stack1, stack2;

			// Push root to first stack
			stack1.push(root);
			NODE* node;

			// Repeat untill first stack is not empty
			while (!stack1.isEmpty()) {
				// pop node from stack1 and push to stack2
				node = stack1.pop();//pop or remove that node from stack1
				stack2.push(node);//save it in stack2

				// push left and right node of current node popped from stack1 
				if (node->LC)
					stack1.push(node->LC);
				if (node->RC)
					stack1.push(node->RC);
			}

			// if stack2 is not empty print the nodes
			while (!stack2.isEmpty()) {
				node = stack2.pop();
				cout << node->data << " ";
			}	
		}
	
};

int main(){
	ExpressionTree e1;
  	int choice=0;
	
  	while(choice!=6)
  	{	
  		cout<<"\n*************Expression Tree***************";
  		cout<<"\n1. Read Expression";
  		cout<<"\n2. Print Expression";
  		cout<<"\n3. Build Tree ";
  		cout<<"\n4. Print Tree Inorder";
		cout<<"\n5. Print Tree Non Recurssive Postorder";
  		cout<<"\n6. Exit Application";
  		cout<<"\nEnter your choice::";
		cin>>choice;
  		switch (choice){
  			case 1:
				e1.readPrefixExp();
  			 	break;
  			case 2:
  			 	e1.printPrefixExp();
  			 	break;
  			case 3:
  			 	e1.generateExpTree();
  			 	break;
  			case 4:
  			 	e1.displayET(e1.getRoot());
  			 	break;
			case 5:
  			 	e1.nonRecursivePost(e1.getRoot());
  			 	break;
  			case 6:
				cout<<"\nThanks for using Application!";
  			 	break;
  			default :
  			    cout<<"\nWrong choice!!";
  		}
  	}
	
	return 0;
}