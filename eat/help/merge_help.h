//
//  merge_help.h
//  easy-git
//
//  Created by arabian9ts on 2017/05/27.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#ifndef merge_help_h
#define merge_help_h


class _Merge : public Help{
    
public:
    
    _Merge(){}
    
    void description() override {
        std::cout << "this is merge help" << std::endl;
    }
        
};

        
#endif /* merge_help_h */
