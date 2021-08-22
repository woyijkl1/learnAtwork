#include <iostream>
#include <vector>
using namespace std;
int learn_vector_raw(void){
	cout<<"learn vector"<<endl;
	int vec[5] = {0,1,2,3,4};
	for (int i=0;i<sizeof(vec)/sizeof(vec[0]);i++){
		cout<<vec[i];
	}
	cout<<endl;
	
	int vec2[2][2] = {{12,22},{3,4}};
	cout<<vec2[0][0]<<vec2[0][1]<<endl;
	
	//二维数组初始化
	vector<vector<int> > newOne(3, vector<int>(4, 8)); 
	for (auto i:newOne){
		for (auto j:i){
			cout<<j<<" ";
		}
		cout<<endl;
	}
	
	
	
}
