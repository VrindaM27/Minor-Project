#include<iostream>
#include<queue>
using namespace std; 

// declaring global variables 
int curr_time=0;
float sum_wat=0,sum_tat=0;

// creating a class for storing infomation related to each process 
//  DATA ENCAPSULATION 
class process{
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
		
}ps[100];

// function for displaying the process
void display_process_in_gaant(int index,int i){
	if(ps[index].rem_bt>0){
		cout<<"P"<<(ps[i].pid+1)<<"------";
	}
	
}
// function for executing the process
void process_execution(int index,int completed,int context,int tq){
	if(ps[index].rem_bt>tq){
		curr_time+=tq;
		ps[index].rem_bt -=tq;
		context++;
	}
	if(ps[index].rem_bt<=tq){
		curr_time+=tq;
		ps[index].rem_bt=0;   // indicating the process has been terminated
		completed++;      // increment number of completed processes
	
		ps[index].tat = curr_time;     // total turnaround time for the process 
		ps[index].wat = ps[index].tat - ps[index].bt;  // total waiting time for the process
		sum_tat+=ps[index].tat; 
		sum_wat+=ps[index].wat;
		context++;
	}
}

int main(){
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
		ps[i].input_bt(i);
	}
	
	// Enter the time quantum 
	cout<<"Enter the Time Quantum: ";
	cin>>tq;
	
	// execution of processes 
	while(completed!=n){
		for(int i=0;i<n;i++){
			q.push(i);   // pushing the burst time into the ready queue
			index=q.front(); 
			display_process_in_gaant(index,i);      // displaying the running process on the gaant chart 
			q.pop();    //removing process from the ready queue 
			process_execution(i,completed,context,tq);	//executing the process
		}
	}
	cout<<endl<<"Context Switches: "<<context<<endl;
	cout<<"Average Waiting Time: "<<sum_wat/n<<" ms"<<endl;
	cout<<"Average Turn Around Time: "<<sum_tat/n<<" ms"<<endl;
	return 0;		
}
