//
//  Bond.cpp
//  sde-test-solution
//
//  Created by fernando marto on 2021-06-11.
//

#include "Bond.hpp"



Bond::Bond(std::string id, std::string type, std::string tenor, std::string yield, double amount_outstanding) : id(id), type(type), tenor(tenor), yield(yield), amount_outstanding(amount_outstanding) {}

Bond::Bond(): id(""), type(""), tenor(""), yield(""), amount_outstanding(0.0) {}

bool Bond::operator < (const Bond& theBond) const {
    return (this->tenor < theBond.tenor);
}

std::string Bond::getBondId() const {
    return this->id;
}

std::string Bond::getBondType() const {
    return this->type;
}

std::string Bond::getBondTenor() const {
    return this->tenor;
}

std::string Bond::getBondYield() const {
    return this->yield;
}

double Bond::getBondAmountOutstanding() const {
    return this->amount_outstanding;
}

void Bond::setBondId(std::string theId) {
    this->id = theId;
}

void Bond::setBondType(std::string theType) {
    this->type = theType;
}

void Bond::setBondTerm(double theTenor) {
    this->tenor = theTenor;
}

void Bond::setBondYield(double theYield) {
    this->yield = theYield;
}

void Bond::setBondAmountOutstanding(double theAmountOutstanding) {
    this->amount_outstanding = theAmountOutstanding;
}
