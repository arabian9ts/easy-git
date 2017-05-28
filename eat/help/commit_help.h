//
//  commit_help.h
//  easy-git
//
//  Created by arabian9ts on 2017/05/27.
//  Copyright © 2017年 arabian9ts. All rights reserved.
//

#ifndef commit_help_h
#define commit_help_h


class _Commit : public Help{
    
public:
    
    _Commit(){}
    
    void description() override {
        std::cout << "this is commit help" << std::endl;
    }
    
};

        
#endif /* commit_help_h */
