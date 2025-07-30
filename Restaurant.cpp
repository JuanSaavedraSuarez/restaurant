#include "Restaurant.hpp"
#include "Customer.hpp"
#include "removeElement.hpp"

#include <codecvt>
#include <iostream>
#include <memory>

using namespace std;

Restaurant::Restaurant(int initialTableCount) {
    for (int i = 0; i < initialTableCount; i++) {
        tables.push_back(std::make_unique<Table>(i));
    }
}

bool Restaurant::reserveTable(std::shared_ptr<Customer>& customer) {
    for (std::unique_ptr<Table>& table : tables) {
        if ((*table).getIsAvailable()) {
            (*table).reserve();
            activeCustomers.push_back((customer));
            return true;
        }
    }
    waitlist.push_back(customer);
    return false;
}

void Restaurant::printWaitlist() {
    std::cout << "The following people are waiting for a table:" << std::endl;

}