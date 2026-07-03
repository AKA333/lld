#include <bits/stdc++.h>

using namespace std;

// Design Stack DS
template <typename T>
class Stack {
	vector<T>data;
public:
	void push(const T& value){
		data.push_back(value);
	}

	const T& top(){
		if(data.empty()){
			throw out_of_range("stack::top()- stack is empty");
		}
		return data.back();
	}

	void pop(){
		if(data.empty()){
			throw out_of_range("Stack::pop()- stack is empty");
		}
		data.pop_back();
	}

	size_t size() {
		return data.size();
	}

	bool empty() {
		return data.empty();
	}
};

int main(){
	Stack<int>s;

	for(int i=1; i<=5; i++){
		s.push(i);
	}

	while(!s.empty()){
		cout<<s.top()<<" ";
		s.pop();
	}

// 	cout<<"check empty stack top: "<<s.top()<<"\n";
	
	return 0;
}