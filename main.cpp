//
//  main.cpp
//  ex8_1
//
//  Created by Artemy Pestretsov on 13.04.14.
//  Copyright (c) 2014 Artemy Pestretsov. All rights reserved.
//

#include <iostream>
#include <iterator>

using namespace std;

template<typename T>
class my_comp {
public:
    bool operator()(const T& t1, const T& t2) const {
        return t1 > t2;
    }
};

template<class P, class Compare>
void Sort(P First, P Last, Compare comp)
{
    int Ok;
    P p1,p2;
    int i;
    int n = sizeof(*p1);
    char *temp=new char[n];
    while(1) {
        p1 = p2 = First;
        p2++;
        Ok=1;
        for ( ; p2 != Last; p1++, p2++)
            if(comp(*p1, *p2)) {
                for(i = 0; i < n; i++)
                    temp[i] = ((char*)&*p1)[i];
                *p1 = *p2;
                for(i = 0; i < n; i++)
                    ((char*)&*p2)[i] = temp[i];
                Ok = 0;
            }
        if(Ok) {
            delete[] temp;
            return;
        }
    }
}

template <typename Key, typename Compare>
class set {
    typedef std::size_t size_type;
    struct Node  {
        Node * next;
        Key value;
    };
    Node * head;
    Node * current;
    size_type sz;
public:
    set() { head = nullptr; }
    set(std::initializer_list<Key> il) {
        for (auto it = il.begin(); it != il.end(); it++)
            insert(*it);
    }
    
    class iterator {
    public:
        Node * p;
        iterator() { p = nullptr; }
        iterator(set<Key, Compare> &st) { p = st.head; }
        ~iterator() {}
        Key& operator*(void) { return p->value; }
        bool operator==(iterator it) { return it.p==p; }
        bool operator!=(iterator it) { return it.p!=p; }
        iterator operator=(iterator it) { p = it.p; return *this; }
        iterator operator++(int)
        {
            iterator temp = *this;
            if(p->next != nullptr)
                p = p->next;
            else
                p = nullptr;
            return temp;
        }
        iterator operator++(void)
        {
            iterator temp = *this;
            if(p->next != nullptr)
                p = p->next;
            else
                p = nullptr;
            return temp;
        }
    };
    
    size_type size() { return sz; }
    
    size_type count(const Key& x) { return find(x)!=end(); }

    void insert(const Key& x) {
        Node * new_node = new Node;
        new_node->value = x;
        if (find(x) != end())
            return;
        if (head == nullptr) {
            current = new_node;
            current->next = nullptr;
            head = current;
        }
        else {
            current->next = new_node;
            current = current->next;
            current->next = nullptr;
        }
        Sort(begin(), end(), Compare());
        sz++;
    }
    
    iterator find(const Key& x) {
        for (iterator it = begin(); it != end(); it++)
            if (it.p->value == x)
                return it;
        return end();
    }
    
    void erase(iterator position) {
        auto it = begin();
        if (position == it) {
            auto temp = head->next;
            delete head;
            head = temp;
            sz--;
        }
        if (position.p->next == nullptr) {
            for ( ; it.p->next->next != nullptr; it++) ;
            delete it.p->next;
            it.p->next = nullptr;
            current = it.p;
            sz--;
        }
        else
            for ( ; it != end(); it++)
                if (it.p->next == position.p) {
                    auto temp = position.p->next;
                    delete position.p;
                    it.p->next = temp;
                    sz--;
                    return;
                }
    }
    
    size_type erase(const Key& x) {
        auto it = find(x);
        if (it != end()) {
            erase(it);
            return 1;
        }
        else
            return 0;
    }
    
    bool operator==(set& that) {
        if (sz != that.size())
            return false;
        for (auto it = begin(), at = that.begin(); it != end(); it++, at++)
            if (it.p->value != at.p->value)
                return false;
        return true;
    }
    
    bool operator!=(set& that) { return !operator==(that); }
    
    iterator begin() { return iterator(*this); }
    
    iterator end() { return iterator(); }             //returns nullptr
    
    ~set() {
        Node *curr, *temp;
        if (head) {
            curr = head;
            while (curr) {
                temp = curr->next;
                delete curr;
                curr = temp;
            }
        }
    }
    
    void print() {
        for (iterator it = begin(); it != end(); it++)
            cout << *it << " ";
    }
};

int main(int argc, const char * argv[])
{
    set<int, my_comp<int>> x {4,2,3,4,5};
    x.insert(1);
    x.find(5);
    x.print();
    x.insert(11);
    cout << "\n";
    x.print();
    x.erase(x.begin());
    cout << "\n";
    x.print();
    x.erase(4);
    cout << "\n";
    x.print();
    
    return 0;
}