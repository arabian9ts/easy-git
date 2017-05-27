//
//  Header.h
//  easy-git
//
//  Created by arabian9ts on 2017/05/23.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#ifndef help_h
#define help_h

namespace help {
    
    std::map<std::string, std::string> help;
    
    enum Commands{
        init = 0,
        add = 1,
        commit = 2,
        reflect = 3,
        branch = 4,
        checkout = 5,
        merge = 6,
        reset = 7,
        log = 8,
    };
    
    const char* command_str[] = {
        "init", "add", "commit", "reflect", "branch", "checkout", "merge", "reset", "log",
    };
    
    const char* help_msg[] = {
        "init cmd places under the management of eat\nformula: eat init\n",
        "add cmd add files or dirs to repo\nformula: eat add file ...",
        "commit cmd saves proj\nformula: eat commit\nAfter this, you will be able to write commit message",
        "reflect cmd does add all and commit\nformula: eat reflect",
        "branch cmd makes another branch\nformula: eat branch <branch_name>",
        "checkout cmd swiches branch to the other\nformula: eat checkout <branch_name>",
        "merge cmd merges branches from specific to base(now)\nformula: eat merge <branch_name>",
        "reset cmd resets workspace status based on specified version\nformula: eat reset <reset_count",
        "log cmd displays commit logs\nformula: eat log <count>",
        
    };
    
    
    void description(Commands command){
        std::cout << help_msg[command] << std::endl;
    }
    

}

#endif /* help_h */
