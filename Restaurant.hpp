#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <vector>
#include <memory>
#include "Table.hpp"
#include "Customer.hpp"


class Restaurant {
private:
    std::vector<std::unique_ptr<Table>> tables;
    std::vector<std::weak_ptr<Customer>> waitlist;

public:

};

#endif
