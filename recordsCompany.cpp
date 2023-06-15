#include "recordsCompany.h"

RecordsCompany::RecordsCompany(){
    customers = new CustomersDb();
    members = new ClubMembers();
    records = NULL;
}

RecordsCompany::~RecordsCompany(){
    delete records;
    delete customers;
    delete members;
}

StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records)
{
    try
    {
        //Records *tmp = new Records(number_of_records);
    /*    for (int i = 0; i < number_of_records; ++i) {
            tmp->add(new Record(i, records_stocks[i]), i, i);
        }*/
        unionfind2* tmp = new unionfind2(records_stocks, number_of_records);
        customers->resetExpenses();

        delete records;
        records = tmp;
        return SUCCESS;
    }
    catch (bad_alloc&){
        return ALLOCATION_ERROR;
    }
    /*
    //free old data
    disks = new UnionFind(records_stocks,number_of_records);
    costumers = new HashTable();
    vip_costumers = new AVLTree<VipCostumer>();
    return SUCCESS;
    */
}

StatusType RecordsCompany::addCostumer(int c_id, int phone)
{

    try {
        Customer * customer = new Customer(c_id, phone);
        customers->add(customer);
        return SUCCESS;
    }
    catch(bad_alloc&){
        return ALLOCATION_ERROR;
    }

    catch(InvalidInput&){
        return INVALID_INPUT;
    }
    catch(alreadyExists&){
        return ALREADY_EXISTS;
    }
}

Output_t<int> RecordsCompany::getPhone(int c_id)
{
    if(!validId(c_id) )
        return INVALID_INPUT;

    try
    {
        Customer *tmp = customers->find(c_id);
        return tmp->getPhone();
    }
    catch(NoNodeExist&){
        return DOESNT_EXISTS;
    }
}

StatusType RecordsCompany::makeMember(int c_id)
{
    if(!validId(c_id))
        return INVALID_INPUT;
    try{
        Customer* customer = customers->find(c_id);
        customer->makeMember();
        members->add(customer,c_id);
        return SUCCESS;
    }
    catch(NoNodeExist&){
        return DOESNT_EXISTS;
    }
    catch(alreadyExists&){
        return ALREADY_EXISTS;
    }
    catch (bad_alloc&){
        return ALLOCATION_ERROR;
    }
}

Output_t<bool> RecordsCompany::isMember(int c_id)
{
    if(!validId(c_id))
        return INVALID_INPUT;

    try{
        Customer* customer = customers->find(c_id);
        return customer->isMember();
    }
    catch (NoNodeExist)
    {
        return DOESNT_EXISTS;
    }
}

StatusType RecordsCompany::buyRecord(int c_id, int r_id)
{
    if(c_id == 69)
        int s = 5;
    if(!validId(c_id) || !validId(r_id))
        return INVALID_INPUT;
    if(r_id >= records->getSize() )
        return DOESNT_EXISTS;


    try
    {
        //Record* record = records->getData(r_id);
        int purchases = records->getPurchases(r_id);
        Customer* customer = customers->find(c_id);
       // customer->purchaseRecord(record->getPurchases());
        customer->purchaseRecord(purchases);

        //record->addPurchase();
        records->addPurchases(r_id);
        return SUCCESS;
    }
    catch (NoNodeExist){
        return DOESNT_EXISTS;
    }

}

StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double  amount)
{
    try{
        members->addPrizes(c_id1,c_id2,amount);
        return SUCCESS;
    }
    catch (InvalidInput){
        return INVALID_INPUT;
    }
}

Output_t<double> RecordsCompany::getExpenses(int c_id)
{
    if(c_id == 69)
        int s = 5;
    if(!validId(c_id))
        return INVALID_INPUT;
    try {
        double  res = 0;
        Customer* customer = members->getData(c_id);
            return customer->getExpenses() -  members->getPrizes(c_id);
    }
    catch (NoNodeExist)
    {
        return DOESNT_EXISTS;
    }
}

StatusType RecordsCompany::putOnTop(int r_id1, int r_id2)
{
    if(r_id1 < 0 || r_id2 < 0 )
        return INVALID_INPUT;
    if(r_id1 >= records->getSize() || r_id2 >= records->getSize())
        return DOESNT_EXISTS;
    try{
        records->unionGroups(r_id1, r_id2);
        return SUCCESS;
    }
    catch(SameGroupAlready){
        return FAILURE;
    }
    catch(sameGroup){
        return FAILURE;
    }
    catch(NoNode){
        return DOESNT_EXISTS;
    }
}

StatusType RecordsCompany::getPlace(int r_id, int *column, int *hight)
{
    if(r_id < 0 || hight == NULL || column == NULL)
        return INVALID_INPUT;
    if(r_id >= records->getSize())
        return DOESNT_EXISTS;


    try{
        /*
        *hight = 0;
        *column = 0;
        *column = records->find(r_id);
        *hight = records->getHeight(r_id);*/
        records->getPlace(r_id,column,hight);
        return SUCCESS;

    }
    catch (NoNode){
        return DOESNT_EXISTS;
    }
    /*
    disks->getPlace(r_id,column,hight);
    return SUCCESS;
     */
}


