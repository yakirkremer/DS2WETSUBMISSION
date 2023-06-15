#include "unionfind2.h"



unionfind2::unionfind2(int* input,int input_size):group_counter(0),elements(new Disk_Node*[input_size]),groups(new Group*[input_size]),number_of_records(input_size)
{
    for(int i=0;i<input_size;i++)
    {
        elements[i] = new Disk_Node(i,input[i]);
        groups[i] = new Group(elements[i],i);
        groups[i]->height = elements[i]->cd_amount;
        elements[i]->AddGroup(groups[i]);
        group_counter++;
    }
    size = group_counter;
}

Group* unionfind2::Find(int a)
{
    int sumR = 0;
    Disk_Node* root = elements[a];
    int rowCounter = 0;
    while(root->up!=nullptr)
    {
        root = root->up;
        rowCounter+= root->r;
    }

    Disk_Node* tmp = elements[a];
    Disk_Node* tmpUp = root->up;
    while(tmpUp!=nullptr)
    {
        int cur_row = tmp->r;
        tmp->r += cur_row;
        rowCounter -= cur_row;
        tmp->up = nullptr;
        tmp->group = root->group;
        root = root->up;
        tmpUp = root->up;
    }


    return root->group;
}

void unionfind2::swapGroups(Group* g1 , Group* g2) {
    int tmpCol = g1->column;
    g1->column = g2->column;
    g2->column = tmpCol;
}
Group* unionfind2::unionGroups(int b,int a)
{
    if(Connected(a,b))
    {
        throw sameGroup();
    }
    Group* A = Find(a);   //g_1 = A
    Group* B = Find(b);   //g_2 = B
    B->head->r+=A->height;
    B->head->up = A->head;
    A->size+=B->size;
    A->height+=B->height;
    B->head->group = NULL;
    /*
    if(A->size < B->size)
        swapGroups(A,B);
        A->head->up = B->head;
        B->head->r += A->height;

        B->size += A->size;
        B->group_id = ++group_counter;
        B->height += A->height;
        //A->head->r = A->head->r - B->head->r;
        A->head->group = nullptr;


        return B;

    B->head->up = A->head;
    A->size += B->size;
    A->group_id = ++group_counter;
    B->head->r = B->head->r + A->height - A->head->r;
    B->head->group = nullptr;
    return A;
     */
}

bool unionfind2::Connected(int a,int b)
{
    return Find(a) == Find(b);
}

void unionfind2::getPlace(int r_id,int* column,int* height)
{
    Group* temp = Find(r_id);
    *column = temp->column;
    *height = 0;
    Disk_Node* root = elements[r_id];
    while(root!=nullptr)
    {
        *height += root->r;
        root = root->up;
    }
}