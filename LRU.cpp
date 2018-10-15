#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
#include <iterator>
#include <algorithm>

using namespace std;

template <typename T1 = int, typename T2 = string >
class LRU
{

	private:

		/* Doubly linked list to store <key value> pair */
		std::list<std::pair<T1, T2> > double_list;

		/* hash map to store the key and the iterator pointing to linked list */
		std::unordered_map<T1, typename std::list<std::pair<T1, T2 > >::iterator > hash_map;

		/* Max entries that should be stored in cache */
		int cachecount;

	public:

		/* Constructor count */
		LRU(int maxCount)
		{
			cachecount = maxCount;
		}

		/* Method to insert the entry into cache */
		bool insertEntry(T1 key, T2 value);

		/* Method to delete the entry from cache */
		void deleteEntry(T1 key);

		/* Get the recently accessed element from cache (Used this function to just test the cache) */
		T2 getRecentlyUsedEntry();

		/* Remove the least used entry */
		void eviction();

		/* API to fetch the entry from the cache, calling this API causes the entry in list to be swapped and added to the front of the list */
		string getEntry(T1 key);

		/* Helper function to print the elements in priority sequence order */
		void printPrioritySequence();

};

template <typename T1, typename T2>
bool LRU<T1, T2>::insertEntry(T1 key, T2 value)
{
	/* Eviction of least recently used element from cache */
	if (hash_map.size() >= cachecount)
	{
		eviction();
	}

	/* Push the new entry to linked list ( Front of the linked list) */
	double_list.push_front(std::make_pair(key, value));

	/* Insert the <key, List iterator> to the hash map for O(1) access */
	hash_map.insert(std::make_pair(key, double_list.begin()));

	return true;
}

template <typename T1, typename T2>
void LRU<T1, T2>::deleteEntry(T1 key)
{
	/* Find the entry in hash map */
	auto iter = hash_map.find(key);

	if (iter == hash_map.end())
	{
		return;
	}

	/* Erase the entry from list using the iterator stored in hash map */
	double_list.erase(iter->second);

	/* Erase the key from hash map */
	hash_map.erase(key);
	
	return;
}

template<typename T1, typename T2>
T2 LRU<T1,T2>::getRecentlyUsedEntry()
{
	/* Recently used <key, value> pair is always in front of the linked list */
	auto pair = double_list.front();

	return pair.second;
}
template <typename T1, typename T2>
string LRU<T1, T2>::getEntry(T1 key)
{
	/* Find if key entry is present in the hash map */
	auto iter = hash_map.find(key);

	/* If key is not found in hash map the return empty string */
	if (iter == hash_map.end())
	{
		return "";
	}

	/* Extract the iterator to linked list where the key, value is stored */
	typename std::list<std::pair<T1, T2>>::iterator iter_list = iter->second;

	/* Copy the value to local variable to be returned */
	string result = iter_list->second;

	/* Erase the <key, value> pair from the list */
	double_list.erase(iter_list);

	/* Erase the key from hash map */
	hash_map.erase(key);

	/* Re-insert back the key value pair as recently accessed element 
	should be in front of the list */
	insertEntry(key, result);

	return result;
}

template<typename T1, typename T2>
void LRU<T1,T2>::eviction()
{
	/* Access the least recently used element from linked list */
	auto pair = double_list.back();

	/* Remove the least recently used entry from hash map */
	hash_map.erase(pair.first);

	/* Eviction is removing the last entry from the table */
	double_list.pop_back();

	return;
}

template<typename T1, typename T2>
void LRU<T1, T2>::printPrioritySequence()
{
	std::for_each(double_list.begin(), double_list.end(), [](std::pair<int, string> &element) 
	{
		cout << element.first << "\t";
		cout << element.second << endl;
	});

	return;
}


int main()
{
	LRU<int, string> cache(3);

	cache.insertEntry(1, "MAKE");
	cache.insertEntry(2, "IN");
	cache.insertEntry(3, "INDIA");

	cout << "Queue just after insertion" << endl;
	cache.printPrioritySequence();
	cout << "--------------------------------" << endl;

	cache.getEntry(2);
	cout << "Queue after accesing 2nd key element" << endl;
	cache.printPrioritySequence();
	cout << "------------------------------------" << endl;

	cache.getEntry(3);
	cout << "Queue after accesing 3rd key element" << endl;
	cache.printPrioritySequence();
	cout << "------------------------------------" << endl;

	/* Insert new key expect KEY = "1" be removed */
	cache.insertEntry(4, "PROJECT");

	cout << "Queue just after 4th element and following eviction procedure" << endl;
	cache.printPrioritySequence();
	cout << "--------------------------------------------------------------" << endl;

	cache.getEntry(2);
	cout << "Queue after accesing 2nd key element" << endl;
	cache.printPrioritySequence();
	cout << "-------------------------------------" << endl;

	cout << "Access non existing key" << endl;
	cout << cache.getEntry(1);

	char c;
	cin >> c;

	return 0;
}