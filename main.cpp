//
//  main.cpp
//  sde-test-solution
//
//  Created by fernando marto on 2021-06-11.
//

//#include <iostream>
#include <fstream>
#include "Bond.hpp" //#include <iostream>

#include "/usr/local/opt/nlohmann_json/include/nlohmann/json.hpp"

struct BondBenchmarkSpread {
    std::string corporateBond;
    std::string governmentBond;
    std::string spread;
    
    BondBenchmarkSpread(std::string corporateBond, std::string governmentBond, std::string spread) : corporateBond(corporateBond), governmentBond(governmentBond), spread(spread) {}
};


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


void findBenchmarkSpread(const std::vector<Bond> &vCorp, const std::vector<Bond> &vGov, std::vector<BondBenchmarkSpread> &benchmarkVector) {
    
    for (auto currentCorpBond : vCorp) {
        
        double corpYield = currentCorpBond.getBondYield();
        double corpTerm = currentCorpBond.getBondTenor();
        
        double minYieldSpread = std::numeric_limits<double>::max();
        double minTermSpread = std::numeric_limits<double>::max();
        double maxAmountOutstanding = std::numeric_limits<double>::min();
        Bond benchmarkBond = Bond();
        
        for (auto currentGovBond : vGov) {
            
            double govYield = currentGovBond.getBondYield();
            double govTerm = currentGovBond.getBondTenor();
            double govAmount = currentGovBond.getBondAmountOutstanding();
            
            double termDiff = std::abs(govTerm - corpTerm);
            
            if( termDiff <= minTermSpread) {
                
                if( govAmount > maxAmountOutstanding) {
                    maxAmountOutstanding = govAmount;
                    
                    minTermSpread = termDiff;
                    minYieldSpread = corpYield - govYield;
                    
                    benchmarkBond.setBondId(currentGovBond.getBondId());
                    benchmarkBond.setBondType(currentGovBond.getBondType());
                    benchmarkBond.setBondTerm(currentGovBond.getBondTenor());
                    benchmarkBond.setBondYield(currentGovBond.getBondYield());
                    benchmarkBond.setBondAmountOutstanding(currentGovBond.getBondAmountOutstanding());
                    
                }
            }
        }
        
        int basisPoints = trunc(minYieldSpread * 100);
        
        std::string bpsString =  std::to_string(basisPoints) + " bps";
        
        
        BondBenchmarkSpread benchmarkSpread = BondBenchmarkSpread( currentCorpBond.getBondId(),
            benchmarkBond.getBondId(), bpsString
        );
        
        benchmarkVector.push_back(benchmarkSpread);
    }
    std::cout << std::endl;
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
    
    if(vCorp.size() && vGov.size() == 0) {
        std::cout << "cannot find any corp or gov bonds in input file" << std::endl;
        return 0;
    }
    
    std::sort(vGov.begin(), vGov.end(), std::less<Bond>()); //sort government bonds by increasing term
    std::sort(vCorp.begin(), vCorp.end(), std::less<Bond>()); //sort corporate bonds by increasing term
    
    
    
    std::vector<BondBenchmarkSpread> benchmarkSpreadVector;
    findBenchmarkSpread(vCorp, vGov, benchmarkSpreadVector);
    
    if(benchmarkSpreadVector.size() == 0) {
        std::cout << "cannot find any benchmark bonds" << std::endl;
        return 0;
    }
    
    nlohmann::json outputJson;
    
    nlohmann::json j;
    nlohmann::json jsonArray = nlohmann::json::array();
    
    
    for(auto bondSpread : benchmarkSpreadVector) {
        
        j = { {"corporate_bond_id", bondSpread.corporateBond}, {"government_bond_id", bondSpread.governmentBond}, {"spread_to_benchmark", bondSpread.spread} };
        
        jsonArray.push_back(j);
        
    }
    
    outputJson["data"] = jsonArray;
    
    std::cout << outputJson["data"];
    
    // write JSON to another file
    std::ofstream o(outputFile);
    o << std::setw(4) << outputJson << std::endl;
    
    
    
    return 0;
}
