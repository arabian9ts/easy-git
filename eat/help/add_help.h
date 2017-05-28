//
//  add_help.h
//  easy-git
//
//  Created by arabian9ts on 2017/05/27.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#ifndef add_help_h
#define add_help_h
#include "help.h"


class _Add : public Help{
    
public:
    
    _Add(){}
    
    void description() override {
        std::cout
        << std::endl
        << "--------------- add help ---------------"
        << std::endl
        << std::endl
        << "Formula: git add <file names ...>"
        <<std::endl
        << "     or: git add ."
        << std::endl
        << std::endl
        << "----------------------------------------"
        << std::endl
        << std::endl;
    }
    
};


#endif /* add_help_h */
