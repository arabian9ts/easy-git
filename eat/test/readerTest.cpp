//
//  readerTest.cpp
//  easy-git
//
//  Created by arabian9ts on 2017/05/07.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#include "readerTest.hpp"


int readerTest(){
    std::string data1=read("read1","",0);
    std::string data2=read("read1","",1);
    
    std::cout << "not skip : " << data1 << std::endl;
    std::cout << "skip : " << data2 << std::endl;
    
    data1=read("read2","",1);
    
    if(data1!=data2){
        std::cout << "skip test ERROR" << std::endl;
        return 1;
    }
    else{
        std::cout << "skip test passed OK" << std::endl;
    }
    
    return 0;
}
