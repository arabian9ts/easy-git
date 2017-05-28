//
//  reset_help.h
//  easy-git
//
//  Created by arabian9ts on 2017/05/27.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#ifndef reset_help_h
#define reset_help_h


class _Reset : public Help{
    
public:
    
    _Reset(){}
    
    void description() override {
        std::cout << "this is reset help" << std::endl;
    }
        
};


#endif /* reset_help_h */
