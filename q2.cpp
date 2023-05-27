#include <iostream>
#include <fstream>
#include <assert.h> 
using namespace std;
template<class v>
struct HashItem
{
	int key;
	v value;
	short status; //short int // 0-empty 1-deleted 2-occupied 
};
template <typename v>
class hashmap
{
public:
	HashItem<v>* arr;
	int capacity;
	int current_elements;
	int lf;
	virtual int getNextCandidateIndex(int key, int i) {
		i++;
		return ((key + i) % capacity);

	}
public:
	hashmap()
	{
		capacity = 10;
		current_elements = 0;
		arr = new HashItem<v>[capacity];
		lf = 0;
	}
	hashmap(int const capacity)
	{
		this->capacity = capacity;
		current_elements = 0;
		arr= new HashItem<v>[capacity];
		lf = 0;

	}
	void insert(int const key, v const value)
	{
		current_elements++;
		float LF = current_elements / capacity;
		if (LF > 0.75) {
			HashItem<v>* t = new HashItem<v>[capacity * 2];
			for (int i = 0; i < capacity; i++) {
				t[i] = arr[i];
			}
			arr = t;
			capacity *= 2;
		}
		int ii = key % capacity;
		if ((arr[ii].status!=2))
		{
			arr[ii].value = value;
			arr[ii].key = key;
			arr[ii].status = 2;
		}
		else {
			int t = 0;
			while (arr[ii].status == 2) {
				ii = getNextCandidateIndex(key, t);
				t++;
			}
			arr[ii].value = value;
			arr[ii].key = key;
			arr[ii].status = 2;
		}
	}
	bool deleteKey(int k) 
	{
		int ii = k % capacity;
		int t = 1;
		while (arr[ii].key != k) {
			if (ii > capacity) {
				return false;
			}
			else {
				ii = getNextCandidateIndex(k, t); t++;
			}
		}
		arr[ii].status = 1;
		current_elements--;
		return true;
	}
	v* get(int const k) {
		int ii = k % capacity;
		int tt = 1;
		
			while (arr[ii].key != k) {
				if (arr[ii].status==1) {
					return nullptr;
				}
				else {
					ii = getNextCandidateIndex(k, tt); tt++;
				}
			}
			if (arr[ii].status == 1) {
				return nullptr;
			}
			v* t = new v;
			t = &arr[ii].value;
			return t;
	}
	~hashmap()
	{
		delete[] arr;
		arr = nullptr;
	}
};
template <typename v>
class Qmap : public hashmap<v> {
public:
	virtual int getNextCandidateIndex(int key, int i) {
		i++;
		i *= i;
		return ((key + i) % this->capacity);

	}
};
template <typename v>
class Dmap : public hashmap<v> {
public:
	virtual int getNextCandidateIndex(int key, int i) {
		int	first_value = key % this->capacity;
		int second_value = (2 - (key % 2));
		int ii = (first_value + i * second_value) % this->capacity;
		return ii;
	}
};
void populateHash(string filename, hashmap<string>*hash) {
	ifstream fin;
	fin.open("s.txt");
	int index;
	fin >> index;
	fin.ignore(100, '\n');
	int key;
	string val;
	while (!fin.eof()) {
		fin >> key;
		fin.ignore();
		fin >> val;
		hash->insert(key, val);

	}

}
int main()
{
	hashmap<string>* map;
	map = new hashmap<string>;
	populateHash("s.txt", map);
	cout << *map->get(9);
	map->deleteKey(9);
	assert(map->get(9) == nullptr);
	delete map;

	map = new Qmap<string>;
	populateHash("s.txt", map);
	cout << *map->get(98);
	map->deleteKey(98);
	assert(map->get(98) == nullptr);
	delete map;

	map = new Dmap<string>;
	populateHash("s.txt", map);
	cout << *map->get(101);
	map->deleteKey(101);
	assert(map->get(101) == nullptr);
	delete map;
}
