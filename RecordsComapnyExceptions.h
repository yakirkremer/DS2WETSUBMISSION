//
// Created by yakir on 6/7/2023.
//

#ifndef DS2WET_RECORDSCOMAPNYEXCEPTIONS_H
#define DS2WET_RECORDSCOMAPNYEXCEPTIONS_H

class invalidId:public std::exception{};
class notExist:public std::exception{};
class alreadyExist:public std::exception{};

#endif //DS2WET_RECORDSCOMAPNYEXCEPTIONS_H
