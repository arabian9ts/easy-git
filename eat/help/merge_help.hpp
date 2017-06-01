//
//  merge_help.hpp
//  easy-git
//
//  Created by arabian9ts on 2017/05/27.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#ifndef merge_help_hpp
#define merge_help_hpp


class _Merge : public Help {
    
public:
    
    _Merge(){}
    
    void description() override {
        std::cout
        << std::endl
        << "-------------- merge help --------------"
        << std::endl
        << std::endl
        << "Formula: eat merge <branch_name>"
        << std::endl
        << std::endl
        << "*** merge cmd merges branches from specific to base_branch(now) ***"
        << std::endl
        << std::endl
        << "----------------------------------------"
        << std::endl
        << std::endl;
    }
        
};

        
#endif /* merge_help_hpp */
