// implementing Least Recently Used cache using doubly linked list and hashmap
#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;

// Store data in LL's Node
class Node
{
public:
    string key;
    int value;
    Node(string key, int value)
    {
        this->key = key;
        this->value = value;
    }
};

// LRU cache Data Structure
class LRUcache
{
public:
    int maxSize;
    list<Node> l;
    unordered_map<string, list<Node>::iterator> mp;
    LRUcache(int maxSize)
    {
        this->maxSize = maxSize > 1 ? maxSize : 1;
    }

    void insertKeyVal(string key, int val)
    {
        if(mp.count(key)!=0) {
            // replace old val and update
            auto it=mp[key];
            it->value=val;
        } else {
            // check if cache is full
            if(l.size()==maxSize) {
                // remove the least recent item from cache
                Node last=l.back();
                mp.erase(last.key); // remove from hasmap
                l.pop_back(); // remove from LL
            }

            Node n(key,val);
            l.push_front(n);
            mp[key]=l.begin();
        }
    }

    int* getVal(string key)
    {
        if((mp.count(key)!=0)) {
            auto it=mp[key];
            int val=it->value; 
            // node should also come to top because accessed recently
            l.push_front(*it);
            l.erase(it);
            mp[key]=l.begin();
            return &((l.begin())->value);
        }
        return NULL;
    }

    string mostRecentKey()
    {
        return l.front().key;
    }
};

int main()
{
    LRUcache lru(3);
    lru.insertKeyVal("item1",1);
    lru.insertKeyVal("item2",2);
    lru.insertKeyVal("item3",3);
    

    return 0;
}
