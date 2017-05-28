//
//  help_help.h
//  easy-git
//
//  Created by arabian9ts on 2017/05/27.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#ifndef help_help_h
#define help_help_h


class _Help : public Help{
    
public:
    
    _Help(){}
    
    void description() override {
        std::cout << "this is _help help" << std::endl;
    }
        
};


#endif /* help_help_h */
