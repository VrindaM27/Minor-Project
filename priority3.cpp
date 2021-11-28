#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

class process
{
public:
	int bt;
	int pr;
	int rem_bt;
	int tat,wt;
int pid;

};

 bool compare(class process a,class process b)
{
return a.pr<b.pr;

}


 bool comparePID(class process x,class process y)
{
   return x.pid < y.pid;
}


int main()
{
   process pro[100];
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

	return 0;
}
