#include<iostream>
#include <algorithm> //for using the comparator function
#include <queue> //for implementing queue DS


using namespace std;

//global variables
int curr_time = 0; //to track the current time in the gantt chart
float sum_tat=0,sum_wt=0;

//ye class hai jo process info store krega (data encapsulation:storing all info under one umbrella)
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


int main()
{
    
    int n,index,i,context=-2,tq; //here context=-2 isliye hai kyunki ek context switch extra ara tha(you can run the code by taking context=0 and see for yourself XD)
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
      
	display_process_in_gantt(index,i); 
	ps[index].process_exhaust(index);
	context++;
   
}//for

//displaying performance metrics

cout<<endl<<"Context Switches:"<<context; 
cout<<endl<<"Average Turnaround Time:"<<sum_tat/n<<" "<<"ms";
cout<<endl<<"Average Waiting Time:"<<sum_wt/n<<" "<<"ms";
   return 0;
}
   
    
