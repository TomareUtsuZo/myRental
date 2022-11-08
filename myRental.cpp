// myRental.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "RentalItem.h"
#include "Shop.h"
#include "Customer.h"

int RentalItem::s_numberOfItemsAdded{ 0 }; // start counting number of items created
int Customer::s_numberOfCustomersServiced{ 0 }; // start counting number of customers serviced



int main()
{
    std::vector<RentalItem> stockList;
    
    std::vector<RentalItem> customerStockList;
    std::vector<Customer> customerList;
    customerList.push_back(Customer("Carl", "200 Duong D5", "0903702342", "Guest", customerStockList, 900, 0));
    
    Shop shopOne = Shop(stockList, customerList);
    shopOne.AddNewItemToStockList();
   

        
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
