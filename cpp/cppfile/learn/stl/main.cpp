#include "vector.h"
#include "stl_vector.h"
#include "stl_set.h"
#include "stl_map.h"
#include "stl_stack.h"
#include "struct.h"
#include "heap.h"
#include "priority_queue.h"
#include "func.h"
#include "sort.h"
#include "string_learn.h"
#include <iostream>

//int partition1(vector<int>& vec, int start, int end){
//	if (start>=end) return start;
//	int pos = start-1;
//	for (int i=start; i<end; i++){
//		if (vec[i]<=vec[end]){
//			pos++;
//			int temp = vec[pos];
//			vec[pos] = vec[i];
//			vec[i] = temp;
//		}
//	}
//	pos++;
//	int temp1 = vec[pos];
//	vec[pos] = vec[end];
//	vec[end] = temp1;
//	
//	partition(vec,0,pos-1);
//	partition(vec,pos+1,end);
//	
//	return pos;
//	
//}

int b_find(vector<int>& vec, int target){
	sort(vec.begin(),vec.end());
	int left = 0, right = vec.size()-1;
	while(left <= right){  //小于等于 不是小于 
		int middle = (left+right)/2;
		if (vec[middle] == target) return middle;
		if(vec[middle]<target) {
			left = middle + 1;
			continue;
		}
		if (vec[middle] > target){
			right = middle -1;
		}
	}
	return -1;
	
	
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
int main(int argc, char** argv) {
//	cout<<"hello world"<<endl;
//	
//	learn_vector_raw();
//	
//	lean_stl_vector();
//	
//	lean_stl_vector();
//	
//	learn_stl_set();
//	
//	learn_stl_map(); 
//	
//	learn_stl_stack();
//	
//	learn_struct();
//	
//	learn_heap();
//	
//	learn_priority_queue(); 
//	
//	learn_function_use();
//
//	learn_sort_use();
//	
//	learn_string();
//	
	
	vector<int> inputs = {2,6,3,9,4,7,19,1};
	int target = 1;
	int result = b_find(inputs,target);
	cout<<result<<endl;
	
	return 0;
}

