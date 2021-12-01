#include<stdio.h>
#include<stdlib.h>
#define MAX 20
#include<iostream>
#include <algorithm> 
#include <queue> 
#include<conio.h>
using namespace std;

int curr_time = 0; 
float sum_tat=0,sum_wt=0,sum_wat=0;
int bt_rem, pid,tat,wt,prior,rem_bt,wat,bt;
void menu()
{
    printf("\n\t\t****MENU*****");
    printf("\n\t\t1. PBRR");
    printf("\n\t\t2. RR");
    printf("\n\t\t3. Priority");
    printf("\n\t\t4. EXIT");
    printf("\n\t\tEnter Choice: \t");
    
}
class process
{
private:
	int bt; //since ek hi function hai jiske liye ye variable imp rkhta hai,therefore,hiding it from others(abstraction)

public:
	int bt_rem;
	int pid;
	int tat,wt;
	int prior;

//member functions

//to input the priority for all the processes
void input_prior(int i){
 cin >> prior;
 pid=i;
}


//to input the BT for all the processes
void input_burst(int i){
    cin >> bt;
    bt_rem=bt;   
}

//in case there is some BT remaining for the process
void process_exhaust(int index){
	
if(bt_rem>0){
curr_time+=bt_rem;
tat = curr_time;
sum_tat+=tat;
  
  
wt = tat - bt; //waiting time
sum_wt+=wt;
  
bt_rem=0; 
}
 
}

}ps[100];//class end


//for sorting on the basis of burst time
bool comparatorBT(class process a,class process b)
{
   int x =a.bt_rem;
   int y =b.bt_rem;
   return x < y;
}

//for sorting on the basis of priority
bool comparatorPrior(class process a,class process b)
{
   int x =a.prior;
   int y =b.prior;
   return x < y;
}
//process id's ko simultaneously sort krne k liye
bool comparatorPID(class process a,class process b)
{
   int x =a.pid;
   int y =b.pid;
   return x < y;
}

//to display all processes in the form of a gantt chart
void display_process_in_gantt(int index,int i){
	
	if(ps[index].bt_rem>0)
		  {
		 	cout<<"P"<<(ps[i].pid+1)<<"-----"; 
		  } 
}
//RR
class process1{
	public:
		int pid;
		int bt; 
		int rem_bt;
		int tat,wat;
		
		// function for input the burst time
		void input_bt(int index){
			pid = index;
			cin>>bt;
			rem_bt = bt;
		}
		
		// function for displaying the process
		void display_process_in_gaant(int i){
			if(rem_bt>0){
				cout<<"P"<<(pid+1)<<"------";
			}
		}
}ps1[100];

//Priority
class process2
{
public:
	int bt;
	int pr;
	int rem_bt;
	int tat,wt;
int pid;

};

 bool compare(class process2 a,class process2 b)
{
return a.pr<b.pr;

}


 bool comparePID(class process2 x,class process2 y)
{
   return x.pid < y.pid;
}


int main()
{
    int ch,TQ,n;
    process P[MAX];
    float avg_WT,avg_TAT;
    do
    {
       
        menu();
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
            {
                
    int n,index,i,context=0,tq; 
    queue<int> q; //ready queue
    int completed= 0; //to check if the process is completed or not
    
    
    cout<<"Enter total number of processes: ";
    cin>>n;    
    
    //loop to input priorities
    for(int i=0;i<n;i++)
    { cout<<"\nEnter Process " <<i<< " Priority: ";
      ps[i].input_prior(i);
    }
    
    //loop to input BT
    for(int i=0;i<n;i++)
    { cout<<"\nEnter Process " <<i<< " Burst Time: ";
      ps[i].input_burst(i);
    
    }

    cout<<"\nEnter time quantum: ";
    cin>>tq;
    cout<<endl;
    
    
   sort(ps,ps+n,comparatorPrior); //pehle sort krlia process table ko on the basis of the priorities assigned by the user
   
  
 
for(i=0;i<n;i++){
      	//pehle process ko push kia in the ready queue
      	
      	q.push(i);
      	index=q.front();
      	
      	
      display_process_in_gantt(index,i);
		
		// process ko ready queue se nikalkr execute kia
        q.pop();
        
    //two cases arise: either bt<tq or bt>=tq
      	
      if(ps[index].bt_rem>tq)
      {    
            ps[index].bt_rem -= tq;
            curr_time += tq;
        
      }
      else if(ps[index].bt_rem<=tq)
      {     
      
          ps[index].process_exhaust(index);
          completed++;
          
      }
      
//context switching occurs
context++;
}//for


//2nd iteration:-

//sorting on the basis of burst time
sort(ps,ps+n,comparatorBT);



for(i=0;i<n;i++){
		
//pehle process ko push kia in the ready queue
	q.push(i);
	index=q.front();
    
    q.pop();
    
    if(ps[index].bt_rem>0)
		  {
		 	context++; 
		  } 
	display_process_in_gantt(index,i); 
	ps[index].process_exhaust(index);
	
   
}//for

//displaying performance metrics

cout<<endl<<"Context Switches:"<<context-1; 
cout<<endl<<"Average Turnaround Time:"<<sum_tat/n<<" "<<"ms";
cout<<endl<<"Average Waiting Time:"<<sum_wt/n<<" "<<"ms";
                break;
            }
            case 2:
            {
                int n; // number of processes
	int tq; // time quantum 
	int index;
	int context = -1;
	queue<int> q;
	int completed=0; // number of completed processes
	
	// Enter number of processes 
	cout<<"Enter the number of Processes: ";
	cin>>n;
	cout<<endl;
	
	// Enter information related to processes by calling input_bt() function
	for(int i=0;i<n;i++){
		cout<<"Process "<<i+1<<" Burst Time: ";
		ps1[i].input_bt(i);
	}
	
	// Enter the time quantum 
	cout<<"Enter the Time Quantum: ";
	cin>>tq;
	
	// execution of processes 
	while(completed!=n){
		for(int i=0;i<n;i++){
			q.push(i);   // pushing the process into the ready queue
			ps1[i].display_process_in_gaant(i);      // displaying the running process on the gaant chart 
			q.pop();    //removing process from the ready queue 
			
			// process execution 
			if(ps1[i].rem_bt>0){
				if(ps1[i].rem_bt>tq){
					curr_time+=tq;
					ps1[i].rem_bt-=tq;
					context++;
				}
				else if(ps1[i].rem_bt<tq || ps1[i].rem_bt==tq){
					curr_time+=ps1[i].rem_bt;
					ps1[i].rem_bt=0;
					completed++;
					ps1[i].tat = curr_time;
					ps1[i].wat = ps1[i].tat - ps1[i].bt;
					sum_tat+=ps1[i].tat;
					sum_wat+=ps1[i].wat;
					context++;
				}
			}
		}
	}
	// Printing evaluation metrics
	cout<<endl<<"Context Switches: "<<context<<endl;
	cout<<"Average Waiting Time: "<<sum_wat/n<<" ms"<<endl;
	cout<<"Average Turn Around Time: "<<sum_tat/n<<" ms"<<endl;
                break;
            }
            case 3:
            {
                 process2 pro[100];
	int n,i,j;
	queue<int>q;
	int curr_time=0;
	int completed=0;
	float sum_tat=0,sum_wat=0;
	cout<<"Enter the number of process:";
	cin>>n;
	cout<<endl;
	for(i=0;i<n;i++){
            cout<<"Enter Processes"<<i<<"Burst Time:";
    cin>>pro[i].bt;
    pro[i].rem_bt=pro[i].bt;
    pro[i].pid=i+1;
    }


for(i=0;i<n;i++){
    cout<<"Enter Processes"<<i<<"Priority:";
    cin>>pro[i].pr;
    }



sort(pro,pro+n,compare);


while(completed!=n){
            for(i=0;i<n;i++){
                if(pro[i].rem_bt>0){
                    q.push(i);
                    cout<<pro[i].pid<<"-----";
                }
                curr_time+=pro[i].rem_bt;
                pro[i].rem_bt=0;
                completed++;
                q.pop();
                
                
                pro[i].tat=curr_time;
                pro[i].wt=pro[i].tat-pro[i].bt;
                sum_tat+=pro[i].tat;
                sum_wat+=pro[i].wt;
            }

	}

	cout<<endl<<"Average waiting time:"<<sum_wat/n<<"ms";
	cout<<endl<<"Average turn around time:"<<sum_tat/n<<"ms";
                break;
            }
            case 4:
                break;
            
        }
        getch();
    }while(ch!=4);
}

