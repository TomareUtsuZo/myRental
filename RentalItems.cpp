#include "RentalItems.h"
#include <fmt/format.h>	
#include <string>
#include <iostream>


// Constructors
RentalItems::RentalItems(std::string newTitle, std::string newRentalType, 
	std::string newLoanType, int newYearPublished, int initialCopiesInStock, 
	double newRentalFee) : title(newTitle), rentalType(newRentalType), 	
	loanType(newLoanType), yearPublished(newYearPublished), copiesInStock(initialCopiesInStock),
	rentalFee(newRentalFee) {
	SetID(s_numberOfItemsAdded++, newYearPublished);
}


// Internal Methods
void RentalItems::SetIsAvailableForRent() {
	if (GetCopiesInStock() < 0) {
		isAvailableForRent = true;
	} // if (isAvailableForRent < 0) {
	else { //if (isAvailableForRent < 0) {
		isAvailableForRent = false;
	} // else { //if (isAvailableForRent < 0) {	
} // void SetIsAvailableForRent() {

// Setters and Getters
std::string RentalItems::GetID() { return id; }
void RentalItems::SetID(int numberOfItemsAdded, int yearPublished) {
	id = fmt::format("I{:0>3}{}", numberOfItemsAdded, yearPublished);
} // std::string RentalItems::SetID(int numberOfItemsAdded) {

std::string RentalItems::GetTitle() { return title; }
void RentalItems::SetTitle(std::string newTitle) { title = newTitle; }

std::string RentalItems::GetRentalType() { return rentalType; }
bool RentalItems::SetRentalType(std::string newRentalType) {
	bool thisIsPassed = std::find(availableRentalTypes.begin(), availableRentalTypes.end(), newRentalType) != availableRentalTypes.end();
	if (thisIsPassed == true)
		rentalType = newRentalType;
	return thisIsPassed;
} // bool RentalItems::SetRentalType(std::string newRentalType) {

std::string RentalItems::GetLoanType() { return loanType; }
bool RentalItems::SetLoanType(std::string newLoanType) { 
	bool thisIsPassed = std::find(availableLoanTypes.begin(), availableLoanTypes.end(), newLoanType) != availableLoanTypes.end();
	if (thisIsPassed == true)
		loanType = newLoanType; 
	return thisIsPassed;
} // bool RentalItems::SetRentalType(std::string newRentalType) {

int RentalItems::GetCopiesInStock() { return copiesInStock; }
void RentalItems::SetCopiesInStock(int newCopiesInStock) { copiesInStock = newCopiesInStock; }

double RentalItems::GetRentalFee() { return rentalFee; }
void RentalItems::SetRentalFee(double newRentalFee) { rentalFee = newRentalFee; }

bool RentalItems::GetIsAvailableForRent() { return isAvailableForRent; }

// Public interfaces
void RentalItems::IncreaseStock(int numberOfNewCopies) {
	SetCopiesInStock(GetCopiesInStock() + numberOfNewCopies);
} // void RentalItems::IncreaseStock(int numberOfNewCopies) {

bool RentalItems::DecreaseStock(int numberOfRemovedCopies) {
	bool thisGotDone = false;
	if (numberOfRemovedCopies <= GetCopiesInStock()) {
		SetCopiesInStock(GetCopiesInStock() - numberOfRemovedCopies);
		thisGotDone = true;
	} // if (numberOfRemovedCopies = < GetCopiesInStock()) {
	return thisGotDone;
} // bool RentalItems::DecreaseStock(int numberOfRemovedCopies) {

bool RentalItems::RentFromStock(int copiesRented) {
	bool thisGotDone = false;
	if (DecreaseStock(copiesRented)) {
		thisGotDone = true;
	}
	return thisGotDone;
} // bool RentalItems::RentFromStock(int copiesToRent) {

void RentalItems::ReturnToStock(int copiesReturned) {
	IncreaseStock(copiesReturned);
} // void RentalItems::ReturnToStock() {

void RentalItems::DisplayItemInfo() {
	std::cout << fmt::format("\nID\t\t\t{}\n", GetID());
	std::cout << fmt::format("Title\t\t\t{}\n", GetTitle());
	std::cout << fmt::format("Rental Type:\t\t{}\n", GetRentalType());
	std::cout << fmt::format("Loan Type\t\t{}\n", GetLoanType());
	std::cout << fmt::format("Copies in stock\t\t{}\n", GetCopiesInStock());
	std::cout << fmt::format("Rental Fee\t\t{}\n", GetRentalFee());

} // void RentalItems:RentFromStock:DisplayItemInfo() {


