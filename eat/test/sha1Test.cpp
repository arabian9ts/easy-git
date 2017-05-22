//
//  sha1Test.cpp
//  eat
//
//  Created by arabian9ts on 2017/04/16.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#include "sha1Test.hpp"

/**
 * sha1ハッシュのテスト
 */
int sha1Test(){
    std::string testArray[] = {"abc","1243err33",":;ads"};
    std::string expected[] = {"a9993e364706816aba3e25717850c26c9cd0d89d",
        "4db093b7f24779a6c06d98f1e2a88ab66817b968",
        "d40f43b7b1e40408d61a0fa73c79dfb4162b4789"};
    
    std::string result;

    for(int i = 0; i < sizeof(testArray)/sizeof(testArray[0]); i++){
        result = hash::sha1(testArray[i]);
        std::cout << "TEST : " << testArray[i] << std::endl;
        if(result == expected[i]){
            std::cout << "OK : " << testArray[i] << " -> " << result << std::endl;
        }
        else{
            std::cout << "ERROR : \n" << result << " should be -> " << std::endl << expected[i] << std::endl;
        }
    }
    return 0;
}
