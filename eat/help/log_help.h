//
//  log_help.h
//  easy-git
//
//  Created by arabian9ts on 2017/05/27.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#ifndef log_help_h
#define log_help_h


class _Log : public Help{
    
public:
    
    _Log(){}
    
    void description() override {
        std::cout << "this is log help" << std::endl;
    }
        
};

        
#endif /* log_help_h */
