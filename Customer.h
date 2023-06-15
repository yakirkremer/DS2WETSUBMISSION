//
// Created by yakir on 6/6/2023.
//

#ifndef DS2WET_CUSTOMER_H
#define DS2WET_CUSTOMER_H

#include <exception>
#include <string>

const int MIN_ID = 0;
const int MIN_PHONE = 0;


class InvalidInput:public std::exception{};

class Customer {
int c_id;
int phone;
int expenses;
bool is_member;


public:
    const int& getId()const;
    const int& getPhone()const;
    const bool isMember ()const;
    void makeMember();
    Customer(int Id, int Phone);
    void purchaseRecord(int);
    int getExpenses()const ;
    void resetExpenses();
};


#endif //DS2WET_CUSTOMER_H
