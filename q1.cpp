#include <iostream>
using namespace std;
template <typename T>
struct node {
	T data;
	node* next;
};
template <typename T>
class queue {
	node<T>* top;
	node<T>* tail;
public:
	queue() {
		top = tail = NULL;
	}
	void push(T x) {
		node<T>* t = new node<T>;
		t->data = x;
		t->next = NULL;
		if (tail == NULL) {
			tail = t;
			top = t;
		}
		else {
			tail->next = t;
			tail = t;
		}
	}
	T pop() {
		if (!isempty()) {
			node<T>* y = top;
			top = top->next;
			return y->data;
		}
		else {
			cout << "empty!";
		}
	}
	bool isempty() {
		if (top == NULL) {
			return 1;
		}
		return 0;
	}
	void print() {
		node<T>* p = top;
		while (p != NULL) {
			cout << p->data << " "; p = p->next;
		}
	}

};
int main() {
	queue<int> q1;
	int x = 0, size = 0;
	cout << "enter size >>: ";
	cin >> size;
	cout << "enter k >>: ";
	cin >> x;
	for (int i = 1; i <= size; i++)
	{
		q1.push(i);
	}
	bool f = 0;
	int i = 0, k = 0;
	while (k != size - 1) {
		if (i == x - 1) {// to be killed 
			q1.pop();
			k++;
			f = 1;
		}
		else { // the survivers pushed back again from start 
			q1.push(q1.pop());
		}
		if (f == 1) {
			i = 0; f = 0;
		}
		else { i++; }
		/*while (!q1.isempty()) {
			queue<int> tt;
			tt.push(q1.pop());
		}*/
		q1.print();
		cout << endl;
		cout << endl;
	}
	q1.print();
}