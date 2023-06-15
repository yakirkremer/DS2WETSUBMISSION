#ifndef _UNION_FIND
#define _UNION_FIND

#include "Disk_Node.h"
#include "Group.h"
#include <exception>
class sameGroup:public std::exception{};
class NoNode:public std::exception{};
class SameGroupAlready:public std::exception{};

class unionfind2
{
private:
    int size;

public:
    int group_counter;
    Disk_Node** elements;
    Group** groups;
    int number_of_records;
    int getSize()const{
        return size;
    }
    int getPurchases(int id)const{
        Disk_Node* record = elements[id];
        return record->sells;
    }
    void addPurchases(int id){
        Disk_Node* record = elements[id];
        record->sells++;
    }
    unionfind2(int* input,int input_size);
    ~unionfind2(){delete[] elements;delete[] groups;}
    Group* Find(int a);
    Group* unionGroups(int b,int a);   // putting b on a
    bool Connected(int a,int b);
    void getPlace(int r_id,int* column,int* height);
    void swapGroups(Group*, Group*);
};

#endif