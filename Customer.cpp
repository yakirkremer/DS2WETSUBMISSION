//
// Created by yakir on 6/6/2023.
//

#include "Customer.h"


Customer::Customer(int Id, int Phone):c_id(Id),phone(Phone),is_member(false),expenses(0) {
    if(c_id < 0 || phone < 0)
        throw InvalidInput();
}

void Customer::makeMember() {is_member = true;}

const int& Customer::getId()const {return c_id;}

const int &Customer::getPhone() const {
    return phone;
}

const bool Customer::isMember()const {
    return is_member;
}

void Customer::purchaseRecord(int purchases) {
    if(c_id == 69)
        int s = 5;
    if(isMember())
        expenses += purchases +100;
}

int Customer::getExpenses() const {
    return expenses;
}

void Customer::resetExpenses() {
    expenses = 0;
}



