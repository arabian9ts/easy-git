//
//  help.hpp
//  easy-git
//
//  Created by arabian9ts on 2017/05/23.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#ifndef help_hpp
#define help_hpp

class Help {

public:
    
    enum commands{
        unknown,
        init,
        add,
        commit,
        reflect,
        branch,
        checkout,
        merge,
        reset,
        log,
        help,
    };
    
    Help(){}
    
    virtual void description() = 0;
    

};

#endif /* help_hpp */
