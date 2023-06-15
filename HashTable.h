//
// Created by yakir on 6/7/2023.
//

#ifndef DS2WET_HASHTABLE_H
#define DS2WET_HASHTABLE_H
const double TABLE_SIZE = 1.3;

#include "CustomersTree.h"
#include "RecordsComapnyExceptions.h"
#define  TEMPLATE template<class T, class K, class tree>


TEMPLATE
class HashTable{
protected:
    int calculateNextTableSize()const;
    tree* data;
    int n;
    int m;
    int resizeFactor;
    void resize();
    int hash(int key);
    int nextm;
    bool isExist(int key);
public:
    HashTable(int = 2);
    virtual ~HashTable();
    void add(T newData);
    void remove(T newData);
    void printTable()const;
    void initArr();
    T find(int key);

};

TEMPLATE
T HashTable<T, K, tree>::find(int key) {
    if(data[hash(key)] == NULL)
        throw NoNodeExist();
        return data[hash(key)]->getData(key);
}
TEMPLATE
HashTable<T,K,tree>::HashTable(int resizeFactor):m(2),n(0),nextm(m*2), resizeFactor(resizeFactor) {
    try {
        data = new tree [m];
        for (int i = 0; i < m; ++i) {
            data[i] = NULL;
        }
    }
    catch (std::bad_alloc){
        throw std::bad_alloc();
    }
}
TEMPLATE
void HashTable<T, K, tree>::initArr() {
    data = new tree[m];
    for (int i = 0; i < m; ++i) {
        data[i] = new CustomersList();
    }
}
TEMPLATE
void HashTable<T,K,tree>::resize() {
    T* tmpDatas = new T[n];
    T tmp;
    int j = 0, oldSize = n;
    //n= 0;
    for (int i = 0; i < oldSize; ++i) {
        tmp = data[j]->popRoot();
        while(tmp == NULL){
            j++;
            tmp = data[j]->popRoot();
        }
        tmpDatas[i] = tmp;

    }
    m*= resizeFactor;
    delete [] data;
    initArr();
    for (int i = 0; i < oldSize; ++i) {
        data[hash(tmpDatas[i]->getId())]->add(tmpDatas[i],tmpDatas[i]->getId());
    }
    return;

}
TEMPLATE
int HashTable<T,K,tree>::hash(int key) {
    return (key% m);
}
TEMPLATE
bool HashTable<T,K,tree>::isExist(int key){
    //if(key>=m)
        //throw notExist();


        int hashKey = hash(key);
        tree cur = data[hashKey];
        try{
             cur->getData(key);
            return true;

        }
        catch (NoNodeExist){
            return false;

        }


}
/*
TEMPLATE
void HashTable<T,K,tree>::remove(T newData){
    try{

        int hashKey = hash((newData->getId()));
        tree cur = data[hashKey];
        tree tmp;
        cur->remove(newData->getId());
        n--;
        if (n >= m*5)
            resize();
    }
    catch (notExist){
        throw notExist();
    }
}
 */
TEMPLATE
void HashTable<T,K,tree>::add(T newData){

    int hashKey = hash((newData->getId()));

    if(data[hashKey] == NULL)
        data[hashKey] = new CustomersList();
    tree cur= data[hashKey];
    if(isExist((newData)->getId())) { throw alreadyExists(); }

        data[hashKey]->add(newData,newData->getId());
        n++;
        if (n >= m*5)
            resize();

}
TEMPLATE
HashTable<T,K,tree>::~HashTable(){
}




#endif //DS2WET_HASHTABLE_H
