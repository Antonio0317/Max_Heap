#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class Max_heap {
	private:
		int* heap;
		int heap_size;
		int capacity;

	public:	
		void ChangeSize1D(int*&, int, int);
		void push(int);
		bool pop();
		bool Is_Empty();
		int Top();
		void Print_heap();
		Max_heap();
		~Max_heap();
		int get_size();
};

class Str_tok {
	public:
		string str;
		string* tmp;
		void String_split(string);
		Str_tok();
		~Str_tok();
};

int main () {
	Max_heap test;
	Str_tok token;

	while(getline(cin, token.str)) {
		token.String_split(" ");
		if(token.tmp[0] == "I") {
			int tmp1 = 0;
			int minus_flag = 0;
			int i = 0;
			if(token.tmp[1][0] == '-') {
				minus_flag = 1;
				i++;
			}
			for(i; i < token.tmp[1].length(); i++) {
				tmp1 *= 10;
				tmp1 += token.tmp[1][i]-'0';
			}
			if(minus_flag) {
				tmp1 *= -1;
				minus_flag = 0;
			}
			test.push(tmp1);
			cout << "done" << endl;
		}
		else if(token.tmp[0] == "D" && token.tmp[1].length() != 0) {
			int tmp1 = 0;
			for(int i= 0; i < token.tmp[1].length(); i++) {
				tmp1 *= 10;
				tmp1 += token.tmp[1][i]-'0';
			}
			if (tmp1 > test.get_size()) {
				cout << "error" << endl;
				continue;
			}
			int * buffer = new int[tmp1+1];
			for(int i = 0; i< tmp1; i++) {
				buffer[i] = test.Top();
				test.pop();
			}
			for(int i = tmp1-2; i>=0; i--) {
				test.push(buffer[i]);
			}
			cout << "done" << endl;
		}
		else if(token.tmp[0] == "T" && token.tmp[1].length() != 0) {
			int tmp1 = 0;
			for(int i= 0; i < token.tmp[1].length(); i++) {
				tmp1 *= 10;
				tmp1 += token.tmp[1][i]-'0';
			}
			if (tmp1 > test.get_size()) {
				cout << "error" << endl;
				continue;
			}
			int * buffer = new int[tmp1+1];
			for(int i = 0; i< tmp1-1; i++) {
				buffer[i] = test.Top();
				test.pop();
			}
			cout << test.Top() << endl;
			for(int i = tmp1-2; i>=0; i--) {
				test.push(buffer[i]);
			}
		}
		else if(token.tmp[0] == "D") {
			if(test.pop()) {
				cout << "done" << endl;
			}
			else {
				cout << "error" << endl;
			}
		}
		else if(token.tmp[0] == "T") {
			if(test.Is_Empty()) {
				cout << "error" << endl;
			}
			else {
				cout << test.Top() << endl;
			}
		}
		else if(token.tmp[0] == "P") {
			if(test.Is_Empty()) {
				cout << "error" << endl;
			}
			else {
				test.Print_heap();
			}
		}
	}
}
void Max_heap::ChangeSize1D(int*& h, int old_size, int new_size) {
	int* tmp = new int[new_size+1];
	int num = min(old_size, new_size);

	copy(h, h+num+1, tmp);
	delete[] h;
	h = tmp;
}

Max_heap::Max_heap() {
	heap = new int[101];
	heap_size = 0;
	capacity = 100;
}

Max_heap::~Max_heap() {
	delete[] heap;
}

bool Max_heap::Is_Empty() {
	if(heap_size == 0) {
		return true;
	}
	return false;
}

void Max_heap::push(int data) {
	if(capacity == heap_size) {
		ChangeSize1D(heap, capacity, capacity*2);
		capacity *= 2;
	}
	int current = ++heap_size;
	while(current != 1 && heap[current/2] < data) {
		heap[current] = heap[current/2];
		current /= 2;
	}
	heap[current] = data;
}

bool Max_heap::pop() {
	if(Is_Empty()) {
		return false;
	}
	int last = heap[heap_size--];

	int current = 1;
	int child = 2;
	while(child <= heap_size) {
		//child를 current노드의 큰자식으로 설정
		if(child < heap_size && heap[child] < heap[child+1]) {
			child++;
		}
		if(last >= heap[child]) {	//current에 last를 삽입할수있는가?
			break;
		}

		heap[current] = heap[child];//큰놈으로 바꿔줌
		current = child;//자식으로 이동
		child *= 2; //한레벨 내려감
	}
	heap[current] = last;
	return true;
}

int Max_heap::Top() {
	return heap[1];
}

void Max_heap::Print_heap() {
	for(int i =1; i<=heap_size; i++) {
		cout << heap[i];
		if(heap_size != i) {
			cout << " ";
		}
	}
	cout << endl;
}

int Max_heap::get_size() {
	return heap_size;
}
Str_tok::Str_tok() {
	str = "";
	tmp = NULL;
}

Str_tok::~Str_tok() {
	delete[] tmp;
}

void Str_tok::String_split(string delimeter) {
	int cutAt;
	int index = 0;
	string* strResult = new string[10];
	string strOrigin = str;

	while((cutAt = strOrigin.find_first_of(delimeter)) != strOrigin.npos) {
		if(cutAt > 0) {
			strResult[index++] = strOrigin.substr(0, cutAt);
		}
		strOrigin = strOrigin.substr(cutAt+1);
	}
	if(strOrigin.length() > 0) {
		strResult[index++] = strOrigin.substr(0, cutAt);
	}
	tmp = strResult;
}
