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
    stockList.push_back(Video ("a movie", "DVD", "two day rental", 1999, 1, 2.99, "Comedy"));
    stockList.push_back(RentalItem ("a game", "Game", "one week loan", 1999, 2, 4.99));
    stockList.push_back(RentalItem ("a record", "Record", "two day loan", 1999, 1, 2.99));
    stockList.push_back(Video ("another movie", "DVD", "one week loan", 1999, 2, 3.99, "Drama"));
    
    std::vector<RentalItem> customerStockList;
    std::vector<Customer> customerList;
    customerList.push_back(Customer("Carl", "200 Duong D5", "0903702342", "Guest", customerStockList, 900, 0));
    

    /*for (int i = 0; i < customerList.size(); i++)
        customerList[i].DisplayCustomerInfo();*/

    std::cout << "\nList before renting stuffs (Should be empty.)\n";
    for (int i = 0; i < customerList[0].GetListOfRentedItems().size(); i++)
        customerList[0].GetListOfRentedItems()[i].DisplayItemInfo();

    std::cout << "\nThis is what is in store stock (should be 2)\n";
    stockList[1].DisplayItemInfo();

    customerList[0].RentThisItem(stockList[1]);
    stockList[1].DecreaseStock();

    std::cout << "\nThis is what is in store stock (should be 1)\n";
    stockList[1].DisplayItemInfo();

    std::cout << "\nFirst Game Rented, should be 1 copy\n";
    for (int i = 0; i < customerList[0].GetListOfRentedItems().size(); i++)
        customerList[0].GetListOfRentedItems()[i].DisplayItemInfo();
        
    customerList[0].RentThisItem(stockList[1]);
    stockList[1].DecreaseStock();

    std::cout << "\nThis is what is in store stock (Should be 0)\n";
    stockList[1].DisplayItemInfo();

    std::cout << "\nSecond Game Rented There should now be 2\n";
    for (int i = 0; i < customerList[0].GetListOfRentedItems().size(); i++)
        customerList[0].GetListOfRentedItems()[i].DisplayItemInfo();

    customerList[0].ReturnThisItem(stockList[1]);
    stockList[1].IncreaseStock();
    std::cout << "\nStore Stock after first return, should be 1\n";
    stockList[1].DisplayItemInfo();

    std::cout << "\nFirst Game Returned There should now be 1\n";
    for (int i = 0; i < customerList[0].GetListOfRentedItems().size(); i++)
        customerList[0].GetListOfRentedItems()[i];

    customerList[0].ReturnThisItem(stockList[1]);
    stockList[1].IncreaseStock();
    std::cout << "\nStore Stock after first return, should be 2\n";
    stockList[1].DisplayItemInfo();

    std::cout << "\nFirst Game Returned There should now empty\n";
    for (int i = 0; i < customerList[0].GetListOfRentedItems().size(); i++)
        customerList[0].GetListOfRentedItems()[i];
   

        
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
