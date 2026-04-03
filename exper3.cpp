/*Use the map of the area around the college as the graph.
Identify the prominent land marks as nodes.
Represent a given graph using adjacency matrix/list 
to perform DFS 
and 
using adjacency list to perform BFS.

INPUT: Graph G

OUTPUT:DFS / BFS travesals

AUTHOR: Sunil Rathod

DATE:17.02.2026

*/
#include<iostream>
#include<ios> //used to get stream size
#include<limits> //used to get numeric limits
#include <cstring>
#define MAX 20
using namespace std;
//Node structure 
typedef struct Node{
	int val;//value of the node
	struct Node *next;//pointer to next node
}NODE;

//ADT Queue
class Queue{
	private:
		int Q[MAX];
		int front, rear;
	public:
	Queue(){
		front=rear=-1;
	}
	
	bool isEmpty(){
		return(front==-1);
	}
	
	bool isFull(){
		return(rear==MAX-1);
	}
	
	void enqueue(int val){
		if(!isFull()){
			if(rear==-1){
				front=rear=0;
				Q[rear]=val;
			}
			else
				Q[++rear]=val;
		}
		else
			cout<<"\nQueue Full!!";
	}
	
	int dequeue(){
		int val;
		if(!isEmpty()){
			if(front == rear){
				val=Q[front];
				front=rear=-1;
				return val;
			}
			else
				return Q[front++];
		}
		else
			cout<<"\nQueue Empty!!";
		return -1;
	}
	
};

//Implementation class
class GraphLandmarks{
	private:
		int GAM[10][10];//To store graph as adjacency matrix/list
		int n;//number of nodes
		int VISITED[10];//indication of the node is visited or not
		NODE HeaderGAL[10];//Adjecency List header
		
		//Actual landmarks of the campus, here we assign numbers to the Name like, 1-Admin, 2-Canteen, 3-Sports, 4-Workshop
		string Landmark[10]={"Admin","Canteen","Sports","Workshop"};
	
	public:
		//Constructor
		GraphLandmarks(){
			//Initialze the the adjacency matrix
			for(int i=0;i<10;i++)
				for(int j=0;j<10;j++)
					GAM[i][j]=0;
			////Initialze the the adjacency list and visited array
			for(int i=1;i<10;i++){
				VISITED[i]=0;
				HeaderGAL[i].val=i;
				HeaderGAL[i].next=NULL;	
			}
		}
		
		//Graph initialization. This function helps to clear the existing graph.
		void initGraph(){
			for(int i=0;i<10;i++)
				for(int j=0;j<10;j++)
					GAM[i][j]=0;
		
			for(int i=1;i<10;i++){
				VISITED[i]=0;
				HeaderGAL[i].val=i;
				HeaderGAL[i].next=NULL;
				
			}
		}
	
		//This function creates graph as adjacency matix and adjacency list in one go
		void createGraph(){
			bool flag = true;
			int s,d;//Variables to take starting and destination node values for any given edge in graph
			
			NODE *p,*cur;
			
			cout<<"\nEnter graph details here!\n";
			cout<<"\nHow many nodes are there in the graph::";
			cin>>n;
			while(flag){
				cout<<"\nEnter source node:";
				cin>>s;
				cout<<"\nEnter destination node:";
				cin>>d;
				//Adjecency Matrix creation 
				GAM[s][d]=1;
				
				//Adjecency List creation 
				p=new NODE;
				p->val=d;
				p->next=NULL;

				if(HeaderGAL[s].next == NULL)
					HeaderGAL[s].next=p;
				else{
					cur=HeaderGAL[s].next;
					while(cur->next != NULL)
						cur=cur->next;
					
					cur->next=p;
				}
				//If more edges are to be added then continue with loop
				cout<<"\nDo you want to add more edges Yes-1 / No-0?::";
				cin>>flag;
			}
		}
		
		//Function to display Graph as Adjecency Matrix
		void displayGAM(){
			cout<<"\nThe Graph as adjacency matrix\n\t";
			for(int i=1;i<=n;i++)
				cout<<Landmark[i-1]<<"\t";
			for(int i=1;i<=n;i++){
				cout<<"\n"<<Landmark[i-1]<<"	";
				for(int j=1;j<=n;j++)
					cout<<GAM[i][j]<<"	";
			}
		}
		
		//Function to display Graph as Adjecency Matrix
		void displayGAL(){
			NODE *cur;
			cout<<"\nThe Graph as adjacency List\nHEADER\t";
			for(int i=1;i<=n;i++){
				cout<<"\n["<<Landmark[i-1]<<"|"<<HeaderGAL[i].next<<"]->";
				cur=HeaderGAL[i].next;
				while(cur){
					cout<<"["<<Landmark[cur->val-1]<<"|"<<cur->next<<"]->";
					cur=cur->next;
				}
				cout<<"NULL";
			}
		}
		
		//Recursive Depth First Traversal
		void DFS(int v){
			//if the starting vertex is not in the vertex set of graph then return
			if(!(v>=1 && v<=n))
				return;
			VISITED[v]=1;
			cout<<Landmark[v-1]<<"->";
			for (int w=1;w<=n;w++)
				if(GAM[v][w]==1 && VISITED[w]==0)
					DFS(w);
		}
		
		//Function for initialization of visited array
		void initVISITED(){
			for(int i=1;i<10;i++)
				VISITED[i]=0;
		}
		
		
		//Function for Breath First Traversal
		void BFS(int v){
			Queue Qobj;//Queue class object 
			NODE *cur;
			//if the starting vertex is not in the vertex set of graph then return
			if(!(v>=1 && v<=n))
				return;
			
			Qobj.enqueue(v);//Add starting vertex in queue
			VISITED[v]=1;//Mark that node as visited
			
			//Till queue is not empty repeat the loop
			while(!Qobj.isEmpty()){
				v=Qobj.dequeue();
				cout<<Landmark[v-1]<<"->";
				cur=HeaderGAL[v].next;
				//Iterate through all the adjecent nodes of the currently visited node
				while(cur){
					//if the adjecent node of current node is not visited then select that node to be explored
					if(VISITED[cur->val] == 0){
						Qobj.enqueue(cur->val);//enqueue the unvisited adjecent node in Queue
						//cout<<"\nCurrent val "<<cur->val<<" in queue";
						VISITED[cur->val]=1;// mark that chosen node as visited
					}
					cur=cur->next;
				}
			}
		}
};


int main(){
	GraphLandmarks G;
	int choice=0,s;

	while(choice != 6){
		cout<<"\n****************Graph Operations (DFS/BFS)**************";
		cout<<"\n1. Create Graph";
		cout<<"\n2. Display Graph as Adejececny Matrix";
		cout<<"\n3. Display Graph as Adejececny List";
		cout<<"\n4. Traveral Graph DFS";
		cout<<"\n5. Traveral Graph BFS";
		cout<<"\n6. Exit";
		cout<<"\nWhat operation you want::";
		cin>>choice;
		
		switch(choice){
			case 1:
				G.initGraph();
				G.createGraph();
				break;
			case 2:
				cout<<"\nDisplay Graph as Adejececny Matrix\n";
				G.displayGAM();
				break;
			case 3:
				cout<<"\nDisplay Graph as Adejececny List\n";
				G.displayGAL();
				break;
			case 4:
				cout<<"\nDFS on Graph Adejececny Matrix\n";
				cout<<"\nWhat is starting vertex::";
				cin>>s;
				G.initVISITED();
				G.DFS(s);
				break;
			case 5:
				cout<<"\nBFS on Graph Adejececny List\n";
				cout<<"\nWhat is starting vertex::";
				cin>>s;
				G.initVISITED();
				G.BFS(s);
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

