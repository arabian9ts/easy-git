//
//  init_help.h
//  easy-git
//
//  Created by arabian9ts on 2017/05/27.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#ifndef init_help_h
#define init_help_h
#include "help.h"

class Init : public Help{
    
public:
    
    Init(){}
    
    void description() override {
        std::cout << "this is add help" << std::endl;
    }
        
};

#endif /* init_help_h */
