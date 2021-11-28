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
		
		// function for displaying the process
		void display_process_in_gaant(int i){
			if(rem_bt>0){
				cout<<"P"<<(pid+1)<<"------";
			}
		}
}ps[100];

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
			q.push(i);   // pushing the process into the ready queue
			ps[i].display_process_in_gaant(i);      // displaying the running process on the gaant chart 
			q.pop();    //removing process from the ready queue 
			
			// process execution 
			if(ps[i].rem_bt>0){
				if(ps[i].rem_bt>tq){
					curr_time+=tq;
					ps[i].rem_bt-=tq;
					context++;
				}
				else if(ps[i].rem_bt<tq || ps[i].rem_bt==tq){
					curr_time+=ps[i].rem_bt;
					ps[i].rem_bt=0;
					completed++;
					ps[i].tat = curr_time;
					ps[i].wat = ps[i].tat - ps[i].bt;
					sum_tat+=ps[i].tat;
					sum_wat+=ps[i].wat;
					context++;
				}
			}
		}
	}
	// Printing evaluation metrics
	cout<<endl<<"Context Switches: "<<context<<endl;
	cout<<"Average Waiting Time: "<<sum_wat/n<<" ms"<<endl;
	cout<<"Average Turn Around Time: "<<sum_tat/n<<" ms"<<endl;
	return 0;		
}
