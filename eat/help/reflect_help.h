//
//  reflect_help.h
//  easy-git
//
//  Created by arabian9ts on 2017/05/27.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#ifndef reflect_help_h
#define reflect_help_h


class _Reflect : public Help{
    
public:
    
    _Reflect(){}
    
    void description() override {
        std::cout
        << std::endl
        << "------------- reflect help -------------"
        << std::endl
        << std::endl
        << "Formula: eat reflect"
        << std::endl
        << std::endl
        << "*** reflect cmd adds all files and saves them ***"
        << std::endl
        << "*** then, you will be able to write commit message ***"
        << std::endl
        << std::endl
        << "----------------------------------------"
        << std::endl
        << std::endl;
    }
        
};

        
#endif /* reflect_help_h */
