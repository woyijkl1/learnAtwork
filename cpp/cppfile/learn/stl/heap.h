#include <algorithm>
#include <vector>
void print_vec(vector<int> vec){
	for (auto i:vec){
		cout<<i<<" ";
	} 
	cout<<endl;
}
void learn_heap(void){
	cout<<"learn heap use"<<endl;
	vector<int> vec = {1,3,2,4,5};
	//make heap
	make_heap(vec.begin(),vec.end());
	print_vec(vec);
	
	//push
	vec.push_back(100);
	push_heap(vec.begin(),vec.end());
	print_vec(vec);
	
	//pop
	pop_heap(vec.begin(),vec.end());
	cout<<vec.back()<<endl;
	vec.pop_back();
	print_vec(vec);
	
	
}
