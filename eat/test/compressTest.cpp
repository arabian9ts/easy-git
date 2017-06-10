//
//  compressTest.cpp
//  easy-git
//
//  Created by arabian9ts on 2017/06/05.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#include "compressTest.hpp"


void compressTest(){
    std::cout << "---------- COMPRESS TEST ----------" << std::endl;
    
    std::string orig = "aiueo";
    std::string comped;
    std::string decomped;
    
    comped = cmp::compress(orig);
    std::cout << comped << std::endl;
    
    decomped = cmp::decompress(comped);
    std::cout << decomped << std::endl;
    
    if(decomped == orig){
        std::cout << "OK: compress test passed" << std::endl;
    }
    else{
        std::cerr << "ERROR: compress failed" << std::endl;
    }
    
    std::cout << "---------- COMPRESS TEST END ----------" << std::endl;
    
}
