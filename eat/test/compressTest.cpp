//
//  compressTest.cpp
//  easy-git
//
//  Created by arabian9ts on 2017/06/05.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#include "compressTest.hpp"


void compressTest(){
    std::cout << "\n---------- COMPRESS TEST ----------" << std::endl;
    
    std::string orig = "aiueo";
    std::string comped;
    std::string decomped;
    
    std::cout << "original string: " << orig << std::endl;
    
    comped = cmp::compress(orig);
    std::cout << "compressed string: " << comped << std::endl;
    
    decomped = cmp::decompress(comped);
    std::cout << "decompressed string: " << decomped << std::endl;
    
    if(decomped == orig){
        std::cout << "OK: compress test passed" << std::endl;
    }
    else{
        std::cerr << "ERROR: compress failed" << std::endl;
    }
    
    std::cout << "---------- COMPRESS TEST END ----------\n" << std::endl;
    
}
