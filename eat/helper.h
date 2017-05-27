//
//  helper.h
//  easy-git
//
//  Created by arabian9ts on 2017/05/28.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#ifndef helper_h
#define helper_h

#include "init_help.h"
#include "add_help.h"
#include "commit_help.h"
#include "reset_help.h"
#include "log_help.h"
#include "merge_help.h"
#include "branch_help.h"
#include "merge_help.h"
#include "reflect_help.h"
#include "help_help.h"

class Helper {
    
private:
    
    Help* policy;
    std::map<std::string, std::string> helper;
    
    const char* command_str[10] = {
        "init", "add", "commit", "reflect", "branch", "checkout", "merge", "reset", "log", "help",
    };
    
public:
    
    Helper(){
        this -> policy = new Add();
        std::cout << "helper constructor" << std::endl;
    }
    
    void describe(){
        this -> policy -> description(Help::commands::add);
    }
    
    ~Helper(){
        delete this -> policy;
    }
    
};

#endif /* helper_h */
