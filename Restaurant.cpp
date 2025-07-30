#include "Restaurant.hpp"
#include "Customer.hpp"
#include "removeElement.hpp"

#include <codecvt>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

Restaurant::Restaurant(int initialTableCount) {
    for (int i = 0; i < initialTableCount; i++) {
        tables.push_back(make_unique<Table>(i));
    }
}

bool Restaurant::reserveTable(shared_ptr<Customer>& customer) {
    for (unique_ptr<Table>& table : tables) {
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
    cout << "The following people are waiting for a table:" << endl;
    for (weak_ptr<Customer>& customer : waitlist) {
        shared_ptr<Customer> customerPtr;
        customerPtr = customer.lock();
        cout << (*customerPtr).getName() << endl;
    }
}

void Restaurant::releaseTable(int tableNumber) {
    for (unique_ptr<Table>& table : tables) {
        if ((*table).getNumber() == tableNumber)
            if (!(*table).getIsAvailable()) {
                (*table).release();
                notifyWaitlist();
            }
    }

}

void Restaurant::notifyWaitlist() {
    if (waitlist.empty())
        return;

    shared_ptr<Customer> customer;
    if ((customer = waitlist.front().lock())) {
        reserveTable(customer);
        cout << "Reserved table for " << customer->getName() << endl;
        removeElement(waitlist, customer);
    }
    else {
        cout << "Unable to lock weak pointer to shared pointer" << endl;
    }

}