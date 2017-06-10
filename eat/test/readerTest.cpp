//
//  readerTest.cpp
//  easy-git
//
//  Created by arabian9ts on 2017/05/07.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#include "readerTest.hpp"

/**
 * read()関数のテスト
 */
void readerTest(){
    std::cout << "\n---------- READER TEST ----------" << std::endl;
    
    std::string data1 = util::read("read1", "", 0);
    std::string data2 = util::read("read1", "", 1);
    
    std::cout << "not skip : " << data1 << std::endl;
    std::cout << "skip : " << data2 << std::endl;
    
    data1 = util::read("read2", "", 1);
    
    if(data1 != data2){
        std::cerr << "skip test ERROR" << std::endl;
    }
    else{
        std::cout << "skip test passed OK" << std::endl;
    }
    
    std::cout << "---------- READER TEST END ----------\n" << std::endl;
    
}
