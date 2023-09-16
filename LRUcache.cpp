#include <unordered_map>
using namespace std;
class LRUCache {
    struct Node{
        Node* pre = nullptr;
        Node* next = nullptr;
        int key;
        int val;
        Node(int k, int v):val(v), key(k){}
        Node():val(-1),key(-1){}
    };
    unordered_map<int,Node*> hash;
    Node *head, *tail;
    int capacity;
public:
    LRUCache(int capacity):head(new Node()), tail(new Node()), capacity(capacity) {
        head->next = tail;
        tail->pre = head;
    }
    
    int get(int key) {
        if(hash.find(key) == hash.end()) return -1;
        int val = hash[key]->val;
        moveToHead(hash[key]);
        return val;
    }
    void removeBack(){
        if(capacity <= 0) return;
        Node* node = tail->pre;
        int key = node->key;
        //remove from list
        node->pre->next = tail;
        tail->pre = node->pre;
        //remove from hash
        hash.erase(hash.find(key));
    }
    void moveToHead(Node* node){
        node->pre->next = node->next;
        node->next->pre = node->pre;
        addTohead(node);
    }
    void addTohead(Node* node){
        node->next = head->next;
        node->pre = head;
        head->next->pre = node;
        head->next = node;
    }
    void put(int key, int value) {
        if(hash.find(key) == hash.end()){
            Node* node = new Node(key, value);
            if(hash.size() == capacity){
                removeBack();
            }
            addTohead(node);
            hash[key] = node;
        }
        else{
            hash[key]->val = value;
            moveToHead(hash[key]);
        }
    }
};