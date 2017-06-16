//
//  log.hpp
//  easy-git
//
//  Created by arabian9ts on 2017/05/22.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#ifndef log_hpp
#define log_hpp

#include <stdio.h>
#include "eat.hpp"
#include "color.hpp"

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
        Clout(Color::pallet::yellow)
        << "commit: " << hash << std::endl;
        std::cout
        << "  date: " << date << std::endl
        << "\n    message: " << message
        << std::endl
        << std::endl;
    }
    
};


#endif /* log_hpp */
