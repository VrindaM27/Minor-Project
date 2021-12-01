#include<iostream>
#include<algorithm> 
#include<queue> 

using namespace std;

int curr_time = 0,n,tq,index,completed; 
float sum_tat=0,sum_wt=0;

void menu()
{   cout<<endl;
	cout<<endl<<"***** CHOOSE A SCHEDULING ALGORITHM *****";
    cout<<endl<<"1. Priority Based Round Robin Scheduling";
    cout<<endl<<"2. Round Robin Scheduling";
    cout<<endl<<"3. Priority Based Scheduling";
    cout<<endl<<"4. Exit";
    cout<<endl<<endl<<"Enter Choice: ";
}

class process
{
private:
	int bt; //data abstraction using access specifiers

public:
	int bt_rem;
	int pid;
	int tat,wt;
	int prior;

//member functions

//to input the priority for all the processes
void input_prior(int i){
 cin >> prior;
}
//to input the BT for all the processes
void input_burst(int i){
	pid=i;
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

}ps[100];


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
//to sort process id's simultaneously
bool comparatorPID(class process a,class process b)
{
   int x =a.pid;
   int y =b.pid;
   return x < y;
}

void display_process_in_gantt(int index,int i){
	
	if(ps[index].bt_rem>0)
		  {cout<<"P"<<(ps[i].pid+1)<<"-----"; } 
}


int main()
{
    int ch;
    menu();
    cin>>ch;
    switch(ch)
{ case 1:
            { int i,context=0; 
              queue<int> q; //ready queue
              completed= 0; //to check if the process is completed or not
    
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
    
    
   sort(ps,ps+n,comparatorPrior); //sort process table on the basis of the priorities assigned by the user
   
  
 
for(i=0;i<n;i++)
{   q.push(i); //push process in ready queue
    index=q.front();
    display_process_in_gantt(index,i);
		
	// pop out of ready queue and execute the process
	q.pop();
        
    //two cases arise: either bt<tq or bt>=tq
    if(ps[index].bt_rem>tq)
      { ps[index].bt_rem -= tq;
        curr_time += tq;
      }
      else if(ps[index].bt_rem<=tq)
      { ps[index].process_exhaust(index);
          completed++;  
      }
      
//context switching occurs
context++;
}//for

//2nd iteration:-
//sorting on the basis of burst time
sort(ps,ps+n,comparatorBT);

for(i=0;i<n;i++)
{   q.push(i);
	index=q.front();
    q.pop();
    
    if(ps[index].bt_rem>0)
	{context++;} 
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
    int context = -1;
	queue<int> q;
	completed=0; // number of completed processes
	
	// Enter number of processes 
	cout<<"Enter the number of Processes: ";
	cin>>n;
	cout<<endl;
	
	// Enter information related to processes by calling input_bt() function
	for(int i=0;i<n;i++){
		cout<<"Enter Process "<<i+1<<" Burst Time: ";
		ps[i].input_burst(i);
	}
	
	// Enter the time quantum 
	cout<<"Enter the Time Quantum: ";
	cin>>tq;
	
	while(completed!=n){
		for(int i=0;i<n;i++){
			q.push(i);   // pushing the process into the ready queue
			index=q.front();
			display_process_in_gantt(index,i);      // displaying the running process on the gaant chart 
			q.pop();    //removing process from the ready queue 
			
			// process execution 
			if(ps[i].bt_rem>0){
				if(ps[i].bt_rem>tq){
					curr_time+=tq;
					ps[i].bt_rem-=tq;
				}
				else if(ps[i].bt_rem<=tq){
					ps[i].process_exhaust(index);
					completed++;
				}
				context++;
			}
		}//for
	}//while
	
cout<<endl<<"Context Switches: "<<context<<endl;
cout<<"Average Waiting Time: "<<sum_wt/n<<" ms"<<endl;
cout<<"Average Turn Around Time: "<<sum_tat/n<<" ms"<<endl;	
 break;
}
    
case 3:
{   queue<int> q;
	completed=0;  // number of completed processes 
	int context=-1;
	
	// Enter number of Processes
	cout<<"Enter the number of Processes: ";
	cin>>n;
	cout<<endl;
	
	// Enter Priority of each process
	for(int i=0;i<n;i++){
		cout<<"Process "<<i+1<<" Priority: ";
		ps[i].input_prior(i);
	}
	
	// Enter Burst Time for each process 
	for(int i=0;i<n;i++){
		cout<<"Process "<<i+1<<" Burst Time: ";
		ps[i].input_burst(i);
	}
	
	// Enter Time Quantum
	cout<<"Enter Time Quantum: ";
	cin>>tq;
	
	//sorting on the basis of priority	
	sort(ps,ps+n,comparatorPrior);
	
	while(completed!=n){
		for(int i=0;i<n;i++){
			q.push(i);
			index=q.front();
			display_process_in_gantt(i, index);
			q.pop();
			
			if(ps[i].bt_rem>0){
				if(ps[i].bt_rem>tq){
					ps[index].bt_rem-=tq;
					curr_time+=tq;
				}
				else if(ps[i].bt_rem<=tq){
					ps[index].process_exhaust(index);
					completed++;
				}
				context++;
			}
		}//for
	}//while
	
	cout<<endl<<"Context Switches:"<<context;
	cout<<endl<<"Average waiting time:"<<sum_wt/n;
	cout<<endl<<"Average turn around time:"<<sum_tat/n;
    break;
}

case 4:
	{ cout<<endl<<"Thank You!!";
      break;
	}
}//switch
return 0;
}
