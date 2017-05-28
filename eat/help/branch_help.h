//
//  branch_help.h
//  easy-git
//
//  Created by arabian9ts on 2017/05/27.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#ifndef branch_help_h
#define branch_help_h


class _Branch : public Help{
    
public:
    
    _Branch(){}
    
    void description() override {
        std::cout << "this is branch help" << std::endl;
    }
        
};


#endif /* branch_help_h */
