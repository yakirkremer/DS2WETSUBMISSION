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

    void fixPrizesRotationRight(Node* cur){
        Node* A = cur;
        Node* B = cur->left;
        Node * C =B->right;
        int x1,x2;
        int x3 = 0;
        x1 = dynamic_cast<MemberNode*>(A)->getPrizes();
        x2 = dynamic_cast<MemberNode*>(B)->getPrizes();
        if(C!= nullptr)
            x3 = dynamic_cast<MemberNode*>(C)->getPrizes();

        dynamic_cast<MemberNode*>(A)->setPrizes(-x2);
        dynamic_cast<MemberNode*>(B)->setPrizes(x1+x2);
        if(C!= nullptr)
            dynamic_cast<MemberNode*>(C)->setPrizes(x2+x3);

    }

    void fixPrizesRotationLeft(Node* cur){
        Node* A = cur;
        Node* B = cur->right;
        Node * C =B->left;
        int x1,x2;
        int x3 = 0;
        x1 = dynamic_cast<MemberNode*>(A)->getPrizes();
        x2 = dynamic_cast<MemberNode*>(B)->getPrizes();
        if(C!= nullptr)
            x3 = dynamic_cast<MemberNode*>(C)->getPrizes();

        dynamic_cast<MemberNode*>(A)->setPrizes(-x2);
        dynamic_cast<MemberNode*>(B)->setPrizes(x1+x2);
        if(C!= nullptr)
            dynamic_cast<MemberNode*>(C)->setPrizes(x2+x3);

    }

    virtual Node* rotateLL(Node *cur){
        fixPrizesRotationRight(cur);
        Node* A = cur;
        Node* B = cur->left;
        A->setLeft(B->right);
        B->setRight(A);
        A->updateHeight();
        B->updateHeight();
        return B;
    }
    virtual Node* rotateRR(Node *cur){
        fixPrizesRotationLeft(cur);
        Node* A = cur;
        Node* B = cur->right;
        A->setRight(B->left);
        B->setLeft(A);
        A->updateHeight();
        B->updateHeight();
        return B;
    }

    Node* nextSon(Node* cur, int Id){
        if(getKey(cur) >= Id)
            return cur->left;
        return cur->right;
    }

    int calculatePrizes(Node * cur,int Id){



        if(cur == NULL)
            return 0;
        if(cur->getId() == Id)
            return dynamic_cast<MemberNode*>(cur)->getPrizes();
        if(cur->getId() < Id){
            return calculatePrizes(cur->right,Id) +dynamic_cast<MemberNode*>(cur)->getPrizes();
        }
        if(cur->getId() > Id){
            return calculatePrizes(cur->left,Id) +dynamic_cast<MemberNode*>(cur)->getPrizes();
        }



        return calculatePrizes(nextSon(cur,Id),Id) + dynamic_cast<MemberNode*>(cur)->getPrizes();

    }



/*
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
    }*/
  /*  void addPrizes(int lastId,Node* cur, double prizes = 1){
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
*/
    void addPrizeRight(int last, Node*cur, double prizes){
        if(cur == NULL)
            return;

        if(cur->getId() >= last){
            dynamic_cast<MemberNode*>(cur)->increasePrizes(-prizes);
            addPrizesNew(last,cur->left,prizes);
        }

        if(cur-> getId() < last){
            addPrizeRight(last,cur->right,prizes);
        }

    }

    void addPrizesNew(int last, Node*cur, double prizes){
        if(cur == NULL)
            return;
        if(cur-> getId() < last){
            dynamic_cast<MemberNode*>(cur)->increasePrizes(prizes);
            addPrizeRight(last,cur->right,prizes);
        }
        if(cur->getId() >= last){
            addPrizesNew(last,cur->left,prizes);
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

        //addPrizes(max,head,amount);
        //addPrizes(min,head,-amount);
        addPrizesNew(max,head,amount);
        addPrizesNew(min,head,-amount);

    }

    void resetPrizes(){
        resetPrizes(dynamic_cast<MemberNode*>(head));
    }

    void resetPrizes(MemberNode* cur){
        if(cur == NULL)
            return;
        resetPrizes(dynamic_cast<MemberNode*>(cur->right));
        resetPrizes(dynamic_cast<MemberNode*>(cur->left));
        cur->setPrizes(0);
    }



};

#endif //DS2WET_CUSTOMERSDB_H
