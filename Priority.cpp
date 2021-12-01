#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

// declaring global variables 
int curr_time=0;
float sum_tat=0,sum_wt=0;	

// creating a class for storing infomation related to each process 

class process{
	private:
		int bt; 
	public:
		int bt_rem;
		int pid;
		int tat,wt;
		int prior;
		
		// Function for accepting priority of each process 
		void input_prior(int i){
			cin>>prior;
			pid=i;
		}
		
		// Funtion for accepting burst time of each process
		void input_burst(int i){
			cin>>bt;
			bt_rem=bt;
		}
		
	    // Function for when processes are exhausted
		void process_exhaust(int index){
			if(bt_rem>0){
				curr_time+=bt_rem;
				tat=curr_time;
				sum_tat+=tat;
				wt = tat-bt;
				sum_wt+=wt;
				bt_rem=0;
			}
		}
}ps[100];

// Function to display the process in gaant chart
void display_process_in_gaant(int i,int index){
	if(ps[index].bt_rem>0){
		cout<<"P"<<(ps[i].pid+1)<<"----";
	}
}

// Function for sorting on the basis of priority
bool comparatorPrior(class process a,class process b)
{
	return a.prior<b.prior;
}

// Function for simultaneously sorting on the basis of process ID
bool comparatorPID(class process x,class process y)
{
	return x.pid<y.pid;
}

int main(){
	int n; // number of processes
	int tq; // time quantum
	queue<int> q;
	int completed=0;  // number of completed processes 
	int context=-1;
	int index;
	
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
	
	// execution of processes
	while(completed!=n){
		for(int i=0;i<n;i++){
			q.push(i);
			index=q.front();
			display_process_in_gaant(i, index);
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
		}
	}
	
	cout<<endl<<"Context Switches:"<<context;
	cout<<endl<<"Average waiting time:"<<sum_wt/n;
	cout<<endl<<"Average turn around time:"<<sum_tat/n;
	return 0;
}


