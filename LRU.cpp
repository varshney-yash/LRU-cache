#include <iostream>
#include <list>
#include <unordered_map>
#include <memory>
using namespace std;

// implementing Least Recently Used cache using doubly linked list and hashmap

// Store data in LL's Node
class Node {
public:
    string key;
    int value;
    Node(string key, int value) : key(key), value(value) {}
};

// LRU cache Data Structure
class LRUcache {
public:
    int maxSize;
    list<shared_ptr<Node>> l;
    unordered_map<string, list<shared_ptr<Node>>::iterator> mp;

    LRUcache(int maxSize) : maxSize(maxSize >  1 ? maxSize :  1) {}

    void insertKeyVal(string key, int val) {
        if (mp.count(key) !=  0) {
            // Replace old value and update
            auto it = mp[key];
            (*it)->value = val;
            l.push_front(*it);
            l.erase(it);
            mp[key] = l.begin();
        } else {
            // Check if cache is full
            if (l.size() == maxSize) {
                // Remove the least recent item from cache
                auto last = l.back();
                mp.erase(last->key); // Remove from hashmap
                l.pop_back(); // Remove from LL
            }

            // Insert new node at the front of the list
            auto newNode = make_shared<Node>(key, val);
            l.push_front(newNode);
            mp[key] = l.begin();
        }
    }

    int* getVal(string key) {
        if (mp.count(key) !=  0) {
            auto it = mp[key];
            l.push_front(*it);
            l.erase(it);
            mp[key] = l.begin();
            return &((*l.begin())->value);
        }
        return nullptr;
    }

    bool removeKey(string key) {
        if (mp.count(key) !=  0) {
            auto it = mp[key];
            l.erase(it);
            mp.erase(key);
            return true;
        }
        return false;
    }

    bool containsKey(string key) {
        return mp.count(key) !=  0;
    }

    int getSize() {
        return l.size();
    }

    string mostRecentKey() {
        if (!l.empty()) {
            return l.front()->key;
        }
        return ""; 
    }
};

// test
int main() {
    LRUcache lru(3);
    lru.insertKeyVal("item1",  1);
    lru.insertKeyVal("item2",  2);
    lru.insertKeyVal("item3",  3);

    int* val = lru.getVal("item1");
    if (val) {
        cout << "Value of item1: " << *val << endl;
    } else {
        cout << "item1 not found in cache." << endl;
    }

    bool removed = lru.removeKey("item1");
    cout << "Removed item1: " << (removed ? "Yes" : "No") << endl;

    bool contains = lru.containsKey("item1");
    cout << "Cache contains item1: " << (contains ? "Yes" : "No") << endl;

    cout << "Cache size: " << lru.getSize() << endl;

    cout << "Most recent key: " << lru.mostRecentKey() << endl;

    return  0;
}
