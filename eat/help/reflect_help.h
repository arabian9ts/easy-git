//
//  reflect_help.h
//  easy-git
//
//  Created by arabian9ts on 2017/05/27.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#ifndef reflect_help_h
#define reflect_help_h


class _Reflect : public Help{
    
public:
    
    _Reflect(){}
    
    void description() override {
        std::cout << "this is reflect help" << std::endl;
    }
        
};

        
#endif /* reflect_help_h */
