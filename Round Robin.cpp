#include<iostream>
#include<queue>
using namespace std; 

// declaring global variables 
int curr_time=0;
float sum_tat=0,sum_wt=0;

// creating a class for storing infomation related to each process 
//  DATA ENCAPSULATION 
class process{
	private:
		int bt;
	public: 
		int bt_rem;
		int pid;
		int tat,wt;
		int prior;
		
		// function for input the burst time
		void input_burst(int i){
			cin>>bt;
			bt_rem = bt;
			pid=i;
		}
		
		// function for process exhaust
		void process_exhaust(int index){
			if(bt_rem>0){
				curr_time+=bt_rem;
				tat=curr_time;
				sum_tat+=tat;
				wt=tat-bt;
				sum_wt+=wt;
				bt_rem=0;
			}
		}
		
}ps[100];

void display_process_in_gaant(int index,int i){
	if(ps[index].bt_rem>0){
		cout<<"P"<<(ps[i].pid+1)<<"----";
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
		cout<<"Enter Process "<<i+1<<" Burst Time: ";
		ps[i].input_burst(i);
	}
	
	// Enter the time quantum 
	cout<<"Enter the Time Quantum: ";
	cin>>tq;
	
	// execution of processes 
	while(completed!=n){
		for(int i=0;i<n;i++){
			q.push(i);   // pushing the process into the ready queue
			index=q.front();
			display_process_in_gaant(index,i);      // displaying the running process on the gaant chart 
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
		}
	}
	// Printing evaluation metrics
	cout<<endl<<"Context Switches: "<<context<<endl;
	cout<<"Average Waiting Time: "<<sum_wt/n<<" ms"<<endl;
	cout<<"Average Turn Around Time: "<<sum_tat/n<<" ms"<<endl;
	return 0;	
}
