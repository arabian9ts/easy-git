//
//  Header.h
//  easy-git
//
//  Created by arabian9ts on 2017/05/23.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#ifndef help_h
#define help_h

class Help {
    
    /*
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
     */
public:
    
    enum commands{
        init,
        add,
        commit,
        reflect,
        branch,
        checkout,
        merge,
        reset,
        log,
        help,
    };
    
    Help(){}
    
    virtual void description() = 0;
    

};

#endif /* help_h */
