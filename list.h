#ifndef HW4_1_LIST_H
#define HW4_1_LIST_H

#include <stdlib.h>
#include <iostream>

template <class T>
class List{
    Node head;
    const Node tail = NULL;
    iterator iterator;
    int num_of_elements = 0;
    class Iterator{
        Node node;
    public:
        Iterator(Node node)= default;
        Iterator(const iterator& iterator)= default;
        Iterator& operator=(const iterator& iterator)= default;
    };
    class Node{
        T data;
        Node *next;
        Node *prev;
    public:
        Node(const T& d = T(),Node *n = NULL,Node *p = NULL):
                data(new T[]),next(n),prev(p){}
        Node(const Node& node)= default;
        ~Node()= default;
        Node& operator=(Node node){
            this->next=node.next;
            this->prev=node.prev;
            this->data=node.data;
        }
        bool operator==(Node node){
            return this->data==node.data && this->prev==node.prev && this->next==node.next;
        }
        bool operator!=(Node node){
            return !(this->data==node.data && this->prev==node.prev && this->next==node.next);
        }
        Node& operator++(){
            this = this->next;
            return *this;
        }
        Node operator++(int){
            Node node = this;
            this = this->next;
            return node;
        }
        Node& operator--(){
            this = this->data;
            return *this;
        }
        Node operator--(int){
            Node node = this;
            this = this->prev;
            return node;
        }
        T& operator*(){
            return this->data;
        }
    };
public:
    void begin(){
        if(this->num_of_elements == 0) this->iterator = this->tail;
        this->iterator = this->head;
    }
    void end(){
        this->iterator = this->tail;
    }
    void insert(const T& data,Iterator<T> iterator){
        if(iterator == this->tail) insert(T);

    }

};

#endif //HW4_1_LIST_H
