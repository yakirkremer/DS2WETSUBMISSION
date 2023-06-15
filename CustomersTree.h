//
// Created by yakir on 5/15/2023.
//

#ifndef DSWET1NOSHARED_USERSTREE_H
#define DSWET1NOSHARED_USERSTREE_H

#include "Customer.h"
#include "AvlTreeNew.h"
using namespace std;
#include <stdexcept>

class CustomersList{
    struct Node{
        Customer* data;
        Node* next;
        int key;

        Node(Customer* data, int key):data(data),next(NULL),key(key){}
        ~Node(){

        }
    };
    Node* head;
public:

    CustomersList():head(NULL){}
    Customer* popRoot(){
        Node* tmp = head;
        if(head == NULL)
            return NULL;
        Customer* res = head->data;
        if(head != NULL)
            head = head->next;
        delete tmp;
        return res;
    }

    void resetExpenses(){
        Node* cur = head;
        while(cur != NULL){
            cur->data->resetExpenses();
            cur = cur->next;
        }
    }

    void add(Customer* data, int key){
        Node* tmp = new Node(data, key);
        if(head == NULL) {
            head = tmp;
            return;
        }
        tmp->next = head;
        head = tmp;
    }
    void print(){
        Node * cur = head;
        cout<<"{ ";
        while(cur!= NULL){
            cout<<cur->data->getId()<<", ";
            cur = cur->next;
        }
        cout<<" }\n";
    }


    Customer* getData(int key){
        Node* cur = head;
        if(cur == NULL)
            throw NoNodeExist();
        while(cur->key != key){
            cur = cur->next;
            if(cur == NULL)
                throw NoNodeExist();
        }
        return cur->data;
    }
    ~CustomersList() {

    }
};


#endif //DSWET1NOSHARED_USERSTREE_H
