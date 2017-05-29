//
//  branch_help.h
//  easy-git
//
//  Created by arabian9ts on 2017/05/27.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#ifndef branch_help_h
#define branch_help_h


class _Branch : public Help{
    
public:
    
    _Branch(){}
    
    void description() override {
        std::cout
        << std::endl
        << "------------- branch help --------------"
        << std::endl
        << std::endl
        << "Formula: eat branch <branch_name>"
        << std::endl
        << "     or: eat branch"
        << std::endl
        << std::endl
        << "*** branch cmd makes new working branch ***"
        << std::endl
        << "*** if no args, list-up existing working branches ***"
        << std::endl
        << std::endl
        << "----------------------------------------"
        << std::endl
        << std::endl;
    }
        
};


#endif /* branch_help_h */
