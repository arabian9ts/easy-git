//
//  helper.hpp
//  easy-git
//
//  Created by arabian9ts on 2017/05/28.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#ifndef helper_hpp
#define helper_hpp

#include "init_help.hpp"
#include "add_help.hpp"
#include "commit_help.hpp"
#include "reset_help.hpp"
#include "log_help.hpp"
#include "merge_help.hpp"
#include "branch_help.hpp"
#include "checkout_help.hpp"
#include "merge_help.hpp"
#include "reflect_help.hpp"
#include "help_help.hpp"

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

#endif /* helper_hpp */
