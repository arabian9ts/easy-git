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

class Add : public Help{
    
public:
    
    Add(){}
    
    void description(commands command) override {
        std::cout << "this is add help" << std::endl;
    }
    
};


#endif /* add_help_h */
