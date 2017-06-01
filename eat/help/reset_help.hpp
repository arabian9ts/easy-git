//
//  reset_help.hpp
//  easy-git
//
//  Created by arabian9ts on 2017/05/27.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#ifndef reset_help_hpp
#define reset_help_hpp


class _Reset : public Help {
    
public:
    
    _Reset(){}
    
    void description() override {
        std::cout
        << std::endl
        << "-------------- reset help --------------"
        << std::endl
        << std::endl
        << "Formula: eat reset"
        << std::endl
        << "     or: eat reset <N: Integer>"
        << std::endl
        << std::endl
        << "*** reset cmd resets workspace status based on specified version ***"
        << std::endl
        << std::endl
        << "*** N is 0 in default. you can go back to N vers ago. ***"
        << std::endl
        << std::endl
        << "----------------------------------------"
        << std::endl
        << std::endl;
    }
        
};


#endif /* reset_help_hpp */
