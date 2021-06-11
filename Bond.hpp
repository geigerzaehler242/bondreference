//
//  Bond.hpp
//  sde-test-solution
//
//  Created by fernando marto on 2021-06-11.
//

#ifndef Bond_hpp
#define Bond_hpp

#include <stdio.h>

#include <iostream>


class Bond {

public:

    
    Bond(std::string id, std::string type, std::string tenor, std::string yield, double amount_outstanding);
    
    Bond();
    
    bool operator < (const Bond& theBond) const;
    
    std::string getBondId() const;
    
    std::string getBondType() const;
    
    std::string getBondTenor() const;
    
    std::string getBondYield() const;
    
    double getBondAmountOutstanding() const;
    
    void setBondId(std::string theId);
    
    void setBondType(std::string theType);
    
    void setBondTerm(double theTenor);
    
    void setBondYield(double theYield);
    
    void setBondAmountOutstanding(double theAmountOutstanding);


private:

    std::string id;
    std::string type;
    std::string tenor;
    std::string yield;
    double amount_outstanding;
    
}; //Bond


//        "id": "c1",
//        "type": "corporate",
//        "tenor": "10.3 years",
//        "yield": "5.30%",
//        "amount_outstanding": 1200000


#endif /* Bond_hpp */
