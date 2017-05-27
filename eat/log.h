//
//  log.hpp
//  easy-git
//
//  Created by arabian9ts on 2017/05/22.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#ifndef log_h
#define log_h

#include <stdio.h>
#include "eat.hpp"

struct Log{
    
    /** コミットメッセージ */
    std::string message;
    
    /** コミット日時 */
    std::string date;
    
    /** コミットハッシュ */
    std::string hash;
    
public:
    
    /** 初期化用コンストラクタ */
    Log(std::string hash, std::string date, std::string message){
        this -> hash = hash;
        this -> date = date;
        this -> message = message;
    }
    
    /** コミット履歴表示 */
    void dump(){
        std::cout << "commit : " << hash << std::endl
        << "date : " << date << std::endl
        << "\n    message : " << message
        << std::endl
        << std::endl;
    }
    
};


#endif /* log_h */