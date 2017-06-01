//
//  help_help.hpp
//  easy-git
//
//  Created by arabian9ts on 2017/05/27.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#ifndef help_help_hpp
#define help_help_hpp


class _Help : public Help {
    
public:
    
    _Help(){}
    
    void description() override {
        std::cout
        << std::endl
        << "----------------  help -----------------"
        << std::endl
        << std::endl
        << "command...: init     \n"
        << "            add      \n"
        << "            commit   \n"
        << "            reflect  \n"
        << "            log      \n"
        << "            reset    \n"
        << "            merge    \n"
        << "            branch   \n"
        << "            checkout \n"
        << "            help     \n"
        << std::endl
        << "Formula: eat <command>"
        << std::endl
        << std::endl
        << "----------------------------------------"
        << std::endl
        << std::endl;
    }
        
};


#endif /* help_help_hpp */
