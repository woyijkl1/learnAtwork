#include <vector>
#include <algorithm>
void print_vector(vector<int> vec){
	for (auto i: vec){
		cout<<i<<" ";
	}
	cout<<endl;
}


vector<int> bubble(vector<int> vec){
	for (int i = 0;i<vec.size();i++ ) {
		for (int j = 0; j<vec.size()-1-i ; j++){
			if (vec[j] > vec[j+1]){
				int temp = vec[j];
				vec[j] = vec[j+1];
				vec[j+1] = temp;
			}
		}		 
	} 
	return vec;
}


int partition (vector<int>& vec, int start , int end){
	if (start >= end) return start;
	//int middel = (start + end)/2;
	
	int pos = start - 1;
	for (int i = start; i<end; i++){
		if (vec[i]<= vec[end]){
			pos ++;
			int temp = vec[pos];
			vec[pos] = vec[i];
			vec[i] = temp;
		}
	}
	pos ++;
	int temp = vec[pos];
	vec[pos] = vec[end];
	vec[end ] = temp;
	
	
	partition (vec,start,pos-1);
	partition(vec,pos+1,end);
	return pos; 
}


vector<int> guibin(vector<int> vec){
	if (vec.size() <= 1) return vec;
	int middle = vec.size()/2;
	vector<int> left(vec.begin(),vec.begin()+middle);
	vector<int> right(vec.begin()+middle,vec.end());
	vector<int> l_result = guibin(left);
	vector<int> r_result = guibin(right);
	
	vector<int> temp;
	int loc = 0;
	int i = 0, j = 0;
	while(i<l_result.size() && j <r_result.size()){
		if (l_result[i] <= r_result[j]){
			temp.push_back(l_result[i]);
			i++;
			loc++;
		}
		else{
			temp.push_back( r_result[j]) ;
			j++;
			loc++;
		}
	}
		
	if (i<l_result.size()){
		for (int k = i; k<l_result.size();k++){
			temp.push_back(l_result[k]);
			loc++;
		}
	}
	if (j < r_result.size()){
		for (int k = j; k<r_result.size();k++){
			temp.push_back(r_result[k])  ;
			loc++;
		}
	}
	return temp;
	
}


void guibin_local(vector<int>& vec, int start, int end){
	if (start>=end) return;
	int middle = (start+end)/2;
	guibin_local(vec,start,middle);
	guibin_local(vec,middle+1,end);
	
	vector<int> temp_vec;
	
	int i=start, j = middle+1;
	while(i<=middle && j<=end){
		if (vec[i]<= vec[j]){
			temp_vec.push_back(vec[i]);
			i++;
		}
		else{
			temp_vec.push_back(vec[j++]);
		}
	}
	while(i<=middle){
		temp_vec.push_back(vec[i++]);
	}
	while(j<=end){
		temp_vec.push_back(vec[j++]);
	}
	for (int x=start; x<=end; x++){
		vec[x] = temp_vec[x-start];
	}
	return;
}



vector<int> heap_sort(vector<int> vec){
	
} 

void learn_sort_use(){
	vector<int> vec = {0,2,3,2,5,6,4,7,8,1,10,5};
	//vector<int> vec_guibin = {2,,1,1,9,9,8,3,4,3,6,5};
	
	cout<<"learn sort use"<<endl;	
	
	//algorithm
	vector<int> vec_2sort(vec);
	sort(vec_2sort.begin(),vec_2sort.end());
	print_vector(vec_2sort); 
	cout<<("reverse")<<endl;
	sort(vec_2sort.begin(),vec_2sort.end(),greater<int>());
	print_vector(vec_2sort);
	
	//bubble
	vector<int> bubble_result = bubble(vec);
	print_vector(bubble_result);
	
	//quick sort
	vector<int> quick_2sort(vec);
	partition(quick_2sort,0,quick_2sort.size()-1);
	print_vector(quick_2sort);
	
	//guibin
	cout<<"guibin result: "<<endl;
	vector<int> guibin_result = guibin(vec);
	print_vector(guibin_result); 
	
	//guibin local
	cout<<"guibin local"<<endl;
	vector<int> vec_guibin_local(vec);
	guibin_local(vec_guibin_local,0, vec.size()-1);
	print_vector(vec_guibin_local); 
	
	
} 
