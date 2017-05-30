//
//  log_help.h
//  easy-git
//
//  Created by arabian9ts on 2017/05/27.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#ifndef log_help_h
#define log_help_h


class _Log : public Help {
    
public:
    
    _Log(){}
    
    void description() override {
        std::cout
        << std::endl
        << "--------------- log help ---------------"
        << std::endl
        << std::endl
        << "Formula: eat log"
        << std::endl
        << "     or: eat log <N: Integer>"
        << std::endl
        << std::endl
        << "*** log cmd displays commit logs ***"
        << std::endl
        << std::endl
        << "----------------------------------------"
        << std::endl
        << std::endl;
    }
        
};

        
#endif /* log_help_h */
