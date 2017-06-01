//
//  commit_help.hpp
//  easy-git
//
//  Created by arabian9ts on 2017/05/27.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#ifndef commit_help_hpp
#define commit_help_hpp


class _Commit : public Help {
    
public:
    
    _Commit(){}
    
    void description() override {
        std::cout
        << std::endl
        << "------------- commit help --------------"
        << std::endl
        << std::endl
        << "Formula: eat commit"
        << std::endl
        << std::endl
        << "*** commit cmd saves project tree structure ***"
        << std::endl
        << "*** then, you will be able to write commit message ***"
        << std::endl
        << std::endl
        << "----------------------------------------"
        << std::endl
        << std::endl;
    }
    
};

        
#endif /* commit_help_hpp */
