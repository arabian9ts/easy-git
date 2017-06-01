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
#include "checkout_help.h"
#include "merge_help.h"
#include "reflect_help.h"
#include "help_help.h"

class Helper {
    
private:
    
    Help* policy;
    std::map<std::string, Help*> helper;
    
public:
    
    Helper(){
        helper.insert(std::pair<std::string,Help*>
                      ("init", new _Init()));
        helper.insert(std::pair<std::string,Help*>
                      ("add", new _Add()));
        helper.insert(std::pair<std::string,Help*>
                      ("commit", new _Commit()));
        helper.insert(std::pair<std::string,Help*>
                      ("reflect", new _Reflect()));
        helper.insert(std::pair<std::string,Help*>
                      ("merge", new _Merge()));
        helper.insert(std::pair<std::string,Help*>
                      ("log", new _Log()));
        helper.insert(std::pair<std::string,Help*>
                      ("reset", new _Reset()));
        helper.insert(std::pair<std::string,Help*>
                      ("branch", new _Branch()));
        helper.insert(std::pair<std::string,Help*>
                      ("checkout", new _Checkout()));
        helper.insert(std::pair<std::string,Help*>
                      ("help", new _Help()));
    }
    
    void describe(std::string cmd_str){
        this -> policy = helper[cmd_str];
        this -> policy -> description();
    }
    
    ~Helper(){
        for(std::map<std::string, Help*>::iterator v = this -> helper.begin(); v != this -> helper.end(); v++)
            delete v -> second;
    }
    
};

#endif /* helper_h */
