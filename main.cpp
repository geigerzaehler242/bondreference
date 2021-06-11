//
//  main.cpp
//  sde-test-solution
//
//  Created by fernando marto on 2021-06-11.
//

//#include <iostream>
#include <fstream>
#include "bond.hpp" //#include <iostream>

#include "/usr/local/opt/nlohmann_json/include/nlohmann/json.hpp"


void parseBondInputData(std::string inputFile, std::vector<Bond> &vCorp, std::vector<Bond> &vGov) {
    
    // read a JSON file
    std::ifstream i(inputFile);
    nlohmann::json inputJson;
    i >> inputJson;
    
    //std::cout << inputJson["data"];
    
    for(auto &bond : inputJson["data"]) {
        
        if(bond["type"] == "corporate"
           && bond["id"] != nullptr
           && bond["type"] != nullptr
           && bond["yield"] != nullptr
           && bond["amount_outstanding"] != nullptr) {
            
            std::string yield = bond["yield"];
            yield.erase(remove(yield.begin(), yield.end(), '%'), yield.end()); //remove %
            
            double yieldDouble = stod(yield);
            
            
            std::string tenor = bond["tenor"];
            
            std::string toErase = " years";
            size_t pos = tenor.find(toErase);
            if (pos != std::string::npos)
            {
                tenor.erase(pos, toErase.length()); // If found then erase it from string
            }
            double tenorDouble = stod(tenor);
            
            Bond corpBond = Bond(bond["id"], bond["type"], tenorDouble, yieldDouble, bond["amount_outstanding"]);
            
            vCorp.push_back(corpBond);
        }
        else if (bond["type"] == "government"
            && bond["id"] != nullptr
            && bond["type"] != nullptr
            && bond["yield"] != nullptr
            && bond["amount_outstanding"] != nullptr) {
            
            
            std::string yield = bond["yield"];
            yield.erase(remove(yield.begin(), yield.end(), '%'), yield.end()); //remove %
            
            double yieldDouble = stod(yield);
            
            
            std::string tenor = bond["tenor"];
            
            std::string toErase = " years";
            size_t pos = tenor.find(toErase);
            if (pos != std::string::npos)
            {
                tenor.erase(pos, toErase.length()); // If found then erase it from string
            }
            double tenorDouble = stod(tenor);
            
            Bond govBond = Bond(bond["id"], bond["type"], tenorDouble, yieldDouble, bond["amount_outstanding"]);
            
            vGov.push_back(govBond);
        }
        
    }

    
}


int main(int argc, const char * argv[]) {
    
    std::cout << std::endl;
    std::cout << "Overbond SDE Test \n";
    
    
    std::string inputFile;
    std::string outputFile;
    
    
    if(argc == 3) {
        inputFile = argv[1];
        outputFile = argv[2];
    }
    else {
        std::cout << "input and output filenames are required!" << std::endl;
        inputFile = "/Users/fernando/Developer/sde-test/sample_input.json";
        outputFile = "/Users/fernando/Developer/sde-test/output.json";
    }
    
    
    std::vector<Bond> vCorp;
    std::vector<Bond> vGov;
    
    parseBondInputData(inputFile, vCorp, vGov);
    
    std::sort(vGov.begin(), vGov.end(), std::less<Bond>()); //sort government bonds by increasing term
    std::sort(vCorp.begin(), vCorp.end(), std::less<Bond>()); //sort corporate bonds by increasing term
    
    
    // write prettified JSON to another file
//    std::ofstream o(outputFile);
//    o << std::setw(4) << inputJson << std::endl;
    
    
    
    return 0;
}
