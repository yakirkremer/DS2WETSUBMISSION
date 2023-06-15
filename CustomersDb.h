//
// Created by yakir on 6/6/2023.
//

#ifndef DS2WET_CUSTOMERSDB_H
#define DS2WET_CUSTOMERSDB_H

#include "Customer.h"
#include "HashTable.h"

//typedef Customer T;




class CustomersDb: public HashTable<Customer*,int, CustomersList*>{

public:
CustomersDb(): HashTable<Customer *, int, CustomersList*>(2){}
void resetExpenses() {
    for (int i = 0; i <m ; ++i) {
        if(data[i]!= NULL)
            data[i]->resetExpenses();
    }
}

};


#include "AvlTreeNew.h"
class ClubMembers:public AvlTreeNew<Customer*, int>{

    class MemberNode:public Node{
        int prizes;
    public:
        MemberNode(Customer* newData, int Id): Node(newData,Id),prizes(0){}
        const int getPrizes()const{
            return prizes;
        }
        void setPrizes(double amount){
            prizes = amount;
        }
        void increasePrizes(double prizesAmount){prizes += prizesAmount;}
    };

    virtual Node* rotateLL(Node *cur){
        //return cur;
        Node* A = cur;
        Node* B = cur->left;
        int Bprizes = dynamic_cast<MemberNode*>(B)->getPrizes();
        int Aprizes = dynamic_cast<MemberNode*>(A)->getPrizes();

        int x1 = dynamic_cast<MemberNode*>(A)->getPrizes();
        int  x2 = dynamic_cast<MemberNode*>(B)->getPrizes();
        if(B->right != NULL){
            dynamic_cast<MemberNode*>(B->right)->increasePrizes(x2);
        }
        A->setLeft(B->right);
        B->setRight(A);


       /* if(A->left != NULL){
            int Cprizes =dynamic_cast<MemberNode*>(A->right)->getPrizes();
            dynamic_cast<MemberNode*>(A->left)->increasePrizes(Bprizes);
        }*/


        dynamic_cast<MemberNode*>(B)->setPrizes(x1+x2);
        dynamic_cast<MemberNode*>(A)->setPrizes(-x2);

        /*
        if(A->left != NULL)
        {
            dynamic_cast<MemberNode *>(A->left)->increasePrizes(-Aprizes);
        }
        */
        A->updateHeight();
        B->updateHeight();

        return B;
    }
    virtual Node* rotateRR(Node *cur){

        Node* A = cur;
        Node* B = cur->right;

        int Bprizes = dynamic_cast<MemberNode*>(B)->getPrizes();
        int Aprizes = dynamic_cast<MemberNode*>(A)->getPrizes();
        int x1 = dynamic_cast<MemberNode*>(A)->getPrizes();
       int  x2 = dynamic_cast<MemberNode*>(B)->getPrizes();
       if(B->left != NULL){
           dynamic_cast<MemberNode*>(B->left)->increasePrizes(x2);
       }
        A->setRight(B->left);
        B->setLeft(A);

        dynamic_cast<MemberNode*>(A)->setPrizes(-x2);
        dynamic_cast<MemberNode*>(B)->increasePrizes(x1+x2);

        A->updateHeight();
        B->updateHeight();
        return B;
    }

    virtual Node* rotateLR(Node *cur) {
        Node* B = cur->left;
        Node * C =B->right;
        int x1,x2,x3;
        x1 = dynamic_cast<MemberNode*>(cur)->getPrizes();
        x2 = dynamic_cast<MemberNode*>(B)->getPrizes();
        x3 = dynamic_cast<MemberNode*>(C)->getPrizes();
        cur->setLeft(rotateRR(cur->left))  ;
        //dynamic_cast<MemberNode*>(cur->left)->increasePrizes()

        Node * res = rotateLL(cur);
        dynamic_cast<MemberNode*>(cur)->setPrizes(-x2 -x3);
        dynamic_cast<MemberNode*>(B)->setPrizes(x1+x2-x3);
        dynamic_cast<MemberNode*>(C)->setPrizes(x1+x2+x3);
        return res;
    }
    virtual  Node* rotateRL(Node *cur) {
        Node* B = cur->right;
        Node * C =B->left;
        int x1,x2,x3;
        x1 = dynamic_cast<MemberNode*>(cur)->getPrizes();
        x2 = dynamic_cast<MemberNode*>(B)->getPrizes();
        x3 = dynamic_cast<MemberNode*>(C)->getPrizes();
        cur->setRight(rotateLL(cur->right));

        Node* res =  rotateRR(cur);
        dynamic_cast<MemberNode*>(cur)->setPrizes(-x2 -x3);
        dynamic_cast<MemberNode*>(B)->setPrizes(x1+x2-x3);
        dynamic_cast<MemberNode*>(C)->setPrizes(x1+x2+x3);
        return res;
    }

    Node* nextSon(Node* cur, int Id){
        if(getKey(cur) >= Id)
            return cur->left;
        return cur->right;
    }

    int calculatePrizes(Node * cur,int Id){
        if(cur == NULL)
            return 0;
        if(getKey(cur) == Id)
            return dynamic_cast<MemberNode*>(cur)->getPrizes();
        return calculatePrizes(nextSon(cur,Id),Id) + dynamic_cast<MemberNode*>(cur)->getPrizes();

    }

    void fixPrizes(int lastId,Node* cur, double prizes){
        if(cur == NULL)
            return;

        if(lastId < getKey(cur))
        {
            dynamic_cast<MemberNode *>(cur)->increasePrizes(prizes*(-1));
            if(cur->left != NULL){
                if(getKey(cur->left)<lastId)
                    return addPrizes(lastId,cur,prizes);
                //dynamic_cast<MemberNode *>(cur->left)->increasePrizes(prizes);
            }
        }
        if(lastId > getKey(cur))
            return fixPrizes(lastId,cur->right,prizes);
    }
    void addPrizes(int lastId,Node* cur, double prizes = 1){
        if(cur == NULL)
            return;
        if(lastId > getKey(cur)) {
            dynamic_cast<MemberNode *>(cur)->increasePrizes(prizes);
            return fixPrizes(lastId,cur->right,prizes);
        }
        else{
            return addPrizes(lastId,cur->left,prizes);
        }
    }
    const int& getKey(Node* cur)const override{
        if(cur == NULL)
            throw NoNodeExist();
        return cur->getId();
        //return cur->data->getId();
    }

    void deleteDatas(Node *cur) {
        if (cur == NULL)
            return;
        deleteDatas(cur->right);
        deleteDatas(cur->left);
        delete cur->data;
        cur->data = NULL;
        return;
    }

    void deleteNode(Node * cur){
        cur->right = NULL;
        cur->left = NULL;
        //delete cur->data;
        delete cur;
    }



public:
    ~ClubMembers(){
        deleteDatas(head);
    }

    ClubMembers():AvlTreeNew<Customer *, int>(){

    }

    Customer* popRoot(){
        if(head == NULL)
            return NULL;
        Customer * tmpHead = head->data;
        remove(head->getId());
        return tmpHead;
    }

    int getPrizes(int Id) {
        try {
            //return calculatePrizes(head, Id);
            return getPrizeNew(head,Id);
        }
        catch (NoNodeExist){
            return 0;
        }
    }

    int getPrizeNew(Node* cur, int id){
        int res = 0;
        while(cur != nullptr){
            res+=dynamic_cast<MemberNode*>(cur)->getPrizes();
            if(cur->getId() == id){
                return res;
            }
            if(id > cur->getId()){
                cur =cur->right;
            }
            else{
                cur = cur->left;
            }
        }
        return res;
    }

    virtual void add(Customer *newData, const int& Id) override{
        int prizesFix = getPrizes(Id);
        try {

            MemberNode* newNode = new MemberNode(newData, Id);
            newNode->increasePrizes(prizesFix * (-1));
            head = addNode(head, newNode);

            size++;
        }
        catch (std::bad_alloc){
            throw std::bad_alloc();
        }


    }

    void addPrizes(int min, int max,double amount){
        if(amount<= 0 || max < min || min < 0)
            throw InvalidInput();

        addPrizes(max,head,amount);
        addPrizes(min,head,-amount);

    }



};

#endif //DS2WET_CUSTOMERSDB_H
