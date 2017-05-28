//
//  checkout_help.h
//  easy-git
//
//  Created by arabian9ts on 2017/05/27.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#ifndef checkout_help_h
#define checkout_help_h


class _Checkout : public Help{
    
public:
    
    _Checkout(){}
    
    void description() override {
        std::cout << "this is checkout help" << std::endl;
    }
        
};

        
#endif /* checkout_help_h */
