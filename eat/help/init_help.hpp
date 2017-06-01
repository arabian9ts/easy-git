//
//  init_help.hpp
//  easy-git
//
//  Created by arabian9ts on 2017/05/27.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#ifndef init_help_hpp
#define init_help_hpp
#include "help.hpp"


class _Init : public Help {
    
public:
    
    _Init(){}
    
    void description() override {
        std::cout
        << std::endl
        << "--------------- init help --------------"
        << std::endl
        << std::endl
        << "Formula: eat init"
        << std::endl
        << std::endl
        << "*** init cmd places under the management of eat system ***"
        << std::endl
        << std::endl
        << "----------------------------------------"
        << std::endl
        << std::endl;
    }
        
};


#endif /* init_help_hpp */
