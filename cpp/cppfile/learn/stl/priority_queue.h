#include <queue>

void learn_priority_queue(){
	cout<<"learn priority queue"<<endl;
	priority_queue<int> a;
	a.push(5);
	cout<<a.top()<<endl;
	a.push(6);
	cout<<a.top()<<endl;
	a.pop();
	cout<<a.top()<<endl;
	
	//¶Ñ  Ä¬ÈÏÊÇ´ó¶¥¶Ñ
	cout<<"learn heap"<<endl;
	priority_queue<int>  max_que;
	max_que.push(1);
	max_que.push(2);
	cout<<"max_hp:"<<max_que.top()<<endl;
	priority_queue<int, vector<int>, greater<int>> min_hp;
	min_hp.push(1);
	min_hp.push(2);
	cout<<"min_hp:"<<min_hp.top()<<endl; 
	
} 
