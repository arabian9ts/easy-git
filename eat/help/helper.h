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
    std::map<std::string, Help::commands> helper;
    
public:
    
    Helper(){
        helper.insert(std::pair<std::string,Help::commands>
                      ("init", Help::commands::init));
        helper.insert(std::pair<std::string,Help::commands>
                      ("add", Help::commands::add));
        helper.insert(std::pair<std::string,Help::commands>
                      ("commit", Help::commands::commit));
        helper.insert(std::pair<std::string,Help::commands>
                      ("reflect", Help::commands::reflect));
        helper.insert(std::pair<std::string,Help::commands>
                      ("merge", Help::commands::merge));
        helper.insert(std::pair<std::string,Help::commands>
                      ("log", Help::commands::log));
        helper.insert(std::pair<std::string,Help::commands>
                      ("reset", Help::commands::reset));
        helper.insert(std::pair<std::string,Help::commands>
                      ("branch", Help::commands::branch));
        helper.insert(std::pair<std::string,Help::commands>
                      ("checkout", Help::commands::checkout));
        helper.insert(std::pair<std::string,Help::commands>
                      ("help", Help::commands::help));


        std::cout << "helper constructor" << std::endl;
    }
    
    void describe(std::string cmd_str){
        Help::commands command = helper[cmd_str];
        
        std::cout << command << std::endl;
        
        std::cout << command << std::endl;
        
        switch (command) {
            case Help::commands::init:
                this -> policy = new _Init();
                break;
            case Help::commands::add:
                this -> policy = new _Add();
                break;
            case Help::commands::commit:
                this -> policy = new _Commit();
                break;
            case Help::commands::reflect:
                this -> policy = new _Reflect();
                break;
            case Help::commands::branch:
                this -> policy = new _Branch();
                break;
            case Help::commands::checkout:
                this -> policy = new _Checkout();
                break;
            case Help::commands::merge:
                this -> policy = new _Merge();
                break;
            case Help::commands::log:
                this -> policy = new _Log();
                break;
            default:
                this -> policy = new _Help();
                break;
        }
        this -> policy -> description();
    }
    
    ~Helper(){
        delete this -> policy;
    }
    
};

#endif /* helper_h */
